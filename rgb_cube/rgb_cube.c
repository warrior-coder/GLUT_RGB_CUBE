#include <GLUT/glut.h>

#define NUM_VERTICES 8
#define NUM_FACES 6


// вращение цветового куба RGB
// поскольку куб является выпуклым многогранником и единственный элемент на сцене, его можно отрисовывать, используя только отсечение задней грани (нет необходимости в буфере глубины)


// куб имеет противоположные углы в точках {0,0,0} и {1,1,1}, которым соответствуют черные и белые вершины
// Ox — красный градиент, Oy — зеленый градиент, Oz — синий градиент
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

// анимация достигается путем очистки окна и отрисовки нового положения куба
void DisplayFunc()
{
    // очистка окна
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glLoadIdentity();

    // вращение куба
    glScalef(0.75f, 0.75f, 0.75f);
    glTranslatef(0, -0.84f, -2.0f);
    glRotatef(54.73561032f, -1, 0, 1);

	glRotatef(rotateAngle, 1, 1, 1);
    rotateAngle += 1.5f;

    // отрисовка граней
	glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            glColor3fv((GLfloat*)(vertexColors + faceIndexes[i][j])); // задает текущий цвет из указанного массива GLfloat[3]
            glVertex3iv((GLint*)(vertices + faceIndexes[i][j])); // задает координаты текущей вершины из указанного массива GLint[3]
        }
    }
    glEnd();

    glPopMatrix();

    glFlush(); // очищает все буферы и заставляет все ранее выданные команды выполниться
    glutSwapBuffers(); // окно имеет двойную буферизацию, поэтому меняем местами буферы, чтобы сделать рисунок видимым и получить анимацию без мерцания
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, value);
}

void ReshapeFunc(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 0.5, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

// единственное, что нужно сделать в начале это включить отсечение задней грани
void Initialize()
{
    glEnable(GL_DEPTH_TEST);
}

// точка входа GLUT-приложения
int main(int argc, char** argv)
{
    // создание окна
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutCreateWindow("GLUT RGB Cube");

    // привязка функций-обработчиков к событиям
	glutReshapeFunc(ReshapeFunc);
    glutTimerFunc(10, TimerFunc, 0);
    glutDisplayFunc(DisplayFunc);

    Initialize();

	glutMainLoop();
}