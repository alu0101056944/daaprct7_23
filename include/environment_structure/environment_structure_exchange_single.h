#ifndef ENVIRONMENT_STRUCTURE_EXCHANGE_SINGLE_H
#define ENVIRONMENT_STRUCTURE_EXCHANGE_SINGLE_H

#include "i_environment_structure.h"

class EnvironmentStructureExchangeSingle : public IEnvironmentStructure {
public:
  EnvironmentStructureExchangeSingle();
  ~EnvironmentStructureExchangeSingle();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
