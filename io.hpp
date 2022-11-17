#pragma once
#include <string>
#include "mess_instance.hpp"

namespace io
{

/**
 * @brief Read an instance without the solution (if present)
 * 
 * @param filename File containing the instance
 * @return MessInstance Instance without solution
 */
MessInstance read_instance(const std::string& filename);

/**
 * @brief Read an instance together with its solution
 * 
 * @param filename File containing the instance with solution
 * @return MessInstance Instance with solution
 */
MessInstance read_instance_with_solution(const std::string& filename);

/**
 * @brief Save instance. Also saves solution if present
 * 
 * @param filename File to be used for storing the instance
 * @param instance Instance to be stored
 */
void save_instance(const std::string& filename, MessInstance instance);

} // namespace io