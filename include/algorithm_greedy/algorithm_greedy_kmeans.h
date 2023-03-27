#ifndef ALGORITHM_GREEDY_KMEANS_H
#define ALGORITHM_GREEDY_KMEANS_H

#include <unordered_map>

#include "i_algorithm_greedy.h"
#include "../heuristics/i_heuristic.h"
#include "../point/point_basic.h"
#include "../../include/point/point_cluster.h"

class AlgorithmGreedyKMeans : IAlgorithmGreedy {
public:
  AlgorithmGreedyKMeans(std::vector<PointBasic> points, int k);
  ~AlgorithmGreedyKMeans();
  
  void setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic);

  virtual void preprocess();
  virtual bool hasCandidates();
  virtual bool isAtSolution();
  virtual void selectBestCandidate();
  virtual bool validCandidate();
  virtual void addCandidate();

  void print();
private:
  int k_;
  int amountOfReassignedPoints_; // meant for isAtSolution()

  std::vector<PointCluster> pointsClient_;
  std::vector<PointCluster> pointsService_;
  
  std::shared_ptr<IHeuristic> ptrHeuristic_;

  /**
   * Used on preprocess() to generate a random list of index without duplicates.
   */
  std::vector<int> generateRandomIndex(int size);
};

#endif
