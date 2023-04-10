#ifndef ALGORITHM_GREEDY_CLUSTERS_H
#define ALGORITHM_GREEDY_CLUSTERS_H

#include "i_algorithm_greedy.h"
#include "framework_greedy.h"
#include "../point/point_basic.h"
#include "../point/point_cluster.h"
#include "../heuristics/i_heuristic.h"

class AlgorithmGreedyClusters : public IAlgorithmGreedy {
public:
  AlgorithmGreedyClusters(std::vector<PointBasic> points, int k);
  AlgorithmGreedyClusters(std::vector<PointBasic> points);

  ~AlgorithmGreedyClusters();
  
  // getters and setters
  std::vector<PointCluster> getServices();
  std::vector<PointCluster> getClients();
  std::vector<PointCluster> getCandidates();
  void setCandidates(std::vector<PointCluster> candidates);
  int getIndexOfFarthest();
  void setIndexOfFarthest(int newIndex);
  std::shared_ptr<IHeuristic> getHeuristic();
  void setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic);

  // greedy functions
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
  PointCluster pointFarthest_;

  FrameworkGreedy greedyAlgorithm_; // for applying KMeans in addCandidate()

  float sse_;
  float ssePrevious_;

  // print() variables:
  const int currentID_;
  int executionIterationNumber_;

  std::vector<PointCluster> pointsClient_;
  std::vector<PointCluster> pointsService_;
  std::vector<PointCluster> pointsCandidate_; // == pointsClient_ if validCandidate() found
  
  std::shared_ptr<IHeuristic> ptrHeuristic_;


  /**
   * mathematical set of points from pointsClient_ by picking randomly
   */
  std::vector<int> generateRandomIndexList(int size);
};

#endif
