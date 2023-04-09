#include "../../include/algorithm_grasp/algorithm_grasp_clusters.h"

#include <chrono>
#include <iostream>

#include "../../include/environment_structure/environment_structure_interchange.h"

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int k, int sizeOfLRC, int msBeforeStop) :
      points_(points),
      k_(k),
      sizeOfLRC_(sizeOfLRC),
      msBeforeStop_(msBeforeStop) {}

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int sizeOfLRC, int msBeforeStop) :
      points_(points),
      k_(0.1 * points.size()),
      sizeOfLRC_(sizeOfLRC),
      msBeforeStop_(msBeforeStop) {}

AlgorithmGRASPClusters::~AlgorithmGRASPClusters() {}

void AlgorithmGRASPClusters::setEnvironmentStructure(
    std::shared_ptr<IEnvironmentStructure> ptrStructure) {

  ptrStructure_ = ptrStructure;
}

void AlgorithmGRASPClusters::preprocess() {
  startTime_ = std::chrono::high_resolution_clock::now();
}

bool AlgorithmGRASPClusters::build() {
  ptrSolution_ = std::make_shared<AlgorithmGreedyClustersLRC>(points_, k_, sizeOfLRC_);
  greedyAlgorithm_.execute(ptrSolution_);
}

bool AlgorithmGRASPClusters::postprocess() {
  // TODO: do the environment structure algorithm before changing the rest ***************
  auto newPointsService = ptrStructure_.getBestServices();
  auto newPointsClient = ptrStructure_.getBestClients();
  ptrSolution_ = std::make_shared<AlgorithmGreedyClustersLRC(newPointsClient, newPointsService);
}

void AlgorithmGRASPClusters::update() {
  if (ptrSolution_->objectiveFunction() < ptrBestSolution_->objectiveFunction()) {
    ptrBestSolution_ = ptrSolution_;
  }
}

bool AlgorithmGRASPClusters::stopCriteria() {
  auto stopTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime - startTime_);
  return (duration.count() / 1000000) > msBeforeStop_;
}

void AlgorithmGRASPClusters::print() {
  std::cout << "no print implementation yet on grasp clusters" << std::endl;
}