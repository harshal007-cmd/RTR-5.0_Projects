/*
#include<iostream>
using namespace std;
class Demo
{
    static Demo _instance;
    Demo()=default;
    int bright;
    int sound;
public:
    static Demo& getInstance()
    {
        static Demo _instance;
        return _instance;
    }
    
    void setValues(int b,int s)
    {
        bright = b;
        sound = s;
    }
    
    void show()
    {
        cout<<"bright = "<<bright<<"\nsound = "<<sound<<"\n"<<endl;
    }
    
    //Demo(const Demo&) = delete;
};

void someFun()
{
    Demo &other = Demo::getInstance();
    other.setValues(200,200);
    other.show();
    
}

void fun2()
{
    Demo &demo = Demo::getInstance();
    demo.show();
}

//Demo *Demo::_instance = NULL;

int main()
{
    Demo &setting = Demo::getInstance();
    setting.setValues(100,100);
    setting.show();
   // cout<<"In other function\n";
    //someFun();
    //cout<<"In another fun\n";
    //fun2();
    
    //cout<<"Direct = "<<Demo::getInstance().show();
    
    cout<<"copy of setting obj\n";
    Demo copy = setting;
    copy.setValues(500,500);
    setting.show();
    copy.show();
    
    return 0;
}
*/

#include<iostream>
using namespace std;

class Shape
{
public:
    virtual void draw() = 0;
    virtual ~Shape(){}
};


class Circle:public Shape
{
public:
    void draw()
    {
        cout<<"In Circle\n";
    }
    
};

class Square:public Shape
{
public:
    void draw()
    {
        cout<<"In Square\n";
    }
    
};

class Ring:public Shape
{
public:
    void draw()
    {
        cout<<"In Ring\n";
    }
};


class ShapeFactory
{
public:
    virtual Shape* createShape()=0;
    virtual ~ShapeFactory(){}
};

//concrete creator
class CircleFactory:public ShapeFactory
{
public:
    Shape* createShape() override
    {
        return new Circle();
    }
};

class SquareFactory:public ShapeFactory
{
public:
    Shape* createShape()override
    {
        return new Square();
    }
};

class RingFactory:public ShapeFactory
{
public:
    Shape* createShape()
    {
        return new Ring();
    }
};

int main()
{
    ShapeFactory *cf = new CircleFactory();
    ShapeFactory *sf = new SquareFactory();
    Ring r;
    
    Shape *c = cf->createShape();
    Shape *s = sf->createShape();
    
    c->draw();
    s->draw();
    
    
    
    
    
    return 0;
}













