#include "../include/objective_function_sse.h"

#include "../include/similarity/similarity_euclidean.h"

ObjectiveFunctionSSE::ObjectiveFunctionSSE() {}
ObjectiveFunctionSSE::~ObjectiveFunctionSSE() {}

float ObjectiveFunctionSSE::get(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService) {
  SimilarityEuclidean euclidean;
  float total = 0;
  for (int i = 0; i < pointsService.size(); ++i) {
    float clusterTotal = 0;
    for (auto& point : pointsClient) {
      if (point.getCluster() == i) {
        clusterTotal += euclidean.similarity(pointsService[i], point);
      }
    }
    total += clusterTotal;
  }
  return total;
}
