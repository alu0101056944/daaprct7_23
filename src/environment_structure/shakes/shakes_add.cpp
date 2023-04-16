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
  auto candidates = solution->getClients();

  // choose random candidate
  srand(time(NULL));
  const int kRandomIndex = rand() % candidates.size();
  services.push_back(candidates[kRandomIndex]);
  
  // apply kmeans and save
  auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
      solution->getClients(), services);
  greedyAlgorithm.execute(ptrKMeans);
  ptrBestSolution_ = ptrKMeans;
}
