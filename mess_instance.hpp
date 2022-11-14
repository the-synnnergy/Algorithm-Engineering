#pragma once
#include "graph.hpp"
#include <string>
#include <vector>
#include <set>

class MessInstance
{
public:
    MessInstance(int n, std::vector<std::vector<int>> adjacency_list, 
        std::vector<int> node_configuration, std::string description)
        : m_graph(n, adjacency_list), m_subgraph(m_graph), m_node_configuration(node_configuration), m_description(description)
        {}

    MessInstance(int n, std::vector<std::vector<int>> adjacency_list, 
        std::vector<int> node_configuration, std::string description, std::vector<int> solution)
        : MessInstance(n, adjacency_list, node_configuration, description)
        {
            setSolution(solution);
        }


    Graph getGraph()
    {
        return m_graph;
    }

    Graph getSubgraph()
    {
        return m_subgraph;
    }

    std::vector<int> getNodeConfiguration()
    {
        return m_node_configuration;
    }

    std::string getDescription()
    {
        return m_description;
    }

    std::vector<int> getSolution()
    {
        return m_solution;
    }

    void setSolution(std::vector<int> solution)
    {
        m_solution = solution;
        m_subgraph.buildSubgraph(m_solution);
    }

    bool isSolutionValid();

    /**
     * 
     * finds all path from all Terminals to the other Terminals
     **/
    std::set<Edge> getTerminalPaths();

    std::set<Edge> getSolutionTerminalPaths();
    /**
     * Finds all paths from one Terminal to the other Terminals
     * 
     **/
    std::set<Edge> BFSfromTerminal(int node, std::vector<std::vector<int>> adjacency_list_collection);


private:
    Graph m_graph;
    Graph m_subgraph;
    std::vector<int> m_node_configuration;
    std::string m_description;
    std::vector<int> m_solution;
};