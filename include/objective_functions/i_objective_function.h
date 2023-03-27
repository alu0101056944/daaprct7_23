#ifndef OBJECTIVE_FUNCTION_H
#define OBJECTIVE_FUNCTION_H

template<typename T>
class IObjectiveFunction {
public:
  virtual ~IObjectiveFunction() {}

  virtual T get() = 0;
private:
};

#endif
