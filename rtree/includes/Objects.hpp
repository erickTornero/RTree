#ifndef __OBJECTS
#define __OBJECTS

#include <vector>
#include <limits>
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
    void set_Y(int y){this->Y = y;}
    void set_X_Y(int x, int y){
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
    void area_added(Polygon &, Point & , Point & );
    
    public:
    int corners;
    //Initialize the Vertices of Polygon
    Polygon(std::vector<Point> ) ;
    //It represent a rectangle region.
    Polygon(Point pmin, Point pmax):Pmin(pmin),Pmax(pmax), corners(4), key(-1){};
    //Generic Polygon, a point is Polygon
    Polygon(Point);
    //Cost of add a polygon.
    int cost_two_poligons(Polygon & );
    Point get_Pmax(){return Pmax;}
    Point get_Pmin(){return Pmin;}
    void set_Polygon(Point min, Point max){this->Pmin = min; this->Pmax = max;}
    bool intersect_with_BB(Polygon &);
    bool traberse_with(Polygon &);
    bool is_Within_of(const Polygon &);
    Polygon get_mbb();
    //To get KNN query- Geometric distance.
    //template <class >
    float distance_geometric(Point );
    //
    //template <class T>
    float max_distance_geometric(Point );

    std::vector<Point> get_vertices();
    bool set_key(int );
    int get_key(){return this->key;}

    ~Polygon();
};
#endif