
USING_NS_CC;
#include "scro.hpp"
#include "Player.h"
#include "main.hpp"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"
using namespace cocos2d;
Scene* scro::createScene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = scro::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool scro::init()
{
    
    
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("UI/over.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("UI/over.mp3");
    
    auto sprit=Sprite::create("UI/home_bg3.png");
    sprit->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(sprit);
    
    auto scrot=Sprite::createWithSpriteFrameName("home_fenshu.png");
    scrot->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-80));
    addChild(scrot,1);
    
 
    
    ma1=main::create();
    sc1=UserDefault::getInstance()->getIntegerForKey("currentScore");
    la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",sc1)->getCString(),"Arial",48);
    la->setPosition(Vec2(scrot->getPositionX()+10,scrot->getPositionY()+la->getContentSize().height*0.4));
    la ->setTag(10);
    la->setColor(cocos2d::Color3B(150,200,150));
    addChild(la,2);
    
    
    atop=UserDefault::getInstance()->getIntegerForKey("top");
    if (atop<sc1) {
        UserDefault::getInstance()->setIntegerForKey("top", sc1);
    }
    
    auto top1=UserDefault::getInstance()->getIntegerForKey("top");
    auto la1=cocos2d::Label::createWithSystemFont(__String::createWithFormat("最高分:%d",top1)->getCString(),"Arial",36);
    la1->setPosition(Vec2(scrot->getPositionX()+10,scrot->getPositionY()-la1->getContentSize().height));
    la1 ->setTag(10);
    la1->setColor(cocos2d::Color3B(150,200,150));
    addChild(la1,2);
    
    
    auto bg2=Sprite::createWithSpriteFrameName("home_btn_gold.png");
    bg2->setPosition(Vec2(50,visibleSize.height-bg2->getContentSize().height));
    addChild(bg2,2);
    
    
    auto glod1=UserDefault::getInstance()->getIntegerForKey("glod1");
    auto glod=UserDefault::getInstance()->getIntegerForKey("glod");
    auto glod3=glod+glod1;
    UserDefault::getInstance()->setIntegerForKey("glod1",glod3);
    
    auto  la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",glod3)->getCString(),"Arial",48);
    la->setPosition(Vec2(bg2->getPosition().x+la->getContentSize().width,visibleSize.height-bg2->getContentSize().height));
    addChild(la,2);
    
    
    auto beng=MenuItemFont::create("contine",this,menu_selector(scro::beng));
    beng->setPosition(Vec2(scrot->getPositionX(),scrot->getPosition().y-scrot->getContentSize().height*0.6));
    beng->setFontSizeObj(60);
    auto pme=Menu::create(beng,NULL);
    pme->setPosition(Vec2(0,0));
    addChild(pme);
    
    auto Home=MenuItemFont::create("Home",this,menu_selector(scro::Home));
    Home->setPosition(Vec2(scrot->getPositionX(),scrot->getPosition().y-scrot->getContentSize().height*0.6 - 100));
    Home->setFontSizeObj(60);
    
    auto end=MenuItemFont::create("end",this,menu_selector(scro::end));
    end->setPosition(Vec2(visibleSize.width-50,visibleSize.height-bg2->getContentSize().height));
    end->setFontSizeObj(60);
    end->setColor(cocos2d::Color3B(160,170,180));
    auto pme1=Menu::create(end,Home,NULL);
    pme1->setPosition(Vec2(0,0));
    addChild(pme1);
    
    auto title = Sprite::create("UI/failure_title2.png");
    title->setPosition(Vec2(scrot->getPositionX(), scrot->getPositionY() + 400));
    this->addChild(title,10);
    
    scheduleUpdate();
    
    return true;
}
void scro::beng(Object *test){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    auto kai=main::createScene();
    Director::getInstance()->replaceScene(kai);
    unscheduleUpdate();
}
void scro::end(Object *test){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void scro::update(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void scro::Home(Ref* ref)
{
    auto scen=HomeScene::createScene();
    Director::getInstance()->replaceScene(scen);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}


