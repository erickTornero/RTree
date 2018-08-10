#ifndef __OBJECTS
#define __OBJECTS
class Point{
    private:
    //2D - Coordinates of Point.  
    int X;
    int Y;

    public:
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
#endif