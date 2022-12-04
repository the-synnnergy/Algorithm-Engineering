//
// Created by marcel on 11/23/22.
//

#include "genetic_algorithm.hpp"
#include <random>
#include <algorithm>
#include <iostream>
void GeneticAlgorithm::applyMutation()
{
    std::uniform_real_distribution<double> distr(0,1);
    std::uniform_int_distribution<int> int_distr(0,m_problemsize-1);
    for(int i = 0; i < m_population.size();i++){
        double random_number = distr(m_generator);
        if(random_number >= m_mutation_rate){
            continue;
        }
        std::vector<bool> individual = std::get<0>(m_population.at(i));
        int random = int_distr(m_generator);
        individual[random] = !individual[random];
    }
}

std::vector<bool> GeneticAlgorithm::crossover()
{
    std::vector<std::vector<bool>> individuals = individualSelection();
    std::vector<bool> individual_a = individuals[0];
    std::vector<bool> individual_b = individuals[1];
    std::uniform_int_distribution<int> dist(0,m_problemsize-1);
    int cut_point_1 = dist(m_generator);
    int cut_point_2 = dist(m_generator);
    int min_cut = std::min(cut_point_1,cut_point_2);
    int max_cut = std::max(cut_point_1,cut_point_1);
    std::vector<bool> new_individual;
    for(int i = 0; i < m_problemsize;i++){
        bool node_chromosome;
        if(i <= max_cut && i >= min_cut){
            node_chromosome = individual_b[i];
        }else{
            node_chromosome = individual_a[i];
        }
        new_individual.push_back(node_chromosome);
    }
    return new_individual;
}

std::vector<std::vector<bool>> GeneticAlgorithm::individualSelection() {
    // Tournament sampling
   std::uniform_int_distribution<int> int_distr(0,m_population.size()-1);
   std::vector<std::vector<bool>> parents;
   int num_of_tournament_participants = 4;
   // parent selection
   auto return_best = [&] (){
       std::vector<bool> best;
       int best_fitnesss = INFINITY;
       for(int i = 0; i< num_of_tournament_participants;i++){
           auto individual = this->m_population.at(int_distr(this->m_generator));
           if(std::get<1>(individual) < best_fitnesss){
               best = std::get<0>(individual);
           }
       }
       return best;
    };
    parents.push_back(return_best());
    parents.push_back(return_best());
    return parents;
}

int GeneticAlgorithm::calculateFitness(std::vector<bool> individual){
    int fitness = 0;
    for(bool chromosome : individual){
        if(chromosome){
            fitness++;
        }
    }

    m_instance.setSolution(individual);
    if(m_instance.isSolutionValid()){
        return fitness;
    }
    return fitness + (m_problemsize *0.75);
}

void GeneticAlgorithm::solve(){
    // kick off the algorithm

    generate_initial_population();
    std::cout<<m_population.size() << std::endl;
    for(int i = 0;i < m_generations;i++){
        // do a crossover
        std::vector<bool> individual_chromosome = crossover();
        int fitness = calculateFitness(individual_chromosome);
        m_population.push_back(std::make_tuple(individual_chromosome,fitness));
        applyMutation();
        auto max = std::max_element(m_population.begin(),m_population.end(),
                               [](const std::tuple<std::vector<bool>,int> &x,
                                  const std::tuple<std::vector<bool>,int> &y) {
                                   return std::get<1>(x) < std::get<1>(y);
                               });
        auto min = std::min_element(m_population.begin(),m_population.end(),
                                    [](const std::tuple<std::vector<bool>,int> &x,
                                       const std::tuple<std::vector<bool>,int> &y) {
                                        return std::get<1>(x) < std::get<1>(y);
                                    });
        if(std::get<1>(*min) < this->m_best_solution_fitness){
            m_best_solution_fitness = std::get<1>(*min);
            m_best_solution = std::get<0>(*min);
        }
        m_population.erase(max);
    }
}

void GeneticAlgorithm::generate_initial_population(){
    // generate initial population.
    int best_fitness = INFINITY;
    m_best_solution_fitness = INFINITY;

    std::bernoulli_distribution dist;
    for(int i = 0; i < m_initial_population;i++){
        std::vector<bool> individual_chromosome;
        for(int j = 0; j< m_problemsize;j++){
            individual_chromosome.push_back(dist(m_generator));
        }
        int fitness = calculateFitness(individual_chromosome);
        if(fitness < best_fitness){
            m_best_solution = individual_chromosome;
            best_fitness = fitness;
            m_best_solution_fitness = fitness;
        }
        m_population.emplace_back(individual_chromosome,fitness);
    }

}

