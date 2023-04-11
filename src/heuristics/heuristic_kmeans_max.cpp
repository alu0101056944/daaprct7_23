#include "../../include/heuristics/heuristic_kmeans_max.h"

#include <cassert>

#include "../../include/similarity/similarity_euclidean.h"
#include "../../include/point/point_cluster.h"

HeuristicKMeansMax::HeuristicKMeansMax() :
  ptrSimilarityAlgorithm_(new SimilarityEuclidean()) {}

HeuristicKMeansMax::~HeuristicKMeansMax() {}

int HeuristicKMeansMax::choose(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) {
  assert(pointsClient.size() > 0);

  // initialize
  float maximumTotalDistance = 0;
  int index = -1;

  // if first greedy clusters execution
  if (pointsService.empty()) {
    // return furthest away point from any other point
    // iterate point, calculate total distance to others. check if best.
    for (int i = 0; i < pointsClient.size(); ++i) {

      float totalDistance = 0;
      for (int j = 0; j < pointsClient.size(); ++j) {
        float distance = ptrSimilarityAlgorithm_->similarity(
            pointsClient[i], pointsClient[j]);
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
  // iterate point, calculate distance to centroids. check if best.
  for (int i = 0; i < pointsClient.size(); ++i) {

    float totalDistance = 0;
    for (int j = 0; j < pointsService.size(); ++j) {
      float distance = ptrSimilarityAlgorithm_->similarity(
          pointsClient[i], pointsService[j]);
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
