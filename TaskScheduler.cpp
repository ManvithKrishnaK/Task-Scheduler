#include <iostream>
#include <thread>
#include "Task.h"
#include "TaskScheduler.h"

int main() {
    TaskScheduler scheduler;

    auto task1 = std::make_shared<Task>([] { std::cout << "Task 1 executed" << std::endl; }, std::chrono::milliseconds(2000));
    auto task2 = std::make_shared<Task>([] { std::cout << "Task 2 executed" << std::endl; }, std::chrono::milliseconds(1000));
    auto task3 = std::make_shared<Task>([] { std::cout << "Task 3 executed" << std::endl; }, std::chrono::milliseconds(3000));

    scheduler.addTask(task1);
    scheduler.addTask(task2);
    scheduler.addTask(task3);

    scheduler.cancelTask(task3);

    scheduler.run();

    return 0;
}
