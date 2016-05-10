
#include "BackgoundMove.hpp"
#include "Player.h"
#include "HomeScene.h"
USING_NS_CC;

Scene* BackgoundMove::createScene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = BackgoundMove::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool BackgoundMove::init()
{
    
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    //路
    sp=Sprite::create("UI/home_bg6.png");
    sp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(sp,1);
    
    //路
    sp1=Sprite::create("UI/home_bg6.png");
    sp1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(sp1,1);
    
    scheduleUpdate();
    
    ma=Player::create();
    with=visibleSize.width;
    with1=visibleSize.width;
    
    speed=5;

    return true;
}
//背景滚动的方法
void BackgoundMove::update(float time)
{
    speed=UserDefault::getInstance()->getIntegerForKey("speed");
    speed=UserDefault::getInstance()->getIntegerForKey("speed");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    with-=speed;
    if (with<=0) {
        with=visibleSize.width;
    }
    sp->setPositionX(with-with1/2);
    sp1->setPositionX(with+with1/2);
}
