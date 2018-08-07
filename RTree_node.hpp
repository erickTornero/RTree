#include <iostream>
#include <vector>
#include <limits>
class Point{
    int X;
    int Y;
    public:
    Point(int x = 0, int y = 0): X(x), Y(y){};
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
//Poligon must be redefined!!. not as Point Max or Point min.
class Poligon{
    Point Pmin;
    Point Pmax;
    public:
    //TODO: When a poligon is created, automaticaly Pmin, and Pmax must be calculated.
    // ... then the region can be returned easily
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
    int area_added(const Poligon & reg, Point & pmin, Point & pmax){
        int x_max = this->Pmax.X;
        if(reg.Pmax.X > x_max){
            x_max = reg.Pmax.X;
        }
        int x_min = this->Pmin.X;
        if(reg.Pmin.X < x_min){
            x_min = reg.Pmin.X;
        }

        int y_max = this->Pmax.Y;
        if(reg.Pmax.Y > y_max){
            y_max = reg.Pmax.Y;
        }
        int y_min = this->Pmin.Y;
        if(reg.Pmin.Y < y_min){
            y_min = reg.Pmin.Y;
        }
        //This points max and minimung will welp to calculate the region of parents
        pmin = Point(x_min,y_min);
        pmax = Point(x_max,y_max);
        return (x_max-x_min)*(y_max-y_min);
    }
    int cost_two_poligons(const Poligon & reg, Point & p1, Point & p2){
        //Point p1 garbage, must be optimized, maybe by a pointer instead reference
        int d = area_added(reg,p1,p2);
        d -= (reg.Pmax.X - reg.Pmin.X)*(reg.Pmax.Y - reg.Pmin.Y);
        d -= (this->Pmax.X - this->Pmin.X)*(this->Pmax.Y - this->Pmin.Y);
        return d;
    }
    //Must be implemented when poligons will be more than single rectangles.
    static Poligon * get_mbb_single_poligon(const Poligon & pol){
        
    }

};

class RTree_node
{
    int M;
    int m;
    int elements;
    bool is_leaf;
    std::vector< Poligon * > Poligons;
    std::vector< Poligon * > Region;

    std::vector< RTree_node * > children_pointer;
    public:
    RTree_node(bool leaf, int M_sz):is_leaf(leaf), M(M_sz),elements(0), m((M_sz+1)/2){
        if(is_leaf){
            Poligons.resize(M+1);
            Region.resize(M+1); 
        }
        else{
            Region.resize(M+1);
            children_pointer.resize(2*m);
        }
    }
    //Get indexes of regions that ocupes maximun area,
    //This two chooses will be the first elements of partition in #Cuadratic - Split
    void choose_origin(int & a, int & b){
        int i = 0;
        int d = std::numeric_limits<int>::min();
        Point x,y; //Garbage
        //Cuadratic choose.
        while(i < elements -1){
            for(int j = i+1; j < elements; j++){
                int costo = Region[i]->cost_two_poligons(*Region[j], x, y);
                if( costo > d){
                    a = i;
                    b = j;
                    d = costo;
                }
            }
            i++;
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
    //This functions was probed successfully when elements are in the root
    void search(RTree_node * node, Poligon & query, std::vector<Poligon * > & ans){
        if(!node->is_leaf){
            for(int i = 0; i < node->elements; i++){
                //Order of call function must be analized then, maybe it's equal.
                if(query.intersect_BB_of(*node->Region[i])){
                    search(node->children_pointer[i],query,ans);
                }
            }
        }
        else{
            for(int i = 0; i <  node->elements; i++){
                if(node->Region[i]->is_Within_from(query)){
                    ans.push_back(node->Poligons[i]);
                }
            }
        }
    }
    //Mbb must be obtained, however for the moment, sinple rectangles are used, 
    //so the Poligon is the same of its MBB. Another parameter is needed
    //or a struct could be used instead.
    bool insert_poligon(RTree_node *node, Poligon *pol, Poligon *region){
        if(root == nullptr){
            this->root = new RTree_node(true, this->M);
            node = root;
        }
        if(!node->is_leaf){

        }
        //If the node is a leaf.
        else{
            //If there is space in the leaf.
            if(node->elements < node->M){
                node->Poligons[node->elements] = pol;
                node->Region[node->elements] = region;
                //TODO: Maybe The MBB of object is missing
                node->elements++;
            }
            //If there isn't space on the current Leaf!
            else{
                //Add the element that overflows the node, there's an space for this.
                node->Poligons[node->elements] = pol;
                node->Region[node->elements] = region;
                node->elements++;
                //Split the leaf into two leafs.
                cuadratic_split(node);
            }
        }
    }
    //Insert elements on internal nodes, its a bit diferent when insert poligons.
    bool insert_internal_region(RTree_node * node, RTree_node * child_node, Poligon * region){
        if(node->elements <= node->M){
            node->Region[node->elements] = new Poligon(region->Pmin, region->Pmax);
            node->children_pointer[node->elements] = child_node;
            node->elements++;
        }
        else{

        }
    }
    void distribute_poligons(RTree_node * parent, RTree_node * brother, RTree_node * node, std::vector<Poligon * > split_pol, std::vector<Poligon * > split_reg){
        int i, j;
        //Choose in which index is the node & the brother
        for(int a = 0; a < parent->elements; a++){
            if(parent->children_pointer[a] == node){
                i = a;
            }
            else if(parent->children_pointer[a] == brother){
                j = a;
            }
        }
        for(int m = 0; m < split_reg.size(); m++){
            Point p_min(0,0);
            Point p_max(0,0);
            Point pb_min(0,0);
            Point pb_max(0,0);
            int cost_node = parent->Region[i]->cost_two_poligons(*split_reg[m], p_min, p_max);
            int cost_brother = parent->Region[j]->cost_two_poligons(*split_reg[m], pb_min, pb_max);
            if(cost_node < cost_brother && node->elements <= node->m){
                insert_poligon(node,split_pol[m],split_reg[m]);
                parent->Region[i]->Pmin = p_min;
                parent->Region[i]->Pmax = p_max;
            }
            else if(cost_node > cost_brother && brother->elements <= brother->m){
                insert_poligon(brother,split_pol[m],split_reg[m]);
                parent->Region[j]->Pmin = pb_min;
                parent->Region[j]->Pmax = pb_max;
            }
            else{
                //If any of the nodes is full fill, then fill the other
                if(node->elements < node->m){
                    insert_poligon(node,split_pol[m],split_reg[m]);

                    parent->Region[i]->Pmin = p_min;
                    parent->Region[i]->Pmax = p_max;
                }
                else{
                    insert_poligon(brother,split_pol[m],split_reg[m]);
                    parent->Region[j]->Pmin = pb_min;
                    parent->Region[j]->Pmax = pb_max;
                }
            }
        }

    }
    //Cuadratic split of a Leaf!.
    void cuadratic_split(RTree_node * node){
        //Brother node, also is a leaf node!
        RTree_node * brother = new RTree_node(true, this->M);
        //Parent node, it isn't a leaf node!.
        //TODO: node parent is created, considering that it not exist. When exists is missing
        RTree_node * parent = new RTree_node(false, this->M);
        //be care with this.
        root = parent;
        int i, j;
        // brother will correspond to the j index
        node->choose_origin(i,j);
        insert_internal_region(parent, node, node->Region[i]);
        insert_internal_region(parent, brother, node->Region[j]);
        //Be care with the following.
        //Clear the node to make the partition using temporal variables.
        /////////////////////Prepare for distribution/////////////////////////
        std::vector<Poligon * > tmp_pol;
        std::vector<Poligon * > tmp_reg;

        for(int n = 0; n < node->elements; n++){
            if(n != i && n != j){
                tmp_pol.push_back(node->Poligons[n]);
                tmp_reg.push_back(node->Region[n]);
            }
        }
        Poligon * tmp_p = node->Poligons[i];
        Poligon * tmp_r = node->Region[i];

        insert_poligon(brother,node->Poligons[j],node->Region[j]);

        for(int m = 0; m < node->elements; m++){
            node->Poligons[m] = nullptr;
            node->Region[m] = nullptr;
        }
        node->elements = 0;

        insert_poligon(node, tmp_p, tmp_r);
        /////////////////End - Prepare for distribution//////////////////////////////////////

        distribute_poligons(parent, brother, node, tmp_pol,tmp_reg);
    }
};
