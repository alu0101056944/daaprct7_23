#include "../../include/algorithm_greedy/algorithm_greedy_clusters.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"
#include "../../include/similarity/similarity_euclidean.h"

int AlgorithmGreedyClusters::ID = 0;

AlgorithmGreedyClusters::AlgorithmGreedyClusters(std::vector<PointBasic> points,
    int k) :
    k_(k),
    ptrHeuristic_(new HeuristicKMeansMax()),
    sse_(-1),
    indexOfFarthest_(-1),
    executionIterationNumber_(0),
    currentID_(++ID),
    pointFarthest_(points.back()) {

  assert(k_ >= 2);
  assert(points.size() >= k);

  for (auto& point : points) {
    assert(point.getComponents().size() == points.back().getComponents().size());
    pointsClient_.push_back(PointCluster(point));
  }
  pointsCandidate_ = pointsClient_;
}

AlgorithmGreedyClusters::AlgorithmGreedyClusters(std::vector<PointBasic> points) :
    k_(points.size() * 0.1),
    ptrHeuristic_(new HeuristicKMeansMax()),
    sse_(-1),
    indexOfFarthest_(-1),
    executionIterationNumber_(0),
    currentID_(++ID),
    pointFarthest_(points.back()) {
  assert(k_ >= 2);
  assert(points.size() >= k_);

  for (auto& point : points) {
    assert(point.getComponents().size() == points.back().getComponents().size());
    pointsClient_.push_back(PointCluster(point));
  }
  pointsCandidate_ = pointsClient_;
}

AlgorithmGreedyClusters::~AlgorithmGreedyClusters() {}

std::vector<PointCluster> AlgorithmGreedyClusters::getServices() {
  return pointsService_;
}

std::vector<PointCluster> AlgorithmGreedyClusters::getClients() {
  return pointsClient_;
}

std::shared_ptr<IHeuristic> AlgorithmGreedyClusters::getHeuristic() {
  return ptrHeuristic_;
}

std::vector<PointCluster> AlgorithmGreedyClusters::getCandidates() {
  return pointsCandidate_;
}

void AlgorithmGreedyClusters::setCandidates(std::vector<PointCluster> candidates) {
  pointsCandidate_ = candidates;
}

int AlgorithmGreedyClusters::getIndexOfFarthest() {
  return indexOfFarthest_;
}

void AlgorithmGreedyClusters::setIndexOfFarthest(int newIndex) {
  indexOfFarthest_ = newIndex;
}

void AlgorithmGreedyClusters::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

void AlgorithmGreedyClusters::preprocess() {
  for (int i = 0; i < 2; ++i) {
    selectBestCandidate();
    addCandidate();
  }
}

bool AlgorithmGreedyClusters::hasCandidates() {
  return pointsService_.size() < pointsClient_.size();
}

bool AlgorithmGreedyClusters::isAtSolution() {
  return pointsService_.size() == k_;
}

void AlgorithmGreedyClusters::selectBestCandidate() {
  indexOfFarthest_ = ptrHeuristic_->choose(pointsCandidate_, pointsService_);
  pointFarthest_ = pointsCandidate_[indexOfFarthest_];
  pointsCandidate_.erase(pointsCandidate_.begin() + indexOfFarthest_);
}

bool AlgorithmGreedyClusters::validCandidate() {
  ++executionIterationNumber_;
  bool similarPointPresentAsService = false;
  for (int i = 0; i < pointsService_.size(); ++i) {
    auto componentsCandidate = pointFarthest_.getComponents();
    auto componentsService = pointsService_[i].getComponents();

    if (componentsCandidate == componentsService) {
      similarPointPresentAsService = true;
    }
  }
  return !similarPointPresentAsService;
}

// execute kmeans algorithm with current services
// add service point and then update all service points to their client average
void AlgorithmGreedyClusters::addCandidate() {
  pointsService_.push_back(pointFarthest_);

  auto ptrKmeans = std::make_shared<AlgorithmGreedyKMeans>(pointsClient_,
      pointsService_);
  greedyAlgorithm_.execute(ptrKmeans);
  pointsService_ = ptrKmeans->getServices();
  pointsClient_ = ptrKmeans->getClients();

  pointsCandidate_ = pointsClient_;

  ssePrevious_ = sse_;
  sse_ = objectiveFunction();
}

// calculate sse
float AlgorithmGreedyClusters::objectiveFunction() {
  SimilarityEuclidean euclidean;
  float total = 0;
  for (int i = 0; i < pointsService_.size(); ++i) {
    float clusterTotal = 0;
    for (auto& point : pointsClient_) {
      if (point.getCluster() == i) {
        clusterTotal += euclidean.similarity(pointsService_[i], point);
      }
    }
    total += clusterTotal;
  }
  return total;
}

void AlgorithmGreedyClusters::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << pointsClient_.size() << "\t\t";
  std::cout << pointsService_.size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << sse_ << "\t\t";
}

std::vector<int> AlgorithmGreedyClusters::generateRandomIndexList(int size) {
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
