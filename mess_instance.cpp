#include "mess_instance.hpp"
#include <queue>
#include <iostream>
#include <unordered_set>

bool MessInstance::isSolutionValid()
{
    std::set<Edge> terminal_paths = getTerminalPaths();

    auto solution_terminal_paths = getSolutionTerminalPaths();
    return terminal_paths == solution_terminal_paths;
}

std::set<Edge> MessInstance::getTerminalPaths()
{
    std::set<Edge> terminal_paths;
    auto adjacency_list = m_graph.getAdjacencyList();
    int node_counter = 0;
    for(int i : m_node_configuration){
        if(i)
        {
            //std::cout << "Doing one BFS" << std::endl;
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
        if(i)
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
    std::vector<bool> visited(m_graph.getNumberOfNodes(), false);
    std::unordered_set<int> visited_nodes;
    std::queue<int> nodes_to_visit;
    std::set<Edge> visitable_terminals;
    std::vector<int> start = adjacency_list_collection.at(node);
    for(int n : start)
    {
            nodes_to_visit.push(n);
            visited[node] = true;
    }
    while (!nodes_to_visit.empty())
    {
        int current_node = nodes_to_visit.front();
        nodes_to_visit.pop();
        //visited_nodes.insert(current_node);
        if(m_node_configuration.at(current_node) && current_node != node){
            visitable_terminals.insert(Edge(node,current_node));
        }
        std::vector<int> adjacency_list = adjacency_list_collection.at(current_node);
        for(auto n : adjacency_list){
            //contains not supported in gcc 9.4 i think
            //const bool is_in = (visited_nodes.find(n) != visited_nodes.end());
            if(visited[n])
            {
                continue;
            }
            visited[n] = true;
            nodes_to_visit.push(n);

        }
    }
    return visitable_terminals;
}
