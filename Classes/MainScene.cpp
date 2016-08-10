#include "MainScene.h"
#include "GlobalDefines.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addListener();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto pngAddNode = CCNode::create();
	pngAddNode->setPosition(visibleSize.width/2, visibleSize.height/2);
	pngAddNode->setName("PngAddNode");
	this->addChild(pngAddNode);

	auto modelAddNode = CCNode::create();
	modelAddNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	modelAddNode->setName("ModelAddNode");
	this->addChild(modelAddNode);
    
    return true;
}


void MainScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void MainScene::addListener()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addCustomEventListener(EVENT_MFC_FILE_TREEVIEW_DOUBLE_CLICK_ITEM, std::bind(&MainScene::onMFCFileTreeViewDClickItem,this, std::placeholders::_1));
}

void MainScene::onMFCFileTreeViewDClickItem(EventCustom* event)
{
	char* s = static_cast<char*>(event->getUserData());
	std::string filename(s);

	std::string fileExtension;
	size_t pos = filename.find_last_of('.');
	if (pos != std::string::npos)
	{
		fileExtension = filename.substr(pos, filename.length());

		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	}
	
	auto size = Director::getInstance()->getWinSize();

	//清理上一次残留
	clearAllAddItem();

	if (fileExtension == ".png")
	{
		auto addNode = getChildByName("PngAddNode");
		if (addNode)
		{

			auto pic = Sprite::create(filename);
			pic->setAnchorPoint(Vec2(0.5f, 0.5f));
			addNode->addChild(pic);
		}
	}
	else if (fileExtension == ".c3b" || fileExtension == ".c3t")
	{
		auto addNode = getChildByName("ModelAddNode");
		if (addNode)
		{

			auto model = Sprite3D::create(filename);
			model->setAnchorPoint(Vec2(0.5f, 0.5f));
			addNode->addChild(model);
		}
	}
}

void MainScene::clearAllAddItem()
{
	auto pngAddNode = getChildByName("PngAddNode");
	if (pngAddNode)
	{
		pngAddNode->removeAllChildrenWithCleanup(true);
	};

	auto modelAddNode = getChildByName("ModelAddNode");
	if (modelAddNode)
	{
		modelAddNode->removeAllChildrenWithCleanup(true);
	};
}
