#pragma once

#include <utility>

class BaseInvocation {
public:
    virtual ~BaseInvocation() = default;
};

template<typename R, typename... Args>
class Invocation : public BaseInvocation {
    R _result;
    std::tuple<Args...> _parameters;

public:
    explicit Invocation(Args... parameters)
            : _parameters{std::make_tuple(parameters...)} {}

    R &result() {
        return _result;
    }

    std::tuple<Args...> &parameters() {
        return _parameters;
    }
};