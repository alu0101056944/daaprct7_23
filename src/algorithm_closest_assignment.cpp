#include "../include/algorithm_closest_assignment.h"


AlgorithmClosestAssignment::AlgorithmClosestAssignment() :
    ptrHeuristic_(new HeuristicKMeansLeast()) {}
AlgorithmClosestAssignment::~AlgorithmClosestAssignment() {}

std::vector<PointCluster> AlgorithmClosestAssignment::getClients() {
  return clients_;

}

std::vector<PointCluster> AlgorithmClosestAssignment::getServices() {
  return services_;
}

void AlgorithmClosestAssignment::execute(std::vector<PointCluster> clients,
      std::vector<PointCluster> services) {
  for (auto& client : clients) {
    const int kIndexOfClosest = ptrHeuristic_->choose(clients, services);
    client.setCluster(services[kIndexOfClosest].getBasic());
  }
  clients_ = clients;
  services_ = services;
}
