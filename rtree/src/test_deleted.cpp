#include <iostream>
#include "RTree.hpp"
RTree * tree;
int main(){
    tree = new RTree(4);
    Polygon * P_2 = new Polygon(Point(632,396),2);
    Polygon * P_4 = new Polygon(Point(368,382),4);
    Polygon * P_6 = new Polygon(Point(436,492),6);
    Polygon * P_7 = new Polygon(Point(622,514),7);
    Polygon * P_8 = new Polygon(Point(673,337),8);

    Polygon * P_2_reg = new Polygon(P_2->get_Pmin(),P_2->get_Pmax());
    Polygon * P_4_reg = new Polygon(P_4->get_Pmin(),P_4->get_Pmax());
    Polygon * P_6_reg = new Polygon(P_6->get_Pmin(),P_6->get_Pmax());
    Polygon * P_7_reg = new Polygon(P_7->get_Pmin(),P_7->get_Pmax());
    Polygon * P_8_reg = new Polygon(P_8->get_Pmin(),P_8->get_Pmax());

    tree->insert_polygon(P_2,P_2_reg);
    tree->insert_polygon(P_4,P_4_reg);
    tree->insert_polygon(P_6,P_6_reg);
    tree->insert_polygon(P_7,P_7_reg);
    tree->insert_polygon(P_8,P_8_reg);

    delete tree;
    int xx = 21;
}