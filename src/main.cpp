
#include <iostream>

#include "../include/instance_filereader.h"
#include "../include/point/point_basic.h"

int main (int argv, char** argc) {
  if (argv < 2) {
    std::cout << "Insufficient amount of arguments. Expected 2" << std::endl;
    return -1;
  }

  InstanceFileReader reader(argc[1]);
  std::vector<PointBasic> points = reader.getPoints();
  for (auto& point : points) {
    point.print();
  }
}
