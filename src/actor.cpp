#include "actor.h"

Actor::Actor(){};

Actor::~Actor(){};

void Actor::start()
{
    t_ = std::thread(&Actor::run, this);
}

void Actor::stop()
{
    t_.join();
}