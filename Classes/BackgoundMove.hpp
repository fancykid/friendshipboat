

#ifndef bg_hpp
#define bg_hpp

#include "cocos2d.h"
#include "Player.h"

class BackgoundMove : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();

    CREATE_FUNC(BackgoundMove);
    //场景1
    cocos2d::Sprite* sp;
    
    //场景2
    cocos2d::Sprite* sp1;
    //场景移动速度
    int speed;
    //控制场景移动
    void update(float dt);
    int with;
    int with1;
    //角色对象
    Player* ma;
    
};

#endif 
