#ifndef POINT_CLUSTER_H
#define POINT_CLUSTER_H

#include <vector>
#include <variant>

#include "i_point.h"
#include "point_basic.h"

class PointCluster : public IPoint {
public:
  PointCluster(std::vector<std::variant<float, std::string>> components);
  PointCluster(PointBasic pointBasic);

  ~PointCluster();

  int getCluster();
  void setCluster(int clusterIndex);

  virtual std::vector<std::variant<float, std::string>> getComponents();

  virtual void print();
private:
  PointBasic pointBasic_;

  int clusterIndex_;
};

#endif
