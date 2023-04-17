#include "../../include/algorithm_grasp/algorithm_grasp_clusters.h"

#include <iostream>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../../include/environment_structure/environment_structure_exchange.h"
#include "../../include/environment_structure/environment_structure_exchange_k.h"
#include "../../include/environment_structure/environment_structure_delete.h"

int AlgorithmGRASPClusters::ID = 0;

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int k, int sizeOfLRC) :
      points_(points),
      k_(k),
      sizeOfLRC_(sizeOfLRC),
      ptrStructure_(new EnvironmentStructureExchange()),
      currentID_(++ID),
      executionIterationNumber_(0),
      hasImproved_(true) {}

AlgorithmGRASPClusters::~AlgorithmGRASPClusters() {}

void AlgorithmGRASPClusters::setEnvironmentStructure(
      std::shared_ptr<IEnvironmentStructure> ptrStructure) {
  ptrStructure_ = ptrStructure;
}

void AlgorithmGRASPClusters::preprocess() {}

// build using builder. Transform to kmeans instance.
void AlgorithmGRASPClusters::build() {
  ++executionIterationNumber_;
  hasImproved_ = false;

  auto builtSolution = std::make_shared<AlgorithmGreedyClustersLRC>(points_, k_, sizeOfLRC_);
  greedyAlgorithm_.execute(builtSolution);

  ptrSolution_ = std::make_shared<AlgorithmGreedyKMeans>(builtSolution->getClients(),
    builtSolution->getServices());
  greedyAlgorithm_.execute(ptrSolution_);

  if (ptrBestSolution_ == nullptr) { // to allow print()
    ptrBestSolution_ = ptrSolution_;
  }
}

// execute structure, substitute solution.
void AlgorithmGRASPClusters::postprocess() {
  ptrStructure_->execute(ptrSolution_);
  ptrSolution_ = ptrStructure_->getBestSolution();
}

void AlgorithmGRASPClusters::update() {
  if (ptrSolution_->getSSE() < ptrBestSolution_->getSSE()) {
    ptrBestSolution_ = ptrSolution_;
    hasImproved_ = true;
  }
}

bool AlgorithmGRASPClusters::stopCriteria() {
  return !hasImproved_ && executionIterationNumber_ > 10;
}

void AlgorithmGRASPClusters::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << points_.size() << "\t\t";
  std::cout << ptrSolution_->getServices().size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  if (ptrSolution_ != nullptr) {
    std::cout << ptrSolution_->objectiveFunction() << "\t\t";
  } else {
    std::cout << "..." << "\t\t";
  }
  std::cout << sizeOfLRC_ << "\t\t";
}
