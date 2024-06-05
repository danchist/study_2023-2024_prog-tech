#include <iostream>
#include <cmath>
using namespace std;



// точка - просто две координаты

class Point{

public:
    // задаём координаты
    double Px, Py;



    // конструктор - на вход подаём две координаты
    Point(double x, double y){
        Px = x;
        Py = y;
    };

    Point(){};
    // дефолтный конструктор, если его нет, и мы при конструировании других фигур что-то не то введём, случится что-то ОЧЕНЬ страшное
    // как минимум мне так пишет IDE
};



// линия - зависит от двух точек - начала и конца

class Line : public Point{
public:
    Point LineStart; // точка начала
    Point LineEnd;   // точка конца


    // конструктор - нужно задать две точки
    Line(Point start, Point end) : LineStart(start), LineEnd(end){};

    Line(){}; // IDE продолжает ругаться, что нет дефолтных конструкторов, поэтому везде видимо буду их ставить

    // выводим точки начала и конца
    void draw(){
        cout << endl << "Line begins at (" << LineStart.Px << "."<< LineStart.Py << ") ";
        cout << "and ends at (" << LineEnd.Px << "." << LineEnd.Py << ")" << endl;
    }

    // передвижение ВСЕЙ линии, значит надо сдивнуть и первую и вторую точку на одинаковое кол-во единиц
    void move(double x, double y){
        cout << endl << "Waiting for input: x y " << endl;
        cin >> x;
        cin >> y;
        LineStart.Px += x;
        LineStart.Py += y;
        LineEnd.Px += x;
        LineEnd.Py += y;
    }

    // Разворот, задаём угол, потому его вычисляем в радианах, и по алгоритму вычисляем новые коориднаты точки конца линии
    void rotate(double angle){
        angle = angle * M_PI / 180;
        LineEnd.Px = (LineEnd.Px - LineStart.Px) * cos(angle) - (LineEnd.Py - LineStart.Py) * sin(angle) + LineEnd.Px;
        LineEnd.Py = (LineEnd.Px - LineStart.Px) * sin(angle) + (LineEnd.Py - LineStart.Py) * cos(angle) + LineEnd.Py;
    }
};




// параллелограмм - четыре линии
class Parallelogramm : public Line{
public:
    Line uno;
    Line dos;
    Line tres;
    Line quatro;

    Parallelogramm(){}; // дефолтный конструктор

    // задаём на вход четыре точки, и на их основе строим прямые
    Parallelogramm(Point A, Point B, Point C, Point D) : uno(A, B), dos(B, C), tres(C, D), quatro(D, A){};

    // раз параллелограмм состоит из линий, то просто воспользуемся методом рисования линий
    void draw(){
        uno.draw();
        dos.draw();
        tres.draw();
        quatro.draw();
    }
    void move(double x, double y){
        uno.move(x, y);
        dos.move(x, y);
        tres.move(x, y);
        quatro.move(x, y);
    }
    void rotate(double angle){
        uno.rotate(angle);
        dos.rotate(angle);
        tres.rotate(angle);
        quatro.rotate(angle);
    }
};



// квадрат - параллелограмм, у которого все стороны равны
class Square : public virtual Parallelogramm{
    Parallelogramm sq;
    Square(){};

    void rotate(double angle){
        sq.rotate(angle);
    }
    void move(double x, double y){
        sq.move(x, y);
    }

public:
    Square(Point A, Point B, Point C, Point D){
        // Чтобы квадрат был квадратом, у него должны быть равны углы по 90 градусов
        // я не уверен, но альтернативно придумал выровнять точки по координатам, тогда точно будет квадрат
        // после выравнивания - строим Параллелограмм в таких точках
        D.Px = A.Px;
        B.Py = A.Py;
        C.Px = B.Px;
        sq = Parallelogramm(A, B, C, D);
    }

    void draw(){
        sq.draw();
    }
};




// Чтобы не повторяться, попробую построить ромб, не как параллелограмм, а с помощью линий.
// В задании просят разными способами попрактиковаться

class Rhombus : public Line{
    Line ein;
    Line zwei;
    Line drei;
    Line funf;
    Rhombus(){};

    Rhombus(Point A, Point B, Point C, Point D){
        // подтянули края, на всякий случай
        D.Px = A.Px;
        C.Px = B.Px;

        // и построили ромб
        ein = Line(A, B);
        zwei = Line(B, C);
        drei = Line(C, D);
        funf = Line(D, A);

    }
    void draw(){
        ein.draw();
        zwei.draw();
        drei.draw();
        funf.draw();
    }
    void move(double x, double y){
        ein.move(x, y);
        zwei.move(x, y);
        drei.move(x, y);
        funf.move(x, y);
    }
    void rotate(double angle){
        ein.rotate(angle);
        zwei.rotate(angle);
        drei.rotate(angle);
        funf.rotate(angle);
    }
};




// Прямоугольник - параллелограмм, у которого две стороны равны и параллельны попарно

class Rectangle : public  Parallelogramm{
    Parallelogramm fear;
    Rectangle(){};
    Rectangle(Point A, Point B, Point C, Point D){

        // запутался как надо привести параллелограмм к прямоугольнику, но вроде вышло
        D.Px = A.Px;
        C.Px = B.Px;
        B.Py = A.Py;
        D.Py = C.Py;
        fear = Parallelogramm(A, B, C, D);

    };

    void draw(){
        fear.draw();
    }
    void rotate(double angle){
        fear.rotate(angle);
    }
    void move(double x, double y){
        fear.move(x, y);
    }
};


int main(){
    Point LOL = Point(4, 6);

    Line Bart = Line(Point(4, 6), Point(8, 5));

    Line Hey = Line(LOL, Point(2, 8));

    Hey.draw();

    Bart.draw();
    Bart.move(5, 6);
    Bart.draw();

    Parallelogramm nice = Parallelogramm(Point(7, 3), Point(2, 4), Point(2, 4), Point(9, 9));

    nice.rotate(45);

    Square cool = Square(Point(1, 1), Point(4, 1), Point(4, 4), Point(1, 4));

    cool.draw();
}