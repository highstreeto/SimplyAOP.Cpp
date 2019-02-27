#include <iostream>

#include "AspectWeaver.h"
#include "AspectConfiguration.h"
#include "ConsoleTraceAdvice.h"

int main(int argc, char *argv[]) {
    auto config = AspectConfiguration();
    config.addAspect(new ConsoleTraceAdvice());

    auto weaver = AspectWeaver<>(config);

    int c = weaver.advice([](int a, int b){
        std::cout << "  Lambda Call! a = " << a << ", b = " << b << std::endl;
        return a + b;
    }, 1, 10);

    weaver.advice([](){
        std::cout << "  Lambda 2 Call!" << std::endl;
        return 15;
    });

    std::cout << "Finished!" << std::endl;
}