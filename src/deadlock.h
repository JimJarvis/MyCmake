/*
 * Eona Studio (c) 2015
 * Author: Jim Fan
 */

#ifndef DEADLOCK_H_
#define DEADLOCK_H_

#include "mythreads.h"
using namespace std;

namespace {

class Dummy
{
public:
	Dummy(int id_, string name_) : id(id_), name(name_) { }

	Dummy& operator=(const Dummy& rhs)
	{
		this->name = rhs.name;
		this->id = rhs.id;
		cout << "guguguu g" << endl;
		return *this;
	}

	void showName() { printf("%s\n", name.c_str()); }
	void showId() { printf("[ID %d]\n", id); }
	// use std::ref when calling in thread
	void mult(int& a)
	{
		a += id;
		printf("[mult %d]\n", id * a );
	}
	friend ostream& operator<<(ostream& oss, Dummy& dum);
private:
	int id; string name;
};

ostream& operator<<(ostream& oss, Dummy& dum)
{
	oss << "[Dummy " << dum.name << ", " << dum.id << "]";
	return oss;
}

// example of deadlock
class SwapLock
{
private:
	Dummy& obj;
	mutex m;

public:
	SwapLock(Dummy& o): obj(o) {}

	friend void swapDeadLock(SwapLock& lhs, SwapLock& rhs);
};

void swapDeadLock(SwapLock& lhs, SwapLock& rhs)
{
	if (&lhs == &rhs) return;
	lock_guard<mutex> lock_l(lhs.m);
	lock_guard<mutex> lock_r(rhs.m);
	std::swap(lhs.obj, rhs.obj);
}

} // anonymous
#endif /* DEADLOCK_H_ */
