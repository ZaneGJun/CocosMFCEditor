#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually

protected:
	void addListener();
	void onMFCFileTreeViewDClickItem(EventCustom* event);

	void clearAllAddItem();
};

#endif // __HELLOWORLD_SCENE_H__