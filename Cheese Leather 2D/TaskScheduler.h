#pragma once

#include <thread>
#include <mutex>
#include <future>
#include <queue>

class TaskScheduler
{
public:
	TaskScheduler(size_t threads);
	~TaskScheduler();

	/* Add tasks you want to be executed routinely in multiple threads.
	* TODO: Add return value "struct RoutinedTask".
	*/
	void addTask(std::function<void()> function);

	// void removeTask(RoutinedTask routinedTask);

	// TODO: EnqueuTask with any type of function.
	//template<class F, class... Args>
	//auto EnqueueTask(F(*function)(Args...), Args... args)
	//	->std::future<F>;

	std::chrono::steady_clock::time_point getLastTaskTimePoint();

private:
	std::vector<std::function<void()>> m_tasks;
	int m_nextTaskIndex = 0;
	std::vector<std::thread> m_threads;
	std::vector<std::chrono::steady_clock::time_point> m_threadTimePoints;
	std::vector<bool> m_activeThreads;

	bool m_stop;
	std::mutex m_mutex;
	std::condition_variable_any m_condition_variable_any;
};

