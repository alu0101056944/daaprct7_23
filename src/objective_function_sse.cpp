#include "../include/objective_function_sse.h"

#include <cmath>
#include <iostream>

#include "../include/similarity/similarity_euclidean.h"

ObjectiveFunctionSSE::ObjectiveFunctionSSE() {}
ObjectiveFunctionSSE::~ObjectiveFunctionSSE() {}

float ObjectiveFunctionSSE::get(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService, float factor) {
  // use euclidean distance
  SimilarityEuclidean euclidean;

  // for each centroid check all points and sum if belongs.
  float sse = 0;
  for (int i = 0; i < pointsService.size(); ++i) {

    float clusterTotal = 0;
    for (auto& point : pointsClient) {
      if (point.getCluster().getComponents() == pointsService[i].getComponents()) {
        clusterTotal += std::pow(euclidean.similarity(pointsService[i], point), 2);
      }
    }

    sse += clusterTotal;
  }
  return sse + factor * pointsService.size();
}
