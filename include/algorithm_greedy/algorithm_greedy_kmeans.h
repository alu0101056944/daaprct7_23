#ifndef ALGORITHM_GREEDY_KMEANS_H
#define ALGORITHM_GREEDY_KMEANS_H

#include "i_algorithm_greedy.h"
#include "../heuristics/i_heuristic.h"
#include "../point/point_basic.h"
#include "../point/point_cluster.h"

class AlgorithmGreedyKMeans : public IAlgorithmGreedy {
public:
  AlgorithmGreedyKMeans(std::vector<PointBasic> pointsClient,
      std::vector<PointBasic> pointsService);
  AlgorithmGreedyKMeans(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService);

  ~AlgorithmGreedyKMeans();
  
  // getters and setters
  void setHeuristic(std::shared_ptr<IHeuristic> ptrHeuristic);
  std::vector<PointCluster> getServices();
  std::vector<PointCluster> getClients();

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
  int amountOfReassignedPoints_;
  int amountOfProcessedPoints_; // for hasCandidates()
  
  // print() variables:
  const int currentID_;
  int executionIterationNumber_;

  std::vector<PointCluster> pointsClient_;
  std::vector<PointCluster> pointsService_;
  
  std::shared_ptr<IHeuristic> ptrHeuristic_;
};

#endif
