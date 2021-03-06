#pragma once

#include "Camera.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
class CameraOrtho : public Camera
{
public:
    CameraOrtho(const std::string &name,
                const Vector2d<pixel_t> &viewSize,
                const Vector2d<pixel_t> &viewPosition,
                const Vector3d<float> &eyePos,
                const Vector3d<float> &direction,
                float left,
                float right,
                float bottom,
                float top,
                float near,
                float far);

    CameraOrtho(const filing::JsonIO &input);
    std::string dump() override;

    void look() override;
    void unlook() override;

    void setLeft(float);
    void setRight(float);
    void setBottom(float);
    void setTop(float);
    void setNear(float);
    void setFar(float);

    float getLeft() const;
    float getRight() const;
    float getBottom() const;
    float getTop() const;
    float getNear() const;
    float getFar() const;

private:
    float _left;
    float _right;
    float _bottom;
    float _top;
    float _near;
    float _far;

    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};

    shaders::ShaderProcessor::Uniform _viewMatrixUniform;
    shaders::ShaderProcessor::Uniform _projectionMatrixUniform;
};
} // namespace ample::graphics
