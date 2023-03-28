#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "../point/point_cluster.h"

class ISimilarity {
public:
  virtual ~ISimilarity() {}

  virtual float similarity(PointCluster pointA, PointCluster pointB) = 0;
private:
};

#endif
