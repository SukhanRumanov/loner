#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
    static Logger* instance_;     
    static std::mutex mutex_;     

    std::ofstream logFile;          
    std::string fileName;           

    
    Logger(const std::string& file) : fileName(file) {
        logFile.open(fileName, std::ios::app);  
        if (logFile.is_open()) {
            logFile << "Логгер инициализирован\n";
        }
        else {
            std::cerr << "ошибка: " << fileName << std::endl;
        }
    }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    
    static Logger* GetInstance(const std::string& file) {
        std::lock_guard<std::mutex> lock(mutex_); 
        if (instance_ == nullptr) {
            instance_ = new Logger(file);
        }
        return instance_;
    }
    void Log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);  
        if (logFile.is_open()) {
            logFile << message << std::endl;
            std::cout << "Запись в лог: " << message << std::endl;  
        }
    }

    void SomeBusinessLogic() {
        Log("Бизнес логика идет...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  
        Log("Бизнес логика завершена");
    }

    std::string value() const {
        return fileName;
    }
};

Logger* Logger::instance_ = nullptr;
std::mutex Logger::mutex_;

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
    Logger* logger = Logger::GetInstance("log.txt");
    logger->SomeBusinessLogic();
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
    Logger* logger = Logger::GetInstance("log.txt");
    logger->SomeBusinessLogic();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);

    t1.join();
    t2.join();

    return 0;
}
