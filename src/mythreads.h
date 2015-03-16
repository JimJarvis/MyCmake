/*
 * Eona Studio (c) 2015
 * Author: Jim Fan
 */

#ifndef MYTHREADS_H_
#define MYTHREADS_H_

#include "myutils.h"
#include <thread>
#include <mutex>
using std::thread;
using std::mutex;
using std::lock;
using std::lock_guard;

// anonymous namespace to avoid multiple definition linker error
namespace {

// RAII guard a thread
class ThreadGuard
{
public:
	// construct directly with R-value temp object
	explicit ThreadGuard(thread t_):
		t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("ThreadGuard: no thread joinable");
	}

	~ThreadGuard()
	{
		t.join();
	}

	thread& get() { return t;	}

	thread::id get_id() { return t.get_id();	}

	// disable assignment and copy ctor
	ThreadGuard(ThreadGuard const&) =delete;
	ThreadGuard& operator=(ThreadGuard const&) =delete;

private:
	thread t;
};

thread::id getThreadId(thread& t) { return t.get_id();	}
thread::id getThreadId(ThreadGuard& tg) { return tg.get_id();	}
thread::id getThisThreadId() { return std::this_thread::get_id();	}
}

#endif /* MYTHREADS_H_ */
