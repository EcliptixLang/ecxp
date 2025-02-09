#include <Values.hpp>

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
    std::string runtimeToJson(const std::shared_ptr<Runtime> runtime) {
        std::string type = runtime->type();
        if (type == "null") {
            return "null";
        } else if (type == "boolean") {
            return dynamic_cast<Boolean*>(runtime.get())->stringValue();
        } else if (type == "number") {
            return dynamic_cast<Number*>(runtime.get())->stringValue();
        } else if (type == "string") {
            return "\"" + dynamic_cast<String*>(runtime.get())->stringValue() + "\"";
        } else if (type == "object") {
            return mapToJson(dynamic_cast<Object*>(runtime.get())->props);
        } else if (type == "array") {
            return arrayToJson(dynamic_cast<Array*>(runtime.get())->elements);
        } else if (type == "shell") {
            return "\"" + dynamic_cast<ShellCommand*>(runtime.get())->command + "\"";
        } else if (type == "function") {
            return "\"<function>\"";
        }
        return "\"<unknown>\"";
    }

    std::string arrayToJson(const std::vector<std::shared_ptr<Runtime>> elements) {
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

    std::string mapToJson(const std::map<std::string, std::shared_ptr<Runtime>> map) {
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