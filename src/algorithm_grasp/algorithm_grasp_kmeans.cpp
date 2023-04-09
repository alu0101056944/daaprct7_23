#include "../../include/algorithm_grasp/algorithm_grasp_kmeans.h"

#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

AlgorithmGRASPKMeans::AlgorithmGRASPKMeans(std::vector<PointBasic> points,
    int k, int sizeOfLRC) :
  points_(points),
  k_(k),
  sizeOfLRC_(sizeOfLRC) {}

AlgorithmGRASPKMeans::AlgorithmGRASPKMeans(std::vector<PointBasic> points,
    int sizeOfLRC) :
  points_(points),
  k_(0.1 * points.size()),
  sizeOfLRC_(sizeOfLRC) {}

AlgorithmGRASPKMeans::~AlgorithmGRASPKMeans() {}

void AlgorithmGRASPKMeans::preprocess() {

}

bool AlgorithmGRASPKMeans::build() {
  auto builderGRASP = std::make_shared<AlgorithmGreedyClustersLRC>(points_,
      k_, sizeOfLRC_);
  greedyAlgorithm_.execute(builderGRASP);
  pointsServiceInitial_ = builderGRASP->getServices();
}

bool AlgorithmGRASPKMeans::postprocess() {

}

void AlgorithmGRASPKMeans::update() {

}

bool AlgorithmGRASPKMeans::stopCriteria() {

}
