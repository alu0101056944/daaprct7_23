#include "../../include/point/point_basic.h"

#include <iostream>

PointBasic::PointBasic(std::vector<std::variant<float, std::string>> components) :
  components_(components) {}

PointBasic::~PointBasic() {}

std::vector<std::variant<float, std::string>> PointBasic::getComponents() {
  return components_;
}

void PointBasic::print() {
  std::cout << "(" << std::endl;
  for (auto component : components_) {
    std::cout << std::get<std::string>(component);
    std::cout << " ";
  }
  std::cout << ")" << std::endl;
}
