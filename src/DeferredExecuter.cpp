#include "DeferredExecuter.hpp"

std::list<DeferredExecuter::DeferredExecuterData> DeferredExecuter::deList;

DeferredExecuter::DeferredExecuter(){

}

void DeferredExecuter::update() {
    for (auto it = deList.begin(); it != deList.end(); /* no increment here */) {
        unsigned long diff = millis() - it->beginMillis;
        if (diff > it->delay) {
            it->funcPtr();
            it = deList.erase(it);
        } else {
            ++it;
        }
    }
}

void DeferredExecuter::registerFunction(unsigned long delay, void (*funcPtr)()){
    deList.push_back({millis(), delay, funcPtr});
}