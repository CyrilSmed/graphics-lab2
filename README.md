# Computer Graphics Laboratory work 2
USATU Engineering Graphics univecity cource. <br>
Drawing a triangle, square, dots and a line in OpenGL freeglut environment.<br>
Выполнил студент группы ПРО-227 Кузнецов Кирилл.<br><br>

# Pipeline Handler

public:
void setPosition(float x, float y, float z);<br>
void setRotation(int degX, int degY, int degZ);<br>
void setScale(float x, float y, float z);<br>
Setters for m_position, m_rotation, m_scale private member variables<br><br>

getTransformationMatrix - calculates and combines rotation, scale and translation transformation matrices (transformation has to be applied last to avoid change in center of rotation)
glm::mat4* PipelineHandler::getTransformationMatrix()<br>
{<br>
glm::mat4 translationTransformation = getTranslationTransformation();<br>
glm::mat4 rotationTransformation = getRotationTransformation();<br>
glm::mat4 scaleTransformation = getScaleTransformation();<br><br>

m_transformation = rotationTransformation * scaleTransformation * translationTransformation;<br>

return &m_transformation;<br>
}<br><br>

private:
glm::vec3 m_position;<br>
glm::vec3 m_rotation;<br>
glm::vec3 m_scale;<br>
glm::mat4 m_transformation; - final transformation matrix that we will return 
<br><br>

Functions that actually create and return transformation matrices are based on linear algebra and properties of matrix multiplication. Rotation happens along 3 axes in 3d space so it requires combining 3 transformation matrices along those axes.<br>

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


# Main Loop 
