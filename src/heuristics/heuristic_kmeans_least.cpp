#include "../../include/heuristics/heuristic_kmeans_least.h"

#include <cassert>

#include "../../include/similarity/similarity_euclidean.h"

HeuristicKMeansLeast::HeuristicKMeansLeast() :
  ptrSimilarityAlgorithm_(new SimilarityEuclidean()) {}

HeuristicKMeansLeast::~HeuristicKMeansLeast() {}

int HeuristicKMeansLeast::choose(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) {
  assert(pointsService.size() > 0);

  // extract single point
  PointCluster& from = pointsClient.back();
  
  // initialize to last centroid is closest.
  float leastDistance = ptrSimilarityAlgorithm_->similarity(from, pointsService.back());
  int index = pointsService.size() - 1;

  // iterate centroids, keep the closest.
  for (int i = 0; i < pointsService.size() - 1; ++i) {
    float newDistance = ptrSimilarityAlgorithm_->similarity(from, pointsService[i]);
    if (newDistance < leastDistance) {
      leastDistance = newDistance;
      index = i;
    }
  }

  return index;
}

void HeuristicKMeansLeast::setSimilarityAlgorithm(
    std::shared_ptr<ISimilarity> ptrSimilarityAlgorithm) {
  ptrSimilarityAlgorithm_ = std::move(ptrSimilarityAlgorithm);
}
