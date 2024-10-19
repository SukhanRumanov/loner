#include "logger.hpp"

Logger* Logger::instance_ = nullptr;
std::mutex Logger::mutex_;

Logger::Logger(const std::string& file) : fileName(file) {
    logFile.open(fileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << "������ ���������������\n";
    }
    else {
        std::cerr << "������: " << fileName << std::endl;
    }
}

Logger* Logger::GetInstance(const std::string& file) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_ == nullptr) {
        instance_ = new Logger(file);
    }
    return instance_;
}

void Logger::Log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        std::cout << "������ � ���: " << message << std::endl;
    }
}

void Logger::SomeBusinessLogic() {
    Log("������ ������ ����...");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Log("������ ������ ���������");
}

std::string Logger::value() const {
    return fileName;
}
