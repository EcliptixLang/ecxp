#include "../values.hpp"

template <typename T>
T* createValue(std::unique_ptr<Values::Runtime> thing){
	return static_cast<T*>(thing.get());
}

Values::Number* switchNumber(std::unique_ptr<Values::Runtime>& thing){
	return static_cast<Values::Number*>(thing.get());
}

Values::String* switchString(std::unique_ptr<Values::Runtime>& thing){
	return static_cast<Values::String*>(thing.get());
}

Values::Object* switchObject(std::unique_ptr<Values::Runtime>& thing){
	return static_cast<Values::Object*>(thing.get());
}


template <typename T>
std::shared_ptr<T> createValue(T thing){
	return std::make_unique<T>(thing);
}

std::unique_ptr<Values::Null> createNull(){
	return std::make_unique<Values::Null>();
}

Values::Type getValue(std::unique_ptr<Values::Runtime> val){
	return val->type();
}

bool ValType(std::unique_ptr<Values::Runtime> &val, Values::Type type){
	return val->type() == type;
}

bool hasNullObjects(std::vector<std::string> objs, std::map<std::string, std::unique_ptr<Values::Runtime>> map){
	for(auto obj : objs){
		auto it = map.find(obj);
        if (it == map.end() || it->second == nullptr) {
            return true;
        }
	}

	return false;
}

namespace Values {
    std::string runtimeToJson(const std::unique_ptr<Values::Runtime>& runtime) {
        const Type& type = runtime->type();
        if (type == Type::Null) {
            return "null";
        } else if (type == Type::Boolean) {
            return static_cast<const Boolean*>(runtime.get())->stringValue();
        } else if (type == Values::Type::Number) {
            return static_cast<const Number*>(runtime.get())->stringValue();
        } else if (type == Type::String) {
            return "\"" + static_cast<const String*>(runtime.get())->stringValue() + "\"";
        } else if (type == Type::Object) {
            const Object* obj = static_cast<const Object*>(runtime.get());
            return obj ? mapToJson(obj->properties()) : "null";
        } else if (type == Type::Array) {
            const Array* arr = static_cast<const Array*>(runtime.get());
            return arr ? arrayToJson(arr->elements()) : "[]";
        } else if (type == Type::ShellCommand) {
            return "\"" + static_cast<const ShellCommand*>(runtime.get())->output() + "\"";
        } else if (type == Type::Function) {
            return "\"<function>\"";
        }
        return "\"<unknown>\"";
    }

    std::string arrayToJson(const std::vector<std::unique_ptr<Values::Runtime>>& elements) {
        std::string json = "[";
        bool first = true;
        for (const auto& element : elements) {
            if (!first) json += ", ";
            json += runtimeToJson(element);
            first = false;
        }
        json += "]";
        return json;
    }

    std::string mapToJson(const std::map<std::string, std::unique_ptr<Values::Runtime>>& map) {
        std::string json = "{";
        bool first = true;
        for (const auto& [key, value] : map) {
            if (!first) json += ", ";
            json += "\"" + key + "\": " + runtimeToJson(value);
            first = false;
        }
        json += "}";
        return json;
    }
}