#include "app.h"

#include "Factories.h"

#include "SystemZReorder.h"
#include "SystemDisplay.h"
#include "SystemMove.h"
#include "InputSystem.h"
#include "SystemAnimation.h"
#include "SystemMoveAnimation.h"
#include "SystemScaling.h"
#include "SystemCollision.h"
#include "SystemConversation.h"
#include "SystemInteraction.h"
#include "SystemDisplayDialog.h"
#include "SystemKeyboardControl.h"
#include "SystemGameStatePolling.h"

using namespace aunteater;

void HardCore::init()
{
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);

	Entity player = createPlayer(mScreen);
	mEngine.addEntity("player", player);

	std::vector<Entity> bgs = createBackground(mScreen);
	for (Entity bg : bgs)
	{
		mEngine.addEntity(bg);
	}

	std::vector<Entity> pngs = createPnj(mScreen);
    // Quick hack so a 'meuf' is actually addressable
    bool first = true;
	for (Entity png : pngs)
	{
        if (first)
        {
            first = false;
            mEngine.addEntity("meuf", png);
        }
        {
            mEngine.addEntity(png);
        }
	}


	std::vector<Entity> barriers = createBarriers();
	for (Entity barrier : barriers)
	{
		mEngine.addEntity(barrier);
	}

	Entity videur = createVideur(mScreen);
	mEngine.addEntity("videur", videur);

	Entity inter = createInteractionVideur(mEngine);
	mEngine.addEntity(inter);

	new SystemDisplay(mEngine,*mScreen);
    new SystemKeyboardControl(mEngine);
	new SystemMove(mEngine);
	new InputSystem(mEngine);
	new SystemAnimation(mEngine);
	new SystemMoveAnimation(mEngine);
	new SystemScaling(mEngine);
	new SystemCollision(mEngine);
	new SystemZReorder(mEngine);
    new SystemConversation(mEngine,
                           mScreen,
                           BASE_PATH "scenarios/accroche.txt",
                           BASE_PATH "scenarios/conversation.txt");
	new SystemInteraction(mEngine);
	new SystemDisplayDialog(mEngine);
    new SystemGameStatePolling(mEngine);
}