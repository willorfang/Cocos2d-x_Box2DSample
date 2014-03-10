//
//  B2Sprite.h
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#ifndef __PhysicsBalls__B2Sprite__
#define __PhysicsBalls__B2Sprite__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class B2Sprite : public cocos2d::CCSprite {
    bool init(const char* file);
    
public:
    static B2Sprite* create(const char* file);
    
    CC_SYNTHESIZE(b2Body*, _b2Body, B2Body);
};

#endif /* defined(__PhysicsBalls__B2Sprite__) */
