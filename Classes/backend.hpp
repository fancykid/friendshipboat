//
//  backend.hpp
//  cash
//
//  Created by K@B on 16/5/9.
//
//

#ifndef backend_hpp
#define backend_hpp

#include <stdio.h>
#include "cocos2d.h"
class backend: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(backend);
    //返回主页面
    void backend1(float dt);
};

#endif /* backend_hpp */
