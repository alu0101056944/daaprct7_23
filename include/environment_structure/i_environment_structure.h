#ifndef I_ENVIRONMENT_STRUCTURE_H
#define I_ENVIRONMENT_STRUCTURE_H

#include <vector>

#include "../point/point_cluster.h"

class IEnvironmentStructure {
public:
  virtual ~IEnvironmentStructure() {}

  virtual std::vector<PointCluster> getBestClients() = 0;
  virtual std::vector<PointCluster> getBestServices() = 0;
  virtual executeLocalSearch(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) = 0;
};

#endif
