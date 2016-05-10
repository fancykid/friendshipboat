//
//  GamePause.hpp
//  FightChild
//
//  Created by kid on 16/4/27.
//
//

#ifndef GamePause_hpp
#define GamePause_hpp

#include "cocos2d.h"
USING_NS_CC;
class Gamepause : public Layer
{
public:
    virtual bool init();
    static Scene* scene(RenderTexture* sqr);
    CREATE_FUNC(Gamepause);
    //继续游戏
    void menuContinueCallback(Object* pSender);
    //回到主页
    void menuHomeCallback(Object* pSender);
    
    //停止音乐
    void stopmusic(CCObject* ps);
    //播放音乐
    void playmusic(CCObject* bj);
    //记录停止音乐状态
    void stop(float dt);
    //记录播放音乐状态
    void play(float dt);
    
};

#endif /* GamePause_hpp */
