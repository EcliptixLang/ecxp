#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include "ast.hpp"

namespace Values {
enum class Type {
    Null,
    Break,
    ReturnedValue,
    Boolean,
    Number,
    String,
    ShellCommand,
    Function,
    Prototype,
    NativeFunction,
    Object,
    Array,
    Skip
};

class Runtime {
public:
    virtual ~Runtime() = default;
    virtual const std::string& stringType() const = 0;
    virtual const Type& type() const = 0;
    virtual const std::string& stringValue() const = 0;
    virtual std::unique_ptr<Runtime> clone() const = 0;
};

std::string runtimeToJson(const std::unique_ptr<Runtime>& runtime);
std::string mapToJson(const std::map<std::string, std::unique_ptr<Runtime>>& map);
std::string arrayToJson(const std::vector<std::unique_ptr<Runtime>>& elements);

template <typename Derived>
class ClonableRuntime : public Runtime {
public:
    std::unique_ptr<Runtime> clone() const override {
        return std::make_unique<Derived>(
            *static_cast<const Derived*>(this)
        );
    }
};

class Null final : public ClonableRuntime<Null> {
    inline static const std::string TYPE = "null";
    inline static const Type _Type = Type::Null;
    inline static const std::string VALUE = "null";
    
public:
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return VALUE; }
};

class Break final : public ClonableRuntime<Break> {
    inline static const std::string TYPE = "break";
    inline static const Type _Type = Type::Break;
    inline static const std::string VALUE = "<break>";
    
public:
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return VALUE; }
};

class ReturnedValue final : public ClonableRuntime<ReturnedValue> {
    std::unique_ptr<Runtime> m_value;
    inline static const std::string TYPE = "return";
    inline static const Type _Type = Type::ReturnedValue;
    
public:
    explicit ReturnedValue(std::unique_ptr<Runtime> value) : m_value(std::move(value)) {}
    ReturnedValue(ReturnedValue&& other) noexcept : m_value(other.m_value ? other.m_value->clone() : nullptr) {}
    ReturnedValue(const ReturnedValue& other) : m_value(other.m_value ? other.m_value->clone() : nullptr) {}
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return m_value->stringValue(); }
    std::unique_ptr<Runtime>& value() { return m_value; }
    std::unique_ptr<Runtime> takeValue() { 
        return std::move(m_value);
    }
};

class Boolean final : public ClonableRuntime<Boolean> {
    bool m_value;
    inline static const std::string TYPE = "boolean";
    inline static const Type _Type = Type::Boolean;
	inline static const std::string v_true = "true";
	inline static const std::string v_false = "false";
    
public:
    explicit Boolean(bool value) : m_value(value) {}
    Boolean(const Boolean& other) = default;
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return m_value ? v_true : v_false; }
    bool value() const { return m_value; }
};

class Number final : public ClonableRuntime<Number> {
    int m_value;
    inline static const std::string TYPE = "int";
    inline static const Type _Type = Type::Number;
    mutable std::string m_stringValue;
    
public:
    explicit Number(int value) : m_value(value) {}
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { 
        m_stringValue = std::to_string(m_value);
        return m_stringValue;
    }
    int value() const { return m_value; }
};

class String final : public ClonableRuntime<String> {
    std::string m_value;
    inline static const std::string TYPE = "char*";
    inline static const Type _Type = Type::String;
    
public:
    explicit String(std::string value) : m_value(std::move(value)) {}
    String(const String& other) = default;
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return m_value; }
    const std::string& value() const { return m_value; }
};

class ShellCommand final : public ClonableRuntime<ShellCommand> {
    std::string m_command;
    std::string m_output;
    inline static const std::string TYPE = "shell";
    inline static const Type _Type = Type::ShellCommand;
    
public:
    ShellCommand(std::string command, std::string output)
        : m_command(std::move(command)), m_output(std::move(output)) {}
    ShellCommand(const ShellCommand& other) = default;
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
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
    inline static const Type _Type = Type::Function;
    
public:
    Function(std::vector<std::shared_ptr<AST::ExprAST>> body,
             std::vector<std::string> parameters,
             std::string name,
             std::string returnType)
        : m_body(std::move(body)),
          m_parameters(std::move(parameters)),
          m_name(std::move(name)),
          m_returnType(std::move(returnType)) {}
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override { return m_name; }
    
    const auto& body() const { return m_body; }
    const auto& parameters() const { return m_parameters; }
    const auto& name() const { return m_name; }
    const auto& returnType() const { return m_returnType; }
};

class Object final : public ClonableRuntime<Object> {
    std::map<std::string, std::unique_ptr<Runtime>> m_properties;
    inline static const std::string TYPE = "Object";
    inline static const Type _Type = Type::Object;
    
public:
    explicit Object(std::map<std::string, std::unique_ptr<Runtime>> props)
        : m_properties(std::move(props)) {}
    
    Object(const Object& other) {
        for (const auto& [key, val] : other.m_properties) {
            m_properties[key] = val->clone();
        }
    }

    std::unique_ptr<Runtime> clone() const override {
        return std::make_unique<Object>(*this);
    }
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override {
        thread_local std::string buffer;
        buffer = mapToJson(m_properties);
        return buffer;
    }
    const std::map<std::string, std::unique_ptr<Runtime>>& properties() const { 
        return m_properties; 
    }
    
    std::map<std::string, std::unique_ptr<Runtime>>& properties() { 
        return m_properties; 
    }
};

class Array final : public ClonableRuntime<Array> {
    std::vector<std::unique_ptr<Runtime>> m_elements;
    inline static const std::string TYPE = "array";
    inline static const Type _Type = Type::Array;

public:
    explicit Array(std::vector<std::unique_ptr<Runtime>> elements)
        : m_elements(std::move(elements)) {}
    Array(const Array& other) {
        for (const auto& element : other.m_elements) {
            m_elements.push_back(element->clone());
        }
    }

    std::unique_ptr<Runtime> clone() const override {
        return std::make_unique<Array>(*this);
    }
    
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
    const std::string& stringValue() const override {
        thread_local std::string buffer;
        buffer = arrayToJson(m_elements);
        return buffer;
    }
    const std::vector<std::unique_ptr<Runtime>>& elements() const {
        return m_elements;
    }
    
    std::vector<std::unique_ptr<Runtime>>& elements() {
        return m_elements;
    }
};

class Skip final : public ClonableRuntime<Skip> {
    inline static const std::string TYPE = "skip";
    inline static const Type _Type = Type::Skip;
    inline static const std::string VALUE = "<skip>";
    
public:
    Skip(const Skip& other) = default;
    const std::string& stringType() const override { return TYPE; }
    const Type& type() const override { return _Type; }
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
T* createValue(std::unique_ptr<Values::Runtime> thing);

Values::Type getValue(std::unique_ptr<Values::Runtime> val);
bool ValType(std::unique_ptr<Values::Runtime> &val, Values::Type type);
bool hasNullObjects(std::vector<std::string> objs, std::map<std::string, std::unique_ptr<Values::Runtime>>& map);
std::unique_ptr<Values::Null> createNull();
Values::Number* switchNumber(std::unique_ptr<Values::Runtime>& thing);
Values::Object* switchObject(std::unique_ptr<Values::Runtime>& thing);
Values::String* switchString(std::unique_ptr<Values::Runtime>& thing);