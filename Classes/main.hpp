//
//  main.hpp
//  cash
//
//  Created by K@B on 16/4/27.
//
//

#ifndef main_hpp
#define main_hpp

#include "cocos2d.h"
#include "Player.h"
class main : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(main);
    
   
    //分数，金币
   int score,glod;
    
    cocos2d::Label* label;
    cocos2d::Label* label1;
    //存储分数，金币
    void update(float dt);
    
    Player* ma;
    //暂停页面
    void menuback(Ref* ref);
    
};

#endif /* main_hpp */
