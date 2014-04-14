//
//  SystemDisplayDialog.cpp
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#include "SystemDisplayDialog.h"

#include "ComponentSentence.h"
#include "ComponentPosition.h"
#include "ComponentTextList.h"
#include "ComponentKeyboard.h"
#include <boost/algorithm/string.hpp>

using namespace aunteater;

class NodeDialog
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeDialog::gComponentTypes = { &typeid(ComponentPosition),
                                                       &typeid(ComponentTextList),
                                                       &typeid(ComponentKeyboard),
};

SystemDisplayDialog::SystemDisplayDialog(Engine &aEngine) :
        mDialogs(aEngine.getNodes<NodeDialog>()),
        mEngine(aEngine)
{
    
    mEngine.addSystem(this);
}

void SystemDisplayDialog::addedToEngine(aunteater::Engine &aEngine)
{}
    
void SystemDisplayDialog::update(float time)
{
    for(auto & dialog : mDialogs)
    {
        auto & position = dialog.get<ComponentPosition>();
        auto & textlist = dialog.get<ComponentTextList>();
        
        textlist.rectangle->setPosition(position.x, position.y);
		textlist.screen->rootEntity.moveChildTop(textlist.rectangle);
        
        
        Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();
        
        std::string nextSentence("");
		if(keyboard->getKeyState(Polycode::KEY_a))
        {
            nextSentence = textlist.list.at(0).second;
            mEngine.removeEntity(dialog.getEntity());
        }
 		else if(keyboard->getKeyState(Polycode::KEY_z) && textlist.list.size()>1)
        {
            nextSentence = textlist.list.at(1).second;
            mEngine.removeEntity(dialog.getEntity());
        }
        
        if (nextSentence != "")
        {
            std::vector<std::string> strs;
            boost::split(strs, nextSentence, boost::is_any_of("_"));
            
            auto entityHandle = mEngine.getEntity(strs.at(0));
            entityHandle->get<ComponentSentence>()->identifier = nextSentence;
 
        }
    }
}
 