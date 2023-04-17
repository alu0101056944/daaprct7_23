#include "../../include/environment_structure/environment_structure_exchange_single.h"

#include <algorithm>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"

EnvironmentStructureExchangeSingle::EnvironmentStructureExchangeSingle() {}

EnvironmentStructureExchangeSingle::~EnvironmentStructureExchangeSingle() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureExchangeSingle::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// substitute centroid with client that is not centroid (does not have one ontop)
void EnvironmentStructureExchangeSingle::execute(
      std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;

  auto bestSolution = solution;

  std::vector<PointCluster> clients = bestSolution->getClients();

  // Choose centroid. get client that is not centroid. Substitute if found. Kmeans.
  // check if best.
  for (int i = 0; i < bestSolution->getServices().size(); ++i) {
    std::vector<PointCluster> services = bestSolution->getServices();

    // get clients that are not centroid
    std::vector<PointCluster> nonServicePoints;
    for (int i = 0; i < clients.size(); ++i) {
      auto componentsClient = clients[i].getComponents();
      bool isService = false;

      for (int j = 0; j < services.size(); ++j) {
        auto componentsService = services[j].getComponents();
        
        if (componentsClient == componentsService) {
          isService = true;
        }
      }

      if (!isService) {
        nonServicePoints.push_back(clients[i]);
      }
    }

    // only substitute if not empty
    if (!nonServicePoints.empty()) {
      srand(time(NULL));
      int randomIndex = rand() % nonServicePoints.size();
      services[i] = nonServicePoints[randomIndex];
    }
    
    auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(clients, services);
    greedyAlgorithm.execute(ptrKMeans);

    if (ptrKMeans->objectiveFunction() < bestSolution->objectiveFunction()) {
      bestSolution = ptrKMeans;
    }
  }

  ptrBestSolution_ = bestSolution;
}
