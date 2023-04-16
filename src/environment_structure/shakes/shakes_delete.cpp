#include "../../../include/environment_structure/shakes/shakes_delete.h"

#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../../include/algorithm_greedy/framework_greedy.h"
#include "../../../include/heuristics/heuristic_kmeans_max.h"

ShakesDelete::ShakesDelete() {}

ShakesDelete::~ShakesDelete() {}

std::shared_ptr<AlgorithmGreedyKMeans> ShakesDelete::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exchange one service point to one other position
void ShakesDelete::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;
  
  auto services = solution->getServices();

  // choose random service
  srand(time(NULL));
  const int kRandomIndex = rand() % services.size();
  services.erase(services.begin() + kRandomIndex);
  
  // apply kmeans and save
  auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
      solution->getClients(), services);
  greedyAlgorithm.execute(ptrKMeans);
  ptrBestSolution_ = ptrKMeans;
}
