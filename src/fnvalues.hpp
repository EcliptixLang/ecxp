#pragma once

#include "values.hpp"
#include "./utilities/env.hpp"
class FunctionCallback {
	public:
		std::string name;
		std::vector<std::string> args;
		std::vector<std::shared_ptr<Values::Runtime>> parsedArgs;
		Environment* env;
		void Errorout(std::string error, bool quit = true){
			std::cout << name << " Errored out\n- " << error << "\n";
			if(quit)
				exit(1);
		}
};
namespace Values {
	class NativeFN : public Runtime {
		public:
		std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*);
        
		NativeFN(std::shared_ptr<Values::Runtime>(*call)(FunctionCallback*)) : call(call) {}

		std::string type() const override {
			return "native-fn";
		}

		std::string stringValue() const override {
			return "<nativeFN cppfunc>";
		}

		std::shared_ptr<Values::Runtime> clone() const override {
			std::shared_ptr<Values::Runtime> ptr = std::make_shared<Values::NativeFN>(call);
          return ptr;
        }
	};
}

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

