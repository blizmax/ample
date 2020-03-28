#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_body.h"
#include "box2d/b2_joint.h"
#include "box2d/b2_distance_joint.h"

#include "WorldLayer2d.h"
#include "WorldDistanceJoint.h"
#include "WorldRevoluteJoint2d.h"
#include "WorldPrismaticJoint2d.h"
#include "WorldPulleyJoint2d.h"
#include "WorldGearJoint2d.h"
#include "WorldMouseJoint2d.h"
#include "WorldWheelJoint2d.h"
#include "WorldWeldJoint2d.h"
#include "WorldRopeJoint2d.h"
#include "WorldFrictionJoint2d.h"
#include "Clock.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity, float z, float thickness)
    : world(b2Vec2(gravity.x, gravity.y)), _z(z), _thickness(thickness) {}

void WorldLayer2d::setContactListener(ContactListener &listener)
{
    world.SetContactListener(&listener);
}

WorldObject2d &WorldLayer2d::addWorldObject(const std::vector<ample::graphics::Vector2d<float>> &shape,
                                            ample::graphics::Vector2d<float> pos,
                                            BodyType type,
                                            float angle,
                                            float relativeThickness)
{
    if (!(0.0f <= relativeThickness && relativeThickness <= 1.0f))
    {
        throw exception::Exception(exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "relative thickness should be from 0.0 to 1.0");
    }
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = angle;
    switch (type)
    {
    case BodyType::STATIC_BODY:
        bodyDef.type = b2_staticBody;
        break;
    case BodyType::KINEMATIC_BODY:
        bodyDef.type = b2_kinematicBody;
        break;
    case BodyType::DYNAMIC_BODY:
        bodyDef.type = b2_dynamicBody;
        break;
    }
    _bodies.emplace_back(new WorldObject2d(world.CreateBody(&bodyDef),
                                           shape,
                                           _thickness * relativeThickness,
                                           _z + (_thickness - _thickness * relativeThickness) / 2.0f));
    graphics::Layer::addObject(*(_bodies[_bodies.size() - 1]));
    return *(_bodies.back());
}

WorldJoint2d &WorldLayer2d::addWorldDistanceJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                  ample::graphics::Vector2d<float> anchorOnBodyA,
                                                  ample::graphics::Vector2d<float> anchorOnBodyB,
                                                  float length,
                                                  bool collideConnected)
{
    b2DistanceJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body,
                        {anchorOnBodyA.x, anchorOnBodyA.y},
                        {anchorOnBodyB.x, anchorOnBodyB.y});
    jointDef.collideConnected = collideConnected;
    if (length > 0)
    {
        jointDef.length = length;
    }
    jointDef.length = length;
    _joints.emplace_back(new WorldDistanceJoint2d((b2DistanceJoint *)world.CreateJoint(&jointDef),
                                                  bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldRevoluteJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                  ample::graphics::Vector2d<float> anchor,
                                                  float referenceAngle)
{
    b2RevoluteJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body,
                        {anchor.x, anchor.y});
    jointDef.referenceAngle = referenceAngle;
    _joints.emplace_back(new WorldRevoluteJoint2d((b2RevoluteJoint *)world.CreateJoint(&jointDef),
                                                  bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldPrismaticJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                   ample::graphics::Vector2d<float> anchor,
                                                   ample::graphics::Vector2d<float> worldAxis,
                                                   float referenceAngle)
{
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body, {anchor.x, anchor.y}, {worldAxis.x, worldAxis.y});
    jointDef.referenceAngle = referenceAngle;
    _joints.emplace_back(new WorldPrismaticJoint2d((b2PrismaticJoint *)world.CreateJoint(&jointDef),
                                                   bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldPulleyJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                ample::graphics::Vector2d<float> groundAnchorA,
                                                ample::graphics::Vector2d<float> groundAnchorB,
                                                ample::graphics::Vector2d<float> anchorA,
                                                ample::graphics::Vector2d<float> anchorB,
                                                float lengthA,
                                                float lengthB,
                                                float ratio)
{
    b2PulleyJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body,
                        {groundAnchorA.x, groundAnchorA.y},
                        {groundAnchorB.x, groundAnchorB.y},
                        {anchorA.x, anchorA.y},
                        {anchorB.x, anchorB.y}, ratio);
    if (lengthA > 0)
    {
        jointDef.lengthA = lengthA;
    }
    if (lengthB > 0)
    {
        jointDef.lengthB = lengthB;
    }
    _joints.emplace_back(new WorldPulleyJoint2d((b2PulleyJoint *)world.CreateJoint(&jointDef),
                                                bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldGearJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                              WorldJoint2d &jointA, WorldJoint2d &jointB,
                                              float ratio)
{
    b2GearJointDef jointDef;
    jointDef.bodyA = bodyA._body;
    jointDef.bodyB = bodyB._body;
    jointDef.joint1 = jointA._joint;
    jointDef.joint2 = jointB._joint;
    jointDef.ratio = ratio;
    _joints.emplace_back(new WorldGearJoint2d((b2GearJoint *)world.CreateJoint(&jointDef),
                                              bodyA, bodyB, jointA, jointB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldMouseJoint(WorldObject2d &bodyA, WorldObject2d &bodyB)
{
    b2MouseJointDef jointDef;
    jointDef.bodyA = bodyA._body;
    jointDef.bodyB = bodyB._body;
    _joints.emplace_back(new WorldMouseJoint2d(world.CreateJoint(&jointDef), bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldWheelJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                               ample::graphics::Vector2d<float> anchor,
                                               ample::graphics::Vector2d<float> axis)
{
    b2WheelJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body, {anchor.x, anchor.y}, {axis.x, axis.y});
    _joints.emplace_back(new WorldWheelJoint2d(world.CreateJoint(&jointDef), bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldWeldJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                              ample::graphics::Vector2d<float> anchor,
                                              float referenceAngle)
{
    b2WeldJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body, {anchor.x, anchor.y});
    jointDef.referenceAngle = referenceAngle;
    _joints.emplace_back(new WorldWeldJoint2d(world.CreateJoint(&jointDef), bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldRopeJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                              ample::graphics::Vector2d<float> localAnchorA,
                                              ample::graphics::Vector2d<float> localAnchorB,
                                              float maxLength)
{
    b2RopeJointDef jointDef;
    jointDef.bodyA = bodyA._body;
    jointDef.bodyB = bodyB._body;
    jointDef.localAnchorA.Set(localAnchorA.x, localAnchorA.y);
    jointDef.localAnchorB.Set(localAnchorB.x, localAnchorB.y);
    jointDef.maxLength = maxLength;
    _joints.emplace_back(new WorldRopeJoint2d(world.CreateJoint(&jointDef), bodyA, bodyB));
    return *(_joints.back());
}

WorldJoint2d &WorldLayer2d::addWorldFrictionJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                  ample::graphics::Vector2d<float> anchor)
{
    b2FrictionJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body, {anchor.x, anchor.y});
    _joints.emplace_back(new WorldFrictionJoint2d(world.CreateJoint(&jointDef), bodyA, bodyB));
    return *(_joints.back());
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
}
} // namespace ample::physics
