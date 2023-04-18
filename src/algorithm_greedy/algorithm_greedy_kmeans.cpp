/**
 * Receives clients and services, applies kmeans by a loop of assign-recalculate
 *    service until no reassignments have taken place.
 * 
 * NOTE: When a cluster results empty, it is deleted.
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
    amountOfReassignedPoints_(pointsClient.size()), // to execute first iteration
    ptrHeuristic_(new HeuristicKMeansLeast()), // choose closest centroid
    executionIterationNumber_(0),
    sse_(0) {
  
  // Convert basic point to cluster point
  for (auto& point : pointsClient) {
    pointsClient_.push_back(PointCluster(point));
  }
  for (auto& point : pointsService) {
    pointsService_.push_back(PointCluster(point));
  }
}

// if points are already cluster points
AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) :
    currentID_(++ID),
    amountOfReassignedPoints_(pointsClient.size()),
    ptrHeuristic_(new HeuristicKMeansLeast()),
    executionIterationNumber_(0),
    sse_(0) {
  // Same logic but for point clusters. Cannot have pointclusters already assigned
  // because the kmeans algorithm will fail.

  // reset cluster points
  for (auto& point : pointsClient) {
    pointsClient_.push_back(PointCluster(point.getComponents()));
  }
  for (auto& point : pointsService) {
    pointsService_.push_back(PointCluster(point.getComponents()));
  }
}

AlgorithmGreedyKMeans::~AlgorithmGreedyKMeans() {}

// ************ getters and setters

void AlgorithmGreedyKMeans::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

std::vector<PointCluster> AlgorithmGreedyKMeans::getServices() {
  return pointsService_;
}

std::vector<PointCluster> AlgorithmGreedyKMeans::getClients() {
  return pointsClient_;
}

// ************ framework methods

// constructor sets it, so not needed.
void AlgorithmGreedyKMeans::preprocess() {}

bool AlgorithmGreedyKMeans::hasCandidates() {
  return !pointsClient_.empty();
}

bool AlgorithmGreedyKMeans::isAtSolution() {
  return amountOfReassignedPoints_ == 0;
}

// Assign points to centroid
void AlgorithmGreedyKMeans::selectBestCandidate() {
  amountOfReassignedPoints_ = 0;

  for (auto& point : pointsClient_) {
    // choose() needs vector
    std::vector<PointCluster> singlePointVector;
    singlePointVector.push_back(point);

    const int kClosestClusterIndex = ptrHeuristic_->choose(singlePointVector,
        pointsService_);

    if (pointsService_[kClosestClusterIndex].getComponents() != point.getCluster().getComponents()) {
      ++amountOfReassignedPoints_;
    }

    point.setCluster(pointsService_[kClosestClusterIndex].getBasic());
  }
  sse_ = objectiveFunction();
}

// Doesnt matter, always true.
bool AlgorithmGreedyKMeans::validCandidate() {
  ++executionIterationNumber_;
  return true;
}

// average centroid recalculus by client average
void AlgorithmGreedyKMeans::addCandidate() {
  for (int i = pointsService_.size() - 1; i >= 0; --i) {

    // auxiliary components, set to 0 floats, ignore strings
    auto componentsAverage = pointsService_[i].getComponents();
    for (auto& component : componentsAverage) {
      if (std::holds_alternative<float>(component)) {
        component = 0;
      }
    }

    int amountOfPointsOnCluster = 0;
    // average = total/(nº elements), total is calculated here
    for (auto& point : pointsClient_) {
      if (point.getCluster().getComponents() == pointsService_[i].getComponents()) {

        // add to auxiliary components
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

    // substitute centroid or delete if empty
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
      pointsService_.erase(pointsService_.begin() + i);
    }
  }
}

void AlgorithmGreedyKMeans::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << pointsClient_.size() << "\t\t";
  std::cout << pointsService_.size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << sse_ << "\t\t";
  std::cout << "..." << "\t\t";
}

float AlgorithmGreedyKMeans::getSSE() {
  return sse_;
}

float AlgorithmGreedyKMeans::objectiveFunction() {
  return ObjectiveFunctionSSE().get(pointsClient_, pointsService_, 8);
}
