//
// Created by marcel on 11/21/22.
//

#include "shortest_path_heuristic.hpp"
#include "../Graph/GraphUtils.hpp"
void ShortestPathHeuristic::solve()
{
    auto all_shortest_paths = GraphUtils::BFS_all_terminal_shortest_paths(m_instance.getGraph(), m_node_configuration);
    /*for (int i = 0; i < all_shortest_paths[0].size(); i++)
    {
        std::cout << i << " size: " << all_shortest_paths[i].size() << std::endl;
        for (int j = 0; j < all_shortest_paths[i].size(); j++)
        {
            std::cout << "Path length for terminal" << i << " path " << j << " " << all_shortest_paths[i][j].size() << std::endl;
            for (int k = 0; k < all_shortest_paths[i][j].size(); k++)
            {
                std::cout << all_shortest_paths[i][j][k].src << " " << all_shortest_paths[i][j][k].dest << std::endl;
            }
        }
    }*/
    //std::cerr << "Solution_edges: " << std::endl;

    // create union of all the different shortest paths
    std::set<Edge> solution_edges;
    for (const auto& shortest_paths : all_shortest_paths)
    {
        for (const auto& shortest_path : shortest_paths)
        {
            for (auto edge : shortest_path)
            {
                solution_edges.insert(edge);
            }
        }
    }
    //std::cerr << "Solution_edges: " << solution_edges.size() << std::endl;

    auto edges = m_instance.getGraph().getEdgeList();
    std::vector<bool> solution;
    // get edges as edgelist
    for (int i = 0; i < edges.size(); i++)
    {
        if (solution_edges.find(edges[i]) != solution_edges.end())
        {
            solution.push_back(true);
        }
        else
        {
            solution.push_back(false);
        }
    }
    // set solution accordingly
    m_solution = solution;


}