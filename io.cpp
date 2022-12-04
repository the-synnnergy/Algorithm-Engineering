#include "io.hpp"
#include <algorithm>
#include <sstream>
#include <fstream>


namespace io
{

MessInstance read_instance_with_solution(const std::string& filename)
{
    //open the file with the given filename
    std::ifstream file;
    file.open(filename);
    if (!file){
        throw std::runtime_error("Could not open file");
    }

    //get instance name
    std::string instance_name;
    getline(file,instance_name);

    //get number of nodes
    std::string buffer;
    getline(file,buffer);
    int number_nodes = stoi(buffer);

    //get terminal node configuration
    std::vector<bool> nodes;
    getline(file,buffer);
    if (buffer[buffer.size() - 1] == '\r')
        buffer.erase(buffer.size() - 1);
    if (buffer[buffer.size() - 1] == '\n')
        buffer.erase(buffer.size() - 1);
    std::for_each(buffer.begin(),buffer.end(),[&](char const & c){
        nodes.push_back(c - '0');
    });

    //get number of edges
    getline(file,buffer);
    int number_edges = stoi(buffer);

    //iterate through all the edges and read them one by one
    int i = 0;
    std::vector<std::vector<int>> adjacency_list(number_nodes);
    std::vector<bool> solution;
    while (i < number_edges)
    {
        //start_node and end_node for edge list, is_included for solution
        int start_node, end_node, is_included;

        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node >> is_included;

        adjacency_list[start_node].push_back(end_node);
        solution.push_back(is_included);
        i++;
    }

    //close file after reading
    file.close();

    //create instance given the read parameters
    MessInstance instance(number_nodes, adjacency_list, 
                            nodes, instance_name, solution);

    return instance;
}

MessInstance read_instance(const std::string& filename)
{
    //open the file with the given filename
    std::ifstream file;
    file.open(filename);
    if (!file){
        throw std::runtime_error("Could not open file");
    }

    //get instance name
    std::string instance_name;
    getline(file,instance_name);

    //get number of nodes
    std::string buffer;
    getline(file,buffer);

    int number_nodes = stoi(buffer);

    //get terminal node configuration
    std::vector<bool> nodes;
    getline(file,buffer);
    if (buffer[buffer.size() - 1] == '\r')
        buffer.erase(buffer.size() - 1);
    if (buffer[buffer.size() - 1] == '\n')
        buffer.erase(buffer.size() - 1);

    std::for_each(buffer.begin(),buffer.end(),[&](char const & c){
        nodes.push_back(c - '0');
    });


    //get number of edges
    getline(file,buffer);
    int number_edges = stoi(buffer);

    //iterate through all the edges and read them one by one
    int i = 0;
    std::vector<std::vector<int>> adjacency_list(number_nodes);
    while (i < number_edges)
    {
        //start_node and end_node for edge list
        int start_node, end_node;

        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node;

        adjacency_list[start_node].push_back(end_node);
        i++;
    }

    //close file after reading
    file.close();

    //create instance given the read parameters 
    MessInstance instance(number_nodes, adjacency_list, 
                            nodes, instance_name);

    return instance;
}


void save_instance(const std::string& filename, MessInstance instance)
{
    Graph graph = instance.getGraph();

    //open/create file
    std::ofstream output_file;
    output_file.open(filename);

    //save name/description
    output_file << instance.getDescription() << std::endl;

    //save number of nodes
    output_file << graph.getNumberOfNodes() << std::endl;

    //save terminal node configuration
    for(const auto &e : instance.getNodeConfiguration()){
        output_file << e;
    }
    output_file << std::endl;
    
    //save number of edges
    output_file << graph.getNumberOfEdges() << std::endl;

    //get solution for storing it
    std::vector<bool> solution = instance.getSolution();

    //iterate through all the edges and store them (with solution if possible)
    int node_counter = 0;
    int solution_counter = 0;

    for(const auto &e : graph.getAdjacencyList()){
        for (const auto &f : e)
        {
            output_file << node_counter << " " << f;

            if (!solution.empty())
            {
                output_file << " " << solution[solution_counter];
                solution_counter++;
            }

            output_file << std::endl;
        }
        node_counter++;
    }

    //close file after writing
    output_file.close();
}
} // namespace io