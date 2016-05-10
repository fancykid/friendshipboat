#include "Player.h"
#include "scro.hpp"
#include "SimpleAudioEngine.h"
#include "scro.hpp"
#include "HomeScene.h"
#include "GameShop.hpp"
USING_NS_CC;

Player::Player(){}
Player::~Player(){}
Scene* Player::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Player::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Player::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //纹理的加载
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/heroaner.plist","UI/heroaner.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/aircraft.plist","UI/aircraft.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/explosion.plist","UI/explosion.png");
    //声音的播放
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("UI/enemy1_down.mp3");
    
    boolto=UserDefault::getInstance()->getIntegerForKey("bool");
    if (boolto==1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("UI/bg_music.mp3",true);
    }
    //一把枪
    sp=Sprite::create("UI/gun1.png");
    sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -100));
    sp->setAnchorPoint(Vec2(0,0.5));
    sp->setTag(1);
    auto mo1=RotateBy::create(2, -180, -180);
    auto mo2=RotateBy::create(2, 180, 180);
    auto sq=Sequence::create(mo1,mo2, NULL);
    auto re=RepeatForever::create(sq);
    sp->runAction(re);
    addChild(sp,1);
    
    //子弹的创建
    creattou();
    sc=0;
    
    //触摸事件（实现获取摆动的方向并移动子弹）
    liat=EventListenerTouchOneByOne::create();
    liat->setSwallowTouches(true);
    liat->onTouchBegan=[](Touch* touch,Event* event){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        auto gro=static_cast<Layer*>(event->getCurrentTarget());
        auto sp=gro->getChildByTag(1);
        auto b=sp->getRotation();
        log("%f",b);
        auto sp2=gro->getChildByTag(2);
        if (b>=-180&&b<-90) {
            auto pox=cosf(b*M_PI/180)*800;
            auto poy=-sinf(b*M_PI/180)*800;
            auto po=Point(pox,poy);
            log("%f,%f",pox,poy);
            auto mo1=MoveBy::create(0.5, po);
            sp2->runAction(mo1);
        }
        
        if (b<=0&&b>-90) {
            auto b1=fabsf(b);
            auto pox=cosf(b1*M_PI/180)*800;
            auto poy=sinf(b1*M_PI/180)*800;
            auto po=Point(pox,poy);
            auto mo1=MoveBy::create(0.5, po);
            log("%f,%f",pox,poy);
            sp2->runAction(mo1);
        }
        if (b==-90) {
            auto pox=cosf(b*M_PI/180)*800;
            auto poy=-sinf(b*M_PI/180)*800;
            auto po=Point(pox,poy);
            auto mo1=MoveBy::create(0.5, po);
            sp2->runAction(mo1);
        }
        
        return true;
    };
    liat->onTouchMoved=[](Touch* touch,Event* event){
        
    };
    liat->onTouchEnded=[](Touch* touch,Event* event){
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(liat, this);
    
    
    scheduleUpdate();

    //敌机的移动的调度器
    schedule(schedule_selector(Player::Run),1.5f);
   
    
    //敌机
    createnemy();
    //自己
    n=UserDefault::getInstance()->getIntegerForKey("jie")+1;
    CCString *string=CCString::createWithFormat("Character_boat%d.png", n);
    zhiji=Sprite::createWithSpriteFrameName(string->getCString());
    zhiji->setScale(1.5);
    zhiji->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -100));
    addChild(zhiji,2);
    
    //设背景速度
    speed=5;
    UserDefault::getInstance()->setIntegerForKey("speed", speed);
    
    
    return true;
}
void Player::update(float dt){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    
    if (sp1->getBoundingBox().intersectsRect(diji->getBoundingBox())) {
        
        removeChild(sp1);
        creattou();
        sc=sc+100;
        glod=glod+1000;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("UI/enemy1_down.mp3");
        fadeout();
        removeChild(diji);
        createnemy();
        count=count+1;
        speed=50;
        UserDefault::getInstance()->setIntegerForKey("speed", speed);
        scheduleOnce(schedule_selector(Player::speedback), 0.5);
        if (count%5==0) {
            difficult=difficult*0.8;
            auto label=cocos2d::Label::createWithSystemFont("超神节奏准备来了", "",50);
            label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
            label->setColor(cocos2d::Color3B(180,45,45));
            addChild(label,3);
            auto  fadein=FadeIn::create(1);
            auto  fadeout=FadeOut::create(1);
            auto  seq=Sequence::create(fadein,fadeout, NULL);
            label->runAction(seq);
        }
    }
    if (diji->getPositionY()<visibleSize.height) {
    //子弹打到外面去时
    if (sp1->getPosition().x+sp1->getContentSize().width<0||sp1->getPosition().x+sp1->getContentSize().width>visibleSize.width) {
        removeChild(sp1);
        creattou();
        zi=Sprite::create("UI/koalio_stand.png");
        zi->setPosition(Vec2(diji->getPositionX(),diji->getPositionY()));
        addChild(zi);
        moveto1();
       _eventDispatcher->removeEventListener(liat);
        //判断敌人的子弹是否打到自己的船上
        schedule(schedule_selector(Player::zhidanpen));

    }
    if (sp1->getPosition().y-sp1->getContentSize().height<0||sp1->getPosition().y-sp1->getContentSize().height>visibleSize.height) {
        removeChild(sp1);
        creattou();
        zi=Sprite::create("UI/koalio_stand.png");
        zi->setPosition(Vec2(diji->getPositionX(),diji->getPositionY()));
        addChild(zi);
        moveto1();
        _eventDispatcher->removeEventListener(liat);
        //判断敌人的子弹是否打到自己的船上
        schedule(schedule_selector(Player::zhidanpen));
        
    }
        
    }
    
    if (diji->getPositionY()>visibleSize.height) {
        //子弹打到外面去时
        if (sp1->getPosition().x+sp1->getContentSize().width<0||sp1->getPosition().x+sp1->getContentSize().width>visibleSize.width)
        {
            removeChild(sp1);
            creattou();
        }
        if (sp1->getPosition().y-sp1->getContentSize().height<0||sp1->getPosition().y-sp1->getContentSize().height>visibleSize.height)
        {
            removeChild(sp1);
            creattou();
        }
        
    }
}
//创建自己的船发射的子弹
void  Player::creattou(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    sp1=Sprite::create("UI/koalio_stand.png");
    sp1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -100));
    sp1->setAnchorPoint(Vec2(0.5,0));
    sp1->setTag(2);
    addChild(sp1,1);
}
void Player::zhidanpen(float de){
    if (zi->getBoundingBox().intersectsRect(zhiji->getBoundingBox())) {
        
        removeChild(zi);
        
        zi=Sprite::create("UI/koalio_stand.png");
        zi->setPosition(Vec2(1500,1500));
        addChild(zi);
        
        removeChild(sp);
        removeChild(sp1);
        
        
        sp=Sprite::create("UI/gun1.png");
        sp->setPosition(Vec2(1000, 1000));
        sp->setTag(1);
        addChild(sp);
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        sp1=Sprite::create("UI/koalio_stand.png");
        sp1->setPosition(Vec2(1000, 1000));
        sp1->setTag(2);
        addChild(sp1,2);
         end();
        unscheduleUpdate();
        _eventDispatcher->removeEventListener(liat);
 
        
    }

}
//敌机随机移动
void Player::Run(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto a2=random(30, 600);
    auto a3=random(600, 1000);
    Move = MoveTo::create(1, Vec2(a2, a3));
    diji->runAction(Move);

}
//敌机移动的方法
void Player::moveto1(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto a1=Point(Vec2(visibleSize.width / 2, visibleSize.height / 2 -100));
    auto mo1=MoveTo::create(0.5, a1);
    zi->runAction(mo1);
    
}
void Player::speedback(float dt){
    speed=5;
    UserDefault::getInstance()->setIntegerForKey("speed", speed);

}
void Player::fadeout(){
    blow=ParticleExplosion::createWithTotalParticles(100);
    blow->setPosition(Vec2(diji->getPosition().x,diji->getPositionY()));
    blow->setLife(1);
    addChild(blow);
}

void Player::createnemy(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    diji=Sprite::createWithSpriteFrameName("aircraft 0");
    diji->setPosition(Vec2(visibleSize.width/2,visibleSize.height+100));
    diji->setScale(difficult);
    this->addChild(diji,1);
    
    auto an=Animation::create();
    for (int i=0; i<19; i++) {
        char sname[100]={0};;
        sprintf(sname, "aircraft %d",i+1);
        auto frame=SpriteFrameCache::getInstance()->getSpriteFrameByName(sname);
        an->addSpriteFrame(frame);
    }
    an->setLoops(-1);
    an->setDelayPerUnit(0.02);
    auto panimate=Animate::create(an);
    diji->runAction(panimate);
}
void Player::end(){
    auto an=Animation::create();
    for (int i=1; i<7; i++) {
        char sname[100]={0};;
        sprintf(sname, "explosion%d.png",i);
        auto frame=SpriteFrameCache::getInstance()->getSpriteFrameByName(sname);
        an->addSpriteFrame(frame);
    }
    an->setLoops(1);
    an->setDelayPerUnit(0.1);
    auto panimate=Animate::create(an);
    auto en=CallFuncN::create(CC_CALLBACK_1(Player::end1, this));
    auto sq=Sequence::create(panimate,en,NULL);
    zhiji->runAction(sq);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("UI/enemy1_down.mp3");
}
void Player::end1(cocos2d::Ref *ref){
        removeChild(zhiji);
        zhiji=Sprite::createWithSpriteFrameName("Character_boat1.png");
        zhiji->setScale(0.8);
        zhiji->setPosition(Vec2(1000, 1000));
        addChild(zhiji);
    auto scr=scro::createScene();
    Director::getInstance()->replaceScene(scr);

}




