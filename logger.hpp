#pragma once
#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
    static Logger* instance_;
    static std::mutex mutex_;

    std::ofstream logFile;
    std::string fileName;

    Logger(const std::string& file);

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* GetInstance(const std::string& file);
    void Log(const std::string& message);
    void SomeBusinessLogic();
    std::string value() const;
};
 