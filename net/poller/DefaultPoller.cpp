#include "EPollPoller.h"
#include "PollPoller.h"
#include "Poller.h"

#include <stdlib.h>

using namespace cppl::net;

Poller *Poller::newDefaultPoller(EventLoop *loop)
{
    if (::getenv("CPPL_USE_POLL"))
    {
        return new PollPoller(loop);
    }
    else
    {
        return new EPollPoller(loop);
    }
}