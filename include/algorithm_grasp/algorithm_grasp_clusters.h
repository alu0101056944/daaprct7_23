#ifndef ALGORITHM_GRASP_CLUSTERS_H
#define ALGORITHM_GRASP_CLUSTERS_H

#include "i_algorithm_grasp.h"

#include "../point/point_basic.h"

#include "../algorithm_greedy/framework_greedy.h"
#include "../algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../environment_structure/i_environment_structure.h"

class AlgorithmGRASPClusters : public IAlgorithmGRASP {
public:
  AlgorithmGRASPClusters(std::vector<PointBasic> points, int k, int sizeOfLRC,
      int msBeforeStop);
  AlgorithmGRASPClusters(std::vector<PointBasic> points, int sizeOfLRC,
      int msBeforeStop);

  ~AlgorithmGRASPClusters();

  void setEnvironmentStructure(std::shared_ptr<IEnvironmentStructure> ptrStructure);

  /**
   * Add elements that must be on a solution. Ease the build process a bit.
   */
  virtual void preprocess();

  virtual bool build();

  /**
   * Improve the solution found on the build phase. Can use VNS, or Tabú search,
   *  or even local searches.
  */
  virtual bool postprocess();
  virtual void update();
  virtual bool stopCriteria();

  void print();
private:
  FrameworkGreedy greedyAlgorithm_; // for build()
  std::shared_ptr<AlgorithmGreedyClustersLRC> ptrSolution_;
  std::shared_ptr<AlgorithmGreedyClustersLRC> ptrBestSolution_;

  std::shared_ptr<IEnvironmentStructure> ptrStructure_;

  std::vector<PointBasic> points_;
  int k_;
  int sizeOfLRC_;

  int msBeforeStop_;
  int startTime_; 

  std::vector<PointCluster> nextBestCandidates_;
};

#endif
