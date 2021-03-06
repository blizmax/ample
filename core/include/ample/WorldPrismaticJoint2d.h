#pragma once

#include "box2d/b2_prismatic_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldPrismaticJoint2d : public WorldJoint2d
{
public:
    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    ample::graphics::Vector2d<float> getLocalAxisA() const;

    float getReferenceAngle() const;

    float getJointTranslation() const;

    float getJointSpeed() const;

    bool isLimitEnabled() const;

    void enableLimit(bool flag);

    float getLowerLimit() const;

    float getUpperLimit() const;

    void setLimits(float lower, float upper);

    bool isMotorEnabled() const;

    void enableMotor(bool flag);

    void setMotorSpeed(float speed);

    float getMotorSpeed() const;

    void setMaxMotorForce(float force);
    float getMaxMotorForce() const;

    float getMotorForce(float inv_dt) const;

    WorldPrismaticJoint2d(const std::string &name,
                          WorldObject2d &bodyA,
                          WorldObject2d &bodyB,
                          const ample::graphics::Vector2d<float> &anchor,
                          const ample::graphics::Vector2d<float> &worldAxis = {1, 0},
                          float referenceAngle = 0,
                          bool collideConnected = false);
};
} // namespace ample::physics
