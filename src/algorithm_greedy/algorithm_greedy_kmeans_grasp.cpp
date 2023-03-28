#include "../../include/algorithm_greedy/algorithm_greedy_kmeans_grasp.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/point/point_cluster.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"
#include "../../include/similarity/similarity_euclidean.h"

AlgorithmGreedyKMeansGRASP::AlgorithmGreedyKMeansGRASP(std::vector<PointBasic> points,
  int k, float deltaSSE, int sizeOfLRC) : greedy_(points, k, deltaSSE),
    sizeOfLRC_(sizeOfLRC) {}

AlgorithmGreedyKMeansGRASP::AlgorithmGreedyKMeansGRASP(std::vector<PointBasic> points,
  float deltaSSE, int sizeOfLRC) : greedy_(points, deltaSSE), sizeOfLRC_(sizeOfLRC) {}

AlgorithmGreedyKMeansGRASP::~AlgorithmGreedyKMeansGRASP() {}

void AlgorithmGreedyKMeansGRASP::setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic) {
  greedy_.setHeuristic(ptrHeuristic);
}

void AlgorithmGreedyKMeansGRASP::preprocess() {
  greedy_.preprocess();
}

bool AlgorithmGreedyKMeansGRASP::hasCandidates() {
  return greedy_.hasCandidates();
}

bool AlgorithmGreedyKMeansGRASP::isAtSolution() {
  return greedy_.isAtSolution();
}

void AlgorithmGreedyKMeansGRASP::selectBestCandidate() {
  auto pointsCandidate = greedy_.getCandidates();
  auto pointsService = greedy_.getServices();
  auto ptrHeuristic = greedy_.getHeuristic();
  
  std::vector<PointCluster> lrcCandidates;
  int lengthAvailable = pointsCandidate.size() < sizeOfLRC_ ? pointsCandidate.size() : sizeOfLRC_;
  for (int i = 0; i < lengthAvailable; ++i) {
    int indexOfFarthest = ptrHeuristic->choose(pointsCandidate, pointsService);
    lrcCandidates.push_back(pointsCandidate[indexOfFarthest]);
    pointsCandidate.erase(pointsCandidate.begin() + indexOfFarthest);
  }

  srand(time(NULL));
  int randomIndex = rand() % lengthAvailable;
  greedy_.setIndexOfFarthest(randomIndex);
  lrcCandidates.erase(lrcCandidates.begin() + randomIndex);

  for (int i = 0; i < lrcCandidates.size(); ++i) {
    pointsCandidate.push_back(lrcCandidates[i]);
  }

  greedy_.setCandidates(pointsCandidate);
}

bool AlgorithmGreedyKMeansGRASP::validCandidate() {
  return greedy_.validCandidate();
}

// execute kmeans algorithm with current services
void AlgorithmGreedyKMeansGRASP::addCandidate() {
  greedy_.addCandidate();
}

// calculate sse
float AlgorithmGreedyKMeansGRASP::objectiveFunction() {
  return greedy_.objectiveFunction();
}

void AlgorithmGreedyKMeansGRASP::print() {
  greedy_.print();
  std::cout << sizeOfLRC_ << "\t\t";
}
