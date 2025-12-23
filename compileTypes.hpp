#pragma once

#include <regex>
#include <vector>
#include <fstream>

using str = std::string;
using ListStr = std::vector<str>;
using std::regex;

str readFile(const str& filePath);
ListStr extractCompileType(const str& fileContent);