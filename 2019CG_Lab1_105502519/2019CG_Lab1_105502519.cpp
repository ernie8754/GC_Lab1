#include<gl/GLUT.H>
#include<iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <math.h>
enum keyState
{
	dot, line, polygon, circle, clear, redo, quit, none
};
keyState _keyState=none;
int linex1, liney1;
int cirx1, ciry1;
class Point
{
public:
	int x; 
	int y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
std::vector<Point> PolyPoint;
std::vector<Point> AllPoints;
void writeDot(int x, int y) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	std::cout << x << " " << y << "\n";
	glEnd();
	glFlush();
	Point temp = Point(x, y);
	AllPoints.push_back(temp);
}
void writeCirDot(int x, int y, int xBias, int yBias) {
	writeDot(x + xBias, y + yBias);
}
void writeLine(int x1, int y1, int x2, int y2) {
	bool swap = false;
	bool isNegX = false;
	bool isNegY = false;
	std::cout << "x1:" << x1 << std::endl << "y1:" << y1 << std::endl << "x2:" << x2 << std::endl << "y2:" << y2 << std::endl;
	if (abs(x2 - x1) < abs(y2 - y1)) {
		swap = true;
		std::cout << "swap";
	}
	if (x2 < x1) {
		isNegX = true;
		std::cout << "NegX";
	}
	if (y2 < y1) {
		isNegY = true;
		std::cout << "NegY";
	}
	if (isNegX) {
		x2 = -x2;
		x1 = -x1;
	}
	if (isNegY) {
		y2 = -y2;
		y1 = -y1;
	}
	if (swap) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}
	
	int x = x1, y = y1;
	int a = abs(y2 - y1);
	int b = -abs(x2 - x1);
	int d = (2 * a + b) / 2 ;
	//std::cout << "a:" << a<<std::endl << "b:" << b << std::endl << "d:" << d << std::endl;
	std::cout << "----------------" << std::endl;
	while (x < x2)
	{
		std::cout << d << std::endl;
		if (d <= 0) {
			x++;
			d += a;
		}
		else {
			x++;
			y++;
			d += (a + b);
		}
		int newX = x, newY = y;
		if (swap) {
			std::swap(newX, newY);
		}
		if (isNegX) {
			newX = -newX;
		}
		if (isNegY) {
			newY = -newY;
		}
		//std::cout << "x:" << newX << std::endl << "y:" << newY << std::endl;
		writeDot(newX, newY);
	}
	std::cout << "----------------" << std::endl;
}
void writeCir(int x1, int y1, int x2, int y2) {
	int r = std::round(sqrt(pow(x1 - x2,2)+ pow(y1 - y2, 2)));
	int xBias=x1, yBias=y1;
	writeCirDot(0, r, xBias, yBias);
	writeCirDot(r, 0, xBias, yBias);
	writeCirDot(0, -r, xBias, yBias);
	writeCirDot(-r, 0, xBias, yBias);
	int newX = 0,newY=r,dini=1 - r,incEini=3,incSEini=-2*r+5;
	int d = dini, incE=incEini, incSE=incSEini;
	while (newX < newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newX++;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX++;
			newY--;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newY = 0, newX = r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX > newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newY++;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newY++;
			newX--;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newX = 0, newY = -r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX > newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newX--;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX--;
			newY++;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newY = 0, newX = -r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX < newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newY--;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newY--;
			newX++;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newX = 0, newY = -r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX < -newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newX++;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX++;
			newY++;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newY = 0, newX = -r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newY < -newX ) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newY++;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX++;
			newY++;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newX = 0, newY = r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX > -newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newX--;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX--;
			newY--;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
	newY = 0, newX = r, dini = 1 - r, incEini = 3, incSEini = -2 * r + 5;
	d = dini, incE = incEini, incSE = incSEini;
	while (newX > -newY) {
		if (d < 0) {
			d += incE;
			incE += 2;
			incSE += 2;
			newY--;
		}
		else {
			d += incSE;
			incE += 2;
			incSE += 4;
			newX--;
			newY--;
		}
		writeCirDot(newX, newY, xBias, yBias);
	}
}
void Initial(void)//初始化函数 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//白色背景，前3个是RGB，最后是Alpha值，用来控制透明，1.0表示完全不透明
	glMatrixMode(GL_PROJECTION);//OpenGL按照三维方式来处理图像，所以需要一个投影变换将三维图形投影到显示器的二维空间中
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);//指定使用正投影将一个x坐标在0~200，y坐标0~150范围内的矩形坐标区域投影到显示器窗口
	glClear(GL_COLOR_BUFFER_BIT);
}
void myDisplay(void)//显示回调函数
{
	//使用glClearColorz中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色
	glColor3f(1.0f, 1.0f, 1.0f);//绘图颜色为黑色
	glRectf(50.0f, 100.0f, 150.0f, 50.0f);//图形的坐标，绘制一个左上角在（50，100），右下角在（150，50）的矩形
	glFlush();//清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
}
void mouseButton(int button, int state, int x, int y) {
	y = 600 - y;
	if (button == GLUT_LEFT_BUTTON && state== GLUT_DOWN) {
		switch (_keyState)
		{
		case dot:
			writeDot(x, y);
			break;
		case line:
			//std::cout << "begin " << x << " " << y;
			writeDot(x, y);
			linex1 = x;
			liney1 = y;
			break;
		case polygon:
			writeDot(x, y);
			if (!PolyPoint.empty()) {
				writeLine(PolyPoint.back().x, PolyPoint.back().y, x, y);
			}
			{Point newPoint = Point(x, y);
			PolyPoint.push_back(newPoint); }
			break;
		case circle:
			cirx1 = x; ciry1 = y;
			_keyState = circle;
			break;
		case clear:
			_keyState = clear;
			break;
		case redo:
			_keyState = redo;
			break;
		case quit:
			_keyState = quit;
			break;
		default:
			break;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		switch (_keyState) {
		case line:
			//std::cout << "end " << x << " " << y<<std::endl;
			writeLine(linex1, liney1, x, y);
			break;
		case circle:
			//std::cout << "end " << x << " " << y<<std::endl;
			writeCir(cirx1, ciry1, x, y);
			break;
		default:
			break;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		switch (_keyState) {
		case polygon:
			//std::cout << "end " << x << " " << y<<std::endl;
			if (PolyPoint.empty())
				return;
			writeLine(PolyPoint.front().x, PolyPoint.front().y, PolyPoint.back().x, PolyPoint.back().y);
			PolyPoint.clear();
			break;
		default:
			break;
		}
	}
}
void mouseDrag(int x, int y) {
	if (_keyState != line)
		return;
}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'd':
		_keyState = dot;
		break;
	case 'l':
		_keyState = line;
		break;
	case 'p':
		_keyState = polygon;
		break;
	case 'o':
		_keyState = circle;
		break;
	case 'c':
		PolyPoint.clear();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		break;
	case 'r':
		for (auto i = 0; i < AllPoints.size(); i++) {
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex2d(AllPoints[i].x, AllPoints[i].y);
			glEnd();
			glFlush();
		}
		break;
	case 'q':
		exit(0);
		_keyState = quit;
		break;
	default:
		break;
	}
}
int main(int argc, char * argv[])//这是使用glut库函数进行窗口管理
{
	glutInit(&argc, argv);//使用glut库需要进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设定窗口显示模式，颜色模型和缓存，这里是RGB颜色模型和单缓存
	glutInitWindowPosition(200, 200);//设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(600, 600);//设定窗口的大小
	glutCreateWindow("My Progect 1");//创建一个窗口，参数是窗口标题名
	//glutDisplayFunc(&myDisplay);//将myDisplay指定为当前窗口的显示内容函数
	glutMouseFunc(&mouseButton);
	glutKeyboardFunc(&keyboard);
	//glutMotionFunc(&mouseDrag);
	Initial();
	glutMainLoop();//使窗口框架运行起来，使显示回调函数开始工作
	return 0;
}