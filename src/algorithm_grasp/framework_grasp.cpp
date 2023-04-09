#include "../../include/algorithm_grasp/framework_grasp.h"

FrameworkGRASP::FrameworkGRASP() {}

FrameworkGRASP::~FrameworkGRASP() {}

void FrameworkGRASP::execute(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm) {
  ptrAlgorithm->preprocess();
  while (!ptrAlgorithm->stopCriteria()) {
    ptrAlgoritm->build();
    ptrAlgoritm->postprocess();
    ptrAlgoritm->update();
  }
}

void FrameworkGRASP::executeAndprint(std::shared_ptr<IAlgorithmGRASP> ptrAlgorithm) {
  int cpuTime = 0;
  std::cout << "Problema\tm\t\tK\t\tEjecución\t\tSSE\t\t|LRC|\t\tCPU" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  ptrAlgorithm->preprocess();
  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  cpuTime += duration.count() / 100000;
  ptrAlgorithm->print();
  std::cout << std::to_string(cpuTime) << "\t\t" << std::endl;

  while (!ptrAlgorithm->stopCriteria()) {

    auto start = std::chrono::high_resolution_clock::now();
    ptrAlgoritm->build();
    ptrAlgoritm->postprocess();
    ptrAlgoritm->update();
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cpuTime += duration.count() / 100000;
    ptrAlgorithm->print();
    std::cout << std::to_string(cpuTime) << "\t\t" << std::endl;
}
