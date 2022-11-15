#include "mess_instance.hpp"
#include <queue>
#include <iostream>

bool MessInstance::isSolutionValid()
{
    auto terminal_paths = getTerminalPaths();
    auto solution_terminal_paths = getSolutionTerminalPaths();
    return terminal_paths == solution_terminal_paths;
}

std::set<Edge> MessInstance::getTerminalPaths()
{
    std::set<Edge> terminal_paths;
    auto adjacency_list = m_graph.getAdjacencyList();
    int node_counter = 0;
    for(int i : m_node_configuration){
        if(i == 1)
        {
            std::set<Edge> edges = BFSfromTerminal(node_counter, adjacency_list);
            terminal_paths.insert(edges.begin(),edges.end());
        }
        
        node_counter++;
        
    }
    return terminal_paths;
}

std::set<Edge> MessInstance::getSolutionTerminalPaths()
{
    std::set<Edge> terminal_paths;
    auto adjacency_list = m_subgraph.getAdjacencyList();
    int node_counter = 0;
    for(int i : m_node_configuration){
        if(i == 1)
        {
            std::set<Edge> edges = BFSfromTerminal(node_counter, adjacency_list);
            terminal_paths.insert(edges.begin(),edges.end());
        }
        
        node_counter++;
        
    }
    return terminal_paths;
}

std::set<Edge> MessInstance::BFSfromTerminal(int node, std::vector<std::vector<int>> adjacency_list_collection)
{
    std::set<int> visited_nodes;
    std::queue<int> nodes_to_visit;
    std::set<Edge> visitable_terminals;
    std::vector<int> start = adjacency_list_collection.at(node);
    for(int n : start)
    {
            nodes_to_visit.push(n);
            visited_nodes.insert(n);
    }
    while (!nodes_to_visit.empty())
    {
        int current_node = nodes_to_visit.front();
        nodes_to_visit.pop();
        visited_nodes.insert(current_node);
        if(m_node_configuration.at(current_node) == 1 && current_node != node){
            visitable_terminals.insert(Edge(node,current_node));
        }
        std::vector<int> adjacency_list = adjacency_list_collection.at(current_node);
        for(auto n : adjacency_list){
            //contains not supported in gcc 9.4 i think
            const bool is_in = (visited_nodes.find(n) != visited_nodes.end());
            if(is_in)
            {
                continue;
            }
            nodes_to_visit.push(n);
        }
    }
    return visitable_terminals;
}
