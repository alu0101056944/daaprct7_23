#ifndef ALGORITHM_GREEDY_CLUSTERS_LRC_H
#define ALGORITHM_GREEDY_CLUSTERS_LRC_H

#include "i_algorithm_greedy.h"
#include "algorithm_greedy_clusters.h"
#include "../heuristics/i_heuristic.h"
#include "../point/point_basic.h"
#include "../point/point_cluster.h"

class AlgorithmGreedyClustersLRC : public IAlgorithmGreedy {
public:
  AlgorithmGreedyClustersLRC(std::vector<PointBasic> points, int k, int sizeOfLRC);

  ~AlgorithmGreedyClustersLRC();
  
  std::vector<PointCluster> getServices();
  std::vector<PointCluster> getClients();
  void setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic);

  virtual void preprocess();
  virtual bool hasCandidates();
  virtual bool isAtSolution();
  virtual void selectBestCandidate();
  virtual bool validCandidate();
  virtual void addCandidate();
  virtual void print();
  float objectiveFunction();
  float getSSE();

  static int ID;
private:
  AlgorithmGreedyClusters greedy_;
  int sizeOfLRC_;
};

#endif

