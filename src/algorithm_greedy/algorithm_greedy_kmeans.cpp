/**
 * Receives clients and services, applies kmeans by a loop of assign-recalculate
 *    service until no reassignments have taken place.
 * 
 * NOTE: When a cluster results empty, it's service is moved to a random client
 *  location.
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
    ptrHeuristic_(new HeuristicKMeansLeast()) {
  
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
    ptrHeuristic_(new HeuristicKMeansLeast()) {}

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
      pointsService_[i] = pointsClient_[generateRandomIndexList(1).back()];
    }
  }
}

void AlgorithmGreedyKMeans::print() {
  std::cout << "Amount of clusters: " << k_ << std::endl;
  for (int i = 0; i < pointsService_.size(); ++i) {
    std::cout << "Cluster " << i << ", ";
    pointsService_[i].print();
    std::cout << ": ";
    for (int j = 0; j < pointsClient_.size(); ++j) {
      if (pointsClient_[j].getCluster() == i) {
        pointsClient_[j].print();
      }
    }
    std::cout << std::endl;
  }
}

float AlgorithmGreedyKMeans::objectiveFunction() {
  return ObjectiveFunctionSSE().get(pointsClient_, pointsService_);
}

std::vector<int> AlgorithmGreedyKMeans::generateRandomIndexList(int size) {
  std::vector<int> set;

  srand(time(NULL));
  int randomIndex = rand() % pointsClient_.size();
  set.push_back(randomIndex);

  for (int i = 0; i < size - 1; ++i) {
    while (std::find(set.begin(), set.end(), randomIndex) !=
        set.end()) {

      srand(time(NULL));
      randomIndex = rand() % pointsClient_.size();
    }

    set.push_back(randomIndex);
  }

  return set;
}
