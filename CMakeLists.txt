cmake_minimum_required(VERSION 3.10.0)
project(prct07 VERSION 0.1.0)
add_library(prct07Library
    include/algorithm_greedy/i_algorithm_greedy.h
    src/algorithm_greedy/algorithm_greedy_kmeans.cpp
    src/algorithm_greedy/algorithm_greedy_clusters.cpp
    src/algorithm_greedy/algorithm_greedy_clusters_lrc.cpp
    src/algorithm_greedy/framework_greedy.cpp

    include/algorithm_grasp/i_algorithm_grasp.h
    src/algorithm_grasp/framework_grasp.cpp
    src/algorithm_grasp/algorithm_grasp_clusters.cpp

    src/algorithm_gvns/algorithm_gvns.cpp

    include/environment_structure/i_environment_structure.h
    src/environment_structure/environment_structure_exchange.cpp
    src/environment_structure/environment_structure_exchange_single.cpp
    src/environment_structure/environment_structure_exchange_k.cpp
    src/environment_structure/environment_structure_delete.cpp
    src/environment_structure/environment_structure_delete_single.cpp
    src/environment_structure/environment_structure_add.cpp
    src/environment_structure/environment_structure_add_single.cpp
    src/environment_structure/shakes/shakes_add.cpp
    src/environment_structure/shakes/shakes_delete.cpp
    src/environment_structure/shakes/shakes_exchange.cpp

    include/heuristics/i_heuristic.h
    src/heuristics/heuristic_kmeans_max.cpp
    src/heuristics/heuristic_kmeans_least.cpp

    include/point/i_point.h
    src/point/point_basic.cpp
    src/point/point_cluster.cpp

    include/similarity/i_similarity.h
    src/similarity/similarity_euclidean.cpp
    src/instance_filereader.cpp
    src/objective_function_sse.cpp
    src/algorithm_closest_assignment.cpp)
add_executable(prct07 src/main.cpp)
target_link_libraries(prct07 prct07Library)
target_compile_features(prct07 PRIVATE cxx_std_20)
target_compile_features(prct07Library PRIVATE cxx_std_20)
