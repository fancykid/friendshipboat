#ifndef __HomeScene_SCENE_H__
#define __HomeScene_SCENE_H__

#include "cocos2d.h"

class HomeScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    //开始游戏
    void menuCloseCallback(cocos2d::Ref* pSender);
    //跳转到appstore
    void menuLikeCallback(cocos2d::Ref* pSender);
    //商店页面
    void menuShopCallback(cocos2d::Ref* pSender);
    //排行榜
    void menuListCallback(cocos2d::Ref* pSender);
    //设置页面
    void menuOptionCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
    
    cocos2d::Animation* an;
    int atop,sc1;
};

#endif // __HomeScene_SCENE_H__
