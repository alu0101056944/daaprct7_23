#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "../point/i_point.h"

class ISimilarity {
public:
  virtual ~ISimilarity() {}

  virtual float similarity(std::shared_ptr<IPoint> pointA,
      std::shared_ptr<IPoint> pointB) = 0;
private:
};

#endif
