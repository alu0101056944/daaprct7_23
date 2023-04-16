#include "../include/objective_function_sse.h"

#include <cmath>
#include <iostream>

#include "../include/similarity/similarity_euclidean.h"

ObjectiveFunctionSSE::ObjectiveFunctionSSE() {}
ObjectiveFunctionSSE::~ObjectiveFunctionSSE() {}

float ObjectiveFunctionSSE::get(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) {
  std::cout << "get() call!" << std::endl << std::endl;
  // use euclidean distance
  SimilarityEuclidean euclidean;

  // for each centroid check all points and sum if belongs.
  float total = 0;
  for (int i = 0; i < pointsService.size(); ++i) {

    std::cout << "Point service: ";
    for (auto& component : pointsService[i].getComponents()) {
      std::cout << std::get<float>(component) << " ";
    }
    std::cout << std::endl;

    float clusterTotal = 0;
    for (auto& point : pointsClient) {

      std::cout << "Point client: ";
      for (auto& component : point.getComponents()) {
        std::cout << std::get<float>(component) << " ";
      }
      std::cout << std::endl;

      if (point.getCluster().getComponents() == pointsService[i].getComponents()) {
        std::cout << "Point of cluster found, distance:";
        clusterTotal += std::pow(euclidean.similarity(pointsService[i], point), 2);
        std::cout << clusterTotal << std::endl;
      }
    }

    total += clusterTotal;
  }
  return total;
}
