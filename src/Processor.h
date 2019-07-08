#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>


namespace ik::jucex::task::work_queue
{
	class Manager;

	class Processor : public juce::Thread
	{
	public:
		Processor(unsigned id, Manager* qPtr, int priority = 5);
		~Processor();
		void run() override;
		bool running{ true };
		Manager* workQueue;

	private:
		std::mutex mtx;
	};
}