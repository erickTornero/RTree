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
    //If a poligon is contained totally in a Rectangle.
    bool is_Within_from(const Poligon & pol){
        if(this->Pmin >= pol.Pmin && this->Pmax <= pol.Pmax)
            return true;
        else
            return false;
    }
    //If part or totaly of polygon intersect with a rectangle (Bonding box)
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
    //Must be implemented when poligons will be more than single rectangles.
    Poligon get_mbb_single_poligon(const Poligon & pol){

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
    public:
    RTree_node *root;
    int M;
    
    RTree(int M):M(M){
        root = nullptr;
    }
    //Basic search function, must be checked again, based on:
    //http://www.mathcs.emory.edu/~cheung/Courses/554/Syllabus/3-index/R-tree3.html
    //All Poligons that are contained in region are charged on 'ans' vector.
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
    //Mbb must be obtained, however for the moment, sinple rectangles are used, 
    //so the Poligon is the same of its MBB. Another parameter is needed
    //or a struct could be used instead.
    bool insert_poligon(RTree_node *node, Poligon *pol){
        if(root == nullptr){
            this->root = new RTree_node(true, this->M);
            node = root;
        }
        if(!node->is_leaf){

        }
        //If the node is a leaf.
        else{
            //If there is space in the leaf.
            if(node->elements <= node->M){
                node->Poligons[node->elements] = pol;
                //TODO: Maybe The MBB of object is missing
                node->elements++;
            }
            //If there isn't space on the current Leaf!
            else{
                //Split the leaf into two leafs.

            }
        }
    }
};
