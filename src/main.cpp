
#include <iostream>
#include <vector>
#include <variant>

#include "../include/instance_filereader.h"
#include "../include/point/point_basic.h"
#include "../include/algorithm_greedy/framework_greedy.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../include/point/point_cluster.h"

int main (int argv, char** argc) {
  if (argv < 5) {
    std::cout << "Insufficient amount of arguments. Expected 5" << std::endl;
    std::cout << "<executable> <path> <nameOfAlgorithm> <amountOfClusters>";
    std::cout << "<deltaSSE>" << std::endl;
    return -1;
  }

  InstanceFileReader reader(argc[1]);
  std::vector<PointBasic> points = reader.getPoints();

  const std::string kNameOfAlgorithm = argc[2];
  const int kAmountOfClusters = std::stoi(argc[3]);
  const int kdeltaSSE = std::stoi(argc[4]);
  
  FrameworkGreedy framework;
  if (kNameOfAlgorithm.compare("grasp") == 0) {
    const int kSizeOfLRC = argv > 5 ? std::stoi(argc[5]) : 2;
    auto ptrAlgorithm =
        std::shared_ptr<AlgorithmGreedyClustersLRC>(
          new AlgorithmGreedyClustersLRC(points, kAmountOfClusters, kdeltaSSE,
            kSizeOfLRC));
    framework.executeAndprint(ptrAlgorithm);
  } else {
    auto ptrAlgorithm =
        std::shared_ptr<AlgorithmGreedyClusters>(
          new AlgorithmGreedyClusters(points, kAmountOfClusters, kdeltaSSE));
    framework.executeAndprint(ptrAlgorithm);
  }
}
  
