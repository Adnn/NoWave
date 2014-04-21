#include "NodeTalker.h"

#include <NoWaveLib/ComponentSentence.h>
#include <NoWaveLib/ComponentPosition.h>

using namespace aunteater;

const ArchetypeTypeSet NodeTalker::gComponentTypes = { &typeid(ComponentSentence),
                                                       &typeid(ComponentPosition) };
