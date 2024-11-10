#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "Task.h"
#include <algorithm>
#include <condition_variable>
#include <mutex>
// Class declaration
class TaskScheduler {
private:
	std::vector<std::shared_ptr<Task>> tasks_;
	std::condition_variable cv_;
	std::mutex mutex_;

public:
	void addTask(std::shared_ptr<Task> task) {
		std::unique_lock<std::mutex> lock(mutex_);
		tasks_.push_back(task);
		cv_.notify_one();
	}

	size_t getTaskCount() const{
		return tasks_.size();
	}

	std::shared_ptr<Task> getTask(size_t index) const {
		return (index < tasks_.size()) ? tasks_[index] : nullptr;
	}

	void run() {
		while (!tasks_.empty()) {
			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait(lock, [this] { return !tasks_.empty();  });

			auto now = std::chrono::steady_clock::now();

			std::sort(tasks_.begin(), tasks_.end(), [](const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) {
				return a->getPriority() < b->getPriority();
			});

			for (auto it = tasks_.begin(); it != tasks_.end(); ) {
				if ((*it)->getExecutionTime() <= now) {
					(*it)->execute();
					it = tasks_.erase(it);
				}
				else {
					++it;
				}
			}
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	bool cancelTask(std::shared_ptr<Task> task) {
		auto it = std::find(tasks_.begin(), tasks_.end(), task);

		if (it != tasks_.end()) {
			tasks_.erase(it);
			std::cout << "Task cancelled successfully!" << std::endl;
			return true;
		}

		std::cout << "Failed to cancel task successfully." << std::endl;
		return false;
	}
};

#endif