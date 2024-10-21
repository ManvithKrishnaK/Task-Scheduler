#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "Task.h"

class TaskScheduler {
private:
	std::vector<std::shared_ptr<Task>> tasks_;

public:
	void addTask(std::shared_ptr<Task> task) {
		tasks_.push_back(task);
	}

	void run() {
		while (!tasks_.empty()) {
			auto now = std::chrono::steady_clock::now();

			for (auto it = tasks_.begin(); it != tasks_.end(); ) {
				if ((*it)->getExecutionTime() <= now) {
					(*it)->execute();
					it = tasks_.erase(it);
				}
				else {
					++it;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
};

#endif