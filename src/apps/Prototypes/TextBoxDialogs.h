#ifndef _IDG_AE_TextBoxDialogs
#define _IDG_AE_TextBoxDialogs

#include <aunteater/Engine.h>

#include <Polycode.h>

class AppCore
{
public:
    AppCore(Polycode::Core *aCore):
                   mCore(aCore),
                   mScreen(new Polycode::Screen())
    {
        
    }
    
	void init();
   
    bool update()
    {
        Number elapsed = mCore->getElapsed();
		mEngine.update(elapsed);
        return mCore->updateAndRender();
    }
    
private:
    Polycode::Screen *mScreen;
//    Polycode::ScreenImage *image;
    Polycode::Core * mCore;
    aunteater::Engine mEngine;
};

#endif  // #ifdef
