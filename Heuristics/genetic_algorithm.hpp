//
// Created by marcel on 11/23/22.
//

#ifndef ALGORITHM_ENGINEERING_GENETIC_ALGORITHM_HPP
#define ALGORITHM_ENGINEERING_GENETIC_ALGORITHM_HPP

#include "../solver.hpp"
#include "../mess_instance.hpp"
#include <map>

/**
 * @brief Class which implements a genetic algorithm for the Minimum Equivalent Steiner Subgraph problem. Solution represation as in Ka...
 */
class GeneticAlgorithm : public Solver {

private:
    MessInstance m_instance;
    std::vector<bool> m_best_solution;
    //
    std::map<int, std::vector<bool>> m_population;
    std::vector<bool> m_node_configuration;
    double m_mutation_rate = 0.1;
    int m_initial_population = 100;

    /**
     * @brief calculates the fitness of a given individual for the genetic algorithm
     * @param individual the individual for which the fitness is calculated
     * @return fitness value as integer
     */
    int calculateFitness(std::vector<bool> individual);

    /**
     * @brief applies mutation to all individuals in the population for the given mutation rate. Mutation is defined as changing if the node is in the graph or not.
     */
    void applyMutation();

    /**
     * makes a crossover mutation from the population and creates a new individual
     * @return individual generated by the crossover
     */
    std::vector<bool> crossover();

public:
    GeneticAlgorithm(MessInstance instance) : m_instance(instance) {
        m_node_configuration = instance.getNodeConfiguration();
    }

    GeneticAlgorithm(MessInstance instance, int population, double mutation_rate) : m_instance(instance) {
        m_initial_population = population;
        m_mutation_rate = mutation_rate;
    }

    void solve() override;

    std::vector<bool> getSolution() {
        return m_best_solution;
    }
};


#endif //ALGORITHM_ENGINEERING_GENETIC_ALGORITHM_HPP
