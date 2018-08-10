#ifndef __RTREE
#define __RTREE

#include "Objects.hpp"

struct d_leaf{
    public: 
    Polygon * polygon;
    Polygon * region;
    d_leaf(Polygon *p = nullptr, Polygon * r = nullptr):polygon(p),region(r){};
    void set_data(Polygon * p , Polygon * r ){polygon = p; region = r;}
};
struct d_internal_node{
    public:
    Polygon * region;
    RTree_node * child;
    d_internal_node(Polygon *r = nullptr, RTree_node * c = nullptr):region(r),child(c){};
    void set_data(Polygon * r, RTree_node * c){region = r; child = c;}
};
class RTree_node{
    private: 
    int elements;
    bool is_leaf;
    RTree_node * father;
    std::vector<d_leaf> data_leafs;
    std::vector<d_internal_node> data_internal_node;

    //choose the first nodes in cuadratic split
    void choose_origin(int & , int &);
    //Get the MBB of the node.
    Polygon mbb_node();
    public:
    RTree_node(bool _l, RTree_node * f = nullptr):is_leaf(_l), elements(0), father(f){};
};

class RTree{
    private:
    RTree_node * root;
    int M;
    //Insert Polygon internaly
    bool insert_polygon(RTree_node *, Polygon *, Polygon *);
    //Insert element in an internal node.
    bool insert_internal_region(RTree_node *, d_internal_node data );
    //Distribute polygons on leaf:
    void distribute_polygons(RTree_node * , RTree_node * , d_leaf);
    //Distribute regions on internal nodes:
    void distribute_regions(RTree_node *, RTree_node *, d_internal_node);
    //Cuadratic split on leafs:
    void cuadratic_split(RTree_node *);
    //Cuadratic split on internal nodes:
    void cuadratic_split_internal_nodes(RTree_node *);
    //Select the leaf where the new Polygon try to be inserted
    RTree_node * select_leaf(RTree_node * node, Polygon * );
    //Adjust the tree after of insert a polygon
    void adjust_tree(RTree_node * );

    public:
    RTree(int _M): M(_M), root(nullptr){};
    void range_search(RTree_node * , const Polygon & , std::vector<Polygon *> &);
    //Insert Polygon in Front-end
    bool insert_polygon(Polygon * , Polygon *);
    //get the k-nearest neighbor Polygons.
    void k_NN_DF(Point q, int k, RTree_node *);
};
#endif