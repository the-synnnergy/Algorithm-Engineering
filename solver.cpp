#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "graph.cpp"

struct node{
    int id;
    bool isTerminal;
};

class MessInstance
{
public:
    MessInstance(Graph graph, std::vector<int> node_configuration,
        std::string description)
        : m_graph(graph), m_node_configuration(node_configuration), m_description(description)
        {}
    
    MessInstance(int n, std::vector<Edge> edges, 
        std::vector<int> node_configuration, std::string description)
        : m_graph(n, edges), m_node_configuration(node_configuration), m_description(description)
        {}

    MessInstance(int n, std::vector<std::vector<int>> adjacency_list, 
        std::vector<int> node_configuration, std::string description)
        : m_graph(n, adjacency_list), m_node_configuration(node_configuration), m_description(description)
        {}

    Graph getGraph()
    {
        return m_graph;
    }

    std::vector<int> getNodeConfiguration()
    {
        return m_node_configuration;
    }

    std::string getDescription()
    {
        return m_description;
    }

private:
    Graph m_graph;
    std::vector<int> m_node_configuration;
    std::string m_description;
};


MessInstance read_instance(const std::string& filename){
    std::ifstream file;
    file.open(filename);
    if (!file){
        throw std::runtime_error("Could not open file");
    }
    std::string instance_name;
    getline(file,instance_name);
    std::string buffer;
    getline(file,buffer);
    int number_nodes = stoi(buffer);
    std::vector<int> nodes;
    getline(file,buffer);
    std::for_each(buffer.begin(),buffer.end(),[&](char const & c){
        nodes.push_back(c - '0');
    });

    getline(file,buffer);
    int number_edges = stoi(buffer);
    int i = 0;
    std::vector<std::vector<int>> adjacency_list(number_nodes);
    while (i < number_edges)
    {
        int start_node, end_node, is_included;
        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node >> is_included;
        adjacency_list[start_node].push_back(end_node);
        i++;
    }
    file.close();

    MessInstance instance(number_nodes, adjacency_list, 
                            nodes, instance_name);

    return instance;
}

void save_instance(const std::string& filename, MessInstance instance)
{
    // should be in a separate function.
    Graph graph = instance.getGraph();

    std::ofstream output_file;
    output_file.open(filename);
    output_file << instance.getDescription() << std::endl;
    output_file << graph.getNumberOfNodes() << std::endl;
    for(const auto &e : instance.getNodeConfiguration()){
        output_file << e;
    }
    output_file << std::endl;
    output_file << graph.getNumberOfEdges() << std::endl;
    int counter = 0;

    for(const auto &e : graph.getAdjacencyList()){
        for (const auto &f : e)
        {
            output_file << counter << " " << f << " " << 1 << std::endl;
        }
        counter++;
    }
    output_file.close();
}



int main(int argc, char const *argv[])
{
    MessInstance instance = read_instance("example.txt");
    save_instance("test.txt", instance);
    return 0;
}

