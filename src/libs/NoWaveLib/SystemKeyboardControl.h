#ifndef _IDG_AE_SystemKeyboardControl
#define _IDG_AE_SystemKeyboardControl

#include <aunteater/System.h>
#include <aunteater/Engine.h>

class SystemKeyboardControl : public aunteater::System
{
public:
    SystemKeyboardControl(aunteater::Engine &aEngine);

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(float time);

private:
    aunteater::Nodes mKeyboardActionControllers;
    aunteater::Engine & mEngine;
};

#endif  // #ifdef