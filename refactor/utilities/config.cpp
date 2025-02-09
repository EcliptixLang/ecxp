#include <string>
#include <iostream>
#include "toml.hpp"
#include "../config.hpp"

using std::cerr;

void error(std::string msg)
{
    cerr << "ERROR: " << msg << "\n";
    exit(1);
}
void warn(std::string msg)
{
    cerr << "WARNING: " << msg << "\n";
}

Settings config() {
    Settings settings;
    TOMLParser parser("config.ecc");

    bool parsed = parser.parse();
    if (!parsed) {
        warn("cannot parse config file, using defaults...");
        return settings;
    }

    if (!parsed) {
        warn("missing [project] table");
    } else {

        std::string name = parser.getValue<std::string>("", "name");
        if (name.empty()) {
            warn("missing or bad project name entry");
        } else {
            settings.project.name = name;
        }

        std::string ver = parser.getValue<std::string>("", "version");
        if (ver.empty()) {
            warn("missing or bad project version entry");
        } else {
            settings.project.version = ver;
        }
    }

    if (!parsed) {
        warn("missing [interpreter] table");
    } else {

        int wennie = parser.getValue<int>("", "max_when");
        if (!wennie) {
            warn("missing or bad interpreter max when entry");
        } else {
            settings.interpreter.max_when = wennie;
        }

    }

    return settings;
}
