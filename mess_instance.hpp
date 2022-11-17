#pragma once
#include "graph.hpp"
#include <string>
#include <vector>
#include <set>

class MessInstance
{
public:
    /**
     * @brief Construct a new MessInstance object
     * 
     * @param n Number of nodes in the instance
     * @param adjacency_list Adjacency list for the underlying graph
     * @param node_configuration Configuration of terminal nodes
     * @param description Name/Description of the instance
     */
    MessInstance(int n, std::vector<std::vector<int>> adjacency_list, 
        std::vector<bool> node_configuration, std::string description)
        : m_graph(n, adjacency_list), m_subgraph(m_graph), m_node_configuration(node_configuration), m_description(description)
        {}

    /**
     * @brief Construct a new Mess Instance object
     * 
     * @param n Number of nodes in the instance
     * @param adjacency_list Adjacency list for the underlying graph
     * @param node_configuration Configuration of terminal nodes
     * @param description Name/Description of the instance
     * @param solution Solution for the given instance
     */
    MessInstance(int n, std::vector<std::vector<int>> adjacency_list, 
        std::vector<bool> node_configuration, std::string description, std::vector<bool> solution)
        : MessInstance(n, adjacency_list, node_configuration, description)
        {
            setSolution(solution);
        }

    /**
     * @brief Get the original Graph object
     * 
     * @return Graph underlying graph for the instance 
     */
    Graph getGraph()
    {
        return m_graph;
    }

    /**
     * @brief Get the Subgraph that results from the solution
     * 
     * @return Graph that results from the solution
     */
    Graph getSubgraph()
    {
        return m_subgraph;
    }

    /**
     * @brief Get the Node Configuration, i.e., the boolean mask of terminals
     * 
     * @return std::vector<bool> boolean mask of terminals
     */
    std::vector<bool> getNodeConfiguration()
    {
        return m_node_configuration;
    }

    /**
     * @brief Get the Description object
     * 
     * @return std::string Description/Name of the instance
     */
    std::string getDescription()
    {
        return m_description;
    }

    /**
     * @brief Get the Solution as boolean mask
     * 
     * @return std::vector<bool> Boolean mask for edges to be included in the solution
     */
    std::vector<bool> getSolution()
    {
        return m_solution;
    }

    /**
     * @brief Set the Solution for the instance. Also builds the corresponding subgraph
     * 
     * @param solution Solution to be set
     */
    void setSolution(std::vector<bool> solution)
    {
        m_solution = solution;
        m_subgraph.buildSubgraph(m_solution);
    }

    /**
     * @brief Check whether solution is valid by comparing terminal reachability in graph and subgraph
     * 
     * @return true If solution if valid
     * @return false Otherwise
     */
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
    std::vector<bool> m_node_configuration;
    std::string m_description;
    std::vector<bool> m_solution;
};