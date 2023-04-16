#include "../../include/algorithm_gvns/algorithm_gvns.h"

#include <chrono>
#include <iostream>

#include "../../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../../include/environment_structure/environment_structure_exchange.h"
#include "../../include/environment_structure/environment_structure_exchange_k.h"
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
  addToLocalSearch(std::make_shared<EnvironmentStructureExchange>());
  addToLocalSearch(std::make_shared<EnvironmentStructureAdd>());
  addToLocalSearch(std::make_shared<EnvironmentStructureDelete>());
  addToLocalSearch(std::make_shared<EnvironmentStructureExchangeK>());
  addToShaking(std::make_shared<ShakesAdd>());
  addToShaking(std::make_shared<ShakesExchange>());
  addToShaking(std::make_shared<ShakesDelete>());
}

AlgorithmGVNS::~AlgorithmGVNS() {}

void AlgorithmGVNS::addToLocalSearch(std::shared_ptr<IEnvironmentStructure> structure) {
  localSearches_.push_back(structure);
}

void AlgorithmGVNS::addToShaking(std::shared_ptr<IEnvironmentStructure> structure) {
  shakes_.push_back(structure);
}

void AlgorithmGVNS::preprocess() {
  auto builtSolution = std::make_shared<AlgorithmGreedyClustersLRC>(points_, k_, sizeOfLRC_);
  greedyAlgorithm_.execute(builtSolution);

  ptrSolution_ = std::make_shared<AlgorithmGreedyKMeans>(builtSolution->getClients(),
    builtSolution->getServices());

  if (ptrBestSolution_ == nullptr) { // to allow print()
    ptrBestSolution_ = ptrSolution_;
  }
}

void AlgorithmGVNS::execute() {
  preprocess();
  while (hasImproved_ || executionIterationNumber_ < 30) {
    ++executionIterationNumber_;
    hasImproved_ = false;
    for (int i = 0; i < shakes_.size(); ++i) {
      shakes_[i]->execute(ptrSolution_);
      auto shakenSolution = shakes_[i]->getBestSolution();

      std::shared_ptr<AlgorithmGreedyKMeans> bestLocal;
      for (int j = 0; j < localSearches_.size(); ++j) {
        localSearches_[j]->execute(shakenSolution);
        auto localSolution = localSearches_[j]->getBestSolution();
        if (bestLocal == nullptr ||
            localSolution->objectiveFunction() < bestLocal->objectiveFunction()) {
          bestLocal = localSolution;
        }
      }

      if (bestLocal->objectiveFunction() < ptrBestSolution_->objectiveFunction()) {
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
  std::cout << ptrBestSolution_->objectiveFunction() << "\t\t";
  std::cout << sizeOfLRC_ << "\t\t";
  std::cout << cpuTime << "\t\t" << std::endl;

  while (hasImproved_ || executionIterationNumber_ < 30) {
    ++executionIterationNumber_;
    hasImproved_ = false;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < shakes_.size(); ++i) {
      shakes_[i]->execute(ptrSolution_);
      auto shakenSolution = shakes_[i]->getBestSolution();

      std::shared_ptr<AlgorithmGreedyKMeans> bestLocal;
      for (int j = 0; j < localSearches_.size(); ++j) {
        localSearches_[j]->execute(shakenSolution);
        auto localSolution = localSearches_[j]->getBestSolution();
        if (bestLocal == nullptr ||
            localSolution->objectiveFunction() < bestLocal->objectiveFunction()) {
          bestLocal = localSolution;
        }
      }

      if (bestLocal->objectiveFunction() < ptrBestSolution_->objectiveFunction()) {
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
    std::cout << ptrBestSolution_->objectiveFunction() << "\t\t";
    std::cout << sizeOfLRC_ << "\t\t";
    std::cout << cpuTime << "\t\t" << std::endl;
  }
  std::cout << std::endl;
}
