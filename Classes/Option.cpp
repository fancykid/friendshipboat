//
//  Option.cpp
//  cash
//
//  Created by kid on 16/5/4.
//
//

#include "Option.hpp"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"

USING_NS_CC;

Scene* Option::scene(RenderTexture* sqr)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Option::create();
    
    // add layer as a child to scene
    scene->addChild(layer, 5);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_spr->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
    back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
    back_spr->setColor(cocos2d::Color3B::GRAY); //图片颜色变灰色
    scene->addChild(back_spr);
    
    // return the scene
    return scene;
}

bool Option::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/optiom.plist","UI/optiom.png");
    
    auto SilenItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_volume.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_Off-Volume.png")),CC_CALLBACK_1(Option::menuSilenCallback, this));
    
    auto BgMusicItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_music.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_off_music.png")),CC_CALLBACK_1(Option::menuBgMusicCallback, this));
    
    auto BackItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_shut-down.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting_btn_shut-down.png")),CC_CALLBACK_1(Option::menuBackCallback, this));
    
    SilenItem->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 100));    //把菜单项添加到菜单精灵中
    
    BgMusicItem->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 100));
    
    BackItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto menu = Menu::create(SilenItem, BgMusicItem, BackItem, NULL);
    menu->setPosition(Vec2::ZERO); //把菜单精灵添加到当前的层中
    this->addChild(menu,6);
    
    return true;
}

void Option::menuSilenCallback(Object* pSender)
{
    UserDefault::getInstance()->setIntegerForKey("bool", 1);
}

void Option::menuBgMusicCallback(Object* pSender)
{
    UserDefault::getInstance()->setIntegerForKey("bool", 0);
}

void Option::menuBackCallback(Object* pSender)
{
    auto boolto=UserDefault::getInstance()->getIntegerForKey("bool");
    if (boolto==1) {
        Director::getInstance()->popScene();
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("UI/bg_music.mp3",true);
        Director::getInstance()->popScene();
    }
}