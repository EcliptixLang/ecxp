#pragma once

#include "values.hpp"
#include "./utilities/env.hpp"
#include <functional>
#include <memory>

namespace Values {

class FunctionCallback {
public:
    std::string name;
    std::vector<std::string> args;
    std::vector<std::shared_ptr<Runtime>> parsedArgs;
    std::shared_ptr<::Runtime::Environment> env;

    void Errorout(const std::string& error, bool quit = true) noexcept {
        std::cout << name << " Errored out\n- " << error << std::endl;
        if (quit) {
            exit(7);
        }
    }
};

class NativeFN : public Runtime {
public:
    using NativeFunction = std::function<std::shared_ptr<Runtime>(FunctionCallback*)>;
    NativeFunction call;

    explicit NativeFN(NativeFunction func) : call(std::move(func)) {}

    const std::string& type() const override {
        static const std::string TYPE = "native-fn";
        return TYPE;
    }

    const std::string& stringValue() const override {
        static const std::string VALUE = "<nativeFN>";
        return VALUE;
    }

    std::shared_ptr<Runtime> clone() const override {
        return std::make_shared<NativeFN>(*this);
    }
};

class ProtoFN : public Runtime {
public:
    using ProtoFunction = std::function<std::shared_ptr<Runtime>(FunctionCallback*, 
                                const std::shared_ptr<Runtime>&)>;
    ProtoFunction call;

    explicit ProtoFN(ProtoFunction func) : call(std::move(func)) {}

    const std::string& type() const override {
        static const std::string TYPE = "proto-fn";
        return TYPE;
    }

    const std::string& stringValue() const override {
        static const std::string VALUE = "<protoFN>";
        return VALUE;
    }

    std::shared_ptr<Runtime> clone() const override {
        return std::make_shared<ProtoFN>(*this);
    }
};

}