#ifndef ENVIRONMENT_STRUCTURE_EXCHANGE_K_H
#define ENVIRONMENT_STRUCTURE_EXCHANGE_K_H

#include "i_environment_structure.h"

class EnvironmentStructureExchangeK : public IEnvironmentStructure {
public:
  EnvironmentStructureExchangeK();
  ~EnvironmentStructureExchangeK();

  void setK(int newK);

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;

  int k_; // how many service points to exchange.

  std::vector<int> uniqueServicePointsFrom(std::vector<PointCluster> points, int size);
};

#endif
