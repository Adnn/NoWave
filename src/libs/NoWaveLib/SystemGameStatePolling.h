#ifndef _IDG_AE_SystemGameStatePolling
#define _IDG_AE_SystemGameStatePolling

#include <aunteater/System.h>
#include <aunteater/Engine.h>


class SystemGameStatePolling : public aunteater::System
{
public:
    SystemGameStatePolling(aunteater::Engine &aEngine);
    
    virtual void addedToEngine(aunteater::Engine &aEngine);
    
    virtual void update(float time);
    
private:
    aunteater::Nodes mTalkers;
    aunteater::Engine & mEngine;
};

#endif  // #ifdef