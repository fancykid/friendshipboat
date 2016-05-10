//
//  backend.cpp
//  cash
//
//  Created by K@B on 16/5/9.
//
//

#include "backend.hpp"
#include "HomeScene.h"
USING_NS_CC;

Scene* backend::createScene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = backend::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool backend::init()
{
    
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto background=Sprite::create("UI/home_bg4.png");
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    background->setColor(cocos2d::Color3B(70,158,70)); //图片颜色变灰
    background->setOpacity(230);
    addChild(background,1);
    
    auto label=cocos2d::Label::createWithSystemFont("敬请期待。。。。", "",50);
    label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    label->setColor(cocos2d::Color3B::GRAY);
    addChild(label,3);
    auto  fadein=FadeIn::create(0.8);
    auto  fadeout=FadeOut::create(0.5);
    auto  seq=Sequence::create(fadein,fadeout, NULL);
    label->runAction(seq);

    
    scheduleOnce(schedule_selector(backend::backend1), 1);
    return true;
}
void backend::backend1(float dt){
    auto ba=HomeScene::createScene();
     Director::getInstance()->replaceScene(ba);
}
