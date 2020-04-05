#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "StateMachine.h"
#include "Behaviour.h"

namespace ample::game
{
class ControlledObject : public activity::Behavior
{
public:
    template <typename ObjectT>
    class ObjectState : public StateMachine::State
    {
    public:
        ObjectState(const std::string &name, std::shared_ptr<ObjectT> object);
        std::shared_ptr<ObjectT> object() const noexcept;

    private:
        std::shared_ptr<ObjectT> _object;

        friend class ControlledObject;
    };

public:
    ControlledObject();
    std::shared_ptr<StateMachine> stateMachine() noexcept;

private:
    std::shared_ptr<StateMachine> _stateMachine;
};
} // namespace ample::game

#include "templates/ControlledObject.hpp"