#ifndef ENVIRONMENT_STRUCTURE_EXCHANGE_H
#define ENVIRONMENT_STRUCTURE_EXCHANGE_H

#include "i_environment_structure.h"

class EnvironmentStructureExchange : public IEnvironmentStructure {
public:
  EnvironmentStructureExchange();
  ~EnvironmentStructureExchange();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
