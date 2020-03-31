#include "GraphicalPolygon.h"

#include "Debug.h"
#include "Vector3d.h"

namespace ample::graphics
{
static std::vector<Vector3d<float>> generateFaceCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                       const float z)
{
    std::vector<Vector3d<float>> faceArray;
    size_t verts = graphicalShape.size();
    for (size_t i = 1; i < verts - 1; ++i)
    {
        faceArray.emplace_back(graphicalShape[0].x, graphicalShape[0].y, z);
        faceArray.emplace_back(graphicalShape[i].x, graphicalShape[i].y, z);
        faceArray.emplace_back(graphicalShape[i + 1].x, graphicalShape[i + 1].y, z);
    }
    return faceArray;
}

static std::vector<Vector3d<float>> generateFaceNormals(const std::vector<Vector2d<float>> &graphicalShape, const float z)
{
    return {generateFaceCoords(graphicalShape, z).size(), {0, 0, -1}};
}

static std::vector<Vector2d<float>> generateFaceUVCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                         const Vector2d<float> &repeats,
                                                         const float z)
{
    auto vert = generateFaceCoords(graphicalShape, z);
    std::vector<Vector2d<float>> uvCoords(vert.size());
    ASSERT(vert.size() > 0);
    Vector2d<float> leftDown{vert[0].x, vert[0].y};
    Vector2d<float> rightTop{vert[0].x, vert[0].y};
    for (size_t i = 1; i < vert.size(); ++i)
    {
        leftDown.x = std::min(leftDown.x, vert[i].x);
        leftDown.y = std::min(leftDown.y, vert[i].y);
        rightTop.x = std::max(rightTop.x, vert[i].x);
        rightTop.y = std::max(rightTop.y, vert[i].y);
    }
    for (size_t i = 0; i < vert.size(); ++i)
    {
        uvCoords[i].x = ((vert[i].x - leftDown.x) / (rightTop.x - leftDown.x)) * repeats.x;
    }
    for (size_t i = 0; i < vert.size(); ++i)
    {
        uvCoords[i].y = ((vert[i].y - leftDown.y) / (rightTop.y - leftDown.y)) * repeats.y;
    }
    return uvCoords;
}

GraphicalPolygon::GraphicalPolygon(const std::vector<Vector2d<float>> &shape,
                                   const float z,
                                   const Vector2d<float> &textureRepeats,
                                   const glm::mat4 &translated,
                                   const glm::mat4 &scaled,
                                   const glm::mat4 &rotated)
    : GraphicalObject(translated, scaled, rotated),
      _textureRepeats(textureRepeats)
{
//    bindVertexArray(std::make_shared<VertexArray>(
//        generateFaceCoords(shape, z),
//        generateFaceUVCoords(shape, textureRepeats, z),
//        generateFaceNormals(shape, z)));
}

//GraphicalPolygon::GraphicalPolygon(filing::JsonIO &input)
//    : GraphicalPolygon(input.read<std::vector<Vector2d<float>>>("shape"),
//                       input.read<float>("z"),
//                       input.read<Vector2d<float>>("textureRepeats"),
//                       input.read<glm::mat4>("translated"),
//                       input.read<glm::mat4>("scaled"),
//                       input.read<glm::mat4>("rotated"))
//{
//}
//
//void GraphicalPolygon::dump(filing::JsonIO &output)
//{
//    GraphicalObject::dump(output);
//    output.write<std::vector<Vector2d<float>>>("shape", _shape);
//    input.write<float>("z", getZ());
//    input.write<Vector2d<float>>("textureRepeats", _textureRepeats);
//}
} // namespace ample::graphics
