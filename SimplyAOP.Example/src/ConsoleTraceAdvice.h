#pragma once

#include <iostream>

#include "Aspect.h"

class ConsoleTraceAdvice : public virtual BeforeAdvice, public virtual AfterAdvice {
    std::string _name = "Console Trace Advice";

public:
    const std::string &name() override {
        return _name;
    }

    void before(BaseInvocation *invoc) override {
        std::cout << "Call start" << std::endl;

        auto *intsInvoc = dynamic_cast<Invocation<int, int, int> *>(invoc);
        if (intsInvoc != nullptr) {
            std::get<0>(intsInvoc->parameters()) = -1;
        }
    }

    void afterReturning(BaseInvocation *invoc) override {
        std::cout << "Call end";

        auto *intsInvoc = dynamic_cast<Invocation<int, int, int> *>(invoc);
        if (intsInvoc != nullptr) {
            std::cout << " = " << intsInvoc->result() << std::endl;
        } else {
            std::cout << std::endl;
        }
    }

    void afterThrowing(BaseInvocation *invoc) override {
        std::cout << "Call failed" << std::endl;
    }
};