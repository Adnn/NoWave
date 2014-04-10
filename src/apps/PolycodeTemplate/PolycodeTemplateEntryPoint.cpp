//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateEntryPoint.h"

#include <NoWaveLib/app.h>

PolycodeTemplateEntryPoint::PolycodeTemplateEntryPoint(PolycodeView *view)
{
    
	juskalamort = new HardCore(new POLYCODE_CORE(view, 1280,640,false,false,0,0,90));
    juskalamort->init();

    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
    Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default");
}

PolycodeTemplateEntryPoint::~PolycodeTemplateEntryPoint() {
    
}

bool PolycodeTemplateEntryPoint::Update() {
    return juskalamort->update();
}