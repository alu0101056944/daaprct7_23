#include "../../include/algorithm_greedy/framework_greedy.h"

FrameworkGreedy::FrameworkGreedy() {}

FrameworkGreedy::~FrameworkGreedy() {}

void FrameworkGreedy::execute(std::shared_ptr<IAlgorithmGreedy> ptrAlgorithm) {
  ptrAlgorithm->preprocess();
  while (ptrAlgorithm->hasCandidates() && !ptrAlgorithm->isAtSolution()) {
    ptrAlgorithm->selectBestCandidate();
    if (ptrAlgorithm->validCandidate()) {
      ptrAlgorithm->addCandidate();
    }
  }
}
