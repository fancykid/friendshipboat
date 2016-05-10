//
//  scro.hpp
//  cash
//
//  Created by K@B on 16/4/27.
//
//

#ifndef scro_hpp
#define scro_hpp

#include "cocos2d.h"
#include "main.hpp"
#include "Player.h"
class scro : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(scro);
    //返回主菜单
    void Home(Ref* ref);
    
    cocos2d::Label* la;
    //继续游戏
    void beng(cocos2d::Object* test);
    //控制音乐停止
    void update(float dt);
    //结束游戏
    void end(cocos2d::Object* test);
    main* ma1;
    
    int atop,sc1;
    
};

#endif /* scro_hpp */
