#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalSleepingAllowedAction : public PhysicalAction
{
public:
    PhysicalSleepingAllowedAction(const std::string &name,
                                  const std::vector<std::string> &bodyNames,
                                  bool flag);
    PhysicalSleepingAllowedAction(const filing::JsonIO &input);

    bool getFlag() const noexcept;

    void setFlag(bool flag) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    bool _flag;
};
} // namespace ample::game::stateMachine::actions
