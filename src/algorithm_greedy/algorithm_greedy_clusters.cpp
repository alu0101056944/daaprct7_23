#include "../../include/algorithm_greedy/algorithm_greedy_clusters.h"

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
#include "../../include/objective_function_sse.h"

int AlgorithmGreedyClusters::ID = 0;

AlgorithmGreedyClusters::AlgorithmGreedyClusters(std::vector<PointBasic> points,
    int k) :
    k_(k),
    ptrHeuristic_(new HeuristicKMeansMax()), // choose() farthest away point from any centroid
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

AlgorithmGreedyClusters::~AlgorithmGreedyClusters() {}

// ************ getters and setters

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

void AlgorithmGreedyClusters::setFarthestPoint(PointCluster pointFarthest) {
  pointFarthest_ = pointFarthest;
}

void AlgorithmGreedyClusters::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  ptrHeuristic_ = ptrHeuristic;
}

// ************ framework methods

// add 2 centroids. All solutions will have minimum 2
void AlgorithmGreedyClusters::preprocess() {
  for (int i = 0; i < 2; ++i) {
    selectBestCandidate();
    addCandidate();
  }
}

// whether can add centroid
bool AlgorithmGreedyClusters::hasCandidates() {
  return pointsService_.size() < pointsClient_.size();
}

// whether reached size = k
bool AlgorithmGreedyClusters::isAtSolution() {
  return pointsService_.size() == k_;
}

// choose farthest client from other centroids as possible centroid
void AlgorithmGreedyClusters::selectBestCandidate() {
  indexOfFarthest_ = ptrHeuristic_->choose(pointsCandidate_, pointsService_);
  pointFarthest_ = pointsCandidate_[indexOfFarthest_];
  pointsCandidate_.erase(pointsCandidate_.begin() + indexOfFarthest_);
}

// whether centroid ontop of candidate. Because kmeans would change both equally
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

// Add new centroid. Execute kmeans.
void AlgorithmGreedyClusters::addCandidate() {
  pointsService_.push_back(pointFarthest_);

  algorithmClosest_.execute(pointsClient_, pointsService_);
  pointsService_ = algorithmClosest_.getServices();
  pointsClient_ = algorithmClosest_.getClients();
  pointsCandidate_ = pointsClient_;

  ssePrevious_ = sse_;
  sse_ = objectiveFunction();
}

float AlgorithmGreedyClusters::getSSE() {
  return sse_;
}

float AlgorithmGreedyClusters::objectiveFunction() {
  return ObjectiveFunctionSSE().get(pointsClient_, pointsService_, 8);
}

void AlgorithmGreedyClusters::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << pointsClient_.size() << "\t\t";
  std::cout << pointsService_.size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << sse_ << "\t\t";
  std::cout << "..." << "\t\t";
}
