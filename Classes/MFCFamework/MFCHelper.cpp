#include "MFCHelper.h"

#include "GlobalDefines.h"
#include "cocos2d.h"
USING_NS_CC;

void MFCHelper::dispatchCocosCustomEvent(const std::string& event, void* userdata)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->dispatchCustomEvent(event, userdata);
}

