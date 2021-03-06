//
//  Factories.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__Factories__
#define __aunteater__Factories__

#define BASE_PATH "/Users/adn/projects/Perso/NoWave_Resources/"

//for TextAndCallbackList
#include "ComponentTextList.h"

#include <aunteater/Entity.h>
#include <aunteater/Engine.h>
#include <Polycode.h>

#include <vector>

class ComponentActionController;

aunteater::Entity createPlayer(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createPnj(Polycode::Screen *aScreen);
aunteater::Entity createVideur(Polycode::Screen *aScreen);

/// Makes a copy of the ComponentActionController
aunteater::Entity createTextBox(Polycode::Screen *aScreen, TextAndCallbackList aTpl,
                                float x, float y,
                                BoxStyle aBoxStyle,
                                std::shared_ptr<ComponentActionController> aController);

std::vector<aunteater::Entity> createPng(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBackground(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBarriers();
aunteater::Entity createInteractionVideur(aunteater::Engine &aEngine);

#endif /* defined(__aunteater__Factories__) */
