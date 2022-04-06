#include "../ProcessInfo.h"
#include <inttypes.h>
#include <stdio.h>

int main()
{
    printf("pid = %d\n", cppl::ProcessInfo::pid());
    printf("uid = %d\n", cppl::ProcessInfo::uid());
    printf("euid = %d\n", cppl::ProcessInfo::euid());
    printf("start time = %s\n", cppl::ProcessInfo::startTime().toFormattedString().c_str());
    printf("hostname = %s\n", cppl::ProcessInfo::hostname().c_str());
    printf("opened files = %d\n", cppl::ProcessInfo::openedFiles());
    printf("threads = %zd\n", cppl::ProcessInfo::threads().size());
    printf("num threads = %d\n", cppl::ProcessInfo::numThreads());
    printf("status = %s\n", cppl::ProcessInfo::procStatus().c_str());
}
