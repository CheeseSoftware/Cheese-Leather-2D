#include "TaskScheduler.h"


// public:
TaskScheduler::TaskScheduler(size_t threads) : m_stop(false)
{
	for (size_t i = 0; i < threads; ++i)
	{
		m_threadTimePoints.push_back(std::chrono::steady_clock::now());
		m_activeThreads.push_back(false);

		m_threads.emplace_back(
			[=]()
		{
			// Infinite loop:
			for (;;)
			{
				// Lock
				std::unique_lock<std::mutex> lock(this->m_mutex);

				this->m_activeThreads[i] = false;

				// Wait if there is nothing to compute.
				while (!this->m_stop && this->m_tasks.empty())
				{
					this->m_condition_variable_any.wait(lock);
				}

				// This will make the threads to stop on the destructor.
				if (this->m_stop)
					return;

				// get a task to do:
				std::function<void()> task = this->m_tasks[m_nextTaskIndex++];
				std::chrono::steady_clock::time_point timePoint = std::chrono::steady_clock::now();

				this->m_threadTimePoints[i] = timePoint;
				this->m_activeThreads[i] = true;

				lock.unlock();

				// Do the task!
				task();
			}
		}
		);
	}
}

TaskScheduler::~TaskScheduler() {
	// Lock and tell the threads that they should stop.
	{
		std::unique_lock<std::mutex>(m_mutex);
		m_stop = true;
	}
	// Notify all threads about the news.
	m_condition_variable_any.notify_all();

	// Wait until every thread is done.
	for (auto &thread : m_threads)
		thread.join();
}


void TaskScheduler::addTask(std::function<void()> function) {
	// Lock and add the function to the queue
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (m_stop)
			return;

		m_tasks.push_back(function);
	}
	// Notify a the threads!
	m_condition_variable_any.notify_all();

	return;
}

std::chrono::steady_clock::time_point TaskScheduler::getLastTaskTimePoint() {
	std::chrono::steady_clock::time_point timePoint;
	std::lock_guard<std::mutex> lock(m_mutex);

	timePoint = std::chrono::steady_clock::now() + std::chrono::seconds(1);

	for (int i = 0; i < m_threads.size(); ++i)
	{
		if (m_activeThreads[i])
		{
			if (m_threadTimePoints[i] < timePoint)
				timePoint = m_threadTimePoints[i];
		}
	}

	return timePoint;
}

