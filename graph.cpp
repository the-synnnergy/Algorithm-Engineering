#include "graph.hpp"

Graph::Graph(int n, std::vector<Edge> edges)
{
    m_adjacency_list.resize(n);
    
    for(const auto& edge: edges)
    {
        m_adjacency_list[edge.src].push_back(edge.dest);
    } 
}

Graph::Graph(int n, std::vector<std::vector<int>> adjacency_list)
{
    m_adjacency_list = adjacency_list;
}

Graph::Graph(Graph& graph)
{
    auto adj = graph.getAdjacencyList();
    std::copy(adj.begin(), adj.end(), back_inserter(m_adjacency_list));
}

std::vector<Edge> Graph::getEdgeList()
{
    std::vector<Edge> edge_list;
    for(int i = 0; i < m_adjacency_list.size(); i++)
    {
        for(int j = 0; j < m_adjacency_list[i].size(); j++)
        {
            edge_list.emplace_back(i, m_adjacency_list[i][j]);
        }
    }
    return edge_list;
}
