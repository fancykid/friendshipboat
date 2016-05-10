#ifndef __Player_SCENE_H__
#define __Player_SCENE_H__

#include "cocos2d.h"

class Player : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    //敌机创建
    void createnemy();
    virtual bool init();
    CREATE_FUNC(Player);
    //枪头
    cocos2d::Sprite* sp;
    //子弹
    cocos2d::Sprite* sp1;
    //碰撞检测
    void update(float dt);
    //敌机
    cocos2d::Node* diji;
    //主角
    cocos2d::Sprite* zhiji;
    //子弹
    cocos2d::Sprite* zi;
    //创建自己的船发射的子弹
    void creattou();
    cocos2d::EventListenerTouchOneByOne* liat;
    //敌机随机移动
    void Run(float dt);
    cocos2d::Action* Move;
    cocos2d::Action* Move1;
    //分数，金币
    int sc,glod=0;
    //移除子弹
    void zhidanpen(float de);
    //敌机移动的方法
    void moveto1();
    float difficult=1.5;
    //主角爆炸
    void end();
    //敌机爆炸
    void fadeout();
    //控制速度
    void speedback(float dt);
    //爆炸效果
    cocos2d::ParticleExplosion* blow;
    int speed=2,boolto,count=0;
    //移除主角
    void end1(Ref* ref);
    int n;
    Player();
    ~Player();
};

#endif // __Player_SCENE_H__
