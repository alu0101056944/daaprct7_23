#include "../../include/environment_structure/environment_structure_add_single.h"

#include <algorithm>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"

EnvironmentStructureAddSingle::EnvironmentStructureAddSingle() {}

EnvironmentStructureAddSingle::~EnvironmentStructureAddSingle() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureAddSingle::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

void EnvironmentStructureAddSingle::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;
  
  auto bestSolution = solution;

  auto services = bestSolution->getServices();
  auto candidates = bestSolution->getClients();

  // insert candidate, execute kmeans, check if best
  while (!candidates.empty()) {
    auto permutation = services;
    const int kIndexOfFarthest = heuristic_.choose(candidates, permutation);
    permutation.push_back(candidates[kIndexOfFarthest]);
    candidates.erase(candidates.begin() + kIndexOfFarthest);
    
    auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
        bestSolution->getClients(), permutation);
    greedyAlgorithm.execute(ptrKMeans);

    if (ptrKMeans->getSSE() < bestSolution->getSSE()) {
      bestSolution = ptrKMeans;
    }
  }

  ptrBestSolution_ = bestSolution;
}
