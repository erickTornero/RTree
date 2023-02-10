#include "RTree.hpp"
#include "iostream"
/*
    Choose origin when split occurs
*/
RTree_node::RTree_node(bool _l, int _M, int _lvl, RTree_node * f = nullptr):is_leaf(_l), M(_M), elements(0), father(f),at_level(_lvl){
    if(this->is_leaf){
        this->data_leafs.resize(M+1); 
    }
    else{
        this->data_internal_node.resize(M+1);
    }
}
void RTree_node::choose_origin(int & a, int & b){
    int i = 0;
    int d = std::numeric_limits<int>::min();
    //Cuadratic choose.
    while(i < elements -1){
        for(int j = i+1; j < elements; j++){
            if(this->is_leaf){
                int costo = this->data_leafs[i].region->cost_two_poligons(*this->data_leafs[j].region);
                if( costo > d){
                    a = i;
                    b = j;
                    d = costo;
                }
            }
            else{
                int costo = this->data_internal_node[i].region->cost_two_poligons(*this->data_internal_node[j].region);
                if( costo > d){
                    a = i;
                    b = j;
                    d = costo;
                }
            }
        }
        i++;
    }
}
Polygon RTree_node::mbb_node(){
    int x_min = std::numeric_limits<int>::max(); 
    int x_max = std::numeric_limits<int>::min();
    int y_min = x_min, y_max = x_max;
    if(this->is_leaf){
        for( int i = 0; i < this->elements; i++){
            if(this->data_leafs[i].region->get_Pmin().get_X() < x_min){
                x_min = this->data_leafs[i].region->get_Pmin().get_X();
            }
            if(this->data_leafs[i].region->get_Pmin().get_Y() < y_min){
                y_min = this->data_leafs[i].region->get_Pmin().get_Y();
            }
                
            if(this->data_leafs[i].region->get_Pmax().get_X() > x_max){
                x_max = this->data_leafs[i].region->get_Pmax().get_X();
            }
            if(this->data_leafs[i].region->get_Pmax().get_Y() > y_max){
                y_max = this->data_leafs[i].region->get_Pmax().get_Y();
            }
        }
    }
    else{
        for( int i = 0; i < this->elements; i++){
            if(this->data_internal_node[i].region->get_Pmin().get_X() < x_min){
                x_min = this->data_internal_node[i].region->get_Pmin().get_X();
            }
            if(this->data_internal_node[i].region->get_Pmin().get_Y() < y_min){
                y_min = this->data_internal_node[i].region->get_Pmin().get_Y();
            }
                
            if(this->data_internal_node[i].region->get_Pmax().get_X() > x_max){
                x_max = this->data_internal_node[i].region->get_Pmax().get_X();
            }
            if(this->data_internal_node[i].region->get_Pmax().get_Y() > y_max){
                y_max = this->data_internal_node[i].region->get_Pmax().get_Y();
            }
        }
    }
    
    return Polygon(Point(x_min,y_min),Point(x_max,y_max));    
}

RTree_node * RTree::insert_polygon(RTree_node * node, d_leaf data){
    //If there isn't any node, create one
    RTree_node * posible_Brother = nullptr;
        //There's space in the leaf?
    if(node->elements < node->M){
            if(data.polygon->set_key(this->indx))
                this->indx++;
            node->data_leafs[node->elements] = data;
            node->elements++;            
    }
    else{
        node->data_leafs[node->elements] = data;
        node->elements++;
        posible_Brother = cuadratic_split(node);
    }
    return posible_Brother;
}
bool RTree::insert(RTree_node *& node, d_leaf data){
    RTree_node * posible_Brother = nullptr;
    RTree_node * leaf_chose = nullptr;
    if(root == nullptr){
        this->root = new RTree_node(true, this->M, 0);
    }
    leaf_chose = select_leaf(this->root, data.region);
    posible_Brother = insert_polygon(leaf_chose, data);
    adjust_tree(leaf_chose,posible_Brother);
    if(this->root->elements > M ){
        RTree_node * internal_brother = nullptr;
        RTree_node * node = this->root; 
        internal_brother = cuadratic_split_internal_nodes(this->root);
        adjust_tree(node, internal_brother);
        this->H++;
    }
    return true;
}

RTree_node * RTree::cuadratic_split(RTree_node * node){
    int i, j;
    node->choose_origin(i,j);
    if(node->father == nullptr){
        node->father = new RTree_node(false,this->M, H+1);
        //Just insert elements.
        insert_internal_region(node->father, d_internal_node(node->data_leafs[i].region, node));
        this->root = node->father;
        this->H++;
    }
    else{
        //father region must be equal to the node region 'i'
        for(int m = 0; m < node->father->elements; m++){
            if(node->father->data_internal_node[m].child == node){
                *node->father->data_internal_node[m].region = *node->data_leafs[i].region;
            }
        }
    }
    RTree_node * brother = new RTree_node(true, this->M, node->at_level, node->father);
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
    return brother;
}
RTree_node *  RTree::cuadratic_split_internal_nodes(RTree_node * node){
    int i, j;
    node->choose_origin(i,j);
    if(node->father == nullptr){
        node->father = new RTree_node(false,this->M, H+1);
        insert_internal_region(node->father, d_internal_node(node->data_internal_node[i].region, node));
        this->root = node->father;
    }
    else{
        //father region must be equal to the node region 'i'
        for(int m = 0; m < node->father->elements; m++){
            if(node->father->data_internal_node[m].child == node){
                *node->father->data_internal_node[m].region = *node->data_internal_node[i].region;
            }
        }
    }
    RTree_node * brother = new RTree_node(false, this->M, node->at_level, node->father);
    insert_internal_region(brother->father, d_internal_node(node->data_internal_node[j].region,brother));
    std::vector<d_internal_node> tmp;
    for(int n = 0; n < node->elements; n++){
        if(n != i && n != j){
            tmp.push_back(node->data_internal_node[n]);
        }
    }
    node->data_internal_node[j].child->father = brother;
    insert_internal_region(brother, node->data_internal_node[j]);
    node->data_internal_node[0] = node->data_internal_node[i];
    for(int m = 1; m < node->elements; m++){
        node->data_internal_node[m].set_data(nullptr,nullptr);
    }
    node->elements = 1;

    distribute_regions(node, brother, tmp);
    return brother;
}
bool RTree::insert_internal_region(RTree_node * node, d_internal_node data ){
    Polygon * reg = new Polygon(data.region->get_Pmin(),data.region->get_Pmax());
    if(reg->set_key(this->indx))
        this->indx++;
    data.region = reg;    
    node->data_internal_node[node->elements] = data;
    node->elements++;
    return true;
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
        else if(cost_node > cost_brother && brother->elements < this->M - this->m + 1){
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
void RTree::distribute_regions(RTree_node * node, RTree_node *brother, const std::vector<d_internal_node> &data){
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
            insert_internal_region(node, data[m]);
            
        }
        else if(cost_node > cost_brother && brother->elements < this->M - this->m + 1){
            data[m].child->father = brother;
            insert_internal_region(brother, data[m]);
        }
        else{
            if(node->elements < this->M - this->m + 1){
                insert_internal_region(node, data[m]);
                
            }
            else{
                data[m].child->father = brother;
                insert_internal_region(brother, data[m]);
            
            }
        }
    }
}
void RTree::adjust_tree(RTree_node * node, RTree_node *brother){
 
    if(node->father != nullptr){
        for(int m = 0; m < node->father->elements; m++){
            if(node->father->data_internal_node[m].child == node){
                int key = node->father->data_internal_node[m].region->get_key();
                *node->father->data_internal_node[m].region = node->mbb_node();
                node->father->data_internal_node[m].region->set_key(key);
            }
            else if(node->father->data_internal_node[m].child == brother){
                int key = brother->father->data_internal_node[m].region->get_key();
                *brother->father->data_internal_node[m].region = brother->mbb_node();
                brother->father->data_internal_node[m].region->set_key(key);
            }
        }
        if(node->elements > this->M && !node->is_leaf){
                
            RTree_node * internal_brother = nullptr;
            internal_brother = cuadratic_split_internal_nodes(node);
            adjust_tree(node, internal_brother);
        }
        else{
            adjust_tree(node->father,nullptr);   
        }
            
    }
        
    //}
}

bool RTree::insert_polygon(Polygon * pol, Polygon * reg){
    RTree::insert(this->root, d_leaf(pol,reg));
    return true;
}
RTree_node * RTree::select_leaf(RTree_node * node, Polygon * p_region){
    if(node->is_leaf){
        return node;
    }
    else{
        int index_min;
        int min_cost = std::numeric_limits<int>::max();
        for(int i = 0; i < node->elements; i++){
            int child_cost = node->data_internal_node[i].region->cost_two_poligons(*p_region);
            if(child_cost < min_cost){
                min_cost = child_cost;
                index_min = i;
            }
        }
        return select_leaf(node->data_internal_node[index_min].child,p_region);
    } 
}

/*
    Range search.
    It returns all the path Regions & Polygons Pointers and its respective level.
    The level will help to draw the path query.
*/
void RTree::range_search_recursive(RTree_node * node, Polygon & query, std::vector<Polygon *> & ans){
    if(node != nullptr){
        if(!node->is_leaf){
            for(int i = 0; i < node->elements;i++){
                if(node->data_internal_node[i].region->intersect_with_BB(query) ){
                    //ans.push_back(data_query_return(node->data_internal_node[i].region,node->get_level()));
                    range_search_recursive(node->data_internal_node[i].child,query,ans);
                }
            }
        }
        else{
            for(int i = 0; i < node->elements; i++){
                if(node->data_leafs[i].region->is_Within_of(query)){
                    ans.push_back(node->data_leafs[i].polygon);
                }
            }
        }
    }
}
void RTree::range_search(Polygon query, std::vector<Polygon *> & ans){
    int x_min = query.get_Pmin().get_X();
    int y_min = query.get_Pmin().get_Y();
    if(query.get_Pmax().get_X() < x_min)
        x_min = query.get_Pmax().get_X();
    if(query.get_Pmax().get_Y() < y_min)
        y_min = query.get_Pmax().get_Y();
    int x_max = query.get_Pmin().get_X();
    int y_max = query.get_Pmin().get_Y();
    if(query.get_Pmax().get_X() > x_max)
        x_max = query.get_Pmax().get_X();
    if(query.get_Pmax().get_Y() > y_max)
        y_max = query.get_Pmax().get_Y();
    Polygon q(Point(x_min,y_min),Point(x_max,y_max));
    range_search_recursive(this->root, q, ans);
}

void RTree::DFT_recursive(Point q, int k, RTree_node * node, std::vector<d_leaf *> & L, std::vector<float> & ddk,float & poor){
	if(node->is_leaf){
        for(int i = 0; i < node->elements; i++){
            ddk.push_back(node->data_leafs[i].region->distance_geometric(q));
            L.push_back(&node->data_leafs[i]);
        }
        if(ddk.size()>k)
        {
	        insert_sort<d_leaf>(ddk,L);
            ddk.resize(k);
            L.resize(k);
        	poor=ddk[k-1];
        }
    }
    else{
	    std::vector<float> branch_value;
		std::vector<RTree_node *> branch;
        for(int i = 0; i < node->elements; i++){
	        branch_value.push_back(node->data_internal_node[i].region->distance_geometric(q));
            branch.push_back(node->data_internal_node[i].child);
        }
        insert_sort<RTree_node>(branch_value,branch);
		for(int i = 0; i < node->elements; i++){
  	        if(branch_value[i]<=poor){
                DFT_recursive(q,k,branch[i],L,ddk,poor);
            }
        }
      }
}
template <class T>
void RTree::insert_sort(std::vector<float> & dtmp, std::vector<T*> & chld){
    for(int i = 0;i < dtmp.size();i++){
		float cur_value = dtmp[i];
		T * cur_child = chld[i];
		int j = i -1;
		while(j>=0 && dtmp[j] > cur_value){
			dtmp[j+1]= dtmp[j];
			chld[j+1] = chld[j];
			j--;
		}
    	dtmp[j+1] = cur_value;
		chld[j+1] = cur_child;
	}
}

void RTree::k_NN_DF(Point q, int k, std::vector<d_leaf*> &L){
    std::vector<float> dk;
    float poor = std::numeric_limits<float>::max();
    
    if(this->root != nullptr)
        DFT_recursive(q, k, this->root,L,dk,poor);
}

std::string RTree::show_values_JSON()
{
    std::string json = "";

    if(this->root != nullptr)
        showAll_values_JSON(this->root, 0, json);
    if(json.length() != 0)
        json.erase(json.length()-1);
    return "["+json+"]";
}

void RTree::showAll_values_JSON(RTree_node *node, int level, std::string &json)
{
    if(!node->is_leaf)
    {
        for(int i=0; i<node->elements; i++)
        {
            
            json +="{";
            json += "\"level\":"+std::to_string(node->at_level)+",\n";
            json += "\"is_leaf\":"+std::to_string(0)+",\n";
            json += "\"key\":"+std::to_string(node->data_internal_node[i].region->get_key())+",\n";
            json += "\"elements\":[";
            json +="["+std::to_string(node->data_internal_node[i].region->get_Pmin().get_X())+","+std::to_string(node->data_internal_node[i].region->get_Pmin().get_Y())+"],\n";
            json +="["+std::to_string(node->data_internal_node[i].region->get_Pmax().get_X())+","+std::to_string(node->data_internal_node[i].region->get_Pmax().get_Y())+"]\n";
            json +="]}";
            json +=",";
            showAll_values_JSON(node->data_internal_node[i].child, level+1, json);

        }
    }
    else
    {
        for(int i=0; i<node->elements; i++)
        {
            json +="{";
            json += "\"level\":"+std::to_string(node->at_level)+",\n";
            json += "\"is_leaf\":"+std::to_string(1)+",\n";
            json += "\"elements\":[";
            std::vector<Point> vertices = node->data_leafs[i].polygon->get_vertices();
            json += "[";
            for(int j=0; j<node->data_leafs[i].polygon->get_vertices().size(); j++)
            {
            json +="["+std::to_string(vertices[j].get_X())+","+std::to_string(vertices[j].get_Y())+"]";
            if(j+1 != node->data_leafs[i].polygon->get_vertices().size())
                    json += ",\n";
            }
            json += "]";
            json +="]}";
            json +=",";
        }
    }
}
void RTree::get_polygons_JSON(const std::vector<d_leaf*> & ans,std::string &json){
    json += "[";
    for(int i=0; i<ans.size(); i++){
        json +="[";    
        for(int j = 0; j < ans[i]->polygon->corners;j++){
           json +="[";
           json += std::to_string(ans[i]->polygon->get_vertices()[j].get_X());
           json += ",";
           json += std::to_string(ans[i]->polygon->get_vertices()[j].get_Y()); 
           json +="]";
           if((j+1) != ans[i]->polygon->corners)
                json +=",";
        }
        json +="]";
        if((i+1) != ans.size())
            json +=",";
    }
    json += "]";
}

void RTree::get_Range_Search_JSON(const std::vector<Polygon *> & data, std::string &json){
    json += "[";
    for(int i=0; i<data.size(); i++){
        json +="[";
        json +="{";
        json +="\"elements\":[";    
        auto dat = data[i]->get_vertices();
        for(int j = 0; j < dat.size(); j++){
            json +="[";  
            
            json += std::to_string(dat[j].get_X());
            json += ",";
            json += std::to_string(dat[j].get_Y()); 
        
            json +="]";
            if((j+1) != dat.size())
                    json +=",";
        }            
    
        json +="],";
        json+="\"level\":"+std::to_string(0);
        json += "}";

        json +="]";
        if((i+1) != data.size())
            json +=",\n";
    }
    json += "]";
}

RTree::~RTree(){
    if(this->root != nullptr)
        delete this->root;
}
RTree_node::~RTree_node(){
    if(!this->is_leaf){
        for(int i = 0; i < this->elements; i++){
            delete this->data_internal_node[i].child;
            this->data_internal_node[i].child = nullptr;
            delete this->data_internal_node[i].region;
            this->data_internal_node[i].region = nullptr;
        }
    }
    else{
        for(int i = 0; i < this->elements; i++){
            if(this->data_leafs[i].polygon!=nullptr){
                delete this->data_leafs[i].polygon;
                this->data_leafs[i].polygon = nullptr;
                delete this->data_leafs[i].region;
                this->data_leafs[i].region = nullptr;
            }
        }
    }
}