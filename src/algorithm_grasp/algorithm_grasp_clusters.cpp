#include "../../include/algorithm_grasp/algorithm_grasp_clusters.h"

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int k, int sizeOfLRC) :
      points_(points),
      k_(k),
      sizeOfLRC_(sizeOfLRC) {

  ptrSolution = std::make_shared<AlgorithmGreedyClustersLRC>(
    points_, k_, sizeOfLRC_
  );
}

AlgorithmGRASPClusters::AlgorithmGRASPClusters(std::vector<PointBasic> points,
    int sizeOfLRC) :
      points_(points),
      k_(0.1 * points.size()),
      sizeOfLRC_(sizeOfLRC) {

    ptrSolution = std::make_shared<AlgorithmGreedyClustersLRC>(
    points_, k_, sizeOfLRC_
  );
}

AlgorithmGRASPClusters::~AlgorithmGRASPClusters() {}

void AlgorithmGRASPClusters::preprocess() {

}

bool AlgorithmGRASPClusters::build() {
  //ptrSolution.forceNextBestCandidates();
  greedyAlgorithm_.execute(ptrSolution);
}

bool AlgorithmGRASPClusters::postprocess() {

}

void AlgorithmGRASPClusters::update() {

}

bool AlgorithmGRASPClusters::stopCriteria() {

}
