#ifndef SAMPLEPLUGIN_HPP
#define SAMPLEPLUGIN_HPP

// RobWork includes
#include <rw/models/WorkCell.hpp>
#include <rw/kinematics/State.hpp>
#include <rwlibs/opengl/RenderImage.hpp>
#include <rwlibs/simulation/GLFrameGrabber.hpp>
#include <rw/math/Transform3D.hpp>
#include<rw/math.hpp>
#include <rw/kinematics/MovableFrame.hpp>
#include <rw/kinematics.hpp>


// RobWorkStudio includes
#include <RobWorkStudioConfig.hpp> // For RWS_USE_QT5 definition
#include <rws/RobWorkStudioPlugin.hpp>


// OpenCV 3
#include <opencv2/opencv.hpp>

// Qt
#include <QTimer>

#include "ui_SamplePlugin.h"

// My includes
#include "fstream"
#include "string"
#include "stdio.h"
#include "vector"
#include <algorithm>
#include "feature_methods.h"

class SamplePlugin: public rws::RobWorkStudioPlugin, private Ui::SamplePlugin
{
Q_OBJECT
Q_INTERFACES( rws::RobWorkStudioPlugin )
Q_PLUGIN_METADATA(IID "dk.sdu.mip.Robwork.RobWorkStudioPlugin/0.1" FILE "plugin.json")
public:
    SamplePlugin();
    virtual ~SamplePlugin();

    virtual void open(rw::models::WorkCell* workcell);

    virtual void close();



    virtual void initialize();
    virtual rw::math::Jacobian calcJacobianImage(double distance,double U,double V, double focalLenght);
    virtual rw::math::Q VelocityLimitReached(rw::math::Q dq, float dt);
    virtual void calcEuclidean(Eigen::VectorXd dudv);
    virtual double findBiggestEuclidean(std::vector<double>anyVec);


private slots:
    void startTrack();
    void setupBot();
    void btnPressed();
    void timer();
    void readFile();
    void stateChangedListener(const rw::kinematics::State& state);



private:
    static cv::Mat toOpenCVImage(const rw::sensor::Image& img);

    QTimer* _timer;

    rw::models::WorkCell::Ptr _wc;
    rw::kinematics::State _state;
    rwlibs::opengl::RenderImage *_textureRender, *_bgRender;
    rwlibs::simulation::GLFrameGrabber* _framegrabber;
    std::vector<double> X;
    std::vector<double>Y;
    std::vector<double>Z;
    std::vector<double> Roll;
    std::vector<double>Pitch;
    std::vector<double>Yaw;
    const float fLenght = 823;
    const float  z = 0.5;
    double u_center_data;
    double v_center_data;
    const float dt = 1.;

    const double tau = 35520/1000000;
    int trackPoints = 1;// either 1 or 3 points is possible
    bool featureDetect = true;
    int size;
    std::string file ="fast"; // choose from slow, medium or fast
    std::ofstream JointPosAndToolPos;
    std::ofstream errorLog;
    std::ofstream JointLimitAndVelocities;
    std::ofstream visionError;
    std::ofstream markerError;

    std::ofstream errorLog3P;
    std::ofstream JointLimitAndVelocities3P;
    std::ofstream JointPosAndToolPos3P;

    std::vector<double>dudvEuclideanDistance;
    std::vector<double>dudvEuclideanDistance3P;
    const std::string _device_name = "PA10";
    rw::models::Device::Ptr _device;

};

#endif /*RINGONHOOKPLUGIN_HPP_*/
