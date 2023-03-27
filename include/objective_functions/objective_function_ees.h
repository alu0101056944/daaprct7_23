#ifndef OBJECTIVE_FUNCTION_EES_H
#define OBJECTIVE_FUNCTION_EES_H

#include <type_traits>
#include "i_objective_function.h"

template<typename T>
class ObjectiveFunctionEES : public IObjectiveFunction<T> {
public:
  ObjectiveFunctionEES();
  ~ObjectiveFunctionEES();

  virtual T get();
private:
};

#endif
