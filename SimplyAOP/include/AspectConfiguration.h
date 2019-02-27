#pragma once

#include <list>

#include "Aspect.h"
#include "Invocation.h"

class AspectConfiguration {
    std::list<BeforeAdvice*> _beforeAdvices;
    std::list<AfterAdvice*> _afterAdvices;

public:
    void addAspect(Aspect* aspect) {
        auto* beforeAdvice = dynamic_cast<BeforeAdvice*>(aspect);
        if (beforeAdvice != nullptr) {
            _beforeAdvices.push_back(beforeAdvice);
        }

        auto* afterAdvice = dynamic_cast<AfterAdvice*>(aspect);
        if (afterAdvice != nullptr) {
            _afterAdvices.push_back(afterAdvice);
        }
    }

    const std::list<BeforeAdvice*> beforeAdvices() const {
        return _beforeAdvices;
    }

    const std::list<AfterAdvice*> afterAdvices() const {
        return _afterAdvices;
    }

    virtual ~AspectConfiguration() {
        for (auto & advice : _beforeAdvices) {
            delete advice;
        }
        for (auto & advice : _afterAdvices) {
            delete advice;
        }
    }
};
