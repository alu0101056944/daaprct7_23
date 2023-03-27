#include "../../include/point/point_basic.h"

#include <iostream>

PointBasic::PointBasic(std::vector<std::variant<float, std::string>> components) :
  components_(components) {}

PointBasic::~PointBasic() {}

std::vector<std::variant<float, std::string>> PointBasic::getComponents() {
  return components_;
}

void PointBasic::print() {
  std::cout << "(";
  for (int i = 0; i < components_.size(); ++i) {
    if (std::holds_alternative<std::string>(components_[i])) {
      std::cout << std::get<std::string>(components_[i]);
    } else {
      std::cout << std::get<float>(components_[i]);
    }
    if (i < components_.size() - 1) {
      std::cout << " ";
    }
  }
  std::cout << ")";
}
