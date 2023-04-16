#ifndef ALGORITHM_GRASP_CLUSTERS_H
#define ALGORITHM_GRASP_CLUSTERS_H

#include <chrono>

#include "i_algorithm_grasp.h"

#include "../point/point_basic.h"

#include "../algorithm_greedy/framework_greedy.h"
#include "../algorithm_greedy/algorithm_greedy_kmeans.h"

#include "../environment_structure/i_environment_structure.h"

class AlgorithmGRASPClusters : public IAlgorithmGRASP {
public:
  AlgorithmGRASPClusters(std::vector<PointBasic> points, int k, int sizeOfLRC);

  ~AlgorithmGRASPClusters();

  void setEnvironmentStructure(std::shared_ptr<IEnvironmentStructure> ptrStructure);

  /**
   * Add elements that must be on a solution. Ease the build process a bit.
   */
  virtual void preprocess();

  virtual void build();

  /**
   * Improve the solution found on the build phase. Can use VNS, or Tabú search,
   *  or even local searches.
  */
  virtual void postprocess();
  virtual void update();
  virtual bool stopCriteria();

  virtual void print();

  static int ID;
private:
  FrameworkGreedy greedyAlgorithm_; // for build()
  std::shared_ptr<AlgorithmGreedyKMeans> ptrSolution_;
  std::shared_ptr<AlgorithmGreedyKMeans> ptrBestSolution_;

  std::shared_ptr<IEnvironmentStructure> ptrStructure_;

  std::vector<PointBasic> points_;
  int k_;
  int sizeOfLRC_;

  bool hasImproved_;

  // print() variables:
  const int currentID_;
  int executionIterationNumber_;
};

#endif
