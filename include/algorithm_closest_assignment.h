
/**
 * Previous versions of this program either applies kmeans or not. The build()
 * from grasp (which uses AlgorithmGreedyClusters) executes kmeans after each
 * added service point, but a better approach is to only do the assignment and
 * not the service point update with average part. This class is kmeans but
 * only the assignment.
*/

#ifndef ALGORITHM_CLOSEST_ASSIGNMENT_H
#define ALGORITHM_CLOSEST_ASSIGNMENT_H

#include <vector>
#include <memory>

#include "point/point_cluster.h"

#include "heuristics/heuristic_kmeans_least.h"

class AlgorithmClosestAssignment {
public:
  AlgorithmClosestAssignment();
  ~AlgorithmClosestAssignment();

  std::vector<PointCluster> getClients();
  std::vector<PointCluster> getServices();

  void execute(std::vector<PointCluster> clients,
      std::vector<PointCluster> services);
private:
  std::shared_ptr<IHeuristic> ptrHeuristic_;

  std::vector<PointCluster> clients_;
  std::vector<PointCluster> services_;
};

#endif
