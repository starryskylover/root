#include <iostream>
#include <math.h>
#include <cmath>

#ifdef M_PI
double const pi = M_PI;
#else
double const pi = 4*std::atan(1);
#endif

class Hep3Vector{
public:
    Hep3Vector();
    Hep3Vector(double x, double y, double z);
    Hep3Vector(const Hep3Vector &v);
    double x();
    double y();
    double z();
    double Phi();
    double cosTheta();
    double mag();
private:
    double r, cos_Theta, ang_phi;
};

Hep3Vector::Hep3Vector(double x, double y, double z){
    r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    (r == 0) ? cos_Theta = 1234567 : cos_Theta =  z / r;
    (r == 0) ? ang_phi =1234567 : (x == 0) ? ang_phi=pi/2 : ang_phi  = atan(x / sqrt(pow(r, 2) - pow(z, 2)));  //phi=atan (y/x)
}

Hep3Vector::Hep3Vector(const Hep3Vector &v) {
    r = v.r;
    ang_phi = v.ang_phi;
    cos_Theta = v.cos_Theta;
}

Hep3Vector::Hep3Vector(){
}

double Hep3Vector::Phi(){
    return ang_phi;
}

double Hep3Vector::cosTheta(){
    return cos_Theta;
}

double Hep3Vector::mag(){
    return r;
}

int main(){
     Hep3Vector v(0.0, 0.0, 0.0);
     Hep3Vector vec = Hep3Vector(v);
     Hep3Vector *vector = new Hep3Vector(v);

         std::cout << v.mag() << '\n';
         std::cout << v.Phi() << '\n';
         std::cout << v.cosTheta() << '\n';

         std::cout << vec.mag() << '\n';
         std::cout << vec.Phi() << '\n';
         std::cout << vec.cosTheta() << '\n';

         double m1=vector->mag();
         double m2=vector->Phi();
         double m3=vector->cosTheta();

         std::cout << m1 << '\n';
         std::cout << m2 << '\n';
         std::cout << m3 << '\n';
   }
