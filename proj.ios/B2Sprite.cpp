//
//  B2Sprite.cpp
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#include "B2Sprite.h"

USING_NS_CC;

B2Sprite* B2Sprite::create(const char* file) {
    B2Sprite* instance = new B2Sprite();
    if (instance && instance->init(file)) {
        instance->autorelease();
        return instance;
    } else {
        CC_SAFE_DELETE(instance);
        return NULL;
    }
}

bool B2Sprite::init(const char* file) {
    if (CCSprite::init()) {
        CCTexture2D* cache = CCTextureCache::sharedTextureCache()->addImage(file);
        this->initWithTexture(cache);
        this->_b2Body = NULL;
        return true;
    }
    return false;
}