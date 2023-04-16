#include "../../include/environment_structure/environment_structure_add.h"

#include <algorithm>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"
#include "../../include/heuristics/heuristic_kmeans_max.h"

EnvironmentStructureAdd::EnvironmentStructureAdd() {}

EnvironmentStructureAdd::~EnvironmentStructureAdd() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureAdd::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exchange one service point to one other position
void EnvironmentStructureAdd::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;
  
  auto bestSolution = solution;
  bool hasImproved;
  do {
    hasImproved = false;

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

      if (ptrKMeans->objectiveFunction() < bestSolution->objectiveFunction()) {
        bestSolution = ptrKMeans;
        hasImproved = true;
      }
    }

  } while (hasImproved);

  ptrBestSolution_ = bestSolution;
}
