
#include <iostream>
#include <vector>
#include <variant>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <cassert>

#include "../include/instance_filereader.h"
#include "../include/point/point_basic.h"
#include "../include/algorithm_greedy/framework_greedy.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters_lrc.h"
#include "../include/algorithm_greedy/algorithm_greedy_clusters.h"
#include "../include/algorithm_greedy/algorithm_greedy_kmeans.h"

#include "../include/algorithm_grasp/framework_grasp.h"
#include "../include/algorithm_grasp/algorithm_grasp_clusters.h"

#include "../include/environment_structure/environment_structure_delete.h"
#include "../include/environment_structure/environment_structure_exchange.h"
#include "../include/environment_structure/environment_structure_exchange_k.h"

#include "../include/point/point_cluster.h"

// Used for random kmeans setup to be able to execute kmeans on main
std::vector<int> uniqueServicePointsFrom(std::vector<PointBasic> points, int size) {
  assert(points.size() >= size);

  std::vector<int> indexSet;
  int amountToAdd = size;
  for (int i = 0; i < points.size(); ++i) {
    // attempt to add
    srand(time(NULL));
    if (rand() % 100 > 50) {
      indexSet.push_back(i);
      --amountToAdd;
      if (amountToAdd == 0) {
        break;
      }
    }
  }
  // if all attemps failed, just add from the back.
  for (int i = 0; i < amountToAdd; ++i) {
    indexSet.push_back(points.size() - 1);
    points.pop_back();
  }
  return indexSet;
}

int main (int argv, char** argc) {
  if (argv < 3) {
    std::cout << "Insufficient amount of arguments. Expected at least 3" << std::endl;
    std::cout << "<executable> <path> <nameOfAlgorithm> <amountOfClusters>";
    std::cout << std::endl;
    return -1;
  }

  // Get the points from file
  InstanceFileReader reader(argc[1]);
  std::vector<PointBasic> points = reader.getPoints();

  const std::string kNameOfAlgorithm = argc[2];

  // Set cluster amount, round up if float.
  // Because builder is not penalized. Gets the amount of clusters to build towards.
  const int kAmountOfClusters = std::stoi(argc[3]) == -1 ? std::ceil(((float)points.size()) * 0.1) : std::stoi(argc[3]);
  
  if (kNameOfAlgorithm.compare("clustersLRC") == 0) {
    FrameworkGreedy frameworkGreedy;
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[4]) : 3;

    auto ptrClustersLRC = std::make_shared<AlgorithmGreedyClustersLRC>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGreedy.executeAndprint(ptrClustersLRC);

  } else if (kNameOfAlgorithm.compare("grasp") == 0) {
    FrameworkGRASP frameworkGRASP;
    const int kSizeOfLRC = argv > 3 ? std::stoi(argc[4]) : 3;

    std::cout << "With exchange environment structure:" << std::endl;

    auto ptrGRASP = std::make_shared<AlgorithmGRASPClusters>(
        points, kAmountOfClusters, kSizeOfLRC);
    frameworkGRASP.executeAndprint(ptrGRASP);
    
    std::cout << "With delete environment structure:" << std::endl;

    auto deleteStructure = std::make_shared<EnvironmentStructureDelete>();
    ptrGRASP = std::make_shared<AlgorithmGRASPClusters>(
        points, kAmountOfClusters, kSizeOfLRC);
    ptrGRASP->setEnvironmentStructure(deleteStructure);
    frameworkGRASP.executeAndprint(ptrGRASP);

    std::cout << "With exchange K environment structure:" << std::endl;

    auto deleteExchangeK = std::make_shared<EnvironmentStructureExchangeK>();
    ptrGRASP = std::make_shared<AlgorithmGRASPClusters>(
        points, kAmountOfClusters, kSizeOfLRC);
    ptrGRASP->setEnvironmentStructure(deleteExchangeK);
    frameworkGRASP.executeAndprint(ptrGRASP);

  } else if (kNameOfAlgorithm.compare("kmeans") == 0) {
    FrameworkGreedy frameworkGreedy;

    // generate k different service points
    std::vector<int> pointsServiceIndex = uniqueServicePointsFrom(points,
        kAmountOfClusters);
    std::vector<PointBasic> pointsService;
    for (auto& index : pointsServiceIndex) {
      pointsService.push_back(points[index]);
    }

    auto ptrKMeans = std::make_shared<AlgorithmGreedyKMeans>(
      points, pointsService);
    frameworkGreedy.executeAndprint(ptrKMeans);
  } else {
    FrameworkGreedy frameworkGreedy;
    auto ptrClusters = std::make_shared<AlgorithmGreedyClusters>(
      points, kAmountOfClusters);
    frameworkGreedy.executeAndprint(ptrClusters);
  }
}
