# Diseño y análisis de algoritmos, práctica 7; algoritmo k-means voraz

alu0101056944@ull.edu.es

Marcos Barrios.

TODO: Edge case on greedy kmeans: if pointsService.size() == pointsClient.size() then all empty clusters, and will be randomly relocalized. So, implement random index to return the same index if no non-service point is available, also make sure it always returns index of pointclient that is not in the same localization as a service point.

TODO: Check why there are more failed iterations than there should be of invalid candidates() on greedy clusters builder.

TODO: a point cluster has a cluster index stored, but the clusters will change constantly. Think about it.

TODO: Think about what to do on the preprocess phase of the GRASP.