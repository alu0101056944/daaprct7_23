#ifndef ALGORITHM_GREEDY_KMEANS_H
#define ALGORITHM_GREEDY_KMEANS_H

#include <unordered_map>

#include "i_algorithm_greedy.h"
#include "../heuristics/i_heuristic.h"
#include "../point/point_basic.h"
#include "../../include/point/point_cluster.h"

class AlgorithmGreedyKMeans : public IAlgorithmGreedy {
public:
  AlgorithmGreedyKMeans(std::vector<PointBasic> points, int k, float deltaSSE);
  AlgorithmGreedyKMeans(std::vector<PointBasic> points, float deltaSSE);

  ~AlgorithmGreedyKMeans();
  
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
  int k_;

  int indexOfFarthest_;

  float deltaSSE_;
  float sse_;
  float ssePrevious_;

  // print() variables:
  const int currentID_;
  int executionIterationNumber_;

  std::vector<PointCluster> pointsClient_;
  std::vector<PointCluster> pointsService_;
  std::vector<PointCluster> pointsCandidate_; // == pointsClient_ if validCandidate() found
  
  std::shared_ptr<IHeuristic> ptrHeuristic_;

  /*
   * called on addCandidate() to update services and it's clients.
  */
  void applyKMeans();

  /**
   * vector of index with unique points from pointsClient_
   */
  std::vector<int> generateRandomIndex(int size);
};

#endif

