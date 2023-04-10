# Diseño y análisis de algoritmos, práctica 7; algoritmo k-means voraz

alu0101056944@ull.edu.es

Marcos Barrios.

TODO: Edge case on greedy kmeans: if pointsService.size() == pointsClient.size() then all empty clusters, and will be randomly relocalized. So, implement random index to return the same index if no non-service point is available, also make sure it always returns index of pointclient that is not in the same localization as a service point.

TODO: Check why there are more failed iterations than there should be of invalid candidates() on greedy clusters builder.

TODO: a point cluster has a cluster index stored, but the clusters will change constantly. Think about it.

TODO: Think about what to do on the preprocess phase of the GRASP.

## About failed iterations on the build phase:

In k-means, it can happen that a cluster remains in the same place, especially when it is about to finish the k-means process. I have it set up so that when a cluster is alone and has not been recalculated because it has no points, but it may be that the random index leads to the same cluster.

However, in greedy clusters, I assume that it will always change at each iteration, which is incorrect. But it's okay because they are discarded if it turns out to be the same.

I could change the heuristic to directly ensure picking a distant point that is not a service point. However, it is fine as it is, it is a design question if the professor wants there to be failed iterations or not.

I would need to change it because then when changing the number of clusters, it is interesting to see the evolution directly (which will be visible because I use k-means and not greedy clusters in the complete GRASP, but repetitions will still be seen in the initial construction). But then, what do I put in "valid candidate()"?