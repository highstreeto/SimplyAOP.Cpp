#pragma once

#include <functional>
#include <type_traits>

#include "AspectConfiguration.h"
#include "Invocation.h"
#include "Apply.h"

template<bool catchExceptions = true>
class AspectWeaver {
    AspectConfiguration _config;

public:
    explicit AspectWeaver(const AspectConfiguration &config) : _config(config) {}

    template<typename Function, typename... Args>
    std::result_of_t<Function(Args...)> advice(Function func, Args... args) {
        auto invoc = Invocation<std::result_of_t<Function(Args...)>, Args...>(args...);
        if (catchExceptions) {
            try {
                for (BeforeAdvice *advice : _config.beforeAdvices()) {
                    advice->before(&invoc);
                }
                invoc.result() = apply(func, invoc.parameters());
                for (AfterAdvice *advice : _config.afterAdvices()) {
                    advice->afterReturning(&invoc);
                }
                return invoc.result();
            } catch (std::exception &ex) {
                for (AfterAdvice *advice : _config.afterAdvices()) {
                    advice->afterThrowing(&invoc);
                }
                throw ex;
            }
        } else {
            for (BeforeAdvice *advice : _config.beforeAdvices()) {
                advice->before(&invoc);
            }
            invoc.result() = apply(func, invoc.parameters());
            for (AfterAdvice *advice : _config.afterAdvices()) {
                advice->afterReturning(&invoc);
            }
            return invoc.result();
        }
    }
};