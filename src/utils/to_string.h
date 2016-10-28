#pragma once

#include <string>
#include <sstream>

#define TO_STRING(x) static_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()