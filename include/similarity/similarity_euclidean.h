#ifndef SIMILARITY_EUCLIDEAN_H
#define SIMILARITY_EUCLIDEAN_H

#include "i_similarity.h"

class SimilarityEuclidean : public ISimilarity {
public:
  SimilarityEuclidean();
  ~SimilarityEuclidean();
  
  virtual float similarity(std::shared_ptr<IPoint> pointA,
      std::shared_ptr<IPoint> pointB);
private:
};

#endif
