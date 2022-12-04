//
// Created by marcel on 11/21/22.
//

#ifndef ALGORITHM_ENGINEERING_GRAPHUTILS_H
#define ALGORITHM_ENGINEERING_GRAPHUTILS_H
#include "graph.hpp"
#include <algorithm>
#include <map>
/**
 * @brief Class for collecting utility algorithms to be used on graphs as defined in graph.hpp
 *
 */
class GraphUtils {
public:
    /**
     * @brief Uses Depth-First-Search to find the shortest path from a given start node to an end node on a Graph.
     * @param g Graph on which the DFS is executed
     * @param start_node_id Integer id of the start node
     * @param end_node_id  Integer id of the end node
     * @return List of edges that build the shortest path from start node to end node
     */
    // static std::vector<Edge> DFS_shortest_path(Graph g, int start_node_id, int end_node_id);
    /**
     * @brief Computes all shortest paths from a given start node.
     * @param g  Graph on which the shortest paths are calculated.
     * @param start_node_id Integer id of the start node.
     * @return A list of lists containing the shortest paths as edge lists, where index of first list is the target node id.
     */
    static std::vector<std::vector<Edge>> BFS_shortest_paths_multiple_targets(Graph g, int start_node_id, std::vector<bool> node_configuration);


    static std::vector<std::vector<std::vector<Edge>>> BFS_all_terminal_shortest_paths(Graph g, std::vector<bool> node_configuration);
    /**
     * @brief computes all pairs shortest paths on a given graph g
     * @param g
     * @return
     */
    // static std::map<std::tuple<int,int>> DFS_all_pairs_shortest_paths(Graph g);
};


#endif //ALGORITHM_ENGINEERING_GRAPHUTILS_H