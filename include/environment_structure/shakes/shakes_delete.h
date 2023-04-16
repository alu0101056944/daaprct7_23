#ifndef SHAKES_DELETE_H
#define SHAKES_DELETE_H

#include "../i_environment_structure.h"

class ShakesDelete : public IEnvironmentStructure {
public:
  ShakesDelete();
  ~ShakesDelete();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
