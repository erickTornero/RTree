#include <iostream>
#include <vector>
class Point{
    int X;
    int Y;
    public:
    Point(int x, int y): X(x), Y(y){};
    friend class Poligon;
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
};
//For the moment each poligon will be a single rectangle as well as and each Bounding box too
class Poligon{
    Point Pmin;
    Point Pmax;
    public:
    Poligon(Point min, Point max):Pmin(min), Pmax(max){};
    friend class RTree;
    friend class RTree_node;
    bool is_Within_from(const Poligon & pol){
        if(this->Pmin >= pol.Pmin && this->Pmax <= pol.Pmax)
            return true;
        else
            return false;
    }
    bool intersect_BB_of(const Poligon & pol){
        if(this->Pmin <= pol.Pmax && this->Pmin >= pol.Pmin){
            return true;
        }
        if(this->Pmax <= pol.Pmax && this-> Pmax >= pol.Pmin){
            return true;
        }
        Point myPoint_leftUP(this->Pmin.X,this->Pmax.Y);
        Point myPoint_right_L(this->Pmax.X, this->Pmin.Y);
        Point BB_point_leftUP(Pmin.X,Pmax.Y);
        Point BB_point_right_L(Pmax.X, Pmin.Y);
        if(myPoint_leftUP <= BB_point_leftUP && myPoint_leftUP >= BB_point_right_L){
            return true;
        }
        if(myPoint_right_L <= BB_point_leftUP && myPoint_right_L >= BB_point_right_L){
            return true;
        }
        return false;
    }
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
    friend class RTree;
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

    void search(RTree_node * node, Poligon & region, std::vector<Poligon * > & ans){
        if(!node->is_leaf){
            for(int i = 0; i < node->elements; i++){
                if(region.intersect_BB_of(*node->Poligons[i])){
                    search(node->children_pointer[i],region,ans);
                }
            }
        }
        else{
            for(int i = 0; i <  node->elements; i++){
                if(region.is_Within_from(*node->Poligons[i])){
                    ans.push_back(node->Poligons[i]);
                }
            }
        }
    }
};
