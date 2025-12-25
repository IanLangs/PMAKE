#include "replacer.hpp"

#include <sstream>
#include <unordered_map>

std::string replace_vars(const std::string& input) {
    std::unordered_map<std::string, std::string> vars;
    std::stringstream in(input);
    std::stringstream out;

    std::string line;
    bool expect_command = false;

    while (std::getline(in, line)) {

        // definición de variable: $NAME = value
        if (!line.empty() && line[0] == '$') {
            auto eq = line.find('=');
            if (eq != std::string::npos) {
                std::string name = line.substr(1, eq - 1);
                std::string value = line.substr(eq + 1);

                // trim simple
                while (!name.empty() && name.back() == ' ') name.pop_back();
                while (!value.empty() && value.front() == ' ') value.erase(0, 1);

                vars[name] = value;
                continue; // no se emite
            }
        }

        // flag tipo -a
        if (line.size() == 2 && line[0] == '-' &&
            line[1] >= 'a' && line[1] <= 'z') {

            out << line << '\n';
            expect_command = true;
            continue;
        }

        // línea de comando: reemplazo
        if (expect_command) {
            for (auto& [k, v] : vars) {
                std::string key = "$" + k;
                size_t pos = 0;

                while ((pos = line.find(key, pos)) != std::string::npos) {
                    line.replace(pos, key.size(), v);
                    pos += v.size();
                }
            }

            out << line << '\n';
            expect_command = false;
            continue;
        }

        // cualquier otra línea se copia tal cual
        out << line << '\n';
    }

    return out.str();
}
