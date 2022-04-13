# Computer Graphics Laboratory work 2
USATU Engineering Graphics univecity cource. <br>
Drawing a triangle, square, dots and a line in OpenGL freeglut environment.<br>
Выполнил студент группы ПРО-227 Кузнецов Кирилл.<br><br>

# Shader Setup
void createShader(GLuint* shaderprog, GLenum shaderType, const GLchar* shaderText)<br>
{<br>
    GLuint ShaderObj = glCreateShader(shaderType) - 
    <br><br>
    const GLchar* p[1] - 
    <br><br>
    p[0] = shaderText - 
    <br><br>
    GLint Lengths[1] - 
    <br><br>
    Lengths[0] = strlen(shaderText) - 
    <br><br>
    glShaderSource(ShaderObj, 1, p, Lengths) - 
    <br><br>

    glCompileShader(ShaderObj) - 
    <br><br>

    glAttachShader(*shaderprog, ShaderObj) - 
    <br><br>

    glGetProgramiv(*shaderprog, GL_LINK_STATUS, &Success) - 
    <br><br>

    glValidateProgram(*shaderprog) - 
    <br><br>
}<br><br>
main():<br>
    GLuint shaderprog = glCreateProgram() - 
    <br><br>

    createShader(&shaderprog, GL_VERTEX_SHADER, pVS) - 
    <br><br>
    createShader(&shaderprog, GL_FRAGMENT_SHADER, pFS) - 
    <br><br>

    glLinkProgram(shaderprog) -
    <br><br>
    glUseProgram(shaderprog) - 
    <br><br>

    globalLocation = glGetUniformLocation(shaderprog, "gWorld") - 
    <br><br>


# Pipeline Handler

# Main Loop 
