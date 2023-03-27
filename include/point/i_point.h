#ifndef I_POINT_H
#define I_POINT_H

#include <type_traits>
#include <variant>
#include <vector>
#include <memory>

class IPoint {
public:
  virtual ~IPoint() {}

  virtual std::vector<std::variant<float, std::string>> getComponents() = 0;

  virtual void print() = 0;
private:
};

#endif