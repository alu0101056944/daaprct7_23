#ifndef SHAKES_ADD_H
#define SHAKES_ADD_H

#include "../i_environment_structure.h"

class ShakesAdd : public IEnvironmentStructure {
public:
  ShakesAdd();
  ~ShakesAdd();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
