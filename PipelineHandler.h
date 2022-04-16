#pragma once
#include <glm/glm.hpp>

class PipelineHandler
{
public:
    PipelineHandler();

    void setPosition(float x, float y, float z);
    void setRotation(int degX, int degY, int degZ);
    void setScale(float x, float y, float z);
    void setPerspective(float fov, float width, float height,
                        float zNear, float zFar);

    glm::mat4* getTransformationMatrix();

private:
    glm::mat4 getTranslationTransformation();
    glm::mat4 getRotationTransformation();
    glm::mat4 getScaleTransformation();
    glm::mat4 getProjectionTransformation();

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    struct Projection
    {
        float fov;
        float width;
        float height;
        float zNear;
        float zFar;
    };

    Projection m_projection;

    glm::mat4 m_transformation;
};