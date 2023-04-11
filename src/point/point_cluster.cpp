#include "../../include/point/point_cluster.h"

#include <iostream>

PointCluster::PointCluster(std::vector<std::variant<float, std::string>> components) :
  pointBasic_(components),
  cluster_(std::vector<std::variant<float, std::string>>()) {}

PointCluster::PointCluster(PointBasic pointBasic) :
    pointBasic_(pointBasic),
    cluster_(std::vector<std::variant<float, std::string>>()) {}

PointCluster::~PointCluster() {}

PointBasic PointCluster::getCluster() {
  return cluster_;
}

void PointCluster::setCluster(PointBasic newCluster) {
  cluster_ = newCluster;
}

PointBasic PointCluster::getBasic()  {
  return pointBasic_;
}

std::vector<std::variant<float, std::string>> PointCluster::getComponents() {
  return pointBasic_.getComponents();
}

void PointCluster::print() {
  pointBasic_.print();
  std::cout << "[";
  cluster_.print();
  std::cout << "]";
}
