
#include <iostream>
#include <vector>
#include <variant>

#include "../include/instance_filereader.h"
#include "../include/point/point_basic.h"
#include "../include/algorithm_greedy/framework_greedy.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"

#include "../include/algorithm_grasp/framework_grasp.h"
#include "../include/algorithm_grasp/algorithm_grasp_clusters.h"

#include "../include/point/point_cluster.h"

int main (int argv, char** argc) {
  if (argv < 3) {
    std::cout << "Insufficient amount of arguments. Expected at least 3" << std::endl;
    std::cout << "<executable> <path> <nameOfAlgorithm> <amountOfClusters>";
    std::cout << std::endl;
    return -1;
  }

  InstanceFileReader reader(argc[1]);
  std::vector<PointBasic> points = reader.getPoints();

  const std::string kNameOfAlgorithm = argc[2];
  const int kAmountOfClusters = std::stoi(argc[3]);
  
  if (kNameOfAlgorithm.compare("clustersLRC") == 0) {
    FrameworkGreedy frameworkGreedy;
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[4]) : 3;

    auto ptrClustersLRC = std::make_shared<AlgorithmGreedyClustersLRC>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGreedy.executeAndprint(ptrClustersLRC);

  } else if (kNameOfAlgorithm.compare("grasp") == 0) {
    FrameworkGRASP frameworkGRASP;
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[4]) : 3;

    auto ptrGRASP = std::make_shared<AlgorithmGRASPClusters>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGRASP.executeAndprint(ptrGRASP);

  } else {
    FrameworkGreedy frameworkGreedy;
    auto ptrClusters = std::make_shared<AlgorithmGreedyClusters>(
      points, kAmountOfClusters);
    frameworkGreedy.executeAndprint(ptrClusters);
  }
}
