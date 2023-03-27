#ifndef IHEURISTIC_H
#define IHEURISTIC_H

#include <vector>
#include "../point/i_point.h"

class IHeuristic {
public:
  virtual ~IHeuristic() {}

  /**
   * the return value should be the index in the available std::vector
   *    of the point that is chosen.
  */
  virtual int choose(std::shared_ptr<IPoint> from,
      std::vector<std::shared_ptr<IPoint>> available) = 0;
private:
};

#endif