#ifndef BASIC_POINT_H
#define BASIC_POINT_H

#include <vector>
#include <variant>
#include <string>
#include <initializer_list>

#include "i_point.h"

class PointBasic : public IPoint {
public:
  PointBasic(std::vector<std::variant<float, std::string>> components);
  ~PointBasic();

  virtual std::vector<std::variant<float, std::string>> getComponents();

  virtual void print();
private:
  std::vector<std::variant<float, std::string>> components_;
};

#endif
