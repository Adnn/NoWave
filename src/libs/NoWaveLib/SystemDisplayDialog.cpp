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
#include "ComponentActionController.h"
#include <boost/algorithm/string.hpp>

using namespace aunteater;

class NodeDialog
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeDialog::gComponentTypes = { &typeid(ComponentPosition),
                                                       &typeid(ComponentTextList),
                                                       &typeid(ComponentActionController),
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

    // This loop is possibly removing the element it is iterating over (in mEngine.removeEntity)
    // For this reason it needs to increment to the next element before the eventual removal.
    for (std::list<Node>::iterator dialogIt = mDialogs.begin();
         dialogIt != mDialogs.end();
         /*++dialogIt*/)
    {
        Node & dialog = *dialogIt;
        ++dialogIt;

        auto & position = dialog.get<ComponentPosition>();
        auto & textlist = dialog.get<ComponentTextList>();
        const auto action = dialog.get<ComponentActionController>();
        
        textlist.rectangle->setPosition(position.x, position.y);
		textlist.screen->rootEntity.moveChildTop(textlist.rectangle);
        

        if(textlist.highlightRect)
        {
            if(action.down == input_state::BUTTON_FALLING_EDGE)
            {
                textlist.highlightedIndex = textlist.highlightedIndex < (textlist.list.size()-1) ?
                    textlist.highlightedIndex + 1 : 0;
            }
            else if(action.up == input_state::BUTTON_FALLING_EDGE)
            {
                textlist.highlightedIndex = textlist.highlightedIndex /* != 0 */ ?
                    textlist.highlightedIndex - 1 : (textlist.list.size()-1);
            }

            textlist.highlightRect
                ->setPosition(ComponentTextList::gPadding,
                              textlist.highlightedIndex*ComponentTextList::gHeight);
        }

		if(action.buttonA == input_state::BUTTON_FALLING_EDGE)
        {
            textlist.list.at(0).second();
            mEngine.removeEntity(dialog.getEntity());
        }
 		else if(action.buttonZ == input_state::BUTTON_FALLING_EDGE && textlist.list.size()>1)
        {
            textlist.list.at(1).second();
            mEngine.removeEntity(dialog.getEntity());
        }
        else if(action.buttonAction == input_state::BUTTON_FALLING_EDGE)
        {
            textlist.list.at(textlist.highlightedIndex).second();
            mEngine.removeEntity(dialog.getEntity());
        }
    }
}
 