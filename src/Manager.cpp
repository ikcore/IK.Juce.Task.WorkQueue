#include "Manager.h"

namespace ik::jucex::task::work_queue
{
	// std::thread::hardware_concurrency()
	// this is useful 

	Manager::Manager(int nthreads, int priority) : threads(nthreads)
	{
		numCpus = nthreads;

		DBG("Worker Queue Manager Started with : " + String(numCpus) + " threads");

		for (unsigned i = 0; i < numCpus; i++)
		{
			threads.push_back(std::make_unique<Processor>(i, this, priority));
		}
	}

	Manager::~Manager()
	{
		std::lock_guard<std::mutex> lk(mtx);
		while (!items.empty())
			items.pop();
	}

	void Manager::addItem(std::unique_ptr<Item> item)
	{
		std::lock_guard<std::mutex> lk(mtx);
		items.push(std::move(item));
	}

	std::unique_ptr<Result> Manager::getNextItem()
	{
		std::lock_guard<std::mutex> lk(mtx);

		if (items.size() > 0) {
			auto result = std::make_unique<Result>();
			result->setItem(std::move(items.front()));
			items.pop();
			return std::move(result);
		}
		else
		{
			auto result = std::make_unique<Result>();
			return std::move(result);
		}
	}
}

