#include <iostream>
#include <vector>
class Point{
    int X;
    int Y;
    public:
    Point(int x, int y): X(x), Y(y){};
    friend class Poligon;
};
//For the moment each poligon will be a single rectangle as well as and each Bounding box too
class Poligon{
    Point Pmin;
    Point Pmax;
    public:
    Poligon(Point min, Point max):Pmin(min), Pmax(max){};
    friend class RTree;
};
class RTree_node
{
    int M;
    int m;
    int elements;
    bool is_leaf;
    std::vector< Poligon * > Poligons;
    std::vector< RTree_node * > children_pointer;
    public:
    RTree_node(bool leaf, int M_sz):is_leaf(leaf), M(M_sz),elements(0), m((M_sz+1)/2){
        if(is_leaf){
            Poligons.resize(M+1); 
        }
        else{
            children_pointer.resize(2*m);
        }
    }
};

class RTree
{
    RTree_node *root;

    public:
    RTree(int M){
        root = nullptr;
    }
    bool insert(Poligon p){

    }
};
