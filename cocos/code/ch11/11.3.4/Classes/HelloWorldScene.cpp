#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap,0,100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(x,y));
	addChild(_player, 2, 200);

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	//获得在OpenGL坐标
	Vec2 touchLocation = touch->getLocation();

	Vec2 playerPos = _player->getPosition();
	Vec2 diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(false));
		} else {
			playerPos.x -= _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(true));
		}
	} else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		} else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}
	this->setPlayerPosition(playerPos);
}

void HelloWorld::setPlayerPosition(Vec2 position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord =  this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		
		if (collision == "true") { //碰撞检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	//移动精灵
	_player->setPosition(position);
}

Vec2 HelloWorld::tileCoordFromPosition(Vec2 pos) 
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x,y);
}