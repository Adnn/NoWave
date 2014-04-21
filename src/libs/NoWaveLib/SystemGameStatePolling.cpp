#include "SystemGameStatePolling.h"

#include <NoWaveLib/ComponentAlignment.h>
#include <NoWaveLib/ComponentDrugState.h>
#include <NoWaveLib/ComponentSentence.h>
#include <NoWaveLib/NodeTalker.h>

using namespace aunteater;

SystemGameStatePolling::SystemGameStatePolling(Engine &aEngine) :
        mTalkers(aEngine.getNodes<NodeTalker>()),
        mEngine(aEngine)
{
    mEngine.addSystem(this);
}

void SystemGameStatePolling::addedToEngine(aunteater::Engine &aEngine)
{}
    
void SystemGameStatePolling::update(float time)
{
    for (auto & talker : mTalkers)
    {
        const std::string nextSentenceId = talker.get<ComponentSentence>().identifier;

        if (nextSentenceId == "player_5weird")
        {
            mEngine.getEntity("player")->get<ComponentDrugState>()->name = "piluleR";
            mEngine.getEntity("player")->get<ComponentAlignment>()->sign = "+";
        }
        else if (nextSentenceId == "player_5crache")
        {
            mEngine.getEntity("player")->get<ComponentDrugState>()->name = "piluleR";
            mEngine.getEntity("player")->get<ComponentAlignment>()->sign = "-";
            std::cerr << "Partie negative pillule rouge" << std::endl;
        }

        else if (nextSentenceId == "player_4connard")
        {
            mEngine.getEntity("player")->get<ComponentDrugState>()->name = "piluleV";
            mEngine.getEntity("player")->get<ComponentAlignment>()->sign = "+";
        }
        else if (nextSentenceId == "player_4merci")
        {
            mEngine.getEntity("player")->get<ComponentDrugState>()->name = "piluleV";
            mEngine.getEntity("player")->get<ComponentAlignment>()->sign = "-";
        }
    }
}
