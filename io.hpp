#pragma once
#include <string>
#include "mess_instance.hpp"

namespace io
{

MessInstance read_instance(const std::string& filename);

MessInstance read_instance_with_solution(const std::string& filename);

void save_instance(const std::string& filename, MessInstance instance);

} // namespace io