
#include "main.hpp"
#include "BackgoundMove.hpp"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "GamePause.hpp"
#include "HomeScene.h"
USING_NS_CC;


Scene* main::createScene()
{
    auto scene = Scene::create();
    auto layer = main::create();
    scene->addChild(layer);
    return scene;
}


bool main::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Plist2.plist","UI/Plist2.png");
    
    auto bg2=Sprite::createWithSpriteFrameName("home_btn_gold.png");
    bg2->setPosition(Vec2(50,visibleSize.height-bg2->getContentSize().height));
    addChild(bg2,2);
    
    
    label = cocos2d::Label::createWithSystemFont("%d","Arial",48);
    label ->setTag(100);
    label->setPosition(Vec2(bg2->getPosition().x+label->getContentSize().width,visibleSize.height-bg2->getContentSize().height));
    this->addChild(label,4);
    
    
    
    label1 = cocos2d::Label::createWithSystemFont("%d","Arial",48);
    label1 ->setTag(100);
    label1->setPosition(Vec2(visibleSize.width/2,visibleSize.height-bg2->getContentSize().height));
    this->addChild(label1,4);
    
    
    
    
    auto men=MenuItemImage::create("UI/time out_btn_time-out.png","UI/time out_btn_time-out.png",this,menu_selector(main::menuback));
    men->setScale(1.5);
    men->setPosition(Vec2(visibleSize.width - men->getContentSize().width ,
                          visibleSize.height - men->getContentSize().height));
    auto menu1=Menu::create(men,NULL);
    menu1->setPosition(Vec2::ZERO);
    menu1->setAnchorPoint(Vec2::ZERO);
    addChild(menu1,5);
    
    
    
    addChild(BackgoundMove::create());
    ma=Player::create();
    addChild(ma);
    
    
    
    UserDefault::getInstance()->setIntegerForKey("bo",score);
    scheduleUpdate();
    return true;
}
void main::update(float dt){
    glod=ma->glod;
    auto userdefault=UserDefault::getInstance();
    userdefault->setIntegerForKey("glod",glod);
    label->setString(String::createWithFormat("%d",glod)->_string);
    
    score=ma->sc;
    auto userdefault1=UserDefault::getInstance();
    userdefault1->setIntegerForKey("currentScore",score);
    label1->setString(String::createWithFormat("%d",score)->_string);
}
void main::menuback(cocos2d::Ref *ref){
    auto visiable=Director::getInstance()->getVisibleSize();
    auto rend=RenderTexture::create(visiable.width, visiable.height);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    rend->begin();
    this->getParent()->visit();
    rend->end();
    Director::getInstance()->pushScene(Gamepause::scene(rend));
}

