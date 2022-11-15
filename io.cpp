#include "io.hpp"
#include <algorithm>
#include <sstream>
#include <fstream>


namespace io
{

MessInstance read_instance_with_solution(const std::string& filename)
{
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
    std::vector<int> solution;
    while (i < number_edges)
    {
        int start_node, end_node, is_included;
        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node >> is_included;
        adjacency_list[start_node].push_back(end_node);
        solution.push_back(is_included);
        i++;
    }
    file.close();

    MessInstance instance(number_nodes, adjacency_list, 
                            nodes, instance_name, solution);

    return instance;
}

MessInstance read_instance(const std::string& filename)
{
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
        int start_node, end_node;
        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node;
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

    std::vector<int> solution = instance.getSolution();

    //for iterating the solution if present
    int i = 0;

    for(const auto &e : graph.getAdjacencyList()){
        for (const auto &f : e)
        {
            output_file << counter << " " << f;

            if (!solution.empty())
            {
                output_file << " " << solution[i];
                i++;
            }

            output_file << std::endl;
        }
        counter++;
    }
    output_file.close();
}
} // namespace io