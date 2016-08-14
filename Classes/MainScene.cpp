#include "MainScene.h"
#include "GlobalDefines.h"
#include "MyUtils.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;

std::vector<std::string> _addChileNodeTypeList;

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


MainScene* MainScene::create()
{
	auto ret = new (std::nothrow) MainScene();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	ret = nullptr;
	return nullptr;
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

	auto pngAddNode = CCNode::create();
	pngAddNode->setPosition(visibleSize.width/2, visibleSize.height/2);
	pngAddNode->setName("PngAddNode");
	this->addChild(pngAddNode);
	_addChileNodeTypeList.push_back("PngAddNode");

	auto modelAddNode = CCNode::create();
	modelAddNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	modelAddNode->setName("ModelAddNode");
	this->addChild(modelAddNode);
	_addChileNodeTypeList.push_back("ModelAddNode");

	auto csbAddNode = CCNode::create();
	csbAddNode->setPosition(0, 0);
	csbAddNode->setName("CsbAddNode");
	this->addChild(csbAddNode);
	_addChileNodeTypeList.push_back("CsbAddNode");
    
    return true;
}

void MainScene::addListener()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addCustomEventListener(EVENT_MFC_FILE_TREEVIEW_DOUBLE_CLICK_ITEM, std::bind(&MainScene::onMFCFileTreeViewDClickItem,this, std::placeholders::_1));
}

void MainScene::onMFCFileTreeViewDClickItem(EventCustom* event)
{
	std::wstring* s = static_cast<std::wstring*>(event->getUserData());

	char fullpath[MAX_PATH] = { 0 };
	MyUtils::wcharTochar(s->c_str(), fullpath, sizeof(fullpath));
	std::string filename(fullpath);

	std::string fileExtension;
	size_t pos = filename.find_last_of('.');
	if (pos != std::string::npos)
	{
		fileExtension = filename.substr(pos, filename.length());

		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	}

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
	else if (fileExtension == ".csb")
	{
		auto addNode = getChildByName("CsbAddNode");
		if (addNode)
		{
			auto model = CSLoader::getInstance()->createNode(filename);
			model->setAnchorPoint(Vec2(0.0f, 0.0f));
			addNode->addChild(model);
		}
	}
}

void MainScene::clearAllAddItem()
{
	for (std::string name : _addChileNodeTypeList)
	{
		auto addNode = getChildByName(name);
		if (addNode)
		{
			addNode->removeAllChildrenWithCleanup(true);
		};
	}
}
