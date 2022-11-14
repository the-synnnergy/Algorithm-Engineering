#pragma once
#include <vector>

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

class Graph
{
public:
    Graph(int n, std::vector<Edge> edges);

    Graph(int n, std::vector<std::vector<int>> adjacency_list);

    Graph(Graph& graph);

    std::vector<Edge> getEdgeList();
    
    int getNumberOfNodes()
    {
        return m_adjacency_list.size();
    }

    int getNumberOfEdges()
    {
        int edge_number = 0;
        for(int i = 0; i < m_adjacency_list.size(); i++)
        {
            edge_number += m_adjacency_list[i].size();
        }
        return edge_number;
    }

    std::vector<std::vector<int>> getAdjacencyList()
    {
        return m_adjacency_list;
    }

    void buildSubgraph(std::vector<int> solution)
    {
        int counter = 0;
        std::vector<std::vector<int>> adjacency_list;
        for (int i = 0; i < m_adjacency_list.size(); i++)
        {
            adjacency_list.emplace_back();
            for (int j = 0; j < m_adjacency_list[i].size(); j++)
            {
                if (solution[counter] == 1)
                {
                    adjacency_list[i].push_back(m_adjacency_list[i][j]);
                }
                counter++;
            }
        }
        m_adjacency_list = adjacency_list;
    }


private:
    std::vector<std::vector<int>> m_adjacency_list;
};