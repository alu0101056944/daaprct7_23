#ifndef ALGORITHM_GRASP_KMEANS_H
#define ALGORITHM_GRASP_KMEANS_H

#include "i_algorithm_grasp.h"

class AlgorithmGRASPKMeans : public IAlgorithmGRASP {
public:
  AlgorithmGRASPKMeans();
  ~AlgorithmGRASPKMeans();

  virtual void preprocess();
  virtual bool build();
  virtual bool postprocess();
  virtual void update();
  virtual bool stopCriteria();
private:
};

#endif
