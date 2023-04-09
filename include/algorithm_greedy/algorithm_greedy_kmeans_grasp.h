#ifndef ALGORITHM_GREEDY_KMEANS_GRASP_H
#define ALGORITHM_GREEDY_KMEANS_GRASP_H

#include "i_algorithm_greedy.h"
#include "algorithm_greedy_clusters.h"
#include "../heuristics/i_heuristic.h"
#include "../point/point_basic.h"
#include "../point/point_cluster.h"

class AlgorithmGreedyKMeansGRASP : public IAlgorithmGreedy {
public:
  AlgorithmGreedyKMeansGRASP(std::vector<PointBasic> points, int k, float deltaSSE,
      int sizeOfLRC);
  AlgorithmGreedyKMeansGRASP(std::vector<PointBasic> points, float deltaSSE,
      int sizeOfLRC);

  ~AlgorithmGreedyKMeansGRASP();
  
  void setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic);

  virtual void preprocess();
  virtual bool hasCandidates();
  virtual bool isAtSolution();
  virtual void selectBestCandidate();
  virtual bool validCandidate();
  virtual void addCandidate();
  virtual void print();
  float objectiveFunction();

  static int ID;
private:
  AlgorithmGreedyClusters greedy_;
  int sizeOfLRC_;
};

#endif

