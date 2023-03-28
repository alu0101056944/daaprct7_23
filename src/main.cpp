
#include <iostream>
#include <vector>
#include <variant>

#include "../include/instance_filereader.h"
#include "../include/point/point_basic.h"
#include "../include/algorithm_greedy/framework_greedy.h"
#include "../include/algorithm_greedy/algorithm_greedy_kmeans.h"

#include "../include/point/point_cluster.h"

int main (int argv, char** argc) {
  if (argv < 2) {
    std::cout << "Insufficient amount of arguments. Expected 2" << std::endl;
    return -1;
  }

  InstanceFileReader reader(argc[1]);
  std::vector<PointBasic> points = reader.getPoints();

  FrameworkGreedy framework;
  auto ptrAlgorithm =
        std::shared_ptr<AlgorithmGreedyKMeans>(new AlgorithmGreedyKMeans(points, 2));
  framework.executeAndprint(ptrAlgorithm);
}
