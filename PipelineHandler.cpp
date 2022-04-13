#include "PipelineHandler.h"
# define MATH_PI 3.14159265358979323846

PipelineHandler::PipelineHandler()
{
    m_scale = { 1.0f, 1.0f, 1.0f };
    m_position = { 0.0f, 0.0f, 0.0f };
    m_rotation = { 0.0f, 0.0f, 0.0f };
}

void PipelineHandler::setPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}
void PipelineHandler::setRotation(float x, float y, float z)
{
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}
void PipelineHandler::setScale(float x, float y, float z) 
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

glm::mat4 PipelineHandler::getTranslationTransformation()
{
    return glm::mat4({
            {1.0f,0.0f,0.0f,m_position.x},
            {0.0f,1.0f,0.0f,m_position.y},
            {0.0f,0.0f,1.0f,m_position.z},
            {0.0f,0.0f,0.0f,1.0f}
        });
}
glm::mat4 PipelineHandler::getRotationTransformation()
{
    double x = ((m_rotation.x) * MATH_PI / 180.0f);
    double y = ((m_rotation.y) * MATH_PI / 180.0f);
    double z = ((m_rotation.z) * MATH_PI / 180.0f);

    glm::mat4 rotationX = {
        {1.0f,  0.0f,   0.0f,       0.0f},
        {0.0f,  cos(x), -sin(x),    0.0f},
        {0.0f,  sin(x), cos(x),     0.0f},
        {0.0f,  0.0f,   0.0f,       1.0f}
    };

    glm::mat4 rotationY = {
        {cos(x),  0.0f,   -sin(x),  0.0f},
        {0.0f,    1.0f,   0.0f,     0.0f},
        {sin(x),  0.0f,   cos(x),   0.0f},
        {0.0f,    0.0f,   0.0f,     1.0f}
    };

    glm::mat4 rotationZ = {
        {cos(z), -sin(z),    0.0f,   0.0f},
        {sin(z),  cos(z),    0.0f,   0.0f},
        {0.0f,      0.0f,   1.0f,   0.0f},
        {0.0f,      0.0f,   0.0f,   1.0f}
    };

    return rotationX * rotationY * rotationZ;
} 
glm::mat4 PipelineHandler::getScaleTransformation()
{
    return glm::mat4({
            {m_scale.x,0.0f,0.0f,0.0f},
            {0.0f,m_scale.y,0.0f,0.0f},
            {0.0f,0.0f,m_scale.z,0.0f},
            {0.0f,0.0f,0.0f,1.1f}
        });
}

glm::mat4* PipelineHandler::getTransformationMatrix()
{
    glm::mat4 translationTransformation = getTranslationTransformation();
    glm::mat4 rotationTransformation = getRotationTransformation();
    glm::mat4 scaleTransformation = getScaleTransformation();

    m_transformation = translationTransformation *
        rotationTransformation * scaleTransformation;

    return &m_transformation;
}