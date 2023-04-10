#include "../../include/algorithm_grasp/algorithm_grasp_clusters.h"

#include <iostream>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../../include/environment_structure/environment_structure_delete.h"

int AlgorithmGRASPClusters::ID = 0;

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int k, int sizeOfLRC) :
      points_(points),
      k_(k),
      sizeOfLRC_(sizeOfLRC),
      ptrStructure_(new EnvironmentStructureDelete()),
      currentID_(++ID),
      executionIterationNumber_(0),
      hasImproved_(true) {}

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int sizeOfLRC) :
      points_(points),
      k_(0.1 * points.size()),
      sizeOfLRC_(sizeOfLRC),
      ptrStructure_(new EnvironmentStructureDelete()),
      currentID_(++ID),
      executionIterationNumber_(0),
      hasImproved_(true) {}

AlgorithmGRASPClusters::~AlgorithmGRASPClusters() {}

void AlgorithmGRASPClusters::setEnvironmentStructure(
      std::shared_ptr<IEnvironmentStructure> ptrStructure) {
  ptrStructure_ = ptrStructure;
}

void AlgorithmGRASPClusters::preprocess() {

}

void AlgorithmGRASPClusters::build() {
  hasImproved_ = false;

  auto builtSolution = std::make_shared<AlgorithmGreedyClustersLRC>(points_, k_, sizeOfLRC_);
  greedyAlgorithm_.execute(builtSolution);

  ptrSolution_ = std::make_shared<AlgorithmGreedyKMeans>(builtSolution->getClients(),
    builtSolution->getServices());
}

void AlgorithmGRASPClusters::postprocess() {
  ptrStructure_->execute(ptrSolution_);
  ptrBestSolution_ = ptrStructure_->getBestSolution();
}

void AlgorithmGRASPClusters::update() {
  ++executionIterationNumber_;

  if (ptrSolution_->objectiveFunction() < ptrBestSolution_->objectiveFunction()) {
    ptrBestSolution_ = ptrSolution_;
    hasImproved_ = true;
  }
}

bool AlgorithmGRASPClusters::stopCriteria() {
  return !hasImproved_;
}

void AlgorithmGRASPClusters::print() {
  std::cout << currentID_ << "\t\t";
  std::cout << points_.size() << "\t\t";
  std::cout << k_ << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  if (ptrBestSolution_ != nullptr) {
    std::cout << ptrBestSolution_->objectiveFunction() << "\t\t";
  } else {
    std::cout << "..." << "\t\t";
  }
  std::cout << sizeOfLRC_ << "\t\t";
}
