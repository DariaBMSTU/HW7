#include <iostream>

using namespace std;

class Vector{
    private:
        double x, y, z;

    public:
        Vector(){x=y=z=0.0;}; // конструктор по умолчанию
        Vector(double x1, double y1, double z1){x=x1; y=y1; z=z1;} // конструктор с параметрами
        ~Vector(){;}

        Vector operator=(const Vector &vec); // присваивание
        Vector operator+(const Vector &vec); // сложение векторов
        Vector operator-(const Vector &vec); // вычитание векторов

        friend Vector operator*(const Vector &vec, const double val); // умножение вектора на число
        friend Vector operator*(double val, const Vector &vec);
        double operator*(const Vector &vec); // скалярное произведение векторов

        Vector operator/(const Vector &vec);

        Vector operator++(); // перегрузка префиксного инкремента
        Vector operator++(int notused); // перегрузка постфиксного инкремента

        Vector operator--(); // перегрузка префиксного декремента
        Vector operator--(int notused); // перегрузка постфиксного декремента

        double operator[](char coord); //перегрузка индексирования

        friend ostream &operator<<(ostream &stream, const Vector &vec);
        friend void ortho_check(Vector *vecs);// проверка векторов на ортогональность
        friend void complan_check(Vector *vecs); // проверка на компланарность
};

Vector Vector::operator=(const Vector &vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this; // возврат модифицированного объекта
}


Vector Vector::operator+(const Vector &vec)
{
    Vector tmp;

    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    tmp.z = z + vec.z;
    return tmp;
}

Vector Vector::operator-(const Vector &vec)
{
    Vector tmp;

    tmp.x = x - vec.x;
    tmp.y = y - vec.y;
    tmp.z = z - vec.z;
    return tmp;
}

Vector operator*(const Vector &vec, const double val)
{
    Vector tmp;
    tmp.x =vec.x * val;
    tmp.y =vec.y * val;
    tmp.z =vec.z * val;
    return tmp;
}

Vector operator*(const double val, const Vector &vec)
{
    Vector tmp;
    tmp.x =val * vec.x ;
    tmp.y =val * vec.y;
    tmp.z =val * vec.z;
    return tmp;
}

double Vector::operator*(const Vector &vec)
{
    return x*vec.x+y*vec.y+z*vec.z;
}

Vector Vector::operator/(const Vector &vec)
{
    Vector tmp;
    tmp.x=x/vec.x;
    tmp.y=y/vec.y;
    tmp.z=z/vec.z;
    return tmp;
}

Vector Vector::operator++()
{
    x++;
    y++;
    z++;
    return *this; // Возврат инкрементированного объекта
}

Vector Vector::operator++(int notused)
{
    Vector tmp = *this; // сохраним исходное значение

    x++;
    y++;
    z++;
    return tmp; // вернем исходное значение
}

Vector Vector::operator--()
{
    x--;
    y--;
    z--;
    return *this; // Возврат декрементированного объекта
}

Vector Vector::operator--(int notused)
{
    Vector tmp = *this; // сохраним исходное значение

    x--;
    y--;
    z--;
    return tmp; // вернем исходное значение
}

double Vector::operator[](char coord)
{
    switch (coord)
    {
        case 'x': return x; break;
        case 'y': return y; break;
        case 'z': return z; break;
        default: return x;
    }
}

ostream &operator<<(ostream &stream, const Vector &vec)
{
    stream<<"("<<vec.x<<", ";
    stream<<vec.y<<", ";
    stream<<vec.z<<")";
    return stream;
}

void ortho_check(Vector *vecs)
{
    if(vecs[0]*vecs[1]==0)
        cout<<"Вектора ортогональны"<<endl;
    else
        cout<<"Вектора не ортогональны"<<endl;

}

void complan_check(Vector *vecs)
{
    if (vecs[1]['x']!=0 && vecs[1]['y']!=0 && vecs[1]['z']!=0)//знаменатель не равен 0
    {
        if ((vecs[0]['x']/vecs[1]['x']==vecs[0]['y']/vecs[1]['y']) && (vecs[0]['y']/vecs[1]['y']==vecs[0]['z']/vecs[1]['z']))
            cout<<"Вектора коллинеарны"<<endl;
        else
            cout<<"Вектора не коллинеарны"<<endl;
    }
    else if(vecs[0]['x']==0 && vecs[0]['y']==0 && vecs[0]['z']==0) //нулевой вектор колинеарен всем векторам
        cout<<"Вектора коллинеарны"<<endl;
    else
        cout<<"Вектора не коллинеарны"<<endl;


}

int main()
{
    cout << "Hello world!" << endl;
    Vector a(1.0,2.0,3.0), b(10.0,10.0,10.0), c;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;

    cout<<"\n";

    c=a+b;
    cout<<"a + b = "<<c<<endl;
    c=a-b;
    cout<<"a - b = "<<c<<endl;

    cout<<"\n";

    c=2.0*a;
    cout<<"2*a = "<<c<<endl;
    c=b*3.0;
    cout<<"b*3 = "<<c<<endl;
    cout<<"a*b = "<<a*b<<endl;

    cout<<"\n";

    char crd='y';
    cout<<"a[y] = "<<a[crd]<<endl;

    cout<<"\n";

    cout<<"++a = "<<++a<<endl;
    cout<<"a++ = "<<a++<<endl; //ничего не прибавляется
    cout<<"a = "<<a<<endl; // значение увеличилось

    cout<<"\n";

    cout<<"--b = "<<--b<<endl;
    cout<<"b-- = "<<b--<<endl; //ничего не вычитается
    cout<<"b = "<<b<<endl; // значение уменьшилось

    cout<<"\n";

    //Массив объектов
    Vector vecs[]= {Vector(1.0, 2.0, 3.0), Vector(2.0, 4.0, 6.0)}; //коллинеарные вектора. a=n*b
    Vector vecs1[]= {Vector(0.0, 2.0, 0.0), Vector(2.0, 0.0, 6.0)}; //ортогональные вектора. скал произ-е=0

    cout<<"vecs[]= ";
    for (int i=0; i<2; i++)
    {
        cout<<vecs[i]<<" ";
    }
    cout<<"\n";
    complan_check(vecs);
    ortho_check(vecs);

    cout<<"vecs1[]= ";
    for (int i=0; i<2; i++)
    {
        cout<<vecs1[i]<<" ";
    }
    cout<<"\n";
    complan_check(vecs1);
    ortho_check(vecs1);


    return 0;
}
