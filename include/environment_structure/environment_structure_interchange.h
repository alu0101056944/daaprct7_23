#ifndef ENVIRONMENT_STRUCTURE_INTERCHANGE_H
#define ENVIRONMENT_STRUCTURE_INTERCHANGE_H

#include "i_environment_structure.h"

class EnvironmentStructureInterchange : public IEnvironmentStructure {
public:
  EnvironmentStructureInterchange();
  ~EnvironmentStructureInterchange();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
