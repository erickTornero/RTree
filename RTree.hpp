#ifndef __RTREE
#define __RTREE

#include "Objects.hpp"
#include <string>
struct d_leaf{
    public: 
    Polygon * polygon;
    Polygon * region;
    d_leaf(Polygon *p = nullptr, Polygon * r = nullptr):polygon(p),region(r){};
    void set_data(Polygon * p , Polygon * r ){polygon = p; region = r;}
};
struct d_internal_node;

class RTree_node{
    private:
    int M;
    int elements;
    bool is_leaf;
    int at_level;
    RTree_node * father;
    std::vector<d_leaf> data_leafs;
    std::vector<d_internal_node> data_internal_node;

    //choose the first nodes in cuadratic split
    void choose_origin(int & , int & );
    //Get the MBB of the node.
    Polygon mbb_node();
    public:
    int get_level(){return at_level;}
    RTree_node(bool _l, int _M, int _lvl, RTree_node * f);
    ~RTree_node();
    friend class RTree;
};
struct d_internal_node{
    public:
    Polygon * region;
    RTree_node * child;
    d_internal_node(Polygon *r = nullptr, RTree_node * c = nullptr):region(r),child(c){};
    void set_data(Polygon * r, RTree_node * c){region = r; child = c;}
};
struct data_query_return{
    public:
    Polygon * Pol;
    int lvl;
    data_query_return(Polygon *p, int _lvl):Pol(p),lvl(_lvl){};
};
class RTree{
    private:
    RTree_node * root;
    int M;
    int m;
    int H; //Height of tree
    int indx;
    //Insert Polygon internaly
    RTree_node * insert_polygon(RTree_node *, d_leaf);
    //general function to insert
    bool insert(RTree_node *&, d_leaf);
    //Insert element in an internal node.
    bool insert_internal_region(RTree_node *, d_internal_node  );
    //Distribute polygons on leaf:
    void distribute_polygons(RTree_node * , RTree_node * , const std::vector<d_leaf> &);
    //Distribute regions on internal nodes:
    void distribute_regions(RTree_node *, RTree_node *, const std::vector<d_internal_node> &);
    //Cuadratic split on leafs:
    RTree_node * cuadratic_split(RTree_node *);
    //Cuadratic split on internal nodes:
    RTree_node *  cuadratic_split_internal_nodes(RTree_node *);
    //Select the leaf where the new Polygon try to be inserted
    RTree_node * select_leaf(RTree_node * node, Polygon * );
    //Adjust the tree after of insert a polygon
    void adjust_tree(RTree_node *, RTree_node * );
    //Recursive Range Search.
    void range_search_recursive(RTree_node * , Polygon & , std::vector<Polygon *> &);

    //Mothods to get KNN

    void DFT_recursive(Point , int , RTree_node * , std::vector<d_leaf *> & , std::vector<float> & ,float & );
    //insert sort
    template <class T>
    void insert_sort(std::vector<float> & , std::vector<T*> & );
    public:
    RTree(int _M): M(_M), m((_M+1)/2),root(nullptr), H(0), indx(0){};
    
    //Insert Polygon in Front-end
    bool insert_polygon(Polygon * , Polygon *);
    //Range search in Front
    void range_search(Polygon , std::vector<Polygon *> &);
    
    
    //get the k-nearest neighbor Polygons.
    void k_NN_DF(Point q, int k, std::vector<d_leaf*> &L);

    std::string show_values_JSON();

    void showAll_values_JSON(RTree_node *father, int level, std::string &);

    void get_polygons_JSON(const std::vector<d_leaf*> &, std::string &);

    void get_Range_Search_JSON(const std::vector<Polygon *> &, std::string &);
    ~RTree();
};

#endif