#ifndef TASK_H
#define TASK_H

#include <functional>

#include <chrono>
//Class declaration
class Task {
private:
	std::function<void()> func_;
	std::chrono::steady_clock::time_point execution_time_;
	int priority_;

public:
	Task(std::function<void()> func, std::chrono::milliseconds delay, int priority = 0) : func_(func), execution_time_(std::chrono::steady_clock::now() + delay), priority_(priority) {}

	void execute() {
		func_();
	}

	std::chrono::steady_clock::time_point getExecutionTime() const {
		return execution_time_;
	}

	int getPriority() const {
		return priority_;
	}

};

#endif
