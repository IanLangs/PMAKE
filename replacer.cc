#include "replacer.hpp"
#include <string>
#include <sstream>
#include <unordered_map>
#include <cctype>

static inline bool is_blank(const std::string& s) {
    for (char c : s) if (!std::isspace((unsigned char)c)) return false;
    return true;
}

std::string replace_vars(const std::string& input) {
    std::unordered_map<std::string, std::string> vars;
    std::stringstream in(input);
    std::stringstream out;

    std::string line;

    while (std::getline(in, line)) {

        // $var = value
        if (!line.empty() && line[0] == '$') {
            auto eq = line.find('=');
            if (eq != std::string::npos) {
                std::string name  = line.substr(1, eq - 1);
                std::string value = line.substr(eq + 1);

                // trim simple
                while (!name.empty() && std::isspace(name.back()))  name.pop_back();
                while (!value.empty() && std::isspace(value.front())) value.erase(0, 1);

                vars[name] = value;
                continue; // no se imprime
            }
        }

        // reemplazo de variables en cualquier línea
        for (auto& [k, v] : vars) {
            std::string key = "$" + k;
            size_t pos = 0;

            while ((pos = line.find(key, pos)) != std::string::npos) {
                line.replace(pos, key.size(), v);
                pos += v.size();
            }
        }

        out << line << '\n';
    }

    return out.str();
}
