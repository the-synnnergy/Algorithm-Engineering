#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "simple_heuristic.hpp"
#include "io.hpp"
#include <chrono>


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
        MessInstance instance = io::read_instance(argv[2]);

        auto start = std::chrono::high_resolution_clock::now();
        SimpleHeuristic solver(instance);
        solver.solve();
        auto solution = solver.getSolution();
        instance.setSolution(solution);
        auto end = std::chrono::high_resolution_clock::now();

        io::save_instance(argv[4], instance);


        std::cout << instance.getSubgraph().getNumberOfEdges() << "\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl; 
    }
    else if (argc == 3 && argv[1] == std::string("-eval"))
    {
        MessInstance instance = io::read_instance_with_solution(argv[2]);
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

