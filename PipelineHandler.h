#pragma once
#include <glm/glm.hpp>

class PipelineHandler
{
public:
    PipelineHandler();

    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    glm::mat4* getTransformationMatrix();

private:
    glm::mat4 getTranslationTransformation();
    glm::mat4 getRotationTransformation();
    glm::mat4 getScaleTransformation();

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4 m_transformation;
};