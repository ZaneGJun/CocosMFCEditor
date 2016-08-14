#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static MainScene* create();

    virtual bool init();

protected:
	void addListener();
	void onMFCFileTreeViewDClickItem(EventCustom* event);
	void onMFCPropertyBaseChange(EventCustom* event);
	void onMFCPropertyModelAnimateChange(EventCustom* event);
	void onMFCPropertyModelMaterialChange(EventCustom* event);

	void clearAllAddItem();
};

#endif // __HELLOWORLD_SCENE_H__
