#ifndef INSTANCE_FILEREADER_H
#define INSTANCE_FILEREADER_H

#include <vector>
#include <string>

#include "point/point_basic.h"

class InstanceFileReader {
public:
  InstanceFileReader(std::string filePath);
  ~InstanceFileReader();

  std::vector<PointBasic> getPoints();
private:
  std::vector<PointBasic> points_;
};

#endif
