#ifndef ENVIRONMENT_STRUCTURE_INTERCHANGE_H
#define ENVIRONMENT_STRUCTURE_INTERCHANGE_H

#include "i_environment_structure.h"

class EnvironmentStructureInterchange : public IEnvironmentStructure {
public:
  EnvironmentStructureInterchange();
  ~EnvironmentStructureInterchange();

  virtual std::vector<PointCluster> getBestClients();
  virtual std::vector<PointCluster> getBestServices();
  virtual executeLocalSearch(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService);
private:
};

#endif
