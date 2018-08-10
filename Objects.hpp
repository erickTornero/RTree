#ifndef __OBJECTS
#define __OBJECTS

#include <vector>
class Point{
    private:
    //2D - Coordinates of Point.  
    int X;
    int Y;

    public:
    //Define a constructor.
    Point(int x = 0, int y = 0): X(x), Y(y){};
    //Overload of operators:
    //A point is equal or less than other if its 'X' value and it 'Y' value
    //are equal or less than the 'X' and 'Y' value of the other Point.
    bool operator>=(const Point& p){
          if(this->X >= p.X && this->Y >=p.Y)
            return true;
          else
            return false;
    }
    //A point is equal or greater than other if its 'X' value and it 'Y' value
    //are equal or greater than the 'X' and 'Y' value of the other Point.
    bool operator<=(const Point& p){
          if(this->X <= p.X && this->Y <= p.Y)
            return true;
          else
            return false;
    }
    //setter & getter functions:
    int get_X(){return this->X;}
    int get_Y(){return this->Y;}
    void set_X(int x){this->X = x;}
    void set_X(int y){this->Y = y;}
    void set_X(int x, int y){
        this->X = x;
        this->Y = y;
    }
};

class Polygon{
    private: 
    //MBB of the Polygon is represented 
    //by its minimum Point & maximun Point
    Point Pmin;
    Point Pmax;
    int key;
    //Colection of Points that represent all vertices
    std::vector<Point> vertices;
    void set_mbb();
    public:
    //Initialize the Vertices of Polygon
    Polygon(std::vector<Point> p, int k):vertices(p), key(k){set_mbb();}
    //It represent a rectangle region.
    Polygon(Point pmin, Point pmax):Pmin(pmin),Pmax(pmax){};

};
#endif