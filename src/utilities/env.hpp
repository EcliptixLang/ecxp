#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <mutex>
#include "../values.hpp"

namespace Runtime {

class EnvironmentException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class VariableNotFound : public EnvironmentException {
public:
    explicit VariableNotFound(const std::string& name)
        : EnvironmentException("Variable not found: " + name) {}
};

class ConstModificationError : public EnvironmentException {
public:
    explicit ConstModificationError(const std::string& name)
        : EnvironmentException("Cannot modify constant variable: " + name) {}
};

struct Variable {
    std::string name;
    std::shared_ptr<Values::Runtime> value;
    bool is_constant;
    
    Variable clone() const {
        return {name, value ? value->clone() : nullptr, is_constant};
    }
};

class Environment : public std::enable_shared_from_this<Environment> {
public:
    using Ptr = std::shared_ptr<Environment>;
    
    explicit Environment(Ptr parent = nullptr);
    
    Ptr get_parent() const noexcept;
    void set_parent(Ptr parent) noexcept;
    size_t parent_depth() const noexcept;
    
    Variable get(const std::string& name) const;
    bool exists(const std::string& name) const noexcept;
    void set(const std::string& name, 
            std::shared_ptr<Values::Runtime> value,
            bool is_constant = false);
    void safe_set(const std::string& name,
                 std::shared_ptr<Values::Runtime> value);
    
    std::unordered_map<std::string, Variable> get_all_variables() const;
    void merge(const Environment& other);
    
    Variable thread_safe_get(const std::string& name) const;
    void thread_safe_set(const std::string& name,
                        std::shared_ptr<Values::Runtime> value,
                        bool is_constant = false);

private:
    mutable std::mutex mutex_{};
    Ptr parent_;
    std::unordered_map<std::string, Variable> variables_;
    
    Variable find_variable(const std::string& name) const;
};

}