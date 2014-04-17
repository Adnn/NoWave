//
//  ComponentTextList.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef aunteater_ComponentTextList_h
#define aunteater_ComponentTextList_h

#include <Polycode.h>
#include <aunteater/Component.h>

#include <functional>
#include <string>
#include <list>


typedef std::vector< std::pair<std::string, std::function<void()> > > TextAndCallbackList;

class ComponentTextList : public aunteater::Component
{
public:
    static const int gHeight = 20;

    ComponentTextList(Polycode::Screen *aScreen, TextAndCallbackList aTpl) :
        list(aTpl),
        highlightRect(nullptr),
        highlightedIndex(0),
		screen(aScreen)
    {

//        Polycode::CoreServices::getInstance()->getFontManager()->registerFont("Script", "c:/Windows/Fonts/consola.ttf");
        Polycode::CoreServices::getInstance()->getFontManager()->registerFont("Script", "/Library/Fonts/Impact.ttf");
 
        int i = 0;
        Number maxWidth = 50.;
        std::vector<Polycode::ScreenLabel *> labels;
        for( const TextAndCallbackList::value_type & pair : aTpl)
        {
            Polycode::ScreenLabel * label = new Polycode::ScreenLabel(pair.first, 18,"Script");
            labels.push_back(label);

            maxWidth = std::max(maxWidth, label->getWidth());
            label->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
            label->setPosition(0, i*gHeight);
            label->setColor(Polycode::Color(200, 0, 0, 255));
            ++i;
        }

        rectangle = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT,
                                              maxWidth, 20*aTpl.size());
        rectangle->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);

        if (labels.size() > 1)
        {
            highlightRect = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT,
                                                      maxWidth, gHeight);
            highlightRect->setColor(Polycode::Color(0, 200, 0, 255));
            highlightRect->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);

            rectangle->addChild(highlightRect);
        }

        for (auto label : labels)
        {
            rectangle->addChild(label);
        }

        aScreen->addChild(rectangle);
    }
    
    TextAndCallbackList list;
    Polycode::ScreenShape *rectangle;
    Polycode::ScreenShape *highlightRect;
    int highlightedIndex;
    std::list<Polycode::ScreenLabel *> labels;
    Polycode::Screen * screen;
};


#endif
