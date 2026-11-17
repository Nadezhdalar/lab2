#include "LoggingProxy.h"
#include <iostream>
#include <fstream>

void LoggingProxy::log(const std::string& source, const std::string& message) {
    std::string line = source + ": " + message;

    std::cout << line << "\n";

    std::ofstream file("system_log.txt", std::ios::app);
    if (file.is_open()) {
        file << line << "\n";
    }
}
