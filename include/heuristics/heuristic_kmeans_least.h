/**
 * An heuristic to choose the service point with the least distance from the
 *   point of interest.
*/

#ifndef HEURISTIC_KMEANS_LEAST_H
#define HEURISTIC_KMEANS_LEAST_H

#include <memory>

#include "i_heuristic.h"
#include "../similarity/i_similarity.h"
#include "../point/point_cluster.h"

class HeuristicKMeansLeast : public IHeuristic {
public:
  HeuristicKMeansLeast();
  ~HeuristicKMeansLeast();
  
  /**
   * get the index of the available point that has the least distance to
   *    the only point in pointClients.
  */
  virtual int choose(std::vector<PointCluster> pointsClient,
      std::vector<PointCluster> pointsService);

  /**
   * To allow to choose a different similarity algorithm, in case a modification
   * is needed to not use euclidean as heuristic but another one.
  */
  void setSimilarityAlgorithm(std::shared_ptr<ISimilarity> ptrSimilarityAlgorithm);
private:
  std::shared_ptr<ISimilarity> ptrSimilarityAlgorithm_;
};

#endif
