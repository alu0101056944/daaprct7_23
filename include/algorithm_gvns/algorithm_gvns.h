
#ifndef ALGORITHM_GVNS_H
#define ALGORITHM_GVNS_H

#include <memory>

#include "../point/point_basic.h"

#include "../algorithm_greedy/framework_greedy.h"
#include "../algorithm_greedy/algorithm_greedy_kmeans.h"

#include "../environment_structure/i_environment_structure.h"

class AlgorithmGVNS {
public:
  AlgorithmGVNS(std::vector<PointBasic> points, int k, int sizeOfLRC);

  ~AlgorithmGVNS();

  void addToLocalSearch(std::shared_ptr<IEnvironmentStructure> structure);
  void addToShaking(std::shared_ptr<IEnvironmentStructure> structure);

  void execute();
  void executeAndprint();

  static int ID;
private:
  FrameworkGreedy greedyAlgorithm_;

  std::vector<std::shared_ptr<IEnvironmentStructure>> localSearches_;
  std::vector<std::shared_ptr<IEnvironmentStructure>> shakes_;

  std::vector<PointBasic> points_;
  int k_;
  int sizeOfLRC_;

  bool hasImproved_;

  std::shared_ptr<AlgorithmGreedyKMeans> ptrSolution_;
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;

  // print() variables:
  const int currentID_;
  int executionIterationNumber_;

  void preprocess(); // called on execute()
};

#endif
