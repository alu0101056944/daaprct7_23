#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"
#include "../../include/similarity/similarity_euclidean.h"

AlgorithmGreedyClustersLRC::AlgorithmGreedyClustersLRC(std::vector<PointBasic> points,
  int k, int sizeOfLRC) : greedy_(points, k),
    sizeOfLRC_(sizeOfLRC) {}

AlgorithmGreedyClustersLRC::~AlgorithmGreedyClustersLRC() {}

std::vector<PointCluster> AlgorithmGreedyClustersLRC::getServices() {
  return greedy_.getServices();;
}

std::vector<PointCluster> AlgorithmGreedyClustersLRC::getClients() {
  return greedy_.getClients();
}

void AlgorithmGreedyClustersLRC::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  greedy_.setHeuristic(ptrHeuristic);
}

void AlgorithmGreedyClustersLRC::preprocess() {
  greedy_.preprocess();
}

bool AlgorithmGreedyClustersLRC::hasCandidates() {
  return greedy_.hasCandidates();
}

bool AlgorithmGreedyClustersLRC::isAtSolution() {
  return greedy_.isAtSolution();
}

// call selectBestCandidate() a few times. Store them. Select one. re-add rest.
void AlgorithmGreedyClustersLRC::selectBestCandidate() {
  auto pointsCandidate = greedy_.getCandidates();
  auto pointsService = greedy_.getServices();
  auto ptrHeuristic = greedy_.getHeuristic();
  
  std::vector<PointCluster> lrcCandidates;

  int lengthAvailable = pointsCandidate.size() < sizeOfLRC_ ? pointsCandidate.size() : sizeOfLRC_;

  // choose and push a few times
  for (int i = 0; i < lengthAvailable; ++i) {
    int indexOfFarthest = ptrHeuristic->choose(pointsCandidate, pointsService);
    lrcCandidates.push_back(pointsCandidate[indexOfFarthest]);
    pointsCandidate.erase(pointsCandidate.begin() + indexOfFarthest);
  }

  // choose random candidate
  srand(time(NULL));
  int randomIndex = rand() % lengthAvailable; // framework checks if there are candidates, should not cause trouble.
  greedy_.setFarthestPoint(lrcCandidates[randomIndex]);
  lrcCandidates.erase(lrcCandidates.begin() + randomIndex);

  // re-add unchosen ones
  for (int i = 0; i < lrcCandidates.size(); ++i) {
    pointsCandidate.push_back(lrcCandidates[i]);
  }

  greedy_.setCandidates(pointsCandidate);
}

bool AlgorithmGreedyClustersLRC::validCandidate() {
  return greedy_.validCandidate();
}

// Add new centroid. Execute kmeans.
void AlgorithmGreedyClustersLRC::addCandidate() {
  greedy_.addCandidate();
}

float AlgorithmGreedyClustersLRC::getSSE() {
  return greedy_.getSSE();
}

// calculate sse
float AlgorithmGreedyClustersLRC::objectiveFunction() {
  return greedy_.objectiveFunction();
}

void AlgorithmGreedyClustersLRC::print() {
  greedy_.print();
  std::cout << sizeOfLRC_ << "\t\t";
}
