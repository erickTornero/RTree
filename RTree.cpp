#include "RTree.hpp"
/*
    Choose origin when split occurs
*/
void RTree_node::choose_origin(int & a, int & b){
    int i = 0;
    int d = std::numeric_limits<int>::min();
    //Cuadratic choose.
    while(i < elements -1){
        for(int j = i+1; j < elements; j++){
            int costo = this->data_leafs[i].region->cost_two_poligons(*this->data_leafs[j].region);
            if( costo > d){
                a = i;
                b = j;
                d = costo;
            }
        }
        i++;
    }
}
Polygon RTree_node::mbb_node(const std::vector<Polygon *> & reg){
    int x_min = std::numeric_limits<int>::max(); 
    int x_max = std::numeric_limits<int>::min();
    int y_min = x_min, y_max = x_max;
    for( int i = 0; i < this->elements; i++){
        if(reg[i]->get_Pmin().get_X() < x_min){
            x_min = reg[i]->get_Pmin().get_X();
        }
        if(reg[i]->get_Pmin().get_Y() < y_min){
            y_min = reg[i]->get_Pmin().get_Y();
        }
            
        if(reg[i]->get_Pmax().get_X() > x_max){
            x_max = reg[i]->get_Pmax().get_X();
        }
        if(reg[i]->get_Pmax().get_Y() > y_max){
            y_max = reg[i]->get_Pmax().get_Y();
        }
    }
    return Polygon(Point(x_min,y_min),Point(x_max,y_max));    
}

bool RTree::insert_polygon(RTree_node * node, d_leaf data){
    //If there isn't any node, create one
    if(root == nullptr){
        this->root = new RTree_node(true, this->M);
        node = root;
    }
    if(!node->is_leaf){

    }
    else{
        //There's space in the leaf?
        if(node->elements < node->M){
            node->data_leafs[node->elements];
            node->elements++;
            adjust_tree(node);
        }
        else{
            node->data_leafs[node->elements];
            node->elements++;
            cuadratic_split(node);
        }
    }
}
void RTree::cuadratic_split(RTree_node * node){
    int i, j;
    node->choose_origin(i,j);
    if(node->father == nullptr){
        node->father = new RTree_node(false,this->M);
        insert_internal_region(node->father, d_internal_node(node->data_leafs[i].region, node));
        this->root = node->father;
    }
    else{
        //father region must be equal to the node region 'i'
        for(int m = 0; m < node->father->elements; m++){
            if(node->father->data_internal_node[m].child == node){
                node->father->data_internal_node[m].region = node->data_leafs[i].region;
            }
        }
    }
    RTree_node * brother = new RTree_node(true, this->M, node->father);
    insert_internal_region(brother->father, d_internal_node(node->data_leafs[j].region,brother));
    std::vector<d_leaf> tmp;
    for(int n = 0; n < node->elements; n++){
        if(n != i && n != j){
            tmp.push_back(node->data_leafs[n]);
        }
    }
    insert_polygon(brother, node->data_leafs[j]);
    //Clear the node, just with its 'i' index data
    node->data_leafs[0] = node->data_leafs[i];
    for(int m = 1; m < node->elements; m++){
        node->data_leafs[m].set_data(nullptr,nullptr);
    }
    node->elements = 1;

    distribute_polygons(node, brother,tmp);

}
bool RTree::insert_internal_region(RTree_node * node, d_internal_node data ){
    data.region = new Polygon(data.region->get_Pmin,data.region->get_Pmax);    
    node->data_internal_node[node->elements] = data;
    node->elements++;
}

void RTree::distribute_polygons(RTree_node * node, RTree_node * brother, const std::vector<d_leaf> & data){
    int i, j ;
    //Search where is the node & brother in the father.
    for(int a = 0; a < node->father->elements; a++){
        if(node->father->data_internal_node[a].child == node){
            i = a;
        }
        else if(node->father->data_internal_node[a].child == brother){
            j = a;
        }
    }
    for(int m = 0; m < data.size(); m++){
        int cost_node = node->father->data_internal_node[i].region->cost_two_poligons(*data[m].region);
        int cost_brother = brother->father->data_internal_node[j].region->cost_two_poligons(*data[m].region);
        if(cost_node < cost_brother && node->elements < this->M - this->m + 1){
            insert_polygon(node, data[m]);
        }
        else if(cost_node > cost_node && brother->elements < this->M - this->m + 1){
            insert_polygon(brother, data[m]);
        }
        else{
            if(node->elements < this->M - this->m + 1){
                insert_polygon(node, data[m]);
            }
            else{
                insert_polygon(brother, data[m]);
            }
        }
    }
}
void RTree::adjust_tree(RTree_node * node){
    if(node == this->root){
        return;
    }
    else{
        if(node->father != nullptr){
            
        }
    }
}