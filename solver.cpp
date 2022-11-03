#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

struct node{
    int id;
    bool isTerminal;
};



void read_instance(const std::string& filename){
    std::ifstream file;
    file.open(filename);
    if(!file){
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
    std::vector<std::vector<int>> adjacency_lists(number_nodes);
    while (i < number_edges)
    {
        int start_node, end_node, is_included;
        std::string edge;
        getline(file,edge);
        std::stringstream ss(edge);
        ss >> start_node >> end_node >> is_included;
        adjacency_lists[start_node].push_back(end_node);
        i++;
    }
    file.close();
    // should be in a separate function.
    std::ofstream output_file;
    output_file.open("test.txt");
    output_file << instance_name << std::endl;
    output_file << number_nodes << std::endl;
    for(const auto &e : nodes){
        output_file << e;
    }
    output_file << std::endl;
    output_file << number_edges << std::endl;
    int counter = 0;
    for(const auto &e : adjacency_lists){
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
    read_instance("example.txt");
    return 0;
}

