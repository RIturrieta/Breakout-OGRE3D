#include "player.h"
#include <algorithm>
#include <iostream>

bool BreakoutPlayer::keyPressed(const OgreBites::KeyboardEvent& evt)
{

    if (evt.keysym.sym == OgreBites::SDLK_LEFT or evt.keysym.sym == 'a')
        direction = Direction::Left;

    if (evt.keysym.sym == OgreBites::SDLK_RIGHT or evt.keysym.sym == 'd')
        direction = Direction::Right;

    return true;
}

bool BreakoutPlayer::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    if ((evt.keysym.sym == OgreBites::SDLK_LEFT or evt.keysym.sym == 'a') and direction == Direction::Left)
        direction = Direction::None;

    if ((evt.keysym.sym == OgreBites::SDLK_RIGHT or evt.keysym.sym == 'd') and direction == Direction::Right)
        direction = Direction::None;

    return true;
}

bool BreakoutPlayer::axisMoved(const OgreBites::AxisEvent& evt)
{
    /*std::cout << evt.type << " - "
        << evt.which << " - "
        << static_cast<int>(evt.axis) << " - "
        << evt.value << std::endl;
        */
    unsigned int axisKey = static_cast<unsigned int>(evt.axis);

    // only checking one specific axis
    if (axisKey != 0)
        return true;

    // JoyStick min/max is -32768 / 32767
    //constexpr int axisMinValue = -32768;
    //constexpr int axisMaxValue = 32767;

    //const float axisNormalized = static_cast<float>(evt.value) / (axisMaxValue - axisMinValue);
    //std::cout << evt.value << " -> " << axisNormalized << std::endl;

    if (evt.value < -10000)
        direction = Direction::Left;
    
    else if (evt.value > 10000)
        direction = Direction::Right;
    
    else
        direction = Direction::None;

    return true;
}

bool BreakoutPlayer::frameStarted(const Ogre::FrameEvent& evt)
{
    float dt = evt.timeSinceLastFrame;

    switch (direction)
    {
    case Direction::Left:
        setPos(Ogre::Vector3(std::max(-20.0f, brickPos.x - xSpeed * dt), brickPos.y, brickPos.z));
        break;
    case Direction::Right:
        setPos(Ogre::Vector3(std::min(20.0f, brickPos.x + xSpeed * dt), brickPos.y, brickPos.z));
        break;
    case Direction::None:
    default:
        break;
    }
    return true;
}