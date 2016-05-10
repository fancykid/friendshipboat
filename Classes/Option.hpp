//
//  Option.hpp
//  cash
//
//  Created by kid on 16/5/4.
//
//

#ifndef Option_hpp
#define Option_hpp

#include "cocos2d.h"
#include "HomeScene.h"

USING_NS_CC;

class Option : public Layer
{
public:
    static Scene* scene(RenderTexture* sqr);
    
    virtual bool init();
    
    // a selector callback
    //静音
    void menuSilenCallback(Object* pSender);
    //播放音乐
    void menuBgMusicCallback(Object* pSender);
    //返回主菜单
    void menuBackCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Option);
};

#endif /* Option_hpp */
