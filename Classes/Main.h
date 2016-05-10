#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"

class Main : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Main);
    cocos2d::Sprite* sp;
    cocos2d::Sprite* sp1;
    void update(float dt);
    cocos2d::Node* diji;
    cocos2d::Sprite* zhiji;
    cocos2d::Sprite* zi;
    void creattou();
    void zidi();
    void zhidanpen(float dt);
    cocos2d::EventListenerTouchOneByOne* liat;
    void Run(float dt);
    void Know(float dt);
    cocos2d::Action* Move;
    cocos2d::Action* Move1;
    int sc;
    Main();
    ~ Main();
    void zaiw(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
