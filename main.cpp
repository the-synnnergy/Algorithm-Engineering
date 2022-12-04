#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Heuristics/simple_heuristic.hpp"
#include "solver.hpp"
#include "io.hpp"
#include <chrono>
#include <memory>
#include "Heuristics/genetic_algorithm.hpp"
#include "Heuristics/shortest_path_heuristic.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Mögliche Aufrufkonfigurationen:" << std::endl;
        std::cerr << argv[0] << " -in: dat1 -out dat2" << std::endl;
        std::cerr << argv[0] << "-eval dat1" << std::endl;
        return 0;
    }
    else if (argc == 5 && argv[1] == std::string("-in") && argv[3] == std::string("-out"))
    {
        //read instance without solution
        MessInstance instance = io::read_instance(argv[2]);

        //start time measurement. Includes solver creation and solving process
        auto start = std::chrono::high_resolution_clock::now();

        //only this line should be changed, rest should remain relatively untouched
        std::shared_ptr<Solver> solver = std::make_shared<ShortestPathHeuristic>(instance);

        solver->solve();
        auto solution = solver->getSolution();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =  std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        //set the solution in the instance and save it
        instance.setSolution(solution);
        io::save_instance(argv[4], instance);

        //output information about the found solution
        std::cout << instance.getSubgraph().getNumberOfEdges() << "\t" << duration << " ms" << std::endl; 
    }
    else if (argc == 3 && argv[1] == std::string("-eval"))
    {
        //read instance with solution
        MessInstance instance = io::read_instance_with_solution(argv[2]);

        //instance provides functionality for checking validity, used here 
        if (!instance.isSolutionValid())
        {
            std::cout << "ERROR" << std::endl;
        }
        else
        {
            std::cout << instance.getSubgraph().getNumberOfEdges() << std::endl;
        }
    }
    else
    {
        std::cerr << "Ungültige Eingabe." << std::endl;
        std::cerr << "Mögliche Aufrufkonfigurationen:" << std::endl;
        std::cerr << argv[0] << " -in: dat1 -out dat2" << std::endl;
        std::cerr << argv[0] << "-eval dat1" << std::endl;
        return -1;
    }
}

