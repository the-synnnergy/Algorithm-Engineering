//
// Created by marcel on 11/21/22.
//

#include "GraphUtils.hpp"
#include <vector>
#include <queue>

std::vector<std::vector<Edge>> GraphUtils::BFS_shortest_paths_multiple_targets(Graph g, int start_node_id, std::vector<bool> node_configuration)
{
    // create queue
    std::queue<int> nodes_to_visit;

    // get adjacency list
    auto adj_list = g.getAdjacencyList();

    // array for marking nodes as visited
    int n = g.getNumberOfNodes();
    std::vector<bool> visited(n, false);
    std::vector<int> predecessors(n, -1);

    // start node is visited
    visited[start_node_id] = true;

    nodes_to_visit.push(start_node_id);

    // bfs
    while (!nodes_to_visit.empty())
    {
        // get next node from queue
        int v = nodes_to_visit.front();
        nodes_to_visit.pop();

        // go through adjacency list and add unvisited nodes to queue
        for (auto u : adj_list[v])
        {
            if (!visited[u])
            {
                // set node to visited and update distance and predecessor
                visited[u] = true;
                predecessors[u] = v;
                nodes_to_visit.push(u);
            }
        }
    }

    // extract paths
    std::vector<std::vector<Edge>> paths;
    for (int i = 0; i < node_configuration.size(); i++)
    {
        if (node_configuration[i] && i != start_node_id)
        {
            // add terminal path to shortest paths
            std::vector<Edge> path;
            
            int cur = i;
            int pred = predecessors[i];
            while (pred != -1)
            {
                path.push_back(Edge(pred, cur));

                cur = pred;
                pred = predecessors[cur];
            }
            std::reverse(path.begin(), path.end());
            paths.push_back(path);
        }
    }

    return paths;

}


std::vector<std::vector<std::vector<Edge>>> GraphUtils::BFS_all_terminal_shortest_paths(Graph g, std::vector<bool> node_configuration)
{
    std::vector<std::vector<std::vector<Edge>>> all_shortest_paths;


    for (int i = 0; i < node_configuration.size(); i++)
    {
        if (node_configuration[i])
        {
            auto shortest_paths = BFS_shortest_paths_multiple_targets(g, i, node_configuration);
            all_shortest_paths.push_back(shortest_paths);
        }
    }
    return all_shortest_paths;
    
}