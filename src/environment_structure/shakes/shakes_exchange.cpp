#include "../../../include/environment_structure/shakes/shakes_exchange.h"

#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../../include/algorithm_greedy/algorithm_greedy_kmeans.h"
#include "../../../include/algorithm_greedy/framework_greedy.h"

ShakesExchange::ShakesExchange() {}

ShakesExchange::~ShakesExchange() {}

std::shared_ptr<AlgorithmGreedyKMeans> ShakesExchange::getBestSolution() {
  assert(ptrBestSolution_ != nullptr);
  return ptrBestSolution_;  
}

// exchange one service point to one other position
void ShakesExchange::execute(std::shared_ptr<AlgorithmGreedyKMeans> solution) {
  FrameworkGreedy greedyAlgorithm;
  
  auto services = solution->getServices();
  auto candidates = solution->getClients();

  // choose random service
  srand(time(NULL));
  const int kRandomIndexService = rand() % services.size();

  // choose random candidate
  srand(time(NULL));
  const int kRandomIndexCandidate = rand() % candidates.size();

  // substitute
  services[kRandomIndexService] = candidates[kRandomIndexCandidate];
  
  // apply kmeans and save
  auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
      solution->getClients(), services);
  greedyAlgorithm.execute(ptrKMeans);
  ptrBestSolution_ = ptrKMeans;
}
