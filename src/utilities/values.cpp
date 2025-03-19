#include "../values.hpp"

template <typename T>
T* createValue(std::shared_ptr<Values::Runtime> thing){
	return dynamic_cast<T*>(thing.get());
}

Values::Number* switchNumber(std::shared_ptr<Values::Runtime> thing){
	return dynamic_cast<Values::Number*>(thing.get());
}

Values::String* switchString(std::shared_ptr<Values::Runtime> thing){
	return dynamic_cast<Values::String*>(thing.get());
}

Values::Object* switchObject(std::shared_ptr<Values::Runtime> thing){
	return dynamic_cast<Values::Object*>(thing.get());
}


template <typename T>
std::shared_ptr<T> createValue(T thing){
	return std::make_shared<T>(thing);
}

std::shared_ptr<Values::Null> createNull(){
	return std::make_shared<Values::Null>();
}

std::string getValue(std::shared_ptr<Values::Runtime> val){
	return val->type();
}

bool ValType(std::shared_ptr<Values::Runtime> val, std::string type){
	return val->type() == type;
}

bool hasNullObjects(std::vector<std::string> objs, std::map<std::string, std::shared_ptr<Values::Runtime>> map){
	for(auto obj : objs){
		auto thingy = map[obj];
		
		if(thingy == nullptr)
			return true;
	}

	return false;
}

namespace Values {
    std::string runtimeToJson(const std::shared_ptr<Values::Runtime>& runtime) {
        const std::string& type = runtime->type();
        if (type == "null") {
            return "null";
        } else if (type == "Boolean") {
            return dynamic_cast<const Boolean*>(runtime.get())->stringValue();
        } else if (type == "int") {
            return dynamic_cast<const Number*>(runtime.get())->stringValue();
        } else if (type == "char*") {
            return "\"" + dynamic_cast<const String*>(runtime.get())->stringValue() + "\"";
        } else if (type == "Object") {
            const Object* obj = dynamic_cast<const Object*>(runtime.get());
            return obj ? mapToJson(obj->properties()) : "null";
        } else if (type == "Array") {
            const Array* arr = dynamic_cast<const Array*>(runtime.get());
            return arr ? arrayToJson(arr->elements()) : "[]";
        } else if (type == "Ahell") {
            return "\"" + dynamic_cast<const ShellCommand*>(runtime.get())->output() + "\"";
        } else if (type == "function") {
            return "\"<function>\"";
        }
        return "\"<unknown>\"";
    }

    std::string arrayToJson(const std::vector<std::shared_ptr<Values::Runtime>>& elements) {
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

    std::string mapToJson(const std::map<std::string, std::shared_ptr<Values::Runtime>>& map) {
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