#include <iostream>
#include "RTree_node.hpp"

int main(){
    Poligon myPol(Point(1,2),Point(2,4));
    Poligon reg = myPol;
    Poligon myPol2(Point(3,1),Point(5,2));
    Poligon reg2 = myPol2;
    Poligon myPol3(Point(8,8),Point(9,9));
    Poligon reg3 = myPol3;
    Poligon myPol4(Point(5,3),Point(6,4));
    Poligon reg4 = myPol4;
    Poligon myPol5(Point(2,11),Point(3,12));
    Poligon reg5 = myPol5;
    Poligon myPol6(Point(4,12),Point(5,14));
    Poligon reg6= myPol6;

    Poligon myPol7(Point(11,12),Point(12,14));
    Poligon reg7= myPol7;
    Poligon myPol8(Point(10,10),Point(13,11));
    Poligon reg8= myPol8;
    Poligon myPol9(Point(1,13),Point(3,15));
    Poligon reg9= myPol9;
    Poligon myPol10(Point(1,6),Point(3,7));
    Poligon reg10= myPol10;
    Poligon myPol11(Point(6, 15),Point(7, 16));
    Poligon reg11= myPol11;
    Poligon myPol12(Point(14,13),Point(16,14));
    Poligon reg12= myPol12;
    Poligon myPol13(Point(12, 15),Point(13, 16));
    Poligon reg13= myPol13;
    Poligon myPol14(Point(4, 6),Point(5, 8));
    Poligon reg14= myPol14;
    
    Poligon myPol15(Point(0, 3),Point(1, 4));
    Poligon reg15= myPol15;
    Poligon myPol16(Point(0, 0),Point(1, 1));
    Poligon reg16= myPol16;

    RTree MyR_tree(3);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol, &reg);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol2, &reg2);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol3, &reg3);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol4, &reg4);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol5, &reg5);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol6, &reg6);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol7, &reg7);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol8, &reg8);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol9, &reg9);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol10, &reg10);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol11, &reg11);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol12, &reg12);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol13, &reg13);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol14, &reg14);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol15, &reg15);
    MyR_tree.insert_poligon(MyR_tree.root, nullptr, &myPol16, &reg16);

    std::queue<Poligon *> ans;
    MyR_tree.k_nearest_DF(Point(10,9),3,MyR_tree.root,ans);
    std::vector<Poligon * >  answer;
    Poligon q(Point(3,1),Point(6,4));
    MyR_tree.search(MyR_tree.root,q,answer);
    MyR_tree.show_values();
    std::cout<<"Values found: "<<std::endl;
    for(int i = 0; i< answer.size(); i++){
        answer[i]->print_poligon();
    }
    int xx = 21;
}