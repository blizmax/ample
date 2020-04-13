#pragma once

namespace ample::game
{
template <class ObjectT>
ObjectOwner<ObjectT>::ObjectOwner(std::shared_ptr<ObjectT> object)
    : _object(object) {}

template <class ObjectT>
ObjectT &ObjectOwner<ObjectT>::object() noexcept
{
    return *_object;
}

template <class ObjectT>
std::shared_ptr<ObjectT> ObjectOwner<ObjectT>::objectPtr() const noexcept
{
    return _object;
}

template <class ObjectT>
ControlledObject::ObjectState<ObjectT>::ObjectState(const std::string &name, std::shared_ptr<ObjectT> object)
    : State(name), ObjectOwner<ObjectT>(object)
{
    setMachine(object->stateMachine());
}
} // namespace ample::game
