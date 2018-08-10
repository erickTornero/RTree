#ifndef __RTREE
#define __RTREE

#include "Objects.hpp"

struct d_leaf{
    public: 
    Polygon * polygon;
    Polygon * region;
    d_leaf(Polygon *p = nullptr, Polygon * r = nullptr):polygon(p),region(r){};
};
struct d_internal_node{
    public:
    Polygon * region;
    RTree_node * child;
    d_internal_node(Polygon *r = nullptr, RTree_node * c = nullptr):region(r),child(c){};
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
#endif