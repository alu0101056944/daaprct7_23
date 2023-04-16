#ifndef SHAKES_EXCHANGE_H
#define SHAKES_EXCHANGE_H

#include "../i_environment_structure.h"

class ShakesExchange : public IEnvironmentStructure {
public:
  ShakesExchange();
  ~ShakesExchange();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
