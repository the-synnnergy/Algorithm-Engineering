//
// Created by marcel on 11/21/22.
//

#ifndef ALGORITHM_ENGINEERING_SHORTEST_PATH_HEURISTIC_H
#define ALGORITHM_ENGINEERING_SHORTEST_PATH_HEURISTIC_H

#include "../mess_instance.hpp"
#include "../solver.hpp"
#include "../Graph/GraphUtils.hpp"
/**
 * @brief Construction Heuristic which computes shortest paths from all terminals to
 * all other connected terminals and adds those edges to the solution.
 */
class ShortestPathHeuristic : public Solver{

private:
    MessInstance m_instance;
    std::vector<bool> m_node_configuration;
    std::vector<bool> m_solution;

public:
    explicit ShortestPathHeuristic(MessInstance instance)
    : m_instance(instance), m_node_configuration(instance.getNodeConfiguration())
    {}

    void solve() override;

    std::vector<bool> getSolution() override
    {
        return m_solution;
    }

    ~ShortestPathHeuristic() override = default;

};

#endif //ALGORITHM_ENGINEERING_SHORTEST_PATH_HEURISTIC_H
