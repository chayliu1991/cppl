#include "../FileUtil.h"
#include <inttypes.h>
#include <stdio.h>

using namespace cppl;

int main()
{
    string result;
    int64_t size = 0;
    int err = FileUtil::readFile("/proc/self", 1024, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/proc/self", 1024, &result, NULL);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/proc/self/cmdline", 1024, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/dev/null", 1024, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/dev/zero", 1024, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/notexist", 1024, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/dev/zero", 102400, &result, &size);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
    err = FileUtil::readFile("/dev/zero", 102400, &result, NULL);
    printf("%d %zd %" PRIu64 "\n", err, result.size(), size);
}
