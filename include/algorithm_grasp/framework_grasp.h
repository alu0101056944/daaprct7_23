#ifndef FRAMEWORK_GRASP_H
#define FRAMEWORK_GRASP_H

#include <memory>

#include "i_algorithm_grasp.h"

class FrameworkGRASP {
public:
  FrameworkGRASP();
  ~FrameworkGRASP();

  void execute(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm);
  void executeAndprint(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm);
private:
};

#endif
