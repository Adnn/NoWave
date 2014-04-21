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

enum class BoxStyle
{
    RECTANGLE,
    THOUGHTS,
};

class ComponentTextList : public aunteater::Component
{
public:
    static const int gHeight = 20;
    static const int gPadding = 5;

    ComponentTextList(Polycode::Screen *aScreen, TextAndCallbackList aTpl, BoxStyle aBoxStyle) :
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
            label->setPosition(gPadding, i*gHeight);
            label->setColor(Polycode::Color(0, 0, 0, 255));
            ++i;
        }

        rectangle = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT,
                                              maxWidth + 2*gPadding, 20*aTpl.size());
        rectangle->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);

        if (aBoxStyle == BoxStyle::THOUGHTS)
        {
            static const Number bubbleDiameter = 20.;
            static const Number bubbleChickenRatio = 4.;
            static const Number bubbleSpacing = bubbleDiameter/1.5;


            Number borderOffset = bubbleDiameter/bubbleChickenRatio;
            Number currentPositionY = borderOffset;
            while( (currentPositionY - bubbleSpacing)
                   < (rectangle->getHeight() - borderOffset) )
            {
                Number currentPositionX = borderOffset;
                while( (currentPositionX - bubbleSpacing)
                       < (rectangle->getWidth() - borderOffset) )
                {
                    drawBubble(rectangle, currentPositionX, currentPositionY, bubbleDiameter);
                    currentPositionX += bubbleSpacing;
                }
                currentPositionY += bubbleSpacing;
            }
        }

        if (labels.size() > 1)
        {
            highlightRect = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT,
                                                      maxWidth, gHeight);
            highlightRect->setColor(Polycode::Color(236, 155, 155, 255));
            highlightRect->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);

            rectangle->addChild(highlightRect);
        }

        for (auto label : labels)
        {
            rectangle->addChild(label);
        }

        aScreen->addChild(rectangle);
    }

void drawBubble(Polycode::ScreenShape * rectangle, Number posX, Number posY, Number bubbleDiameter)
{
    Polycode::ScreenShape *bubble = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_CIRCLE, bubbleDiameter, bubbleDiameter);
    // It is easier to reason in term of the center of the circle
    //  bubble->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
//    bubble->setColor(Polycode::Color(0, 0, 200, 255));
    //bubble->setPosition(0., 0.);
    bubble->setPosition(posX, posY);
    rectangle->addChild(bubble);
}

    TextAndCallbackList list;
    Polycode::ScreenShape *rectangle;
    Polycode::ScreenShape *highlightRect;
    int highlightedIndex;
    std::list<Polycode::ScreenLabel *> labels;
    Polycode::Screen * screen;
};


#endif
