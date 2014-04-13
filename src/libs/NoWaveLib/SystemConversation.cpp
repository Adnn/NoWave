//
//  SystemConversation.cpp
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#include "SystemConversation.h"

#include "ComponentAddressee.h"
#include "ComponentAlignment.h"
#include "ComponentDrugState.h"
#include "ComponentPosition.h"
#include "ComponentSentence.h"
#include "Factories.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

using namespace aunteater;

class NodeInitiators
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeInitiators::gComponentTypes = { &typeid(ComponentDrugState),
                                                       &typeid(ComponentAddressee),
                                                       &typeid(ComponentAlignment) };

class NodeTalkers
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeTalkers::gComponentTypes = { &typeid(ComponentSentence),
                                                    &typeid(ComponentPosition) };

SystemConversation::SystemConversation(Engine &aEngine,
                                       Polycode::Screen *aScreen,
                                       const std::string &aInitialDoc,
                                       const std::string &aConversationDoc) :
        mInitiators(aEngine.getNodes<NodeInitiators>()),
        mTalkers (aEngine.getNodes<NodeTalkers>()),
        mEngine(aEngine),
        mScreen(aScreen)
{
    
    mEngine.addSystem(this);
    boost::property_tree::read_json(aInitialDoc, mInitialTree);
    boost::property_tree::read_json(aConversationDoc, mConversationTree);
}

void SystemConversation::addedToEngine(Engine &aEngine)
{
}

std::string SystemConversation::stateKey(aunteater::Node &aInitiatorNode)
{
    auto & drugState = aInitiatorNode.get<ComponentDrugState>();
    auto & alignment = aInitiatorNode.get<ComponentAlignment>();
    
    return drugState.name + "_0_0_" + alignment.sign;
}

void SystemConversation::update(float time)
{
    std::cout << "Initers: " << mInitiators.size() << std::endl;
    for (auto & initiator : mInitiators)
    {
        auto & addressee = initiator.get<ComponentAddressee>();
        if (addressee.entityName != "")
        {
            std::cout << '+' ;
            //std::string nextSentenceId = mInitialTree.get<std::string>(addressee.entityName + "." + stateKey(initiator));
			std::string nextSentenceId = "";
			
			BOOST_FOREACH(boost::property_tree::ptree::value_type & value,
                          mInitialTree.get_child(addressee.entityName + "." + stateKey(initiator)))
			{
				nextSentenceId = value.second.get<std::string>("");
				if (nextSentenceId != "")
				{
					break;
				}
			}

			std::vector<std::string> splittedStrings;
			boost::split(splittedStrings, nextSentenceId, boost::is_any_of("_"));
            
            Handle<Entity> nextTalking = mEngine.getEntity(splittedStrings.at(0));
            if ((*nextTalking).has(&typeid(ComponentSentence)))
            {
                auto & nextSentence = *nextTalking->get<ComponentSentence>();
                nextSentence.identifier = nextSentenceId;
            }
            
            // Once the addresse has be handled, remove it from the initiator.
            addressee.entityName = "";
        }
    }
    
    for (auto & talker : mTalkers)
    {
        auto & sentence = talker.get<ComponentSentence>();
        auto & position = talker.get<ComponentPosition>();
        if(sentence.identifier != "")
        {
            TextPairList textPairList;
            
            std::list< std::pair<std::string, std::string> > mParams;
            BOOST_FOREACH(boost::property_tree::ptree::value_type & value,
                          mConversationTree.get_child(sentence.identifier))
            {
                int id = 0;
                std::pair<std::string, std::string> pair;
                BOOST_FOREACH(boost::property_tree::ptree::value_type & subvalue,
                              value.second)
                {
                    if(!id)
                    {
                        pair.first = subvalue.second.get<std::string>("");
                    }
                    else
                    {
                        pair.second = subvalue.second.get<std::string>("");
                    }
                    ++id;
                }
                
                textPairList.push_back(pair);
            }
            
            mEngine.addEntity(createTextBox(mScreen, textPairList, position.x, position.y));
            
            sentence.identifier = "";
        }
    }
}