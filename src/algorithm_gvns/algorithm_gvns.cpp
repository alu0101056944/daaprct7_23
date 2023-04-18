#include "../../include/algorithm_gvns/algorithm_gvns.h"

#include <chrono>
#include <iostream>

#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../../include/environment_structure/environment_structure_exchange.h"
#include "../../include/environment_structure/environment_structure_delete.h"
#include "../../include/environment_structure/environment_structure_add.h"

#include "../../include/environment_structure/shakes/shakes_add.h"
#include "../../include/environment_structure/shakes/shakes_delete.h"
#include "../../include/environment_structure/shakes/shakes_exchange.h"

int AlgorithmGVNS::ID = 0;

AlgorithmGVNS::AlgorithmGVNS(std::vector<PointBasic> points, int k, int sizeOfLRC) :
      points_(points),
      k_(k),
      sizeOfLRC_(sizeOfLRC),
      currentID_(++ID),
      executionIterationNumber_(0),
      hasImproved_(true) {
  addToShaking(std::make_shared<ShakesExchange>());
  addToShaking(std::make_shared<ShakesDelete>());
  addToShaking(std::make_shared<ShakesAdd>());
  addToLocalSearch(std::make_shared<EnvironmentStructureExchange>()); // Antes EnvironmentStructureExchangeSingle
  addToLocalSearch(std::make_shared<EnvironmentStructureDelete>()); // Antes EnvironmentStructureDeleteSingle
  addToLocalSearch(std::make_shared<EnvironmentStructureAdd>()); // Antes EnvironmentStructureAddSingle
}

AlgorithmGVNS::~AlgorithmGVNS() {}

void AlgorithmGVNS::addToLocalSearch(std::shared_ptr<IEnvironmentStructure> structure) {
  localSearches_.push_back(structure);
}

void AlgorithmGVNS::addToShaking(std::shared_ptr<IEnvironmentStructure> structure) {
  shakes_.push_back(structure);
}

// build initial solution
void AlgorithmGVNS::preprocess() {
  auto builtSolution = std::make_shared<AlgorithmGreedyClustersLRC>(points_, k_, sizeOfLRC_);
  greedyAlgorithm_.execute(builtSolution);

  ptrBestSolution_ = std::make_shared<AlgorithmGreedyKMeans>(builtSolution->getClients(),
    builtSolution->getServices());
  greedyAlgorithm_.execute(ptrBestSolution_);

  int iterationAmount = 0;
  bool hasImprovedLocal = true;
  while (hasImprovedLocal || iterationAmount < 30) {
    ++iterationAmount;
    hasImprovedLocal = false;
    for (int i = 0; i < shakes_.size(); ++i) {
      shakes_[i]->execute(ptrBestSolution_);
      auto shakenSolution = shakes_[i]->getBestSolution();
      if (shakenSolution->getSSE() < ptrBestSolution_->getSSE()) {
        ptrBestSolution_ = shakenSolution;
        hasImprovedLocal = true;
        i = 0;
      }
    }
  }
}

// not full local search, but rather a "single step" search.
void AlgorithmGVNS::execute() {
  preprocess();
  while (hasImproved_ || executionIterationNumber_ < 10) {
    ++executionIterationNumber_;
    hasImproved_ = false;

    // 1 shakes then ALL local searches
    for (int i = 0; i < shakes_.size(); ++i) {
      shakes_[i]->execute(ptrBestSolution_);
      auto shakenSolution = shakes_[i]->getBestSolution();

      auto bestLocal = shakenSolution;
      for (int j = 0; j < localSearches_.size(); ++j) {
        localSearches_[j]->execute(bestLocal);
        auto localSolution = localSearches_[j]->getBestSolution();
        if (localSolution->getSSE() < bestLocal->getSSE()) {
          bestLocal = localSolution;
          j = 0;
        }
      }

      if (bestLocal->getSSE() < ptrBestSolution_->getSSE()) {
        ptrBestSolution_ = bestLocal;
        hasImproved_ = true;
        i = 0;
      }
    }
  }
}

void AlgorithmGVNS::executeAndprint() {
  int cpuTime = 0;
  std::cout << "Problema\tm\t\tK\t\tkmaxVNS\t\tEjecución\t\tSSE\t\t|LRC|\t\tCPU" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  preprocess();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  cpuTime += duration.count() / 100000;
  
  std::cout << currentID_ << "\t\t";
  std::cout << points_.size() << "\t\t";
  std::cout << ptrBestSolution_->getServices().size() << "\t\t";
  std::cout << shakes_.size() << "\t\t";
  std::cout << executionIterationNumber_ << "\t\t\t";
  std::cout << ptrBestSolution_->getSSE() << "\t\t";
  std::cout << sizeOfLRC_ << "\t\t";
  std::cout << cpuTime << "\t\t" << std::endl;

  while (hasImproved_ || executionIterationNumber_ < 10) {
    ++executionIterationNumber_;
    hasImproved_ = false;
    auto start = std::chrono::high_resolution_clock::now();

    // 1 shakes then ALL local searches
    for (int i = 0; i < shakes_.size(); ++i) {
      shakes_[i]->execute(ptrBestSolution_);
      auto shakenSolution = shakes_[i]->getBestSolution();

      auto bestLocal = shakenSolution;
      for (int j = 0; j < localSearches_.size(); ++j) {
        localSearches_[j]->execute(bestLocal);
        auto localSolution = localSearches_[j]->getBestSolution();
        if (localSolution->getSSE() < bestLocal->getSSE()) {
          bestLocal = localSolution;
          j = 0;
        }
      }

      if (bestLocal->getSSE() < ptrBestSolution_->getSSE()) {
        ptrBestSolution_ = bestLocal;
        hasImproved_ = true;
        i = 0;
      }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cpuTime += duration.count() / 100000;

    std::cout << currentID_ << "\t\t";
    std::cout << points_.size() << "\t\t";
    std::cout << ptrBestSolution_->getServices().size() << "\t\t";
    std::cout << shakes_.size() << "\t\t";
    std::cout << executionIterationNumber_ << "\t\t\t";
    std::cout << ptrBestSolution_->getSSE() << "\t\t";
    std::cout << sizeOfLRC_ << "\t\t";
    std::cout << cpuTime << "\t\t" << std::endl;
  }
  std::cout << std::endl;
}
