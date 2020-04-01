#pragma once

#include "EventManager.h"
#include "EnvironmentTransition.h"

namespace ample::game
{
class KeyboardTransition : public EnvironmentTransition
{
public:
    enum class type
    {
        DOWN,
        NOT_DOWN,
        PRESSED,
        RELEASED,
    };

public:
    KeyboardTransition(std::shared_ptr<ample::game::StateMachine::State> state,
                       control::EventManager &manager,
                       type pressType,
                       control::keysym key);

    bool listen() override;

private:
    type _pressType;
    control::keysym _key;
};
} // namespace ample::game