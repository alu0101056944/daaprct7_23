#include "../../include/point/point_cluster.h"

#include <iostream>

PointCluster::PointCluster(std::vector<std::variant<float, std::string>> components) :
  pointBasic_(components), clusterIndex_(-1) {}

PointCluster::PointCluster(PointBasic pointBasic) : pointBasic_(pointBasic) {}

PointCluster::~PointCluster() {}

int PointCluster::getCluster() {
  return clusterIndex_;  
}

void PointCluster::setCluster(int clusterIndex) {
  clusterIndex_ = clusterIndex;
}

std::vector<std::variant<float, std::string>> PointCluster::getComponents() {
  return pointBasic_.getComponents();
}

void PointCluster::print() {
  pointBasic_.print();
  std::cout << "[" << clusterIndex_ << "] ";
}
