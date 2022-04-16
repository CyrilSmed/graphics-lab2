#include "PipelineHandler.h"
# define MATH_PI 3.14159265358979323846

PipelineHandler::PipelineHandler()
{
    m_scale =    { 1.0f, 1.0f, 1.0f };
    m_position = { 0.0f, 0.0f, 0.0f };
    m_rotation = { 0.0f, 0.0f, 0.0f };
}

void PipelineHandler::setPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}
void PipelineHandler::setRotation(int x, int y, int z)
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
void PipelineHandler::setPerspective(
    float fov, 
    float width, 
    float height, 
    float zNear, 
    float zFar)
{
    m_projection.fov = fov;
    m_projection.width = width;
    m_projection.height = height;
    m_projection.zNear = zNear;
    m_projection.zFar = zFar;
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
        {0.0f,0.0f,0.0f,     1.0f}
    });
}
glm::mat4 PipelineHandler::getProjectionTransformation()
{
    const float ar = m_projection.width / m_projection.height;
    const float zNear = m_projection.zNear;
    const float zFar = m_projection.zFar;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = glm::tan(glm::radians(m_projection.fov) / 2.0);
    
    glm::mat4 matrix = glm::mat4({
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f}
    });

    float test = 1.0f / (tanHalfFOV * ar);
    matrix[0][0] = test;

    matrix[1][1] = 1.0f / tanHalfFOV;
    matrix[2][2] = (-zNear - zFar) / zRange;
    matrix[2][3] = 2.0f * zFar * zNear / zRange;

    return matrix;
}

glm::mat4* PipelineHandler::getTransformationMatrix()
{
    glm::mat4 translationTransformation = getTranslationTransformation();
    glm::mat4 rotationTransformation = getRotationTransformation();
    glm::mat4 scaleTransformation = getScaleTransformation();
    glm::mat4 projectionTransformation = getProjectionTransformation();

    m_transformation = projectionTransformation *
                       scaleTransformation * 
                       rotationTransformation *
                       translationTransformation;

    //float matrix[4][4] = { {0, 1, 2, 3},
    //                       {4, 5, 6, 7},  
    //                       {8, 9, 10, 11}, 
    //                       {12, 13, 14, 15} };

    //for (int x = 0; x < 4; x++)
    //{
    //    for (int y = 0; y < 4; y++)
    //    {
    //        matrix[x][y] = m_transformation[x][y];
    //    }
    //}

    return &m_transformation;
}