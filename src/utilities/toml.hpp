#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>

class TOMLParser {
private:
    struct Value {
        enum class Type { String, Integer, Array, Boolean };
        Type type;
        std::string strVal;
        int64_t intVal;
        std::vector<std::string> arrayVal;
		bool boolVal;
    };

    struct Table {
        std::unordered_map<std::string, Value> values;
        std::unordered_map<std::string, std::shared_ptr<Table>> subTables;
    };

    std::vector<std::string> lines;
    std::shared_ptr<Table> rootTable;
    std::shared_ptr<Table> currentTable;

    bool isTableHeader(const std::string& line) {
        return line.front() == '[' && line.back() == ']';
    }

    std::string parseTableName(const std::string& line) {
        return line.substr(1, line.length() - 2);
    }

    Value parseValue(const std::string& raw) {
        Value val;

        // Check if array
        if (raw.front() == '[' && raw.back() == ']') {
            val.type = Value::Type::Array;
            std::string items = raw.substr(1, raw.length() - 2);
            std::stringstream ss(items);
            std::string item;

            while (std::getline(ss, item, ',')) {
                // Trim whitespace and quotes
                item.erase(0, item.find_first_not_of(" \t\""));
                item.erase(item.find_last_not_of(" \t\"") + 1);
                val.arrayVal.push_back(item);
            }
            return val;
        }

        // Check if integer
        try {
            val.intVal = std::stoll(raw);
            val.type = Value::Type::Integer;
            return val;
        } catch (...) {
            // Not an integer
        }

		try {
            val.boolVal = (raw == "true" || raw == "True") ? true : (raw == "false" || raw == "False") ? false : throw std::invalid_argument("Not a boolean");
            val.type = Value::Type::Boolean;
            return val;
        } catch (...) {
            // Not a boolean
        }

        // Default to string
        val.type = Value::Type::String;
        val.strVal = raw;
        return val;
    }
    bool fileExists = true;
public:
    TOMLParser(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            fileExists = false;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }

        rootTable = std::make_shared<Table>();
        currentTable = rootTable;
    }

    template<typename T>
    T getValue(const std::string& tableName, const std::string& key) {
        auto table = tableName.empty() ? rootTable : rootTable->subTables[tableName];
        if (!table) return T();

        auto it = table->values.find(key);
        if (it == table->values.end()) return T();

        if constexpr (std::is_same_v<T, std::string>) {
            return it->second.strVal;
        }
        else if constexpr (std::is_integral_v<T>) {
            return static_cast<T>(it->second.intVal);
        }
        else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
            return it->second.arrayVal;
        }
        return T();
    }

    bool parse() {
        if(!fileExists)
            return false;
        for (const std::string& line : lines) {
            if (line.empty() || line[0] == '#') continue;

            if (isTableHeader(line)) {
                std::string tableName = parseTableName(line);
                auto newTable = std::make_shared<Table>();
                rootTable->subTables[tableName] = newTable;
                currentTable = newTable;
                continue;
            }

            size_t delimPos = line.find('=');
            if (delimPos != std::string::npos) {
                std::string key = line.substr(0, delimPos);
                std::string rawValue = line.substr(delimPos + 1);

                // Trim whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                rawValue.erase(0, rawValue.find_first_not_of(" \t"));
                rawValue.erase(rawValue.find_last_not_of(" \t") + 1);

                currentTable->values[key] = parseValue(rawValue);
            }
        }

        return true;
    }

    bool hasTable(const std::string& tableName) {
        return rootTable->subTables.find(tableName) != rootTable->subTables.end();
    }
};
