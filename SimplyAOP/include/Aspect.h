#pragma once

#include <string>

#include "Invocation.h"

class Aspect {

public:
    virtual const std::string &name() = 0;

    virtual ~Aspect() = default;
};

class BeforeAdvice : public virtual Aspect {

public:
    virtual void before(BaseInvocation *invoc) = 0;

    ~BeforeAdvice() override = default;
};

class AfterAdvice : public virtual Aspect {

public:
    virtual void afterReturning(BaseInvocation *invoc) = 0;

    virtual void afterThrowing(BaseInvocation *invoc) = 0;

    ~AfterAdvice() override = default;
};
