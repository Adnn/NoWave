#include "TextBoxDialogs.h"

#include <NoWaveLib/Factories.h>
#include <NoWaveLib/ComponentActionController.h>
#include <NoWaveLib/SystemDisplayDialog.h>

using namespace aunteater;

void AppCore::init()
{
    auto nullCallback = [](){};

    TextAndCallbackList list = { {"Hello", nullCallback},
                                 {"Goodbye", nullCallback},
                               };

    Entity textBox = createTextBox(mScreen, list, 10, 10,
                                   BoxStyle::THOUGHTS,
                                   std::make_shared<ComponentActionController>() );

    mEngine.addEntity("TB_choice", textBox);

    list = { {"Interesting one liner", nullCallback} };
    textBox = createTextBox(mScreen, list, 10, 100,
                            BoxStyle::RECTANGLE,
                            std::make_shared<ComponentActionController>() );

    mEngine.addEntity("TB_no_choice", textBox);

    new SystemDisplayDialog(mEngine);
}

