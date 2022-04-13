# Computer Graphics Laboratory work 2
USATU Engineering Graphics univercity cource. <br>
Creating and applying transformation matrices.<br>
Выполнил студент группы ПРО-227 Кузнецов Кирилл.<br><br>

# Pipeline Handler

public:
Setters for m_position, m_rotation, m_scale private member variables:<br>

	void setPosition(float x, float y, float z);
	void setRotation(int degX, int degY, int degZ);
	void setScale(float x, float y, float z);

getTransformationMatrix - calculates and combines rotation, scale and translation transformation matrices (transformation has to be applied last to avoid change in center of rotation):<br>

	glm::mat4* PipelineHandler::getTransformationMatrix()<br>
	{
		glm::mat4 translationTransformation = getTranslationTransformation();<br>
		glm::mat4 rotationTransformation = getRotationTransformation();<br>
		glm::mat4 scaleTransformation = getScaleTransformation();<br><br>

		m_transformation = rotationTransformation * scaleTransformation * translationTransformation;<br>

		return &m_transformation;<br>
	}

private:<br>
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

scale += 0.001f; - every loop we increase global scale variable to create motion<br><br>
By using sin and cos we create cyclical motion:<br>

    PipelineHandler pipeline;
    pipeline.setPosition(sin(scale)*0.2f, cos(scale) * 0.2f, 0.0f);
    pipeline.setRotation(0,0, sin(scale) * 180);
    pipeline.setScale(cos(scale) + 0.2f, cos(scale) + 0.2f, 0.0f);
    
    glUniformMatrix4fv(globalLocation, 1, GL_TRUE, (const GLfloat*)pipeline.getTransformationMatrix());
    
After which we get our final transormation matrix and pass it to glUniformMatrix4fv to update our points<br>

