#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include "Processor.h"
#include <queue>

namespace ik::jucex::task::work_queue
{
	class Item {
	public:
		Item() {};
		virtual ~Item() {};
		virtual void execute() { DBG("executing item"); }
	private:
	};


	class Result {
	public:
		Result() {};
		~Result() {};

		std::unique_ptr<Item> unwrap() {
			return std::move(item);
		}
		bool isOk() {
			return item != nullptr;
		}
		void setItem(std::unique_ptr<Item> val) {
			item = std::move(val);
		}

	private:
		std::unique_ptr<WorkItem> item = { nullptr };
	};

	class Manager
	{
	public:
		Manager(int numThreads, int priority = 5);
		~Manager();
		std::vector<std::unique_ptr<Processor>> threads;
		std::queue<std::unique_ptr<Item>> items;
		std::unique_ptr<Result> getNextItem();

		void addItem(std::unique_ptr<Item>);
	private:
		unsigned int numCpus{ 0 };
		std::mutex mtx;
	};
}