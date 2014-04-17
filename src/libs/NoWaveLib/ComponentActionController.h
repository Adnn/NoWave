#ifndef _IDG_AE_ComponentActionController
#define _IDG_AE_ComponentActionController

#include <aunteater/Component.h>

static const int EDGE_MASK = 0x04;
enum class input_state
{
    BUTTON_UP = 0x01,
    BUTTON_RISING_EDGE = BUTTON_UP + EDGE_MASK,
    BUTTON_DOWN = 0x02,
    BUTTON_FALLING_EDGE = BUTTON_DOWN + EDGE_MASK,


};

class ComponentActionController : public aunteater::Component
{
public:
    input_state up;
    input_state down;
    input_state left;
    input_state right;

    input_state buttonAction;
    input_state buttonA;
    input_state buttonZ;

};

inline bool isUp(input_state aState)
{
    return static_cast<int>(aState) & static_cast<int>(input_state::BUTTON_UP);
}

inline bool isDown(input_state aState)
{
    return static_cast<int>(aState) & static_cast<int>(input_state::BUTTON_DOWN);
}

#endif  // #ifdef
