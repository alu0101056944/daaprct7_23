#include "../../include/environment_structure/environment_structure_exchange.h"

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"

EnvironmentStructureExchange::EnvironmentStructureExchange() {}

EnvironmentStructureExchange::~EnvironmentStructureExchange() {}


std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureExchange::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exhange one service point for a random client point that doesn't have a
// service point on the same location
void EnvironmentStructureExchange::execute(
      std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;

  auto bestSolution = solution;
  bool hasImproved;
  do {
    hasImproved = false;

    std::vector<PointCluster> clients = bestSolution->getClients();
    for (int i = 0; i < bestSolution->getServices().size(); ++i) {
      std::vector<PointCluster> services = bestSolution->getServices();

      // calculate list of client points that are not service points
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

      if (!nonServicePoints.empty()) {
        srand(time(NULL));
        int randomIndex = rand() % nonServicePoints.size();
        services[i] = nonServicePoints[randomIndex];
      }
      
      auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(clients, services);
      greedyAlgorithm.execute(ptrKMeans);

      if (ptrKMeans->objectiveFunction() < bestSolution->objectiveFunction()) {
        bestSolution = ptrKMeans;
        hasImproved = true;
      }
    }
  } while (hasImproved);

  ptrBestSolution_ = bestSolution;
}
