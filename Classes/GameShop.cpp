//
//  GameShop.cpp
//  cash
//
//  Created by kid on 16/5/4.
//
//

#include "GameShop.hpp"
#include "HomeScene.h"
#include "Player.h"

USING_NS_CC;
using namespace cocos2d;
Scene* GameShop::createScene()
{
    auto scene = Scene::create();
    
    
    auto layer = GameShop::create();
    
    
    scene->addChild(layer);
    
    
    
    return scene;
}

bool GameShop::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Plist1.plist","UI/Plist1.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Plist2.plist","UI/Plist2.png");
    
    auto background=Sprite::create("UI/home_bg4.png");
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    background->setColor(cocos2d::Color3B(13,158,196)); //图片颜色变灰
    background->setOpacity(230);
    addChild(background,1);
    
    
    
    glod=UserDefault::getInstance()->getIntegerForKey("glod1");
    la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",glod)->getCString(), "", 60);
    la->setPosition(Vec2(visibleSize.width/2,visibleSize.height-la->getContentSize().height));
    addChild(la,2);
    
    auto bg2=Sprite::createWithSpriteFrameName("home_btn_gold.png");
    bg2->setPosition(Vec2(la->getPositionX()-la->getContentSize().width,visibleSize.height-la->getContentSize().height));
    addChild(bg2,2);
    
    auto home=Sprite::createWithSpriteFrameName("setting_btn_shut-down.png");
    auto menut= MenuItemSprite::create(home,home,CC_CALLBACK_1(GameShop::menuHCallback, this));
    menut->setPosition(Vec2(visibleSize.width-home->getContentSize().width/2,visibleSize.height-home->getContentSize().height/2));
    men=Menu::create(menut,NULL);
    men->setPosition(Vec2::ZERO);
    men->setTag(50);
    addChild(men,2);
    
    
    wg=visibleSize.width*0.35;
    hg=la->getPositionY()/4-la->getContentSize().height/8;
    for (int i=0; i<6;i++) {
        auto b=i/2;
        auto sp1=Sprite::create("UI/store_box1.png");
        auto sp2=Sprite::create("UI/store_box2.png");
        auto sp3=Sprite::create("UI/store_box3.png");
        auto n=i+1;
        CCString *string=CCString::createWithFormat("Character_boat%d.png", n);
        if (i%2==0) {
            auto poy=hg*(b+1);
            auto pox=wg;
            auto menut= MenuItemSprite::create(sp1,sp2,sp3);
            menut->setPosition(Vec2(pox,poy));
            menut->setTag(i);
            menut->setEnabled(false);
            men->addChild(menut);
            
            auto b=5000;
            b1=Value(b).asString();
            auto menuItemFont3 = MenuItemFont::create(b1);
            auto menuItemFont4 = MenuItemFont::create(b1);
            
            auto boat=Sprite::createWithSpriteFrameName(string->getCString());
            boat->setScale(1);
            boat->setPosition(Vec2(pox, poy));
            this->addChild(boat,11);
            
            auto ment1=MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameShop::menuHCallback1,this),menuItemFont3,menuItemFont4,NULL);
            ment1->setPosition( Vec2(pox, poy-menuItemFont3->getContentSize().height*2-5));
            ment1->setTag(i);
            men->addChild(ment1);
        }
        else{
            auto poy=hg*(b+1);
            auto pox=wg*2;
            auto menut= MenuItemSprite::create(sp1,sp2,sp3);
            menut->setPosition(Vec2(pox,poy));
            menut->setTag(i);
            menut->setEnabled(false);
            men->addChild(menut);
            
            auto boat=Sprite::createWithSpriteFrameName(string->getCString());
            boat->setScale(1);
            boat->setPosition(Vec2(pox, poy));
            this->addChild(boat,11);
            
            auto b=5000;
            auto b1=Value(b).asString();
            auto menuItemFont3 = MenuItemFont::create(b1);
            auto menuItemFont4 = MenuItemFont::create(b1);
            
            
            
            auto ment1=MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameShop::menuHCallback1,this),menuItemFont3,menuItemFont4,NULL);
            ment1->setPosition( Vec2(pox, poy-menuItemFont3->getContentSize().height*2-5));
            ment1->setTag(i);
            men->addChild(ment1);
        }
    }
    
    
    mentb=Vector<MenuItemSprite*>();
    
    sprit=Sprite::create("UI/store_btn_Tick.png");
    addChild(sprit,5);
    
    for (int i=0; i<6; i++) {
        
        char sname[100]={0};
        sprintf(sname, "tog%d",i);
        auto a=UserDefault::getInstance()->getIntegerForKey(sname);
        auto be=(MenuItemToggle*)men->getChildByTag(a);
        be->setVisible(false);
        auto be1=(MenuItemSprite*)men->getChildByTag(a);
        
        
        auto sp1=Sprite::create("UI/store_box1.png");
        auto sp2=Sprite::create("UI/store_box2.png");
        auto sptri=MenuItemSprite::create(sp1, sp2, CC_CALLBACK_1(GameShop::menuHCallback2, this));
        sptri->setTag(a+10);
        sptri->setPosition(Vec2(be1->getPositionX(),be1->getPositionY()));
        men->addChild(sptri,16);
    }
    auto a2=UserDefault::getInstance()->getIntegerForKey("jie");
    auto b2=(MenuItemSprite*)men->getChildByTag(a2);
    sprit->setPosition(Vec2(b2->getPositionX()+sprit->getContentSize().width*2,b2->getPositionY()+sprit->getContentSize().height*2));
    auto b3=(MenuItemSprite*)men->getChildByTag(a2+10 );
    b3->selected();

    return true;
}
void   GameShop::menuHCallback(cocos2d::Ref* pSender){
    auto home=HomeScene::createScene();
    Director::getInstance()->replaceScene(home);
}
void   GameShop::menuHCallback1(cocos2d::Ref* pSender){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto menultemtog=(MenuItemToggle*)pSender;
    tog=menultemtog->getTag();
    
    auto men1=(Menu*)this->getChildByTag(50);
    menut=(MenuItemSprite*)men1->getChildByTag(tog);
    if (glod>5000) {
        menultemtog->setVisible(false);
        switch( menultemtog->getSelectedIndex() ) {
            case 0:
                menut->setEnabled(false);
                break;
            case 1:
                menut->setEnabled(true);
                break;
        }
        
        isSelect();
        
    }
    else{
        auto label=cocos2d::Label::createWithSystemFont("挫逼，没钱还想打架喔！", "",50);
        label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        label->setColor(cocos2d::Color3B(180,150,145));
        addChild(label,3);
        auto  fadein=FadeIn::create(1);
        auto  fadeout=FadeOut::create(1);
        auto  seq=Sequence::create(fadein,fadeout, NULL);
        label->runAction(seq);
    }
    
}
void GameShop::isSelect(){
    menuItemFont3 = MenuItemFont::create("                        ");
    menuItemFont4 = MenuItemFont::create("                        ");
    auto ment1=MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameShop::menuCCallback1,this),menuItemFont3,menuItemFont4,NULL);
    ment1->setTag(tog);
    ment1->setPosition( Vec2(menut->getPositionX(), menut->getPositionY()-menuItemFont3->getContentSize().height*2-5));
    men->addChild(ment1,10);
}

void GameShop::menuCCallback1(Ref* ref)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto menultemtog=(MenuItemToggle*)ref;
    auto tog1=menultemtog->getTag();
    auto men1=(Menu*)this->getChildByTag(50);
    auto menut1=(MenuItemSprite*)men1->getChildByTag(tog1);
    log("%d",menultemtog->getSelectedIndex());
    mentb.pushBack(menut1);
    switch( menultemtog->getSelectedIndex()) {
        case 0:
            for (int i=0; i<mentb.size(); i++) {
                auto object=mentb.at(i);
                object->unselected();
            }
            menut1->selected();
            UserDefault::getInstance()->setIntegerForKey("jie", menut1->getTag());
            break;
        case 1:
            for (int i=0; i<mentb.size(); i++) {
                auto object=mentb.at(i);
                object->unselected();
                menultemtog->cocos2d::MenuItem::setEnabled(true);
            }
            menut1->selected();
            UserDefault::getInstance()->setIntegerForKey("jie", menut1->getTag());
            break;
    }
    sprit->setPosition(Vec2(menut1->getPositionX()+menut1->getContentSize().width*0.6-sprit->getContentSize().width,menut1->getPositionY()+menut1->getContentSize().height*0.6-sprit->getContentSize().height));
    auto label=cocos2d::Label::createWithSystemFont("购买成功", "",50);
    label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    label->setColor(cocos2d::Color3B(60,180,45));
    addChild(label,3);
    auto  fadein=FadeIn::create(0.5);
    auto  fadeout=FadeOut::create(0.5);
    auto  seq=Sequence::create(fadein,fadeout, NULL);
    label->runAction(seq);
    
    
    auto b=glod-5000;
    UserDefault::getInstance()->setIntegerForKey("glod1", b);
    removeChild(la);
    glod=UserDefault::getInstance()->getIntegerForKey("glod1");
    la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",glod)->getCString(), "", 60);
    la->setPosition(Vec2(visibleSize.width/2,visibleSize.height-la->getContentSize().height));
    addChild(la,2);
    
    
    UserDefault::getInstance()->setIntegerForKey("tog10", tog1);
    char sname[100]={0};
    sprintf(sname, "tog%d",tog1);
    UserDefault::getInstance()->setIntegerForKey(sname, tog1);
}
void GameShop::menuHCallback2(cocos2d::Ref *pSender){
    for (int i=0; i<6; i++) {
        char sname[100]={0};
        sprintf(sname, "tog%d",i);
        auto a=UserDefault::getInstance()->getIntegerForKey(sname);
        auto sp=(MenuItemSprite*)men->getChildByTag(a+10);
        sp->unselected();
    }
    auto men1=(MenuItemSprite*)pSender;
    men1->selected();
    sprit->setPosition(Vec2(men1->getPositionX()+sprit->getContentSize().width*2,men1->getPositionY()+sprit->getContentSize().height*2));
    UserDefault::getInstance()->setIntegerForKey("jie", men1->getTag()-10);
}

