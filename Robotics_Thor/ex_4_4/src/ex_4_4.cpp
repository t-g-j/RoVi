#include <iostream>
#include <rw/rw.hpp>
#include <rwlibs/pathplanners/rrt/RRTPlanner.hpp>
#include <rwlibs/pathplanners/rrt/RRTQToQPlanner.hpp>
#include <rwlibs/proximitystrategies/ProximityStrategyFactory.hpp>


#include <rw/kinematics/MovableFrame.hpp>
#include <rw/kinematics/FKRange.hpp>
#include <rw/math/Transform3D.hpp>
#include <rw/math.hpp>
#include <rw/math/LinearAlgebra.hpp>

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
    cout<<"u:"<<uv(0)<<" v:"<<uv(1)<<endl;
    jar(0,0)=-f/z;
    jar(0,1)=0;
    jar(0,2)=u/z;
    jar(0,3)=(u*v)/f;
    jar(0,4)=-(pow(f,2) + pow(u,2) ) / f;
    jar(0,5)= v;
    //Second row
    jar(1,0)=0;
    jar(1,1)=-f/z;
    jar(1,2)=v/z;
    jar(1,3)=(pow(f,2) + pow(u,2) ) / f;
    jar(1,4)=-(u*v)/f;
    jar(1,5)= -u;
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

JImage=
   -125,       0,   31.25,   31.25, -531.25,     125
      0 ,   -125,   31.25, 531.25,   -31.25,    -125
*/

int main() {

    //Constructs
    rw::math::VectorND<4,double> r ;//= {0.0, 0.0, 0.0, 0.0};
    rw::math::Vector2D<double>uv;
    rw::math::Q q;

    //Constants
    const int f = 500;                // Focal lenght

    // Paths to workcell and name of robot
    //const std::string workcell_path = "/mnt/hgfs/7. Semester/RoVi/Robotics/Lec 3/UR5WorkCellFinal/Scene.wc.xml";
    const std::string workcell_path = "/mnt/hgfs/7. Semester/RoVi/Robotics/URInterpolate/Scene.wc.xml";
     const std::string device_name = "UR-6-85-5-A";

    // Load workcell
    rw::models::WorkCell::Ptr wc = rw::loaders::WorkCellLoader::Factory::load(workcell_path);
    // Get device and check if it has been loaded correctly
    rw::models::Device::Ptr device = wc->findDevice(device_name);
    if(device == nullptr) {
        RW_THROW("Device " << device_name << " was not found!");
    }
    
    // Get an initial configuration, q
    rw::kinematics::State state = wc->getDefaultState();
    rw::math::Q q_init = device->getQ(state);


    //checking for Q pos
    cout<<"Q: "<<q_init<<endl;
    q=addConfigurationVector(6,1,1,-1,1,2,1); // invalid position
    cout<<q<<endl;

    device->setQ(q, state);
    rw::math::Q q2 = device->getQ(state);
    cout<<"new Q: "<<q2<<endl;

    // Compute baseTtool
    rw::kinematics::Frame* tool_frame = wc->findFrame("Tool");
    if(tool_frame == nullptr) {
        RW_THROW("Tool frame not found!");
    }
    const rw::math::Transform3D<> baseTtool = device->baseTframe(tool_frame, state);


    //Functions
    r = addPoint(1.,1.,4.,1.);
    uv = pinHoleModel(r,f);
    printPoint(r);
    cout <<calcJacobian(r,uv,f)<<endl;

    rw::math::Jacobian jimage(2,6);
    jimage = calcJacobian(r,uv,f);

    rw::math::Jacobian J = device->baseJend(state);
    cout<<"J"<<endl<<J<<endl;
    

    
    rw::math::Jacobian S(6,6);
    S = rw::math::Jacobian::zero(6,6);


    rw::math::Rotation3D<double>rot;
    rw::math::Rotation3D<double>rotT;
    //rot = baseTtool.R();    
    rot = baseTtool.R();//.inverse();
    rotT= rot;
    rotT.inverse();
    //auto test = baseTtool.R().inverse();

//    rotT(0,0)=rot(0,0);
    rotT(1,0)=rot(0,1);
    rotT(2,0)=rot(0,2);
    rotT(0,1)=rot(1,0);
//    rotT(1,1)=rot(1,1);
    rotT(2,1)=rot(1,2);
    rotT(0,2)=rot(2,0);
    rotT(1,2)=rot(2,1);
//    rotT(2,2)=rot(2,2);

    rw::math::Jacobian S2(rotT);
    
    
    cout<<"transpose"<<rotT<<endl;
    cout<<"rot"<<rot<<endl;

    S(0,0)=rot(0,0);
    S(0,1)=rot(0,1);
    S(0,2)=rot(0,2);
    S(1,0)=rot(1,0);
    S(1,1)=rot(1,1);
    S(1,2)=rot(1,2);
    S(2,0)=rot(2,0);
    S(2,1)=rot(2,1);
    S(2,2)=rot(2,2);

    S(3,3)=rot(0,0);
    S(3,4)=rot(0,1);
    S(3,5)=rot(0,2);
    S(4,3)=rot(1,0);
    S(4,4)=rot(1,1);
    S(4,5)=rot(1,2);
    S(5,3)=rot(2,0);
    S(5,4)=rot(2,1);
    S(5,5)=rot(2,2);

    cout<<"S"<<endl<<S<<endl;
    cout<<endl<<endl<<"S2"<<endl<<S2<<endl;

    rw::math::Jacobian zimage(2,6);
    rw::math::Jacobian zimage2(2,6);
    rw::math::Jacobian zimage2e(2,6);
    zimage = jimage*S*J;
    zimage2=jimage*S2*J;
    zimage2e=(jimage*S2*J);
    
    cout<<"zimage"<<zimage<<endl;
    cout<<endl;
    cout<<"zimage2"<<zimage2<<endl;
    cout<<endl;
    cout<<"zimage2.e()"<<zimage2e.e()<<endl;

				//auto Jimage = Jacobian(JCombined);

				// Gets transform from base to tool
				//auto TToolWorld = _device->baseTframe(_CameraFrame, _state);

				/* Calculate S*/

				//auto RBaseTool = TToolWorld.R().inverse();
				//auto S = Jacobian(RBaseTool);

				/* Robot Jacobian */
				//auto J = _device->baseJframe(_CameraFrame, _state); // Returns jacobian from tool to base frame.

				//auto Zimage = (Jimage*S*J).e();
				//auto ZimageT = Zimage.transpose();
				//auto Zimage_tmp = ZimageT * (Zimage*ZimageT).inverse();
				//auto dq = Zimage_tmp*dudv;

				// Get current robot configuration
				//auto q_cur = _device->getQ(_state);

				// Set max vel
				//Q dq_constrained = VelocityLimitReached(Q(dq), float(dt)/1000);

				// Add the change in robot configuration
				//q_cur += Q(dq_constrained);




//Assume now that the camera is placed aligned with the tool frame of a Universal UR5 robot residing at a joint configuration q = (1, 2, 1, −1, 1, 1). Compute Zimage(q).
    cout<<"Program ended correctly"<<endl;
        return 0;
}


