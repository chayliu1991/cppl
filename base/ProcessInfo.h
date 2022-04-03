#pragma once

#include "StringPiece.h"
#include "Timestamp.h"
#include "Types.h"

#include <sys/types.h>
#include <vector>

namespace cppl
{
    namespace ProcessInfo
    {
        pid_t pid();
        std::string pidString();
        uid_t uid();
        string username();
        uid_t euid();
        Timestamp startTime();
        int clockTicksPerSecond();
        int pageSize();
        bool isDebugBuild(); // constexpr

        std::string hostname();
        std::string procname();
        StringPiece procname(const std::string &stat);

        /// read /proc/self/status
        string procStatus();

        /// read /proc/self/stat
        string procStat();

        /// read /proc/self/task/tid/stat
        string threadStat();

        /// readlink /proc/self/exe
        string exePath();

        int openedFiles();
        int maxOpenFiles();

        struct CpuTime
        {
            double userSeconds;
            double systemSeconds;

            CpuTime() : userSeconds(0.0), systemSeconds(0.0) {}

            double total() const { return userSeconds + systemSeconds; }
        };
        CpuTime cpuTime();

        int numThreads();
        std::vector<pid_t> threads();
    }
}
