#pragma once

#include <Values.hpp>
#include <ENV.hpp>
class FunctionCallback {
	public:
		std::string name;
		std::vector<std::string> args;
		std::vector<std::shared_ptr<Values::Runtime>> parsedArgs;
		Environment* env;
		void Errorout(std::string error, bool quit = true){
			std::cout << name << " Errored out" << error << "\n";
			if(quit)
				exit(1);
		}
};
class NativeFN : public Values::Runtime {
	public:
		std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*);
        
		NativeFN(std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*)) : call(call) {}

		std::string type() const override {
			return "native-fn";
		}

		std::string stringValue() const override {
			return "null";
		}

		std::shared_ptr<Values::Runtime> clone() const override {
          return std::make_shared<NativeFN>(NativeFN(call));
        }
};

class ProtoFN : public Values::Runtime {
	public:
		std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*, std::shared_ptr<Values::Runtime>&);
        
		ProtoFN(std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*, std::shared_ptr<Values::Runtime>&)) : call(std::move(call)) {}

		std::string type() const override {
			return "proto-fn";
		}

		std::string stringValue() const override {
			return "null";
		}
};

