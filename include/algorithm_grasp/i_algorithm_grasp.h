#ifndef ALGORITHM_GRASP_H
#define ALGORITHM_GRASP_H

class IAlgorithmGRASP {
public:
  virtual ~IAlgorithmGRASP() {}

  virtual void preprocess() = 0;
  virtual void build() = 0;
  virtual void postprocess() = 0;
  virtual void update() = 0;
  virtual bool stopCriteria() = 0;
  virtual void print() = 0;
private:
};

#endif
