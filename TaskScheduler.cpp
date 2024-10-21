#include <iostream>
#include <thread>
#include "Task.h"
#include "TaskScheduler.h"

int main() {
    TaskScheduler scheduler;

    scheduler.addTask(std::make_shared<Task>([] { std::cout << "Task 1 executed" << std::endl; }, std::chrono::milliseconds(2000)));
    scheduler.addTask(std::make_shared<Task>([] { std::cout << "Task 2 executed" << std::endl; }, std::chrono::milliseconds(1000)));
    scheduler.addTask(std::make_shared<Task>([] { std::cout << "Task 3 executed" << std::endl; }, std::chrono::milliseconds(3000)));

    scheduler.run();

    return 0;
}
