#ifndef OBJECTIVE_FUNCTION_SSE_H
#define OBJECTIVE_FUNCTION_SSE_H

#include <vector>

#include "point/point_cluster.h"

class ObjectiveFunctionSSE {
public:
  ObjectiveFunctionSSE();
  ~ObjectiveFunctionSSE();

  float get(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService, float factor);
};

#endif
