#ifndef ALGORITHM_GRASP_H
#define ALGORITHM_GRASP_H

class IAlgorithmGRASP {
public:
  virtual ~IAlgorithmGRASP() {}

  virtual void preprocess() = 0;
  virtual bool build() = 0;
  virtual bool postprocess() = 0;
  virtual void update() = 0;
  virtual bool stopCriteria() = 0;
private:
};

#endif
