#ifndef I_ENVIRONMENT_STRUCTURE_H
#define I_ENVIRONMENT_STRUCTURE_H

#include <vector>

#include "../point/point_cluster.h"
#include "../algorithm_greedy/algorithm_greedy_kmeans.h"

class IEnvironmentStructure {
public:
  virtual ~IEnvironmentStructure() {}

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution() = 0;
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) = 0;
};

#endif
