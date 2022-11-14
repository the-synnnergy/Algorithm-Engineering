#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "simple_heuristic.hpp"
#include "io.hpp"


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

        SimpleHeuristic solver(instance);
        solver.solve();
        auto solution = solver.getSolution();
        instance.setSolution(solution);
        std::cout << "Solution valid: " << (instance.isSolutionValid()) << std::endl;

        io::save_instance(argv[4], instance);

    }
    else if (argc == 3 && argv[1] == std::string("-eval"))
    {
        MessInstance instance = io::read_instance(argv[2]);
    }
    else
    {
        std::cerr << "Invalid program input." << std::endl;
        return -1;
    }
}

