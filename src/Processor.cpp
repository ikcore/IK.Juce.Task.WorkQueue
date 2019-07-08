#include "Processor.h"
#include "Manager.h"

namespace ik::jucex::task::work_queue
{
	Processor::Processor(unsigned id, Manager* queue, int priority) : Thread("WQ_" + String(id))
	{
		workQueue = queue;
		startThread(priority);
	}

	Processor::~Processor()
	{
		running = false;
		stopThread(500);
	}

	void Processor::run()
	{
		while (running)
		{
			auto result = workQueue->getNextItem();
			if (result->isOk()) {
				auto item = result->unwrap();
				item->execute();
			}
			else {
				yield();
				wait(1);
			}
		}
	}
}
