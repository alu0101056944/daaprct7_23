#ifndef SIMILARITY_EUCLIDEAN_H
#define SIMILARITY_EUCLIDEAN_H

#include "i_similarity.h"

class SimilarityEuclidean : public ISimilarity {
public:
  SimilarityEuclidean();
  ~SimilarityEuclidean();
  
  virtual float similarity(PointCluster pointA, PointCluster pointB);
private:
};

#endif
