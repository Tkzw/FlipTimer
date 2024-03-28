#ifndef DEFERRED_EXECUTER_H
#define DEFERRED_EXECUTER_H

#include <M5Core2.h>
#include <list>

class DeferredExecuter{
private:
struct DeferredExecuterData
{
    unsigned long beginMillis;
    unsigned long delay;
    void (*funcPtr)();
};

private:
    DeferredExecuter();

private:
    static std::list<DeferredExecuterData> deList;

public:
    static void update();
    static void registerFunction(unsigned long delay, void (*funcPtr)());
};

#endif