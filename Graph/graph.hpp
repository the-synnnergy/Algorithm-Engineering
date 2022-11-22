#pragma once
#include <vector>
#include <iostream>

/**
 * @brief Edge struct for the Graph, simply contains source and destination node
 * 
 */
struct Edge
{
    Edge(int src, int dest)
    : src(src), dest(dest)
    {};
    int src, dest;

    bool operator==(const Edge& b) const
    {
        return (src == b.src && dest == b.dest); 
    }

    bool operator<(const Edge& b) const
    {
        if(src < b.src) return true;
        if(src == b.src && dest < b.dest) return true;
        return false;
    }
};

/**
 * @brief Adjacency-List-based Graph class
 * 
 */
class Graph
{
public:
    /**
     * @brief Construct a new Graph object from edge list
     * 
     * @param n Number of nodes
     * @param edges Edge list
     */
    Graph(int n, std::vector<Edge> edges);

    /**
     * @brief Construct a new Graph object from its adjacency list
     * 
     * @param n Number of nodes
     * @param adjacency_list Adjacency list for the graph
     */
    Graph(int n, std::vector<std::vector<int>> adjacency_list);

    /**
     * @brief Copy Constructor, creates a deep copy
     * 
     * @param graph Graph to be copied
     */
    Graph(Graph& graph);

    /**
     * @brief Get the Edge List for the graph, necessary for storing the graph
     * 
     * @return std::vector<Edge> Edge list
     */
    std::vector<Edge> getEdgeList();
    
    /**
     * @brief Get the number of nodes
     * 
     * @return int Number of nodes
     */
    int getNumberOfNodes()
    {
        return m_adjacency_list.size();
    }

    /**
     * @brief Get the Number Of Edges
     * 
     * @return int Number of edges
     */
    int getNumberOfEdges()
    {
        int edge_number = 0;
        for(int i = 0; i < m_adjacency_list.size(); i++)
        {
            edge_number += m_adjacency_list[i].size();
        }
        return edge_number;
    }

    /**
     * @brief Get the Adjacency List
     * 
     * @return std::vector<std::vector<int>> Adjacency list
     */
    std::vector<std::vector<int>> getAdjacencyList()
    {
        return m_adjacency_list;
    }

    /**
     * @brief Build the subgraph corresponding to the given solution
     * 
     * @param solution Solution to be used for the subgraph
     */
    void buildSubgraph(std::vector<bool> solution)
    {
        int edge_counter = 0;
        std::vector<std::vector<int>> adjacency_list;

        for (int i = 0; i < m_adjacency_list.size(); i++)
        {
            //insert an adjacency list for each node
            adjacency_list.emplace_back();

            //copy over all the edges that are in the solution
            for (int j = 0; j < m_adjacency_list[i].size(); j++)
            {
                if (solution[edge_counter])
                {
                    adjacency_list[i].push_back(m_adjacency_list[i][j]);
                }
                edge_counter++;
            }
        }
        m_adjacency_list = adjacency_list;
    }


private:
    std::vector<std::vector<int>> m_adjacency_list;
};