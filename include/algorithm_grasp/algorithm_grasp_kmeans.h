#ifndef ALGORITHM_GRASP_KMEANS_H
#define ALGORITHM_GRASP_KMEANS_H

#include "i_algorithm_grasp.h"

class AlgorithmGRASPKMeans : public IAlgorithmGRASP {
public:
  AlgorithmGRASPKMeans();
  ~AlgorithmGRASPKMeans();

  /**
   * Add elements that must be on a solution. Ease the build process a bit.
   */
  virtual void preprocess();

  virtual bool build();

  /**
   * Improve the solution found on the build phase. Can use VNS, or Tabú search,
   *  or even local searches.
  */
  virtual bool postprocess();
  virtual void update();
  virtual bool stopCriteria();
private:
};

#endif
