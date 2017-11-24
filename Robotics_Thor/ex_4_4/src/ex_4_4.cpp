#include <iostream>
#include <rw/rw.hpp>
#include <rwlibs/pathplanners/rrt/RRTPlanner.hpp>
#include <rwlibs/pathplanners/rrt/RRTQToQPlanner.hpp>
#include <rwlibs/proximitystrategies/ProximityStrategyFactory.hpp>


#include <rw/kinematics/MovableFrame.hpp>
#include <rw/kinematics/FKRange.hpp>
#include <rw/math/Transform3D.hpp>
#include <rw/math.hpp>

#include <string>

#include <vector>
#include <math.h>


using namespace std;

void printMatrices(vector<vector<double> > aMatrix){
    int row = aMatrix[0].size();
    int col = aMatrix[0].size();
    for(int i = 0; i< row; i++){
        for(int j = 0; j<col; j++){
            cout<<aMatrix[i][j]<< " ";
        }
        cout<<endl;
    }
}

rw::math::VectorND<4,double> addPoint(double x,double y, double z,double fill){
    rw::math::VectorND<4,double> R ;
    R(0)=x;
    R(1)=y;
    R(2)=z;
    R(3)=fill;
    return R;
}
rw::math::Vector2D<double>pinHoleModel(rw::math::VectorND<4,double> point, const int fLength){

    rw::math::Vector2D<double>uv;
    uv(0)=(fLength*point(0))/point(2);        // u= f*x/z
    uv(1)=(fLength*point(1))/point(2);        // v= f*y/z
    cout<<"u:\t"<<uv(0)<<endl<<"v:\t"<<uv(1)<<endl;
    return uv;

}
//vector<float> dudv(vector<float>point,int fLength){
//    vector<float>dudv={0,0};
//    dudv[0]=(fLength*point[0])/point[2];        // u= f*x/z
//    dudv[1]=(fLength*point[1])/point[2];        // v= f*y/z
//    return dudv;
//}



void printPoint(rw::math::VectorND<4,double>anyVec){
    cout<<"This vector contains"<<endl;
    for(int i = 0; i<anyVec.size() ;i ++){
        cout<<anyVec[i]<<" ";
    }
    cout<<endl;
}

rw::math::Jacobian calcJacobian(rw::math::VectorND<4,double> point,rw::math::Vector2D<double> uv, const int fLenght){
    rw::math::Jacobian jar(2,6);
    int rows = jar.size1();
    int cols = jar.size2();
    const int f = fLenght;
    const double u =uv(0);
    const double v =uv(1);
    const double z =point(2);
    cout<<"**** dimensions of the jacobian *****"<<endl;
    cout<<"rows:\t"<< rows<<endl<<"cols:\t"<< cols<<endl;
    //First row
    jar(0,0)=-f/z;
    jar(0,1)=0;
    jar(0,2)=u/z;
    jar(0,3)=(u*v)/z;
    jar(0,4)=-(pow(f,2) + pow(u,2) ) / f;
    jar(0,5)= v;
    //Second row
    jar(1,0)=0;
    jar(1,1)=-f/z;
    jar(1,2)=v/z;
    jar(1,3)=(pow(f,2) + pow(u,2) ) / f;
    jar(1,4)=-(u*v)/z;
    jar(1,5)=u;
    return jar;
}
rw::math::Q addConfigurationVector(int size, double j1, double j2,double j3, double j4, double j5, double j6){
    rw::math::Q myQ(size);
    myQ(0)=j1;
    myQ(1)=j2;
    myQ(2)=j3;
    myQ(3)=j4;
    myQ(4)=j5;
    myQ(5)=j6;
    return myQ;
}
/* gunu code
zimagejacobian calcZimage (jimage , device, q, state)
set q , and state,

rotate etc.

jacobian S(6,9)

S.e.setzero
S.e().block - transposed initialize matrix.

jacobian j = device -> baseJend 
*/

int main() {
    //Constructs
    rw::math::VectorND<4,double> r ;//= {0.0, 0.0, 0.0, 0.0};
    rw::math::Vector2D<double>uv;
    rw::math::Q q;

    //Constants
    const int f = 500;                // Focal lenght

    //Functions
    r = addPoint(1.,1.,4.,1.);
    uv = pinHoleModel(r,f);
    printPoint(r);
    cout <<calcJacobian(r,uv,f)<<endl;
    q=addConfigurationVector(6,1,2,1,-1,1,1); // invalid position

    cout<<q<<endl;










//Assume now that the camera is placed aligned with the tool frame of a Universal UR5 robot residing at a joint configuration q = (1, 2, 1, −1, 1, 1). Compute Zimage(q).
    cout<<"Program ended correctly"<<endl;
        return 0;
}


