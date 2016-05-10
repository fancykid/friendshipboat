#include "HomeScene.h"
#include "main.hpp"
#include "scro.hpp"
#include "GameShop.hpp"
#include "Option.hpp"
#include "BackgoundMove.hpp"
#include "SimpleAudioEngine.h"
#include "backend.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    
   CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("UI/bg_music.mp3");
   auto boolto=UserDefault::getInstance()->getIntegerForKey("bool");
    if (boolto==1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("UI/bg_music.mp3",true);
    }

    
    
    
    
    
    this->addChild(BackgoundMove::create());
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Plist.plist","UI/Plist.png");
    
    
    auto scrot=Sprite::createWithSpriteFrameName("home_fenshu.png");
    scrot->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-80));
    addChild(scrot,2);
    
    auto bg1=Sprite::createWithSpriteFrameName("home_title.png");
    bg1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+300));
    addChild(bg1,2);
    
    auto bg2=Sprite::createWithSpriteFrameName("home_btn_gold.png");
    bg2->setPosition(Vec2(50,visibleSize.height-bg2->getContentSize().height));
    addChild(bg2,2);
    
    
    auto glod=UserDefault::getInstance()->getIntegerForKey("glod1");
    auto  la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",glod)->getCString(), "", 48);
    la->setPosition(Vec2(bg2->getPosition().x+la->getContentSize().width,visibleSize.height-bg2->getContentSize().height));
    addChild(la,2);
    
    auto one=1;
    la=cocos2d::Label::createWithSystemFont(__String::createWithFormat("%d",one)->getCString(),"Arial",80);
    la->setPosition(Vec2(scrot->getPositionX()+10,scrot->getPositionY()+la->getContentSize().height*0.4));
    la ->setTag(10);
    la->setColor(cocos2d::Color3B(200,30,50));
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
    
    auto ShopItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_shopping.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_shopping.png")),CC_CALLBACK_1(HomeScene::menuShopCallback, this));
    
    auto LikeItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_like.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_like.png")),CC_CALLBACK_1(HomeScene::menuLikeCallback, this));
    
    auto ListItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_Leaderboard.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_Leaderboard.png")),CC_CALLBACK_1(HomeScene::menuLikeCallback, this));
    
    auto OptionItem = MenuItemSprite::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_Set-up.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("home_btn_Set-up.png")),CC_CALLBACK_1(HomeScene::menuOptionCallback, this));
    
    ShopItem->setPosition(Vec2(visibleSize.width / 6 + 20, visibleSize.height / 8));    //把菜单项添加到菜单精灵中
    
    LikeItem->setPosition(Vec2(visibleSize.width / 6 + 140, visibleSize.height / 8));
    
    ListItem->setPosition(Vec2(visibleSize.width / 6 + 260, visibleSize.height / 8));
    
    OptionItem->setPosition(Vec2(visibleSize.width / 6 + 380, visibleSize.height / 8));
    auto menu = Menu::create(ShopItem, LikeItem, ListItem, OptionItem, NULL);
    menu->setPosition(Vec2::ZERO); //把菜单精灵添加到当前的层中
    this->addChild(menu,2);
    
    auto start=MenuItemFont::create("点击开始",this,menu_selector(HomeScene::menuCloseCallback));
    start->setPosition(Vec2(scrot->getPosition().x,scrot->getPosition().y-scrot->getContentSize().height*0.6));
    start->setFontSizeObj(50);
    start->setColor(cocos2d::Color3B(160,170,180));
    auto pme=Menu::create(start,NULL);
    pme->setPosition(Vec2(0,0));
    addChild(pme,2);
    return true;
}


void HomeScene::menuCloseCallback(Ref* pSender)
{
   CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("UI/bg_music.mp3",true);
   auto scen=main::createScene();
    Director::getInstance()->replaceScene(scen);
}

void HomeScene::menuLikeCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto ba=backend::createScene();
    Director::getInstance()->replaceScene(ba);
}

void HomeScene::menuShopCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto scen=GameShop::createScene();
    Director::getInstance()->replaceScene(scen);
}

void HomeScene::menuListCallback(Ref* pSender)
{

}

void HomeScene::menuOptionCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto visiable=Director::getInstance()->getVisibleSize();
    auto rend=RenderTexture::create(visiable.width, visiable.height);
    rend->begin();
    this->getParent()->visit();
    rend->end();
    Director::getInstance()->pushScene(Option::scene(rend));
}


