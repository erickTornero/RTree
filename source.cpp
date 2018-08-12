#include <iostream>
#include "RTree.hpp"


int main(){
    Polygon myPol(Point(1,2),Point(2,4));
    Polygon reg = myPol;
    Polygon myPol2(Point(3,1),Point(5,2));
    Polygon reg2 = myPol2;
    Polygon myPol3(Point(8,8),Point(9,9));
    Polygon reg3 = myPol3;
    Polygon myPol4(Point(5,3),Point(6,4));
    Polygon reg4 = myPol4;
    Polygon myPol5(Point(2,11),Point(3,12));
    Polygon reg5 = myPol5;
    Polygon myPol6(Point(4,12),Point(5,14));
    Polygon reg6= myPol6;
    Polygon myPol7(Point(11,12),Point(12,14));
    Polygon reg7= myPol7;
    Polygon myPol8(Point(10,10),Point(13,11));
    Polygon reg8= myPol8;
    Polygon myPol9(Point(1,13),Point(3,15));
    Polygon reg9= myPol9;
    Polygon myPol10(Point(1,6),Point(3,7));
    Polygon reg10= myPol10;
    Polygon myPol11(Point(6, 15),Point(7, 16));
    Polygon reg11= myPol11;
    Polygon myPol12(Point(14,13),Point(16,14));
    Polygon reg12= myPol12;
    Polygon myPol13(Point(12, 15),Point(13, 16));
    Polygon reg13= myPol13;
    Polygon myPol14(Point(4, 6),Point(5, 8));
    Polygon reg14= myPol14;
    Polygon myPol15(Point(0, 3),Point(1, 4));
    Polygon reg15= myPol15;
    Polygon myPol16(Point(0, 0),Point(1, 1));
    Polygon reg16= myPol16;

    Polygon myPol17(Point(20,20),Point(26,21));
    Polygon reg17 = myPol17;
    Polygon myPol18(Point(0,19),Point(5,22));
    Polygon reg18 = myPol18;
    Polygon myPol19(Point(6,6),Point(8,9));
    Polygon reg19 = myPol19;
    Polygon myPol20(Point(16,3),Point(17,5));
    Polygon reg20 = myPol20;
    Polygon myPol21(Point(11,21),Point(13,23));
    Polygon reg21 = myPol21;
    Polygon myPol22(Point(15,6),Point(19,10));
    Polygon reg22= myPol22;
    Polygon myPol23(Point(23,0),Point(26,1));
    Polygon reg23= myPol23;
    Polygon myPol24(Point(5,10),Point(6,11));
    Polygon reg24= myPol24;
    Polygon myPol25(Point(1,24),Point(3,25));
    Polygon reg25= myPol25;

    RTree MyR_tree(3);
    MyR_tree.insert_polygon(&myPol,&reg);
    MyR_tree.insert_polygon(&myPol2, &reg2);
    MyR_tree.insert_polygon(&myPol3,&reg3);
    MyR_tree.insert_polygon(&myPol4, &reg4);
    MyR_tree.insert_polygon(&myPol5,&reg5);
    MyR_tree.insert_polygon(&myPol6, &reg6);
    MyR_tree.insert_polygon(&myPol7,&reg7);
    MyR_tree.insert_polygon(&myPol8, &reg8);
    MyR_tree.insert_polygon(&myPol9, &reg9);
    MyR_tree.insert_polygon(&myPol10, &reg10);
    MyR_tree.insert_polygon(&myPol11,&reg11);
    MyR_tree.insert_polygon(&myPol12, &reg12);
    MyR_tree.insert_polygon(&myPol13, &reg13);
    MyR_tree.insert_polygon(&myPol14, &reg14);
    MyR_tree.insert_polygon(&myPol15, &reg15);
    MyR_tree.insert_polygon(&myPol16, &reg16);

    MyR_tree.insert_polygon(&myPol17,&reg17);
    MyR_tree.insert_polygon(&myPol18, &reg18);
    MyR_tree.insert_polygon(&myPol19, &reg19);
    MyR_tree.insert_polygon(&myPol20, &reg20);
    MyR_tree.insert_polygon(&myPol21, &reg21);
    MyR_tree.insert_polygon(&myPol22, &reg22);
    
    MyR_tree.insert_polygon(&myPol23, &reg23);
    MyR_tree.insert_polygon(&myPol24, &reg24);
    MyR_tree.insert_polygon(&myPol25, &reg25);
    int xx = 22;
}