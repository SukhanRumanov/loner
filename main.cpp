#include <iostream>
#include <thread>
#include "logger.hpp"

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
