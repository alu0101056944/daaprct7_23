#include "../../include/environment_structure/environment_structure_delete.h"

#include <algorithm>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"

EnvironmentStructureDelete::EnvironmentStructureDelete() {}

EnvironmentStructureDelete::~EnvironmentStructureDelete() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureDelete::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exchange one service point to one other position
void EnvironmentStructureDelete::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;

  auto bestSolution = solution;
  bool hasImproved;
  do {
    hasImproved = false;

    // Delete position, execute kmeans, check if best.
    auto services = bestSolution->getServices();
    for (int i = 0; i < services.size(); ++i) {
      std::vector<PointCluster> permutation = services;
      permutation.erase(permutation.begin() + i);

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
