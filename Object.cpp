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

bool Polygon::intersect_with_BB(const Polygon & pol){
    if(this->Pmin <= pol.Pmax && this->Pmin >= pol.Pmin){
            return true;
    }
    if(this->Pmax <= pol.Pmax && this-> Pmax >= pol.Pmin){
        return true;
    }
    Point myPoint_leftUP(this->Pmin.get_X(),this->Pmax.get_Y());
    Point myPoint_right_L(this->Pmax.get_X(), this->Pmin.get_Y());
    Point BB_point_leftUP(Pmin.get_X(),Pmax.get_Y());
    Point BB_point_right_L(Pmax.get_X(), Pmin.get_Y());
    if(myPoint_leftUP <= BB_point_leftUP && myPoint_leftUP >= BB_point_right_L){
        return true;
    }
    if(myPoint_right_L <= BB_point_leftUP && myPoint_right_L >= BB_point_right_L){
        return true;
    }
    return false;
}

bool Polygon::is_Within_of(const Polygon & pol){
    if(this->Pmin >= pol.Pmin && this->Pmax <= pol.Pmax)
            return true;
        else
            return false;
}