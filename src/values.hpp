#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include "ast.hpp"

namespace Values {

class Runtime {
public:
    virtual ~Runtime() = default;
    virtual const std::string& type() const = 0;
    virtual const std::string& stringValue() const = 0;
    virtual std::shared_ptr<Runtime> clone() const = 0;
};

std::string runtimeToJson(const std::shared_ptr<Runtime>& runtime);
std::string mapToJson(const std::map<std::string, std::shared_ptr<Runtime>>& map);
std::string arrayToJson(const std::vector<std::shared_ptr<Runtime>>& elements);

template <typename Derived>
class ClonableRuntime : public Runtime {
public:
    std::shared_ptr<Runtime> clone() const override {
        return std::make_shared<Derived>(static_cast<const Derived&>(*this));
    }
};

class Null final : public ClonableRuntime<Null> {
    inline static const std::string TYPE = "null";
    inline static const std::string VALUE = "null";
    
public:
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return VALUE; }
};

class Break final : public ClonableRuntime<Break> {
    inline static const std::string TYPE = "break";
    inline static const std::string VALUE = "<break>";
    
public:
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return VALUE; }
};

class ReturnedValue final : public ClonableRuntime<ReturnedValue> {
    std::shared_ptr<Runtime> m_value;
    inline static const std::string TYPE = "return";
    
public:
    explicit ReturnedValue(std::shared_ptr<Runtime> value) : m_value(std::move(value)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return m_value->stringValue(); }
    std::shared_ptr<Runtime> value() const { return m_value; }
};

class Boolean final : public ClonableRuntime<Boolean> {
    bool m_value;
    inline static const std::string TYPE = "boolean";
	inline static const std::string v_true = "true";
	inline static const std::string v_false = "false";
    
public:
    explicit Boolean(bool value) : m_value(value) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return m_value ? v_true : v_false; }
    bool value() const { return m_value; }
};

class Number final : public ClonableRuntime<Number> {
    int m_value;
    inline static const std::string TYPE = "int";
    mutable std::string m_stringValue;
    
public:
    explicit Number(int value) : m_value(value) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { 
        m_stringValue = std::to_string(m_value);
        return m_stringValue;
    }
    int value() const { return m_value; }
};

class String final : public ClonableRuntime<String> {
    std::string m_value;
    inline static const std::string TYPE = "char*";
    
public:
    explicit String(std::string value) : m_value(std::move(value)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return m_value; }
    const std::string& value() const { return m_value; }
};

class ShellCommand final : public ClonableRuntime<ShellCommand> {
    std::string m_command;
    std::string m_output;
    inline static const std::string TYPE = "shell";
    
public:
    ShellCommand(std::string command, std::string output)
        : m_command(std::move(command)), m_output(std::move(output)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return m_output; }
    const std::string& command() const { return m_command; }
    const std::string& output() const { return m_output; }
};

class Function final : public ClonableRuntime<Function> {
    std::vector<std::shared_ptr<AST::ExprAST>> m_body;
    std::vector<std::string> m_parameters;
    std::string m_name;
    std::string m_returnType;
    inline static const std::string TYPE = "function";
    
public:
    Function(std::vector<std::shared_ptr<AST::ExprAST>> body,
             std::vector<std::string> parameters,
             std::string name,
             std::string returnType)
        : m_body(std::move(body)),
          m_parameters(std::move(parameters)),
          m_name(std::move(name)),
          m_returnType(std::move(returnType)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return m_name; }
    
    const auto& body() const { return m_body; }
    const auto& parameters() const { return m_parameters; }
    const auto& name() const { return m_name; }
    const auto& returnType() const { return m_returnType; }
};

class Object final : public ClonableRuntime<Object> {
    std::map<std::string, std::shared_ptr<Runtime>> m_properties;
    inline static const std::string TYPE = "Object";
    
public:
    explicit Object(std::map<std::string, std::shared_ptr<Runtime>> props)
        : m_properties(std::move(props)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override {
        thread_local std::string buffer;
        buffer = mapToJson(m_properties);
        return buffer;
    }
    const auto& properties() const { return m_properties; }
};

class Array final : public ClonableRuntime<Array> {
    std::vector<std::shared_ptr<Runtime>> m_elements;
    inline static const std::string TYPE = "array";
    
public:
    explicit Array(std::vector<std::shared_ptr<Runtime>> elements)
        : m_elements(std::move(elements)) {}
    
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override {
        thread_local std::string buffer;
        buffer = arrayToJson(m_elements);
        return buffer;
    }
    const auto& elements() const { return m_elements; }
};

class Skip final : public ClonableRuntime<Skip> {
    inline static const std::string TYPE = "skip";
    inline static const std::string VALUE = "<skip>";
    
public:
    const std::string& type() const override { return TYPE; }
    const std::string& stringValue() const override { return VALUE; }
};

template <typename T>
std::shared_ptr<T> value_cast(const std::shared_ptr<Runtime>& value) {
    if (auto casted = std::dynamic_pointer_cast<T>(value)) {
        return casted;
    }
    throw std::runtime_error("Invalid value type cast");
}

}

template <typename T>
T* createValue(std::shared_ptr<Values::Runtime> thing);

std::string getValue(std::shared_ptr<Values::Runtime> val);
bool ValType(std::shared_ptr<Values::Runtime> val, std::string type);
bool hasNullObjects(std::vector<std::string> objs, std::map<std::string, std::shared_ptr<Values::Runtime>> map);
std::shared_ptr<Values::Null> createNull();
Values::Number* switchNumber(std::shared_ptr<Values::Runtime> thing);
Values::Object* switchObject(std::shared_ptr<Values::Runtime> thing);
Values::String* switchString(std::shared_ptr<Values::Runtime> thing);