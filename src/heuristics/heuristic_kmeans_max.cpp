#include "../../include/heuristics/heuristic_kmeans_max.h"

#include <cassert>

#include "../../include/similarity/similarity_euclidean.h"
#include "../../include/point/point_cluster.h"

HeuristicKMeansMax::HeuristicKMeansMax() :
  ptrSimilarityAlgorithm_(new SimilarityEuclidean()) {}

HeuristicKMeansMax::~HeuristicKMeansMax() {}

int HeuristicKMeansMax::choose(std::vector<PointCluster> pointClients,
      std::vector<PointCluster> pointServices) {
  assert(pointClients.size() > 0);

  float maximumTotalDistance = 0;
  int index = -1;

  // furthest away point from any other point
  if (pointServices.empty()) {
    for (int i = 0; i < pointClients.size(); ++i) {
      float totalDistance = 0;
      for (int j = 0; j < pointClients.size(); ++j) {
        float distance = ptrSimilarityAlgorithm_->similarity(
            pointClients[i], pointClients[j]);
        totalDistance += distance;
      }
      if (totalDistance > maximumTotalDistance) {
        maximumTotalDistance = totalDistance;
        index = i;
      }
    }
    return index;
  }

  maximumTotalDistance = 0;

  // furthest away point from the service points
  for (int i = 0; i < pointClients.size(); ++i) {
    float totalDistance = 0;
    for (int j = 0; j < pointServices.size(); ++j) {
      float distance = ptrSimilarityAlgorithm_->similarity(
          pointClients[i], pointServices[j]);
      totalDistance += distance;
    }
    if (totalDistance > maximumTotalDistance) {
      maximumTotalDistance = totalDistance;
      index = i;
    }
  }
  return index;
}

void HeuristicKMeansMax::setSimilarityAlgorithm(
    std::shared_ptr<ISimilarity> ptrSimilarityAlgorithm) {
  ptrSimilarityAlgorithm_ = std::move(ptrSimilarityAlgorithm);
}