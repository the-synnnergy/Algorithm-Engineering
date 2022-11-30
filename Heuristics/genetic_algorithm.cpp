//
// Created by marcel on 11/23/22.
//

#include "genetic_algorithm.hpp"

void GeneticAlgorithm::applyMutation()
{
    // TODO generate real random number
    double random_number;
    if(random_number >= m_mutation_rate){
        return;
    }
    //TODO generate real random number
    int random_element;
    std::vector<bool> individual = m_population.at(random_element);
    int random_node;
    while(m_node_configuration.at(random_node)){
        //TODO placeholder right now. generate real random number
        random_node = rand();
    }
    //not sure if this works
    print(individual.at(random_node))
    individual[random_node] = !individual[random_node];
    print(individual.at(random_node));
}

std::vector<bool> GeneticAlgorithm::crossover()
{
    std::vector<std::vector<bool>> individuals = individualSelection();
    std::vector<bool> individual_a = individuals[0];
    std::vector<bool> individual_b = individuals[1];
    int cut_point;
    std::vector<bool> new_individual;
    for(int i = 0; i < m_node_configuration.size();i++){
        bool node_chromosome;
        if(i < cut_point){
            node_chromosome = individual_a[i];
        }else{
            node_chromosome = individual_b[i];
        }
        new_individual.push_back(node_chromosome);
    }
    return new_individual;
}

std::vector<std::vector<bool>> GeneticAlgorithm::individualSelection() {
    // implement a roulette wheel
}