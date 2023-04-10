
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
  
  FrameworkGreedy frameworkGreedy;
  FrameworkGRASP frameworkGRASP;
  if (kNameOfAlgorithm.compare("grasp") == 0) {
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[3]) : 3;
    auto ptrAlgorithm = std::make_shared<AlgorithmGreedyClustersLRC>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGreedy.executeAndprint(ptrAlgorithm);
  } else if (kNameOfAlgorithm.compare("final") == 0) {
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[3]) : 3;
    auto ptrAlgorithm = std::make_shared<AlgorithmGRASPClusters>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGRASP.executeAndprint(ptrAlgorithm);
  } else {
    auto ptrAlgorithm =
        std::shared_ptr<AlgorithmGreedyClusters>(
          new AlgorithmGreedyClusters(points, kAmountOfClusters));
    frameworkGreedy.executeAndprint(ptrAlgorithm);
  }
}
  
