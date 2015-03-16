/*
 * Eona Studio (c) 2015
 * Author: Jim Fan
 */
#include "mythreads.h"
#include "deadlock.h"
#include <boost/thread.hpp>
using namespace std;

void hello(int i)
{
	printf("dudulu %d\n", i);
}

int main(int argc, char **argv)
{
	vector<thread> thvec;
    vector<int> veca {1};
    if (argc > 1)
        cout << "argc " << argv[1] << argv[1] << endl;
    else
    {
        for (auto i : veca)
            thvec.push_back(thread(hello, i));
        for_each(thvec.begin(), thvec.end(), mem_fn(&thread::join));
        cout << "hardware=" <<  thread::hardware_concurrency() << endl;
    }

    boost::thread ttt(hello, 199);
    ttt.join();
}
