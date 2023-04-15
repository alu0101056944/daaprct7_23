#include "../../include/similarity/similarity_euclidean.h"

#include <cassert>
#include <variant>
#include <cmath>
#include <limits>

#include "../../include/point/point_basic.h"

SimilarityEuclidean::SimilarityEuclidean() {}

SimilarityEuclidean::~SimilarityEuclidean() {}

// if string is different -> infinite distance
float SimilarityEuclidean::similarity(PointCluster pointA, PointCluster pointB) {
  auto componentsA = pointA.getComponents();
  auto componentsB = pointB.getComponents();
  
  assert(componentsA.size() == componentsB.size()); // just in case

  float distance = 0;
  // iterate components one by one, add the difference of each to distance
  for (int i = 0; i < componentsA.size(); ++i) {

    // if float calculate normally
    if (std::holds_alternative<float>(componentsA[i])) {
      
      const float kA = std::get<float>(componentsA[i]);
      const float kB = std::get<float>(componentsB[i]);

      distance += std::pow(kA - kB, 2);

      // if string set infinite distance
    } else if (std::holds_alternative<std::string>(componentsA[i])) {

      const std::string kA = std::get<std::string>(componentsA[i]);
      const std::string kB = std::get<std::string>(componentsB[i]);

      if (kA.compare(kB) != 0) {
        return std::numeric_limits<float>::max(); // to make sure distance is max
      }
    }
  }
  return std::sqrt(distance);
}
