#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "Task.h"
#include "TaskScheduler.h"

//Main method
int main() {
    TaskScheduler scheduler;

    std::thread schedulerThread([&scheduler]() { scheduler.run(); });

    // Simulate some delay before adding tasks
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    auto task1 = std::make_shared<Task>([] { std::cout << "Task 1 executed" << std::endl; }, std::chrono::milliseconds(2000));
    auto task2 = std::make_shared<Task>([] { std::cout << "Task 2 executed" << std::endl; }, std::chrono::milliseconds(1000));
    auto task3 = std::make_shared<Task>([] { std::cout << "Task 3 executed" << std::endl; }, std::chrono::milliseconds(3000));

    scheduler.addTask(task1);
    scheduler.addTask(task2);
    scheduler.addTask(task3);

    scheduler.cancelTask(task1);

    schedulerThread.join();
    std::cin.get();
    return 0;
}
