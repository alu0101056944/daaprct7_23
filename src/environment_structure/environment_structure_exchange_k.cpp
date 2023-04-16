#include "../../include/environment_structure/environment_structure_exchange_k.h"

#include <algorithm>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../include/algorithm_greedy/framework_greedy.h"

EnvironmentStructureExchangeK::EnvironmentStructureExchangeK() :
  k_(3) {}

EnvironmentStructureExchangeK::~EnvironmentStructureExchangeK() {}

void EnvironmentStructureExchangeK::setK(int newK) {
  k_ = newK;
}

std::shared_ptr<AlgorithmGreedyKMeans> EnvironmentStructureExchangeK::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exhange one service point for a random client point that doesn't have a
// service point on the same location
void EnvironmentStructureExchangeK::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;

  auto bestSolution = solution;
  bool hasImproved;
  do {
    hasImproved = false;

    /**
     * Choose k different centroids. Choose k different clients. Substitute.
     */

    std::vector<PointCluster> clients = bestSolution->getClients();
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

    // centroid amount may be smaller than k_
    const int kExchangeAmount = nonServicePoints.size() >= k_ ? k_ : nonServicePoints.size();

    // select different services
    std::vector<int> chosenServices;
    for (int i = 0; i < kExchangeAmount; ++i) {
      srand(time(NULL));
      int randomIndex = rand() % services.size();
      while (std::find(chosenServices.begin(), chosenServices.end(), randomIndex) !=
          chosenServices.end()) {

        srand(time(NULL));
        randomIndex = rand() % services.size();
      }

      chosenServices.push_back(randomIndex);
    }

    // select different clients that are not service
    std::vector<int> newServices;
    for (int i = 0; i < kExchangeAmount; ++i) {
      srand(time(NULL));
      int randomIndex = rand() % nonServicePoints.size();
      while (std::find(newServices.begin(), newServices.end(), randomIndex) !=
          newServices.end()) {

        srand(time(NULL));
        randomIndex = rand() % nonServicePoints.size();
      }

      newServices.push_back(randomIndex);
    }

    // substitute
    for (int i = 0; i < kExchangeAmount; ++i) {
      services[chosenServices[i]] = nonServicePoints[newServices[i]];
    }
    
    auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(clients, services);
    greedyAlgorithm.execute(ptrKMeans);

    if (ptrKMeans->objectiveFunction() < bestSolution->objectiveFunction()) {
      bestSolution = ptrKMeans;
      hasImproved = true;
    }
  } while (hasImproved);

  ptrBestSolution_ = bestSolution;
}
