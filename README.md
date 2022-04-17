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

getTransformationMatrix - calculates and combines rotation, scale and translation transformation matrices (transformation has to be applied last to avoid change in center of rotation and scaling):<br>

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

# Perspective Projection 

We will store and set all projection attributes using a structure:

	struct ProjectionProps
	{
		float fov;
		float width;
		float height;
		float zNear;
		float zFar;
	};
	ProjectionProps m_projection;
	
Given those attributes we can construct a projection transformation matrix. Using some clever math we get that fancy piece, with tans and screen ratios and the like. Real smart and complicated is what it is. Just have a look:

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

	    matrix[0][0] = 1.0f / (tanHalfFOV * ar);

	    matrix[1][1] = 1.0f / tanHalfFOV;
	    matrix[2][2] = (-zNear - zFar) / zRange;
	    matrix[2][3] = 2.0f * zFar * zNear / zRange;

	    return matrix;
	}

# Camera Transformations
We will store and set all camera attributes using a structure:

    struct CameraProps
    {
        glm::vec3 posVec;
        glm::vec3 targetVec;
        glm::vec3 upVec;
    };
    CameraProps m_camera;

Given those attributes we can construct a camera rotation transformation matrix. Using some clever math we get that fancy piece, with normalized vectors and cross products and the like. Real smart and complicated is what it is. Just have a look:

glm::mat4 PipelineHandler::getCameraRotationTransformation(
    const glm::vec3& targetVec,
    const glm::vec3& upVec)
{
    glm::vec3 N = targetVec;
    N = glm::normalize(N);
    glm::vec3 U = upVec;
    U = glm::normalize(U);
    U = glm::cross(U, targetVec);
    glm::vec3 V = glm::cross(N, U);


    glm::mat4 matrix = glm::mat4({
        {U.x,  U.y,  U.z,  0.0f},
        {V.x,  V.y,  V.z,  0.0f},
        {N.x,  N.y,  N.z,  0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    });
    return matrix;
}

Camera translation transformation is mush simpler. When camera moves everything else moves in the opposite direction, so we just get a translation transformation matrix with the negative with respect to camera position components:

    glm::mat4 cameraTranslation = getTranslationTransformation(
        -m_camera.posVec.x,
        -m_camera.posVec.y,
        -m_camera.posVec.z);
	
# Main Loop 

scale += 0.001f; - every loop we increase global scale variable to create motion<br><br>
By using sin and cos we create cyclical motion:<br>

    PipelineHandler pipeline;
    pipeline.setPosition(cos(Scale) * 0.25f, sin(Scale) * 0.065f, sin(Scale * 50) * 0.02f);
    pipeline.setScale(sin(Scale)*0.2f + 1.0f, cos(Scale) * 0.2f + 1.0f, 1.0f);
    pipeline.setRotation((int)(Scale * 100) % 360, 0, 0);
    
    pipeline.setPerspective(
        30.0f,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        1.0f,
        100.0f);
    pipeline.setCamera(glm::vec3({ 0.0f,0.0f,0.0f }),
        glm::vec3({ 0.8f,0.8f ,2.0f }),
        glm::vec3({ 0.0f,1.0f ,0.0f }));
    
    glUniformMatrix4fv(globalLocation, 1, GL_TRUE, (const GLfloat*)pipeline.getTransformationMatrix());
    
After which we get our final transormation matrix and pass it to glUniformMatrix4fv to update our point positions<br>
