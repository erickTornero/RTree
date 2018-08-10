#include "Objects.hpp"
void Polygon::area_added(Polygon & reg, Point & pmin, Point & pmax){
    int x_max = this->Pmax.get_X();
    if(reg.Pmax.get_X() > x_max){
        x_max = reg.Pmax.get_X();
    }
    int x_min = this->Pmin.get_X();
    if(reg.Pmin.get_X() < x_min){
        x_min = reg.Pmin.get_X();
    }

    int y_max = this->Pmax.get_Y();
    if(reg.Pmax.get_Y() > y_max){
        y_max = reg.Pmax.get_Y();
    }
    int y_min = this->Pmin.get_Y();
    if(reg.Pmin.get_Y() < y_min){
        y_min = reg.Pmin.get_Y();
    }
        //This points max and minimung will welp to calculate the region of parents
    pmin = Point(x_min,y_min);
    pmax = Point(x_max,y_max);
}
int Polygon::cost_two_poligons(Polygon & reg){
    Point pmin, pmax;
    area_added(reg,pmin,pmax);
    int d = (pmax.get_X()-pmin.get_X())*(pmax.get_Y()-pmin.get_Y());
    d -= (reg.Pmax.get_X() - reg.Pmin.get_X())*(reg.Pmax.get_Y() - reg.Pmin.get_Y());
    d -= (this->Pmax.get_X() - this->Pmin.get_X())*(this->Pmax.get_Y() - this->Pmin.get_Y());
    return d;
}