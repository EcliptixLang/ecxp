#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class ArgumentParser {
public:
    ArgumentParser(int argc, char* argv[]) {
        parseArguments(argc, argv);
    }

    bool hasFlag(const std::string& flag) const {
        return flags.find(flag) != flags.end();
    }

    std::vector<std::string> getFlagValues(const std::string& flag) const {
        auto it = flags.find(flag);
        if (it != flags.end()) {
            return it->second;
        }
        return {};
    }

    std::vector<std::string> getPositionalArgs() const {
        return positionalArgs;
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> flags;
    std::vector<std::string> positionalArgs;

    void parseArguments(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg[0] == '-') {
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    flags[arg].push_back(argv[i + 1]);
                    ++i;
                } else {
                    flags[arg].push_back("");
                }
            } else {
                positionalArgs.push_back(arg);
            }
        }
    }
};