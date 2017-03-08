#include <GLTools.h>
#include <glut/glut.h>
#include <iostream>

GLBatch g_triangle_batch;
GLShaderManager g_shader_manager;

GLfloat verts[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f,  0.0f, 0.0f,
        0.0f,  0.5f, 0.0f
};

void change_size(int w, int h){
    glViewport(0, 0, w, h);
}

void setup_rc(){
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        g_shader_manager.InitializeStockShaders();

        g_triangle_batch.Begin(GL_TRIANGLES, 3);
        g_triangle_batch.CopyVertexData3f(verts);
        g_triangle_batch.End();
}

void special_keys(int key, int x, int y)
{
    GLfloat step_size = 0.025f;

    GLfloat block_x = verts[0];
    GLfloat block_y = verts[7];

    if(GLUT_KEY_UP == key){
        block_y += step_size;
    }

    if(GLUT_KEY_DOWN == key){
        block_y -= step_size;
    }

    if(GLUT_KEY_LEFT == key){
        block_x -= step_size;
    }

    if(GLUT_KEY_RIGHT == key){
        block_x += step_size;
    }

    if(block_x < -1.0f) block_x = -1.0f;
    if(block_x > 0.0f) block_x = 0.0f;
    if(block_y > 1.0f) block_y = 1.0f;
    if(block_y < -0.5f) block_y = -0.5f;

    verts[0] = block_x;
    verts[1] = block_y - 0.5;

    verts[3] = block_x + 1;
    verts[4] = block_y - 0.5;

    verts[6] = block_x + 0.5;
    verts[7] = block_y;

    for(int i = 0 ; i < 9; i++){
        std::cout << verts[i] << " ";
    }
    std::cout << std::endl;
    g_triangle_batch.Begin(GL_TRIANGLES, 3);
    g_triangle_batch.CopyVertexData3f(verts);
    g_triangle_batch.End();
    glutPostRedisplay();

}

void rander_scence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat v_red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    g_shader_manager.UseStockShader(GLT_SHADER_IDENTITY, v_red);
    g_triangle_batch.Draw();

    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("my first opangl application");
    glutReshapeFunc(change_size);
    glutDisplayFunc(rander_scence);
    glutSpecialFunc(special_keys);

    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        std::cout << "error:" << glewGetErrorString(err) << std::endl;
        return 1;
    }
    setup_rc();

    glutMainLoop();
    return 0;
}
