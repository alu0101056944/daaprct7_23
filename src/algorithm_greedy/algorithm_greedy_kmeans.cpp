#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"
#include "../../include/similarity/similarity_euclidean.h"

int AlgorithmGreedyKMeans::ID = 0;

AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointBasic> points,
    int k, float deltaSSE) :
    k_(k),
    deltaSSE_(deltaSSE),
    ptrHeuristic_(new HeuristicKMeansMax()),
    sse_(900),
    ssePrevious_(999),
    indexOfFarthest_(-1),
    executionIterationNumber_(0),
    currentID_(++ID) {

  assert(k_ >= 2);
  assert(points.size() >= k);

  for (auto& point : points) {
    assert(point.getComponents().size() == points.back().getComponents().size());
    pointsClient_.push_back(PointCluster(point));
  }
  pointsCandidate_ = pointsClient_;
}

AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointBasic> points,
  float deltaSSE) :
    k_(points.size() * 0.1),
    deltaSSE_(deltaSSE),
    ptrHeuristic_(new HeuristicKMeansMax()),
    sse_(0),
    ssePrevious_(0),
    indexOfFarthest_(-1),
    executionIterationNumber_(0),
    currentID_(++ID) {

  assert(k_ >= 2);
  assert(points.size() >= k_);

  for (auto& point : points) {
    assert(point.getComponents().size() == points.back().getComponents().size());
    pointsClient_.push_back(PointCluster(point));
  }
  pointsCandidate_ = pointsClient_;
}

AlgorithmGreedyKMeans::~AlgorithmGreedyKMeans() {}

void AlgorithmGreedyKMeans::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

void AlgorithmGreedyKMeans::preprocess() {
  for (int i = 0; i < k_; ++i) {
    selectBestCandidate();
  }
}

bool AlgorithmGreedyKMeans::hasCandidates() {
  return pointsService_.size() < pointsClient_.size();
}

bool AlgorithmGreedyKMeans::isAtSolution() {
  return std::abs(ssePrevious_ - sse_) < deltaSSE_;
}

void AlgorithmGreedyKMeans::selectBestCandidate() {
  // PointCluster to std::shared_ptr<IPoint> for choose()
  std::vector<std::shared_ptr<IPoint>> candidates;
  for (int j = 0; j < pointsCandidate_.size(); j++) {
    candidates.push_back(std::make_shared<PointCluster>(pointsCandidate_[j]));
  }

  // PointCluster to std::shared_ptr<IPoint> for choose()
  std::vector<std::shared_ptr<IPoint>> services;
  for (int j = 0; j < pointsService_.size(); j++) {
    services.push_back(std::make_shared<PointCluster>(pointsService_[j]));
  }

  indexOfFarthest_ = ptrHeuristic_->choose(candidates, services);
  pointsCandidate_.erase(pointsCandidate_.begin() + indexOfFarthest_);
}

bool AlgorithmGreedyKMeans::validCandidate() {
  ++executionIterationNumber_;
  bool similarPointPresentAsService = false;
  for (int i = 0; i < pointsService_.size(); ++i) {
    auto componentsCandidate = pointsClient_[indexOfFarthest_].getComponents();
    auto componentsService = pointsService_[i].getComponents();

    if (componentsCandidate == componentsService) {
      similarPointPresentAsService = true;
    }
  }
  return !similarPointPresentAsService;
}

// execute kmeans algorithm with current services
void AlgorithmGreedyKMeans::addCandidate() {
  pointsService_.push_back(pointsClient_[indexOfFarthest_]);
  pointsCandidate_ = pointsClient_;

  applyKMeans();
  
  ssePrevious_ = sse_;
  sse_ = objectiveFunction();
}

void AlgorithmGreedyKMeans::applyKMeans() {
  SimilarityEuclidean euclidean;
  int amountOfReassigned = pointsClient_.size();
  while(amountOfReassigned > 0) {
    amountOfReassigned = 0;

    // assign clients to services
    for (int i = 0; i < pointsClient_.size(); ++i) {
      auto ptrPoint = std::make_shared<PointCluster>(pointsClient_[i]);
      float minimumDistance = -1;
      int indexCluster;
      for (int j = 0; j < pointsService_.size(); ++j) {
        auto ptrService = std::make_shared<PointCluster>(pointsService_[j]);
        float distance = euclidean.similarity(ptrPoint, ptrService);
        if (minimumDistance == -1 || distance < minimumDistance) {
          indexCluster = j;
          minimumDistance = distance;
        }
      }
      if (pointsClient_[i].getCluster() != indexCluster) {
        ++amountOfReassigned;
      }
      pointsClient_[i].setCluster(indexCluster);
    }

    // Recalculate service points
    for (int i = 0; i < pointsService_.size(); ++i) {
      // get components layout. set numerics to 0, nominals left as is
      auto componentsAverage = pointsService_[i].getComponents();
      for (auto& component : componentsAverage) {
        if (std::holds_alternative<float>(component)) {
          component = 0;
        }
      }

      int amountOfPointsOnCluster = 0;

      // calculate the numerator of the average mathematical operation
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
        // apply denominator division of the average mathematical operation
        for (int j = 0; j < componentsAverage.size(); ++j) {
          if (std::holds_alternative<float>(componentsAverage[j])) {
            componentsAverage[j] = std::get<float>(componentsAverage[j]) /
                amountOfPointsOnCluster;
          }
        }
        pointsService_[i] = PointCluster(componentsAverage);
      } else {
        pointsService_[i] = pointsClient_[generateRandomIndex(1).back()];
      }
    }
  }
}


// calculate sse
float AlgorithmGreedyKMeans::objectiveFunction() {
  SimilarityEuclidean euclidean;
  float total = 0;
  for (int i = 0; i < pointsService_.size(); ++i) {
    auto ptrService = std::make_shared<PointCluster>(pointsService_[i]);
    float clusterTotal = 0;
    for (auto& point : pointsClient_) {
      if (point.getCluster() == i) {
        auto ptrPoint = std::make_shared<PointCluster>(point);
        clusterTotal += euclidean.similarity(ptrService, ptrPoint);
      }
    }
    total += clusterTotal;
  }
  return total;
}

void AlgorithmGreedyKMeans::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << pointsClient_.size() << "\t\t";
  std::cout << pointsService_.size() << "\t\t\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << sse_ << "\t\t";
}

std::vector<int> AlgorithmGreedyKMeans::generateRandomIndex(int size) {
  std::vector<int> previous;

  srand(time(NULL));
  int randomIndex = rand() % pointsClient_.size();
  previous.push_back(randomIndex);

  for (int i = 0; i < size - 1; ++i) {
    while (std::find(previous.begin(), previous.end(), randomIndex) !=
        previous.end()) {
      srand(time(NULL));
      randomIndex = rand() % pointsClient_.size();
    }
    previous.push_back(randomIndex);
  }
  return previous;
}