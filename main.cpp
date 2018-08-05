#include <iostream>
#include "RTree_node.hpp"

int main(){
    Poligon myPol(Point(0,0),Point(2,2));
    Poligon myPol2(Point(3,2),Point(4,3));
    Poligon myPol3(Point(1,0),Point(2,2));
    Poligon myPol4(Point(10,10),Point(11,11));
    Poligon myPol5(Point(5,2),Point(6,3));
    Poligon myPol6(Point(2,2),Point(3,3));
    RTree MyR_tree(4);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol2);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol3);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol4);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol5);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol6);
    int xx = 21;
}