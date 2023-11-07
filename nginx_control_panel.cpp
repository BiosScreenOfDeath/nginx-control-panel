// NGINX Control Panel
// Description: Basically a set of calls for nginx to open/close and 
// run PHP CGI at an IP/Port. Yes, I had nothing better to do.

#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>

using namespace std;

#include <includes/nginxCalls.h>
#include <includes/checks.h>
#include <includes/init.h>

// on execution: runs nginx, allow it to shut down nginx as well
// args: IP, Port default 127.0.0.1:9999

// performance note: constant "string_view" types are faster than most strings 

// if possible, use unique_ptr and vector
// and then string, string_view, shared_ptr, mutex/shared_mutex, unordered_map, std::chrono

int main(int argc, char** argv)
{
    cout << "NGINX Control Panel\n";
    return init(argc, argv);
}