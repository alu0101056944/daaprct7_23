#ifndef ENVIRONMENT_STRUCTURE_ADD_H
#define ENVIRONMENT_STRUCTURE_ADD_H

#include "i_environment_structure.h"
#include "../heuristics/heuristic_kmeans_max.h"

class EnvironmentStructureAdd : public IEnvironmentStructure {
public:
  EnvironmentStructureAdd();
  ~EnvironmentStructureAdd();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
  HeuristicKMeansMax heuristic_;
};

#endif
