#include "../../include/heuristics/heuristic_kmeans_least.h"

#include <cassert>

#include "../../include/similarity/similarity_euclidean.h"

HeuristicKMeansLeast::HeuristicKMeansLeast() :
  ptrSimilarityAlgorithm_(new SimilarityEuclidean()) {}

HeuristicKMeansLeast::~HeuristicKMeansLeast() {}

int HeuristicKMeansLeast::choose(std::shared_ptr<IPoint> from,
      std::vector<std::shared_ptr<IPoint>> available) {
  assert(available.size() > 0);

  float leastDistance = ptrSimilarityAlgorithm_->similarity(from, available.back());
  int index = available.size() - 1;

  for (int i = 0; i < available.size() - 1; ++i) {
    float newDistance = ptrSimilarityAlgorithm_->similarity(from, available[i]);
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