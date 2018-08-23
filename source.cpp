#include <iostream>
#include "RTree.hpp"


int main(){
    //Creation of basic Polygon through a vector of Points.
    /*std::vector<Point> a{Point(1,13),Point(3,13),Point(2,15)};
    Polygon myReal_poligon(a, 1);
    //MBB of the Polygon
    Polygon reg_real = Polygon(myReal_poligon.get_Pmin(), myReal_poligon.get_Pmax());
    //Creation of a Point.
    Polygon pol_point(Point(7,7), 1);
    Polygon point_reg(pol_point.get_Pmin(),pol_point.get_Pmax());
    //Creation of rectangle polygons
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
    //Polygon myPol9(Point(1,13),Point(3,15));
    //Polygon reg9= myPol9;
    
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
    //MyR_tree.insert_polygon(&myPol9, &reg9);
    //Insertion of a triangle
    MyR_tree.insert_polygon(&myReal_poligon, &reg_real);
    //Insertion of a point
    MyR_tree.insert_polygon(&pol_point,&point_reg);
    //Insertion of single rectangle polygons.
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
    MyR_tree.insert_polygon(&myPol25, &reg25);*/
    RTree * MyR_tree = new RTree(3);
    Polygon P_2(Point(632,396),2);
Polygon P_4(Point(368,382),4);
Polygon P_6(Point(436,492),6);
Polygon P_7(Point(622,514),7);
Polygon P_8(Point(673,337),8);
Polygon P_10(Point(730,354),10);
Polygon P_17(Point(616,346),17);
Polygon P_18(Point(560,432),18);
Polygon P_19(Point(560,459),19);
Polygon P_20(Point(618,228),20);
Polygon P_22(Point(226,405),22);

Polygon P_2_reg(P_2.get_Pmin(),P_2.get_Pmax());
Polygon P_4_reg(P_4.get_Pmin(),P_4.get_Pmax());
Polygon P_6_reg(P_6.get_Pmin(),P_6.get_Pmax());
Polygon P_7_reg(P_7.get_Pmin(),P_7.get_Pmax());
Polygon P_8_reg(P_8.get_Pmin(),P_8.get_Pmax());
Polygon P_10_reg(P_10.get_Pmin(),P_10.get_Pmax());
Polygon P_17_reg(P_17.get_Pmin(),P_17.get_Pmax());
Polygon P_18_reg(P_18.get_Pmin(),P_18.get_Pmax());
Polygon P_19_reg(P_19.get_Pmin(),P_19.get_Pmax());
Polygon P_20_reg(P_20.get_Pmin(),P_20.get_Pmax());
Polygon P_22_reg(P_22.get_Pmin(),P_22.get_Pmax());

MyR_tree->insert_polygon(&P_2,&P_2_reg);
MyR_tree->insert_polygon(&P_4,&P_4_reg);
MyR_tree->insert_polygon(&P_6,&P_6_reg);
MyR_tree->insert_polygon(&P_7,&P_7_reg);
MyR_tree->insert_polygon(&P_8,&P_8_reg);
MyR_tree->insert_polygon(&P_10,&P_10_reg);
MyR_tree->insert_polygon(&P_17,&P_17_reg);
MyR_tree->insert_polygon(&P_18,&P_18_reg);
MyR_tree->insert_polygon(&P_19,&P_19_reg);
MyR_tree->insert_polygon(&P_20,&P_20_reg);
MyR_tree->insert_polygon(&P_22,&P_22_reg);

std::vector<Point> R_1{Point(528,355),Point(555,355),Point(555,402),Point(529,402)};
std::vector<Point> R_3{Point(360,462),Point(448,462),Point(448,412),Point(358,414)};
std::vector<Point> R_5{Point(320,174),Point(319,137),Point(374,135),Point(376,175)};
std::vector<Point> R_11{Point(661,184),Point(653,184),Point(654,236),Point(662,236)};
std::vector<Point> R_12{Point(726,184),Point(750,184),Point(750,236),Point(725,237)};
std::vector<Point> R_13{Point(45,471),Point(46,478),Point(29,483),Point(30,492),Point(8,500),Point(8,517),Point(56,505),Point(108,518),Point(166,513),Point(166,460)};
std::vector<Point> R_14{Point(2,448),Point(42,446),Point(54,448),Point(100,423),Point(110,418),Point(106,404),Point(98,407),Point(96,395),Point(122,387),Point(147,389),Point(155,324),Point(147,302),Point(111,301),Point(84,280),Point(75,254),Point(64,238),Point(40,229),Point(22,229),Point(1,239)};
std::vector<Point> R_15{Point(564,396),Point(599,397),Point(600,361),Point(566,361)};
std::vector<Point> R_16{Point(2,545),Point(26,529),Point(49,521),Point(90,528),Point(142,534),Point(192,540),Point(228,560),Point(240,598),Point(2,599)};
std::vector<Point> R_21{Point(612,338),Point(661,339),Point(661,323),Point(612,320)};

Polygon myReal_R_1(R_1);
Polygon myReal_R_3(R_3);
Polygon myReal_R_5(R_5);
Polygon myReal_R_11(R_11);
Polygon myReal_R_12(R_12);
Polygon myReal_R_13(R_13);
Polygon myReal_R_14(R_14);
Polygon myReal_R_15(R_15);
Polygon myReal_R_16(R_16);
Polygon myReal_R_21(R_21);

Polygon reg_real_R_1=Polygon(myReal_R_1.get_Pmin(),myReal_R_1.get_Pmax());
Polygon reg_real_R_3=Polygon(myReal_R_3.get_Pmin(),myReal_R_3.get_Pmax());
Polygon reg_real_R_5=Polygon(myReal_R_5.get_Pmin(),myReal_R_5.get_Pmax());
Polygon reg_real_R_11=Polygon(myReal_R_11.get_Pmin(),myReal_R_11.get_Pmax());
Polygon reg_real_R_12=Polygon(myReal_R_12.get_Pmin(),myReal_R_12.get_Pmax());
Polygon reg_real_R_13=Polygon(myReal_R_13.get_Pmin(),myReal_R_13.get_Pmax());
Polygon reg_real_R_14=Polygon(myReal_R_14.get_Pmin(),myReal_R_14.get_Pmax());
Polygon reg_real_R_15=Polygon(myReal_R_15.get_Pmin(),myReal_R_15.get_Pmax());
Polygon reg_real_R_16=Polygon(myReal_R_16.get_Pmin(),myReal_R_16.get_Pmax());
Polygon reg_real_R_21=Polygon(myReal_R_21.get_Pmin(),myReal_R_21.get_Pmax());

MyR_tree->insert_polygon(&myReal_R_1,&reg_real_R_1);
MyR_tree->insert_polygon(&myReal_R_3,&reg_real_R_3);
MyR_tree->insert_polygon(&myReal_R_5,&reg_real_R_5);
MyR_tree->insert_polygon(&myReal_R_11,&reg_real_R_11);
MyR_tree->insert_polygon(&myReal_R_12,&reg_real_R_12);
MyR_tree->insert_polygon(&myReal_R_13,&reg_real_R_13);
MyR_tree->insert_polygon(&myReal_R_14,&reg_real_R_14);
MyR_tree->insert_polygon(&myReal_R_15,&reg_real_R_15);
MyR_tree->insert_polygon(&myReal_R_16,&reg_real_R_16);
MyR_tree->insert_polygon(&myReal_R_21,&reg_real_R_21);

   /* std::vector<Point> R_1{Point(483,393),Point(500,394),Point(525,375)};
    std::vector<Point> R_3{Point(613,337),Point(630,357),Point(668,347),Point(662,364)};
    std::vector<Point> R_5{Point(320,174),Point(319,137),Point(374,135),Point(376,175)};
    std::vector<Point> R_11{Point(661,184),Point(653,184),Point(654,236),Point(662,236)};
    Polygon myReal_R_1(R_1);
    Polygon myReal_R_3(R_3);
    Polygon myReal_R_5(R_5);
    Polygon myReal_R_11(R_11);
    Polygon reg_real_R_1=Polygon(myReal_R_1.get_Pmin(),myReal_R_1.get_Pmax());
    Polygon reg_real_R_3=Polygon(myReal_R_3.get_Pmin(),myReal_R_3.get_Pmax());
    Polygon reg_real_R_5=Polygon(myReal_R_5.get_Pmin(),myReal_R_5.get_Pmax());
    Polygon reg_real_R_11=Polygon(myReal_R_11.get_Pmin(),myReal_R_11.get_Pmax());
    
    MyR_tree.insert_polygon(&myReal_R_1,&reg_real_R_1);
    MyR_tree.insert_polygon(&myReal_R_3,&reg_real_R_3);
    MyR_tree.insert_polygon(&myReal_R_5,&reg_real_R_5);
    MyR_tree.insert_polygon(&myReal_R_11,&reg_real_R_11);
    */
    MyR_tree->show_values_JSON();

    std::vector<Polygon * > answ;
    MyR_tree->range_search(Polygon(Point(476, 408),Point(691, 322)),answ);

    std::vector<d_leaf*> ans_knn;
    MyR_tree->k_NN_DF(Point(10,9),3, ans_knn);
    //Show Values
    //std::cout << MyR_tree.show_values_JSON() << std::endl;
    std::string jsn ="";
    MyR_tree->get_Range_Search_JSON(answ,jsn);
    std::cout << jsn<<std::endl;
    delete MyR_tree;
    int xx = 22;
}