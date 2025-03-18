#include "env.hpp"

namespace Runtime {

Environment::Environment(Ptr parent) 
    : parent_(std::move(parent)) {}

Environment::Ptr Environment::get_parent() const noexcept {
    std::lock_guard lock(mutex_);
    return parent_;
}

void Environment::set_parent(Ptr parent) noexcept {
    std::lock_guard lock(mutex_);
    parent_ = std::move(parent);
}

size_t Environment::parent_depth() const noexcept {
    size_t depth = 0;
    auto current = parent_;
    while(current) {
        depth++;
        current = current->parent_;
    }
    return depth;
}

Variable Environment::get(const std::string& name) const {
    if(exists(name)) {
        std::lock_guard lock(mutex_);
        auto var = find_variable(name);
        return var.clone();
    }
    throw VariableNotFound(name);
}

bool Environment::exists(const std::string& name) const noexcept {
    std::lock_guard lock(mutex_);
    return find_variable(name).value != nullptr;
}

void Environment::set(const std::string& name,
                     std::shared_ptr<Values::Runtime> value,
                     bool is_constant) {
    std::lock_guard lock(mutex_);
    
    auto it = variables_.find(name);
    if(it != variables_.end()) {
        if(it->second.is_constant) {
            throw ConstModificationError(name);
        }
        it->second.value = std::move(value);
        return;
    }
    
    variables_.emplace(name, Variable{name, std::move(value), is_constant});
}

void Environment::safe_set(const std::string& name,
                          std::shared_ptr<Values::Runtime> value) {
    std::lock_guard lock(mutex_);
    
    try {
        auto& var = variables_.at(name);
        if(!var.is_constant) {
            var.value = std::move(value);
        }
    }
    catch(const std::out_of_range&) {
        if(parent_) {
            parent_->safe_set(name, std::move(value));
        }
        else {
            variables_.emplace(name, Variable{name, std::move(value), false});
        }
    }
}

std::unordered_map<std::string, Variable> Environment::get_all_variables() const {
    std::lock_guard lock(mutex_);
    std::unordered_map<std::string, Variable> result;
    for(const auto& [name, var] : variables_) {
        result.emplace(name, var.clone());
    }
    return result;
}

void Environment::merge(const Environment& other) {
    std::scoped_lock lock(mutex_, other.mutex_);
    for(const auto& [name, var] : other.variables_) {
        variables_.emplace(name, var.clone());
    }
}

Variable Environment::thread_safe_get(const std::string& name) const {
    return get(name);
}

void Environment::thread_safe_set(const std::string& name,
                                 std::shared_ptr<Values::Runtime> value,
                                 bool is_constant) {
    set(name, std::move(value), is_constant);
}

Variable Environment::find_variable(const std::string& name) const {
    auto it = variables_.find(name);
    if(it != variables_.end()) {
        return it->second;
    }
    if(parent_) {
        return parent_->find_variable(name);
    }
    return {name, nullptr, false};
}

}