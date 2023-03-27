#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cassert>

#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_least.h"

AlgorithmGreedyKMeans::AlgorithmGreedyKMeans(std::vector<PointBasic> points,
    int k) : k_(k), amountOfReassignedPoints_(0),
    ptrHeuristic_(new HeuristicKMeansLeast()) {

  assert(points.size() >= k);

  for (auto& point : points) {
    assert(point.getComponents().size() == points.back().getComponents().size());
    pointsClient_.push_back(PointCluster(point));
  }
}

AlgorithmGreedyKMeans::~AlgorithmGreedyKMeans() {}

void AlgorithmGreedyKMeans::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

/**
 * Use randomly generated index that hasn't been already generated before to
 *  access and insert a copy of a point as point of service.
 */
void AlgorithmGreedyKMeans::preprocess() {
  std::vector<int> randomIndex = generateRandomIndex(k_);
  for (int i = 0; i < k_; ++i) {
    int index = randomIndex[i];
    pointsService_.push_back(pointsClient_[index]);
  }
}

// Because the algorithm simply iterates all client points to search
// the closest service point to it and to reassign it, so amount
// of candidates is irrelevant.
bool AlgorithmGreedyKMeans::hasCandidates() {
  return true;
}

bool AlgorithmGreedyKMeans::isAtSolution() {
  return amountOfReassignedPoints_ == 0;
}

void AlgorithmGreedyKMeans::selectBestCandidate() {
  amountOfReassignedPoints_ = 0;

  for (auto& point : pointsClient_) {

    // vector<IPoint> to vector<shared_ptr> for heuristic->choose()
    std::vector<std::shared_ptr<IPoint>> available;
    for (int j = 0; j < pointsService_.size(); ++j) {
      available.push_back(std::shared_ptr<PointCluster>(&(point)));
    }

    int closestClusterIndex = ptrHeuristic_->choose(
      std::shared_ptr<PointCluster>(&(point)), available);

    if (closestClusterIndex != point.getCluster()) {
      ++amountOfReassignedPoints_;
    }

    point.setCluster(closestClusterIndex);
  }
}

// Because on this algorithm there is no such thing as candidate, the greedy
// part is simply choosing the cluster as the one of the service point
// that is closer in distance to the client point.
bool AlgorithmGreedyKMeans::validCandidate() {
  return true;
}

// Recalculate clusters instead.
void AlgorithmGreedyKMeans::addCandidate() {
  for (int i = 0; i < pointsService_.size(); ++i) {

    // initialize components to 0, nominals left as is
    auto componentsAverage = pointsService_[i].getComponents();
    for (auto& component : componentsAverage) {
      if (std::holds_alternative<float>(component)) {
        component = 0;
      }
    }

    // add partial average to componentsAverage
    for (auto& point : pointsClient_) {
      if (point.getCluster() == i) {
        for (auto& component : point.getComponents()) {

          if (std::holds_alternative<float>(component)) {
            componentsAverage[i] = std::get<float>(componentsAverage[i]) +
                (std::get<float>(component) / pointsClient_.size());
          }
        }
      }
    }

    pointsService_[i] = PointCluster(componentsAverage);
  }
}

void AlgorithmGreedyKMeans::print() {
  for (int i = 0; i < pointsService_.size(); ++i) {
    
  }
}

std::vector<int> AlgorithmGreedyKMeans::generateRandomIndex(int size) {
  std::vector<int> previous;

  srand(time(NULL));
  int randomIndex = rand() % pointsClient_.size();
  previous.push_back(randomIndex);

  for (int i = 0; i < size; ++i) {

    while (std::find(previous.begin(), previous.end(), randomIndex) !=
        previous.end()) {

      srand(time(NULL));
      randomIndex = rand() % pointsClient_.size();
    }

    previous.push_back(randomIndex);
  }

  return previous;
}