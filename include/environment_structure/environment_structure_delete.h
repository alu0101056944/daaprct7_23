#ifndef ENVIRONMENT_STRUCTURE_DELETE_H
#define ENVIRONMENT_STRUCTURE_DELETE_H

#include "i_environment_structure.h"

class EnvironmentStructureDelete : public IEnvironmentStructure {
public:
  EnvironmentStructureDelete();
  ~EnvironmentStructureDelete();

  virtual std::shared_ptr<AlgorithmGreedyKMeans> getBestSolution();
  virtual void execute(std::shared_ptr<AlgorithmGreedyKMeans> solution);
private:
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;
};

#endif
