#pragma once

#include "ColoredGraph.h"
#include <string>
#include <iostream>
#include <fstream>

namespace ecnGraph {
	ColoredGraph ReadColFile(std::string fileName);
}