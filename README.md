# Diseño y análisis de algoritmos, práctica 7; algoritmo k-means voraz

alu0101056944@ull.edu.es

Marcos Barrios.

TODO: Check why there are more failed iterations than there should be of invalid candidates() on greedy clusters builder.

    Its meant to count failed executions where the candidate is invalid. It happens because the choose() can choose a repeated point, so it is rejected and removed from candidates list.

TODO: a point cluster has a cluster index stored, but the clusters will change constantly. Think about it.

    I need a representation of the cluster anyways. If a point has an invalid cluster index
    does not matter because the first step of kmeans is calculating cluster and the other
    algorithms are not in charge of assignment. As long as I dont modify cluster information
    on another place it will be ok. And if that is necessary, then service points is always
    passed with client points, two entities used at the same time on the same places, so
    again, it should not be a problem.

TODO: Think about what to do on the preprocess phase of the GRASP. *refused*

TODO: make is so that CLI works without specifying k *refused*

TODO: Make a decision on if nominal similarity is well designed. *done*

TODO: Adjust the minimum k amount so that it is minimum 2 when doing k * 0.1 *done*

TODO: triangular restriction on the similirity function

TODO: read whole directory and execute all the files using the same amount of clusters.

TODO: efficiency. Don't recalculate SSE each time a change takes place, instead just add/substract to the previous sse total.

TODO: Remove kmeans application on grasp builder, use assignment algorithm instead. The objetive is to avoid different order leading to different results. **done**

TODO: calculate penalization value for the objective function.

TODO: Choose own penalization formula other than AIC.

## About failed iterations on the build phase:

In k-means, it can happen that a cluster remains in the same place, especially when it is about to finish the k-means process. I have it set up so that when a cluster is alone and has not been recalculated because it has no points, but it may be that the random index leads to the same cluster.

However, in greedy clusters, I assume that it will always change at each iteration, which is incorrect. But it's okay because they are discarded if it turns out to be the same.

I could change the heuristic to directly ensure picking a distant point that is not a service point. However, it is fine as it is, it is a design question if the professor wants there to be failed iterations or not.

I would need to change it because then when changing the number of clusters, it is interesting to see the evolution directly (which will be visible because I use k-means and not greedy clusters in the complete GRASP, but repetitions will still be seen in the initial construction). But then, what do I put in "valid candidate()"?