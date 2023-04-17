#ifndef ENVIRONMENT_STRUCTURE_DELETE_SINGLE_H
#define ENVIRONMENT_STRUCTURE_DELETE_SINGLE_H

#include "i_environment_structure.h"

class EnvironmentStructureDeleteSingle : public IEnvironmentStructure {
public:
  EnvironmentStructureDeleteSingle();
  ~EnvironmentStructureDeleteSingle();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
