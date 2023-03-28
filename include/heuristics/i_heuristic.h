#ifndef IHEURISTIC_H
#define IHEURISTIC_H

#include <vector>
#include "../point/point_cluster.h"

class IHeuristic {
public:
  virtual ~IHeuristic() {}

  /**
   * the return value should be the index in the available std::vector
   *    of the point that is chosen.
  */
  virtual int choose(std::vector<PointCluster> pointClients,
      std::vector<PointCluster> pointServices) = 0;
private:
};

#endif