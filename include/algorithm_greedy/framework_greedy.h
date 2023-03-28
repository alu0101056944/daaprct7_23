#ifndef FRAMEWORK_GREEDY_H
#define FRAMEWORK_GREEDY_H

#include <memory>

#include "i_algorithm_greedy.h"

class FrameworkGreedy {
public:
  FrameworkGreedy();
  ~FrameworkGreedy();

  void execute(std::shared_ptr<IAlgorithmGreedy> ptrAlgorithm);
  void executeAndprint(std::shared_ptr<IAlgorithmGreedy> ptrAlgorithm);
private:
};

#endif
