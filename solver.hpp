#pragma once
#include <vector>
/**
 * @brief Abstract class for solvers
 * 
 */
class Solver
{
public:
    /**
     * @brief Kick off solving process. All the work happens here.
     * 
     */
    virtual void solve() = 0;

    /**
     * @brief Get the Solution after the solving process
     * 
     * @return std::vector<bool> Solution, true entry indicates edge is included in solution
     */
    virtual std::vector<bool> getSolution() = 0;
};