#include <iostream>
#include <cmath>

struct Point
{
    Point()
    : x(0), y(0)
    {
    }
    Point(int x, int y)
    : x(x), y(y)
    {
    }
    int x, y;
};

// недостаток оператора <: он может быть только один
bool operator<(const Point &l, const Point &r)
{
    return l.x > r.x;
}

bool pointXLessComparator(const Point &l, const Point &r)
{
    return l.x < r.x;
}

bool pointYLessComparator(const Point &l, const Point &r)
{
    return l.y < r.y;
}

std::istream& operator>>(std::istream &in, Point &point)
{
    in >> point.x >> point.y;
    return in;
}

std::ostream& operator<<(std::ostream &out, const Point &point)
{
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

template <typename T>
bool defaultLess(const T &l, const T &r)
{
    return l < r;
}

// Компаратор, сравнивающий две точки по их близости к точке p0
class PointComparator
{
public:
    PointComparator()
    {
    }
    PointComparator(const Point &p0)
    : p0(p0)
    {
    }
    
    // оператор () позволяет вызывать объекты данного класса как функцию
    bool operator()(const Point &l, const Point &r)
    {
        auto distance1 = std::sqrt((p0.x - l.x)*(p0.x - l.x) + (p0.y - l.y)*(p0.y - l.y));
        auto distance2 = std::sqrt((p0.x - r.x)*(p0.x - r.x) + (p0.y - r.y)*(p0.y - r.y));
        return distance1 < distance2;
    }
private:
    Point p0;
};

/*
// Как пробросить компаратор через шаблон
template <typename T, typename Comparator>
class Heap
{
public:
    Heap()
    : cmp(...) // инициализируем конструктор (если у него есть конструктор по умолчанию, можно опустить строчку)
    {
        
    }
private:
    void siftDown(...)
    {
        ...
        cmp(arr[i], arr[ch1])
        ...
    }
    Comparator cmp;
};
*/

// компаратор в виде указателя на функцию
// если не указать явно, по умолчанию будет использоваться defaultLess
template <typename T>
void mySort(T *arr, int l, int r, bool (*cmp)(const T &l, const T &r) = defaultLess)
{
    for (int i = l; i < r; i++)
    {
        for (int j = l; j < r; j++)
        {
            if (cmp(arr[j + 1], arr[j]))
            {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}


// теперь в качестве компаратора можно передавать что угодно, лишь бы это можно было вызвать при помощи ()
// если явно не передавать компаратор, то в качестве него будет использован объект типа std::less<T>
template <typename T, typename Comparator = std::less<T>>
void mySort2(T *arr, int l, int r, Comparator cmp = Comparator())
{
    for (int i = l; i < r; i++)
    {
        for (int j = l; j < r; j++)
        {
            if (cmp(arr[j + 1], arr[j]))
            {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int n = 0;
    std::cin >> n;
    Point *arr = new Point[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    
    //Point p0;
    //std::cin >> p0;
    
    // В шаблонных функциях не обязательно указывать шаблонные аргументы. Компилятор сам вычислит фактические типы T и Comparator на основе переданных аргументов. Но можно и явно указать.
    // Эти два вызова эквивалентны:
    // mySort2<Point, PointComparator>(arr, 0, n - 1);
    // mySort2(arr, 0, n - 1, PointComparator());
    
    // При создании объектов шаблонного класса обязательно нужно указывать все шаблонные типы, у которых не определен тип по умолчанию.
    
    mySort2(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] arr;
    return 0;
}
