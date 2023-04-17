#include "../../include/algorithm_grasp/framework_grasp.h"

#include <iostream>
#include <chrono>

FrameworkGRASP::FrameworkGRASP() {}

FrameworkGRASP::~FrameworkGRASP() {}

// Standard grasp structure
void FrameworkGRASP::execute(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm) {
  ptrAlgorithm->preprocess();
  while (!ptrAlgorithm->stopCriteria()) {
    ptrAlgorithm->build();
    ptrAlgorithm->postprocess();
    ptrAlgorithm->update();
  }
}

void FrameworkGRASP::executeAndprint(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm) {
  int cpuTime = 0;
  std::cout << "Problema\tm\t\tK\t\tEjecución\t\tSSE\t\t|LRC|\t\tCPU" << std::endl;
  ptrAlgorithm->preprocess();
  while (!ptrAlgorithm->stopCriteria()) {
    // Measure and print postprocess() and update()
    auto start = std::chrono::high_resolution_clock::now();
    ptrAlgorithm->build();
    ptrAlgorithm->postprocess();
    ptrAlgorithm->update();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cpuTime += duration.count() / 100000;
    ptrAlgorithm->print();
    std::cout << std::to_string(cpuTime) << "\t\t" << std::endl;
  }
}
