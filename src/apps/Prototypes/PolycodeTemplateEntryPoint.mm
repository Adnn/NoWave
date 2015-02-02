//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateEntryPoint.h"

#include "TextBoxDialogs.h"

PolycodeTemplateEntryPoint::PolycodeTemplateEntryPoint(PolycodeView *view)
{
    
	auntCore = new AppCore(new POLYCODE_CORE(view, 1280,640,false,false,0,0,90));
    auntCore->init();

    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
    Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default");
}

PolycodeTemplateEntryPoint::~PolycodeTemplateEntryPoint() {
    
}

bool PolycodeTemplateEntryPoint::Update() {
    return auntCore->update();
}
