//
//  GamePause.cpp
//  FightChild
//
//  Created by kid on 16/4/27.
//
//

#include "GamePause.hpp"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"

USING_NS_CC;

Scene* Gamepause::scene(RenderTexture* sqr)
{
    
    auto *scene = Scene::create();
    Gamepause *layer = Gamepause::create();
    scene->addChild(layer,5);
    //增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
    //并将Sprite添加到GamePause场景层中
    //得到窗口的大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_spr->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
    back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
    back_spr->setColor(cocos2d::Color3B::GRAY); //图片颜色变灰色
    scene->addChild(back_spr);
    return scene;
}

bool Gamepause::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Plist2.plist","UI/Plist2.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/optiom.plist","UI/optiom.png");
    
    //白色背景
    auto sp=Sprite::create("UI/pusebei.png");
    sp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    sp->setOpacity(200);
    addChild(sp,6);
    
    //退出按钮
    auto ContinueItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_shut-down.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_shut-down.png")),CC_CALLBACK_1(Gamepause::menuContinueCallback, this));
    
    ContinueItem->setPosition(Vec2(sp->getPosition().x-sp->getContentSize().width/2, sp->getPosition().y+sp->getContentSize().height/2));    //把菜单项添加到菜单精灵中
    
    //停声音
    auto stopmusic = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_volume.png")),Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_Off-Volume.png")),CC_CALLBACK_1(Gamepause::stopmusic, this));
    stopmusic->setPosition(Vec2(visibleSize.width/2 - stopmusic->getContentSize().width-20,visibleSize.height/2));
    //返回home主页
    auto Homemusic = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("time out_btn_home.png")),Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("time out_btn_home.png")),CC_CALLBACK_1(Gamepause::menuHomeCallback, this));
    Homemusic->setScale(1.5);
    Homemusic->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    //开声音
    auto playmusic = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_music.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_off_music.png")),CC_CALLBACK_1(Gamepause::playmusic, this));
    playmusic->setPosition(Vec2(visibleSize.width/2 + stopmusic->getContentSize().width+20,visibleSize.height/2));
    
    auto menu = Menu::create(ContinueItem,stopmusic,playmusic, Homemusic, NULL);
    menu->setPosition(Vec2::ZERO); //把菜单精灵添加到当前的层中
    this->addChild(menu,6);

    
    
    return true;  
}
//返回战斗的场景的方法
void Gamepause::menuContinueCallback(Object* pSender)
{  
    Director::getInstance()->popScene();
}
////停声音的方法
void Gamepause::stopmusic(CCObject *ps){
    schedule(schedule_selector(Gamepause::stop));
    UserDefault::getInstance()->setIntegerForKey("bool", 1);
}
//停声音的方法
void Gamepause::stop(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
//开声音的方法
void Gamepause::playmusic(CCObject *bj){
    schedule(schedule_selector(Gamepause::play));
    UserDefault::getInstance()->setIntegerForKey("bool", 0);
}
void Gamepause::play(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("UI/bg_music.mp3",true);
}
//返回home的方法
void Gamepause::menuHomeCallback(Object* pSender)
{
    auto scen=HomeScene::createScene();
    Director::getInstance()->replaceScene(scen);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

