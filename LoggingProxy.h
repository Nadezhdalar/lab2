#pragma once
#include <string>

class LoggingProxy {
public:
    // единый статический метод логирования с указанием источника 
    static void log(const std::string& source, const std::string& message);
};
