//
//  GameScene.cpp
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#include "GameScene.h"
#include "BallsLayer.h"
USING_NS_CC;

bool GameScene::init() {
    if (CCScene::init()) {
        BallsLayer* layer = BallsLayer::create();
        this->addChild(layer);
        return true;
    }
    return false;
}