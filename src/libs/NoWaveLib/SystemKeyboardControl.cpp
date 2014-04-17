#include "SystemKeyboardControl.h"

#include "ComponentKeyboard.h"
#include "ComponentActionController.h"

#include <Polycode.h>

using namespace aunteater;

class NodeKeyboardActionController
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeKeyboardActionController::gComponentTypes =
    { &typeid(ComponentKeyboard),
      &typeid(ComponentActionController) };

SystemKeyboardControl::SystemKeyboardControl(aunteater::Engine &aEngine) :
    mKeyboardActionControllers(aEngine.getNodes<NodeKeyboardActionController>()),
    mEngine(aEngine)
{
    mEngine.addSystem(this);
}

void SystemKeyboardControl::addedToEngine(aunteater::Engine &aEngine)
{}

void buttonUpdate(Polycode::CoreInput *aKeyboard,
                  input_state &aButton, Polycode::PolyKEY aKey)
{
    if(aKeyboard->getKeyState(aKey))
    {
        aButton = isDown(aButton) ?
                  input_state::BUTTON_DOWN : input_state::BUTTON_FALLING_EDGE;
    }
    else
    {
        aButton = isUp(aButton) ?
                  input_state::BUTTON_UP : input_state::BUTTON_RISING_EDGE;
    }
}

void SystemKeyboardControl::update(float time)
{
    Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();

    for (auto & keyboardActionCtrl : mKeyboardActionControllers)
    {
        ComponentActionController & actionController =
            keyboardActionCtrl.get<ComponentActionController>();

        buttonUpdate(keyboard, actionController.up, Polycode::KEY_UP);
        buttonUpdate(keyboard, actionController.down, Polycode::KEY_DOWN);
        buttonUpdate(keyboard, actionController.left, Polycode::KEY_LEFT);
        buttonUpdate(keyboard, actionController.right, Polycode::KEY_RIGHT);
        buttonUpdate(keyboard, actionController.buttonAction, Polycode::KEY_SPACE);
        buttonUpdate(keyboard, actionController.buttonA, Polycode::KEY_a);
        buttonUpdate(keyboard, actionController.buttonZ, Polycode::KEY_z);
    }
}
