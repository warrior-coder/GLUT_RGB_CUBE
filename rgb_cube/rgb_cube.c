#include <GLUT/glut.h>

#define NUM_VERTICES 8
#define NUM_FACES 6

GLint vertices[NUM_VERTICES][3] = {
	{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
	{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
};

GLint faceIndexes[NUM_FACES][4] = {
	{1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
	{3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}
};

GLfloat vertexColors[NUM_VERTICES][3] = {
	{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
	{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
};

GLfloat rotateAngle = 0.0f;

void DisplayFunc()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
     
    glPushMatrix();
    glLoadIdentity();

    glScalef(0.75f, 0.75f, 0.75f);
    glTranslatef(0, -0.84f,  0);
    glRotatef(54.73561032f, -1, 0, 1);

	glRotatef(rotateAngle, 1, 1, 1);
    rotateAngle += 1.5f;

	glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            glColor3fv((GLfloat*)(vertexColors + faceIndexes[i][j]));
            glVertex3iv((GLint*)(vertices + faceIndexes[i][j]));
        }
    }
    glEnd();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, value);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutCreateWindow("RGB Cube");
    
    glutTimerFunc(10, TimerFunc, 0);
    glutDisplayFunc(DisplayFunc);

	glutMainLoop();
}