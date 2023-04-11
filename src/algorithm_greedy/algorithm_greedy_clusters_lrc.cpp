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

/**
 * Alternative: select best candidate, get and store, repeat LCR.size() times.
*/
void AlgorithmGreedyClustersLRC::selectBestCandidate() {
  auto pointsCandidate = greedy_.getCandidates();
  auto pointsService = greedy_.getServices();
  auto ptrHeuristic = greedy_.getHeuristic();
  
  std::vector<PointCluster> lrcCandidates;
  /**
   * equivalent syntax:
  while (!pointsCandidate.empty() && pointsCandidate.size() < sizeOfLRC_) {
    int indexOfFarthest = ptrHeuristic->choose(pointsCandidate, pointsService);
    lrcCandidates.push_back(pointsCandidate[indexOfFarthest]);
    pointsCandidate.erase(pointsCandidate.begin() + indexOfFarthest);
  }
  */
  int lengthAvailable = pointsCandidate.size() < sizeOfLRC_ ? pointsCandidate.size() : sizeOfLRC_;
  for (int i = 0; i < lengthAvailable; ++i) {
    int indexOfFarthest = ptrHeuristic->choose(pointsCandidate, pointsService);
    lrcCandidates.push_back(pointsCandidate[indexOfFarthest]);
    pointsCandidate.erase(pointsCandidate.begin() + indexOfFarthest);
  }

  srand(time(NULL));
  int randomIndex = rand() % lengthAvailable; // framework checks if there are candidates, should not cause trouble.
  greedy_.setFarthestPoint(lrcCandidates[randomIndex]);
  lrcCandidates.erase(lrcCandidates.begin() + randomIndex);

  for (int i = 0; i < lrcCandidates.size(); ++i) {
    pointsCandidate.push_back(lrcCandidates[i]);
  }

  greedy_.setCandidates(pointsCandidate);
}

bool AlgorithmGreedyClustersLRC::validCandidate() {
  return greedy_.validCandidate();
}

// execute kmeans algorithm with current services
void AlgorithmGreedyClustersLRC::addCandidate() {
  greedy_.addCandidate();
}

// calculate sse
float AlgorithmGreedyClustersLRC::objectiveFunction() {
  return greedy_.objectiveFunction();
}

void AlgorithmGreedyClustersLRC::print() {
  greedy_.print();
  std::cout << sizeOfLRC_ << "\t\t";
}
