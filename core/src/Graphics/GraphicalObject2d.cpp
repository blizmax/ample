#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Debug.h"
#include "Exception.h"
#include "GraphicalObject2d.h"
#include "ShaderProcessor.h"
#include "Vector2d.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::string &name,
                                     const std::string &className,
                                     const std::vector<Vector2d<float>> &graphicalShape,
                                     const float thickness,
                                     const float z,
                                     const Vector2d<float> &faceTextureRepeats,
                                     const Vector2d<float> &sideTextureRepeats,
                                     const normalsMode sideNormalsMode,
                                     const glm::mat4 &translated,
                                     const glm::mat4 &scaled,
                                     const glm::mat4 &rotated)
    : GraphicalObject(name, className, translated, scaled, rotated),
      _face(std::make_shared<GraphicalPolygon>(name + ".face", graphicalShape, z, faceTextureRepeats)),
      _side(std::make_shared<GraphicalEdge>(name + ".side", graphicalShape, z, thickness, sideTextureRepeats, sideNormalsMode))
{
    addSubObject(std::static_pointer_cast<GraphicalObject>(_face));
    addSubObject(std::static_pointer_cast<GraphicalObject>(_side));
}

GraphicalObject2d::GraphicalObject2d(const std::string &name,
                                     const std::string &className,
                                     const std::vector<Vector2d<float>> &graphicalShape,
                                     const float thickness,
                                     const float z,
                                     const Vector2d<float> &faceTextureRepeats,
                                     const Vector2d<float> &sideTextureRepeats,
                                     const normalsMode sideNormalsMode,
                                     const Vector2d<float> &translated,
                                     const float &rotated)
    : GraphicalObject2d(name,
                        className,
                        graphicalShape,
                        thickness,
                        z,
                        faceTextureRepeats,
                        sideTextureRepeats,
                        sideNormalsMode,
                        glm::translate(glm::vec3{translated.x, translated.y, z}),
                        glm::scale(glm::vec3{1.0f}),
                        glm::rotate(rotated, glm::vec3{0.0f, 0.0f, 1.0f}))
{
}

GraphicalEdge &GraphicalObject2d::side() noexcept
{
    return *_side;
}

GraphicalPolygon &GraphicalObject2d::face() noexcept
{
    return *_face;
}

std::shared_ptr<GraphicalEdge> GraphicalObject2d::sidePointer() noexcept
{
    return _side;
}

std::shared_ptr<GraphicalPolygon> GraphicalObject2d::facePointer() noexcept
{
    return _face;
}

GraphicalObject2d::GraphicalObject2d(filing::JsonIO input)
    : GraphicalObject(input),
      _face(std::make_shared<GraphicalPolygon>(input.updateJsonIO("face"))),
      _side(std::make_shared<GraphicalEdge>(input.updateJsonIO("side")))
{
    addSubObject(std::static_pointer_cast<GraphicalObject>(_face));
    addSubObject(std::static_pointer_cast<GraphicalObject>(_side));
}

std::string GraphicalObject2d::dump()
{
    return filing::mergeStrings({GraphicalObject::dump(),
                                 filing::makeField("face", _face->dump()),
                                 filing::makeField("side", _side->dump())});
}
} // namespace ample::graphics
