#ifndef TASK_H
#define TASK_H

#include <functional>
#include <chrono>

class Task {
private:
	std::function<void()> func_;
	std::chrono::steady_clock::time_point execution_time_;

public:
	Task(std::function<void()> func, std::chrono::milliseconds delay) : func_(func), execution_time_(std::chrono::steady_clock::now() + delay) {}

	void execute() {
		func_();
	}

	std::chrono::steady_clock::time_point getExecutionTime() const {
		return execution_time_;
	}

};

#endif
