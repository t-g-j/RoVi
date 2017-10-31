#include <iostream>
#include <rw/rw.hpp>
#include <rwlibs/pathplanners/rrt/RRTPlanner.hpp>
#include <rwlibs/pathplanners/rrt/RRTQToQPlanner.hpp>
#include <rwlibs/proximitystrategies/ProximityStrategyFactory.hpp>


#include <rw/kinematics/MovableFrame.hpp>
#include <rw/kinematics/FKRange.hpp>
#include <rw/math/Transform3D.hpp>

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


int main() {


    vector<vector<double> > R1(3,vector<double>(3) );
    vector<vector<double> >R2{{0.,0.,0.},{0.,0.,0.},{0.,0.,0.}};


    /* First row */
    R1[0][0]= (1.0/4);
    R1[0][1]=sqrt(3)/4;
    R1[0][2]=sqrt(3)/2;
    /* Second row */
    R1[1][0]=sqrt(3)/4;
    R1[1][1]= (3/4);
    R1[1][2]= -(1.0/2);
    /* Third row */
    R1[2][0]= -sqrt(3)/2;;
    R1[2][1]= (1.0/2);
    R1[2][2]= 0.0;
    cout<<R1[1][2]<<endl;
    //Second rotation matrix

    /*First row */
    R2[0][0]=-5.0/8;
    R2[0][1]=(3*sqrt(3) )/8;
    R2[0][2]=sqrt(3)/4;
    /* Second row */
    R2[1][0]=(3*sqrt(3) )/8;
    R2[1][1]=1.0/8;
    R2[1][2]=3.0/4;
    /* Third row */
    R2[2][0]=sqrt(3)/4;
    R2[2][1]=3.0/4;
    R2[2][2]=-1.0/2;

    cout<<"R1"<<endl;
    printMatrices(R1);
    cout<<endl<<"R2"<<endl;
    printMatrices(R2);

    cout<<"test"<<endl;
        return 0;
}


