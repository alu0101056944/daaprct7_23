/**
 * Receives clients and services, applies kmeans by a loop of assign-recalculate
 *    service until no reassignments have taken place.
 * 
 * NOTE: When a cluster results empty, it's service is moved to a random client
 *  location.
 * NOTE: Because a client point can have a service point on top, I make sure
 *    that when pointsClient.size() == pointsService.size() then the service
 *    points stay as they are and are not recalculated.
*/

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cassert>

#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_least.h"
#include "../../include/objective_function_sse.h"

int AlgorithmGreedyKMeans::ID = 0;

AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointBasic> pointsClient,
      std::vector<PointBasic> pointsService) :
    currentID_(++ID),
    amountOfReassignedPoints_(pointsClient.size()),
    ptrHeuristic_(new HeuristicKMeansLeast()),
    executionIterationNumber_(0) {
  
  for (auto& point : pointsClient) {
    pointsClient_.push_back(PointCluster(point));
  }

  for (auto& point : pointsService) {
    pointsService_.push_back(PointCluster(point));
  }
}

AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) :
    pointsClient_(pointsClient),
    pointsService_(pointsService),
    currentID_(++ID),
    amountOfReassignedPoints_(pointsClient.size()),
    ptrHeuristic_(new HeuristicKMeansLeast()),
    executionIterationNumber_(0) {}

AlgorithmGreedyKMeans::~AlgorithmGreedyKMeans() {}

void AlgorithmGreedyKMeans::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

std::vector<PointCluster> AlgorithmGreedyKMeans::getServices() {
  return pointsService_;
}

std::vector<PointCluster> AlgorithmGreedyKMeans::getClients() {
  return pointsClient_;
}

// No preprocessing needed because all points are set on constructor
void AlgorithmGreedyKMeans::preprocess() {}

// Because if there are no clients then there is nothing to do
bool AlgorithmGreedyKMeans::hasCandidates() {
  return !pointsClient_.empty();
}

bool AlgorithmGreedyKMeans::isAtSolution() {
  return amountOfReassignedPoints_ == 0;
}

void AlgorithmGreedyKMeans::selectBestCandidate() {
  amountOfReassignedPoints_ = 0;

  for (auto& point : pointsClient_) {
    std::vector<PointCluster> singlePointVector; // for IHeuristic.choose()
    singlePointVector.push_back(point);
    const int kClosestClusterIndex = ptrHeuristic_->choose(singlePointVector,
        pointsService_);

    if (kClosestClusterIndex != point.getCluster()) {
      ++amountOfReassignedPoints_;
    }

    point.setCluster(kClosestClusterIndex);
  }
}

// Always true because I need addCandidate() to always be called
bool AlgorithmGreedyKMeans::validCandidate() {
  ++executionIterationNumber_;
  return true;
}

// recalculate service points based on the client average
void AlgorithmGreedyKMeans::addCandidate() {
  for (int i = 0; i < pointsService_.size(); ++i) {

    // initialize components to 0, nominals left the same
    auto componentsAverage = pointsService_[i].getComponents();
    for (auto& component : componentsAverage) {
      if (std::holds_alternative<float>(component)) {
        component = 0;
      }
    }

    int amountOfPointsOnCluster = 0;
    // average = total/(nº elements), total is calculated here
    for (auto& point : pointsClient_) {
      if (point.getCluster() == i) {
        auto components = point.getComponents();
        for (int j = 0; j < components.size(); ++j) {

          if (std::holds_alternative<float>(components[j])) {
            componentsAverage[j] = std::get<float>(componentsAverage[j]) +
                std::get<float>(components[j]);
          }
        }

        ++amountOfPointsOnCluster;
      }
    }

    if (amountOfPointsOnCluster > 0) {
      // average = total/(nº elements), average is calculated here
      for (int j = 0; j < componentsAverage.size(); ++j) {
        if (std::holds_alternative<float>(componentsAverage[j])) {
          componentsAverage[j] = std::get<float>(componentsAverage[j]) /
              amountOfPointsOnCluster;
        }
      }

      pointsService_[i] = PointCluster(componentsAverage);
    } else {
      // when pointsService.size() == pointsClient.size() I dont want it to
      // choose a point that has a service point on top
      auto otherNonServices = getSetOfRandomNonServicePoints(1);
      if (!otherNonServices.empty()) {
        pointsService_[i] = pointsClient_[otherNonServices.back()];
      }
    }
  }
}

void AlgorithmGreedyKMeans::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << pointsClient_.size() << "\t\t";
  std::cout << pointsService_.size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << objectiveFunction() << "\t\t";
  std::cout << "..." << "\t\t";
}

float AlgorithmGreedyKMeans::objectiveFunction() {
  return ObjectiveFunctionSSE().get(pointsClient_, pointsService_);
}

std::vector<int> AlgorithmGreedyKMeans::getSetOfRandomNonServicePoints(int size) {

  // calculate list of client points that are not service points
  std::vector<PointCluster> nonServicePoints;
  for (int i = 0; i < pointsClient_.size(); ++i) {
    auto componentsClient = pointsClient_[i].getComponents();
    bool isService = false;

    for (int j = 0; j < pointsService_.size(); ++j) {
      auto componentsService = pointsService_[j].getComponents();
      
      if (componentsClient == componentsService) {
        isService = true;
      }
    }

    if (!isService) {
      nonServicePoints.push_back(pointsClient_[i]);
    }
  }

  std::vector<int> set;

  if (nonServicePoints.empty()) { // to signal that all clients have a service ontop
    return set;
  }

  srand(time(NULL));
  int randomIndex = rand() % nonServicePoints.size();
  set.push_back(randomIndex);

  for (int i = 0; i < size - 1; ++i) {
    while (std::find(set.begin(), set.end(), randomIndex) !=
        set.end()) {

      srand(time(NULL));
      randomIndex = rand() % nonServicePoints.size();
    }

    set.push_back(randomIndex);
  }

  return set;
}
