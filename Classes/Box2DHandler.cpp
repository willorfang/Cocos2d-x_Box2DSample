//
//  Box2DHandler.cpp
//  PhysicsBalls
//
//  Created by Wei Fang on 3/7/14.
//
//

#include "Box2DHandler.h"

USING_NS_CC;

Box2DHandler* Box2DHandler::_handler = NULL;

Box2DHandler* Box2DHandler::sharedBox2DHandler() {
    if (_handler) {
        return _handler;
    } else {
        _handler = new Box2DHandler();
        if (_handler && _handler->init()) {
            _handler->autorelease();
            return _handler;
        } else {
            CC_SAFE_DELETE(_handler);
            return NULL;
        }
    }
}

bool Box2DHandler::init() {
    if (CCNode::init()) {
        // create box2d world
        b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
        _world = new b2World(gravity);
        _world->SetAllowSleeping(true);
        _world->SetContinuousPhysics(true);
        _world->SetContactListener(this);
        
        // create body for edge
        b2BodyDef edgeBodyDef;
        edgeBodyDef.position.Set(0, 0);
        edgeBodyDef.type=b2_staticBody;
        _edgeBody = _world->CreateBody(&edgeBodyDef);
        
        // create fixture for edge
        b2EdgeShape edgeShape;
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        // bottom
        edgeShape.Set(b2Vec2(0, 0), b2Vec2(winSize.width/PTM_RADIO, 0));
        _edgeBody->CreateFixture(&edgeShape, 0);
        // top
        edgeShape.Set(b2Vec2(0, winSize.height/PTM_RADIO), b2Vec2(winSize.width/PTM_RADIO, winSize.height/PTM_RADIO));
        _edgeBody->CreateFixture(&edgeShape, 0);
        // left
        edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height/PTM_RADIO));
        _edgeBody->CreateFixture(&edgeShape, 0);
        // bottom
        edgeShape.Set(b2Vec2(winSize.width/PTM_RADIO, 0), b2Vec2(winSize.width/PTM_RADIO, winSize.height/PTM_RADIO));
        _edgeBody->CreateFixture(&edgeShape, 0);
        
        this->scheduleUpdate();
        return true;
    }
    return false;
}

Box2DHandler::~Box2DHandler() {
    _world->DestroyBody(_edgeBody);
    CC_SAFE_DELETE(_world);
}

void Box2DHandler::addSprite(B2Sprite *sprite) {
    // add to the tree
    this->addChild(sprite);
    
    // create body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(sprite->getPosition().x/PTM_RADIO, sprite->getPosition().y/PTM_RADIO);
    
    // set rotation and velocity in a random way
    unsigned int randomNumber = arc4random()%300;
    unsigned int randomNumberTwo = arc4random()%300;
    float veciloty_x = ((float)randomNumber) / 10.0;
    veciloty_x = randomNumber%2 == 0 ? veciloty_x : veciloty_x*(-1);
    float veciloty_y = ((float)randomNumberTwo) / 10.0;
    veciloty_y = randomNumberTwo%2 == 0 ? veciloty_y : veciloty_y*(-1);
    ballBodyDef.linearVelocity = b2Vec2(veciloty_x, veciloty_y);
    
    ballBodyDef.userData = sprite;
    b2Body* _body = _world->CreateBody(&ballBodyDef);
    sprite->setB2Body(_body);

    // create shape
    b2CircleShape shape;
    shape.m_radius = sprite->boundingBox().size.width/(2*PTM_RADIO);
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &shape;
    ballShapeDef.density = 2.0f;
    ballShapeDef.friction = 0.2f;
    ballShapeDef.restitution = 0.7f;
    _body->CreateFixture(&ballShapeDef);
}

void Box2DHandler::update(float dt) {
    // update sprite status
    for (b2Body* b=_world->GetBodyList(); b!=NULL; b=b->GetNext()) {
        if (b && b->GetUserData()) {
            B2Sprite* sprite = static_cast<B2Sprite*>(b->GetUserData());
            b2Vec2 pos = b->GetPosition();
            float rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
            sprite->setPosition(ccp(pos.x*PTM_RADIO, pos.y*PTM_RADIO));
            sprite->setRotation(rotation);
        }
    }
    // update box2d
    _world->Step(dt, 8, 8);
    this->dealCollisions();
}

void Box2DHandler::removeSprite(B2Sprite* sprite) {
    if (sprite->getB2Body()) {
        _world->DestroyBody(sprite->getB2Body());
        sprite->setB2Body(NULL);
    }
    //
    this->removeChild(sprite);
}

void Box2DHandler::dealCollisions() {
    
}

void Box2DHandler::BeginContact(b2Contact *contact) {
    
}

void Box2DHandler::EndContact(b2Contact *contact) {
    
}
