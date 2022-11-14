#pragma once
#include <string>
#include "mess_instance.hpp"

namespace io
{

MessInstance read_instance(const std::string& filename);

void save_instance(const std::string& filename, MessInstance instance);

} // namespace io