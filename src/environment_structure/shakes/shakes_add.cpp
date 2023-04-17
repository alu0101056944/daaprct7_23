#include "../../../include/environment_structure/shakes/shakes_add.h"

#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../../include/algorithm_greedy/framework_greedy.h"

ShakesAdd::ShakesAdd() {}

ShakesAdd::~ShakesAdd() {}

std::shared_ptr<AlgorithmGreedyKMeans> ShakesAdd::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exchange one service point to one other position
void ShakesAdd::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;
  
  auto services = solution->getServices();
  auto clients = solution->getClients();

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

  // choose random non service point
  srand(time(NULL));
  const int kRandomIndex = rand() % nonServicePoints.size();
  services.push_back(nonServicePoints[kRandomIndex]);
  
  // apply kmeans and save
  auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
      solution->getClients(), services);
  greedyAlgorithm.execute(ptrKMeans);
  ptrBestSolution_ = ptrKMeans;
}
