/*
 * Eona Studio (c) 2015
 * Author: Jim Fan
 */
#include "myutils.h"
#include <iostream>
  using std::cerr;
  using std::cout;
  using std::endl;
#include <string>
  using std::string;

#include <boost/program_options.hpp>
  namespace po = boost::program_options;

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread.hpp>

int main(
    int    argc,
    char** argv
)
{
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "display this help")
        ("add,a", po::value< string >(), "add a new entry to the To Do list")
        ;

    bool parseError = false;
    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (po::error& error)
    {
        cerr << "Error: " << error.what() << "\n" << endl;
        parseError = true;
    }

    if (parseError || vm.count("help"))
    {
        cout << "todo:  A simple To Do list program" << "\n";
        cout                                         << "\n";
        cout << "Usage:"                             << "\n";
        cout << "  " << argv[0] << " [options]"      << "\n";
        cout                                         << "\n";
        cout << desc                                 << "\n";

        if (parseError)
        {
            return 64;
        }
        else
        {
            return 0;
        }
    }
    
    boost::shared_mutex mymutex;
    mymutex.lock();

    vector<int> aaa {14, 13, 19, 22, 1};
    cout << aaa << endl;

    boost::thread bth([]() { cout << "hello boost thread" << endl; });
    bth.join();

    return 0;
}
