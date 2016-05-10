//
//  GameShop.hpp
//  cash
//
//  Created by kid on 16/5/4.
//
//

#ifndef GameShop_hpp
#define GameShop_hpp

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class GameShop : public Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    //可用按钮切换
    void menuCCallback1(Ref* ref);
    //返回主菜单
    void menuHCallback(cocos2d::Ref* pSender);
    cocos2d::Menu* men;
    //判断按钮是否可用
    void isSelect();
    Vector<cocos2d::MenuItemSprite*> mentb;
    MenuItemSprite* menut;
    CREATE_FUNC(GameShop);
    int glod;
    int wg,hg ,tog,a1;
    std::string b1;
    
    //判断是否可以解锁按钮
    void menuHCallback1(cocos2d::Ref* pSender);
    MenuItemFont* menuItemFont3;
    MenuItemFont* menuItemFont4;
    std::string va;
    Sprite* sprit;
    Label* la;
    int b=1;
    
    void menuHCallback2(cocos2d::Ref* pSender);
};

#endif /* GameShop_hpp */
