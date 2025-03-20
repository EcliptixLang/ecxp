#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <mutex>
#include "../values.hpp"

namespace Exceptions {

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

};
class Environment {
    public:
        explicit Environment(const Environment* parent = nullptr) 
            : parent_(parent) {}

        Values::Runtime* get(const std::string& name) const noexcept {
            if (auto it = variables_.find(name); it != variables_.end()) {
                return it->second.value.get();
            }
            return parent_ ? parent_->get(name) : nullptr;
        }

        void set(const std::string& name, std::unique_ptr<Values::Runtime> value) {
            variables_[name].value = std::move(value);
        }

        template <typename T, typename... Args>
        void create(const std::string& name, Args&&... args) {
            variables_[name].value = std::make_unique<T>(std::forward<Args>(args)...);
        }

        void enter_scope() {
            if (!child_) {
                child_ = std::make_unique<Environment>(this);
            }
        }

        void leave_scope() {
            if (child_) {
                child_.reset();
            }
        }

    private:
        const Environment* parent_;
        std::unique_ptr<Environment> child_;
        
        struct Variable {
            std::unique_ptr<Values::Runtime> value;
            bool is_constant = false;
        };
        
        std::unordered_map<std::string, Variable> variables_;
    };