#include <iostream>
#include "RTree_node.hpp"

int main(){
    Poligon myPol(Point(0,0),Point(2,2));
    Poligon reg = myPol;
    Poligon myPol2(Point(3,2),Point(4,3));
    Poligon reg2 = myPol2;
    Poligon myPol3(Point(1,0),Point(2,2));
    Poligon reg3 = myPol3;
    Poligon myPol4(Point(10,10),Point(11,11));
    Poligon reg4 = myPol4;
    Poligon myPol5(Point(5,2),Point(6,3));
    Poligon reg5 = myPol5;
    Poligon myPol6(Point(2,2),Point(3,3));
    Poligon reg6= myPol6;
    RTree MyR_tree(4);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol, &reg);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol2, &reg2);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol3, &reg3);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol4, &reg4);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol5, &reg5);
    MyR_tree.insert_poligon(MyR_tree.root, &myPol6, &reg6);

    std::vector<Poligon * >  answer;
    Poligon q(Point(0,0),Point(3,3));
    MyR_tree.search(MyR_tree.root,q,answer);
    int xx = 21;
}