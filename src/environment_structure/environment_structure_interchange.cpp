#include "../../include/environment_structure/environment_structure_interchange.h"

#include <algorithm>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"

EnvironmentStructureInterchange::EnvironmentStructureInterchange() {}

EnvironmentStructureInterchange::~EnvironmentStructureInterchange() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureInterchange::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exhange one service point to one other position
void EnvironmentStructureInterchange::execute(
      std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;

  auto bestSolution = solution;
  
  for (int i = 0; i < solution->getServices().size(); ++i) {
    for (int j = 0; j < solution->getServices().size(); ++j) {
      if (j != i) {
        std::vector<PointCluster> permutation = solution->getServices();
        std::iter_swap(permutation.begin() + i, permutation.begin() + j);

        auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(solution->getClients(),
            permutation);
        greedyAlgorithm.execute(ptrKMeans);

        if (ptrKMeans->objectiveFunction() < bestSolution->objectiveFunction()) {

        }
      }
    }
  }
}

