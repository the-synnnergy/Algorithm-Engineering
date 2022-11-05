#pragma once
#include "mess_instance.cpp"
#include <vector>
#include <set>
#include <queue>
#include <iostream>

/**
 * No optimization done, i'm stupid with pointers and ref in c++. At least right now.
 * */
class SimpleHeuristic
{
public:
    SimpleHeuristic(MessInstance i) : m_instance(i)
    {
        m_node_configuration = i.getNodeConfiguration();
    }

    void solve()
    {
        std::set<Edge> terminal_paths = getTerminalPaths(m_instance.getGraph().getAdjacencyList());
        std::vector<Edge> edges = m_instance.getGraph().getEdgeList();
        auto adjacency_lists = m_instance.getGraph().getAdjacencyList();
        for(Edge e : edges)
        {
            // as it is a trival, stupid heurisitic this part isn't optimized and will be slow!
            auto  pos_it = std::find(adjacency_lists.at(e.src).begin(),adjacency_lists.at(e.src).end(), e.dest);
            adjacency_lists.at(e.src).erase(pos_it);
            std::set<Edge> new_terminal_paths = getTerminalPaths(adjacency_lists);
            if(new_terminal_paths== terminal_paths)
            {
                continue;
            }
            adjacency_lists.at(e.src).push_back(e.dest);
        }
        // create solution
        for(Edge e : edges)
        {
            auto pos_it = std::find(adjacency_lists.at(e.src).begin(),adjacency_lists.at(e.src).end(), e.dest);
            if(pos_it != adjacency_lists.at(e.src).end())
            {
                m_solution.push_back(1);
            }else{
                m_solution.push_back(0);
            }
        }
    }

    std::vector<int> getSolution()
    {
        return m_solution;
    }

private:
    MessInstance m_instance;
    std::vector<int> m_node_configuration;
    std::vector<int> m_solution;
    /**
     * 
     * finds all path from all Terminals to the other Terminals
     **/
    std::set<Edge> getTerminalPaths(std::vector<std::vector<int>> adjaceny_lists)
    {
        std::set<Edge> terminal_paths;
        auto adjacency_list = m_instance.getGraph().getAdjacencyList();
        int node_counter = 0;
        for(int i : m_node_configuration){
            if(i == 0)
            {
                continue;
            }
            std::set<Edge> edges = BFSfromTerminal(node_counter, adjaceny_lists);
            terminal_paths.insert(edges.begin(),edges.end());
            node_counter++;
        }
        return terminal_paths;
    }
    /**
     * Finds all paths from one Terminal to the other Terminals
     * 
     **/
    std::set<Edge> BFSfromTerminal(int node, std::vector<std::vector<int>> adjacency_list_collection)
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
            if(m_node_configuration.at(current_node) == 1){
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
};