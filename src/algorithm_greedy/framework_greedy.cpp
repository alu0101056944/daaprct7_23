#include "../../include/algorithm_greedy/framework_greedy.h"

#include <iostream>
#include <chrono>

FrameworkGreedy::FrameworkGreedy() {}

FrameworkGreedy::~FrameworkGreedy() {}

// Standard greedy algorithm structure
void FrameworkGreedy::execute(std::shared_ptr<IAlgorithmGreedy> ptrAlgorithm) {
  ptrAlgorithm->preprocess();
  while (ptrAlgorithm->hasCandidates() && !ptrAlgorithm->isAtSolution()) {
    ptrAlgorithm->selectBestCandidate();
    if (ptrAlgorithm->validCandidate()) {
      ptrAlgorithm->addCandidate();
    }
  }
}

void FrameworkGreedy::executeAndprint(std::shared_ptr<IAlgorithmGreedy> ptrAlgorithm) {
  // add cpuTime as the algorithm executes using chrono
  int cpuTime = 0;
  std::cout << "Problema\tm\t\tK\t\tEjecución\t\tSSE\t\t|LRC|\t\tCPU" << std::endl;

  // Measure and print preprocess
  auto start = std::chrono::high_resolution_clock::now();
  ptrAlgorithm->preprocess();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  cpuTime += duration.count() / 100000;
  ptrAlgorithm->print();
  std::cout << std::to_string(cpuTime) << "\t\t" << std::endl;

  while (ptrAlgorithm->hasCandidates() && !ptrAlgorithm->isAtSolution()) {
    // measure and print the loop iteration
    auto start = std::chrono::high_resolution_clock::now();
    ptrAlgorithm->selectBestCandidate();
    if (ptrAlgorithm->validCandidate()) {
      ptrAlgorithm->addCandidate();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cpuTime += duration.count() / 100000;
    ptrAlgorithm->print();
    std::cout << std::to_string(cpuTime) << "\t\t" << std::endl;
  }
}
