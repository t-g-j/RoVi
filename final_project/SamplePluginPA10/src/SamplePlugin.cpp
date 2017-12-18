#include "SamplePlugin.hpp"

#include <rws/RobWorkStudio.hpp>

#include <QPushButton>

#include <rw/loaders/ImageLoader.hpp>
#include <rw/loaders/WorkCellFactory.hpp>

#include <functional>

using namespace rw::common;
using namespace rw::graphics;
using namespace rw::kinematics;
using namespace rw::loaders;
using namespace rw::models;
using namespace rw::sensor;
using namespace rwlibs::opengl;
using namespace rwlibs::simulation;

using namespace rws;

using namespace cv;

using namespace std::placeholders;

SamplePlugin::SamplePlugin():
    RobWorkStudioPlugin("SamplePluginUI", QIcon(":/pa_icon.png"))
{
	setupUi(this);

	_timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timer()));

	// now connect stuff from the ui component
	connect(_btn0    ,SIGNAL(pressed()), this, SLOT(btnPressed()) );
	connect(_btn1    ,SIGNAL(pressed()), this, SLOT(btnPressed()) );
    connect(_btn2    ,SIGNAL(pressed()), this, SLOT(startTrack())  );
    connect(_btn3    ,SIGNAL(pressed()), this, SLOT(readFile() )   );
    connect(_btn4   ,SIGNAL(pressed() ), this, SLOT(setupBot()) );



	connect(_spinBox  ,SIGNAL(valueChanged(int)), this, SLOT(btnPressed()) );

	Image textureImage(300,300,Image::GRAY,Image::Depth8U);
	_textureRender = new RenderImage(textureImage);
	Image bgImage(0,0,Image::GRAY,Image::Depth8U);
	_bgRender = new RenderImage(bgImage,2.5/1000.0);
	_framegrabber = NULL;
}

SamplePlugin::~SamplePlugin()
{
    delete _textureRender;
    delete _bgRender;
}

void SamplePlugin::initialize() {
	log().info() << "INITALIZE" << "\n";

	getRobWorkStudio()->stateChangedEvent().add(std::bind(&SamplePlugin::stateChangedListener, this, _1), this);

	// Auto load workcell
    WorkCell::Ptr wc = WorkCellLoader::Factory::load("/mnt/hgfs/github/RoVi_My_Own/final_project/PA10WorkCell/ScenePA10RoVi1.wc.xml");
	getRobWorkStudio()->setWorkCell(wc);

	// Load Lena image
	Mat im, image;
    im = imread("/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/src/lena.bmp", CV_LOAD_IMAGE_COLOR); // Read the file
	cvtColor(im, image, CV_BGR2RGB); // Switch the red and blue color channels
	if(! image.data ) {
		RW_THROW("Could not open or find the image: please modify the file path in the source code!");
	}
	QImage img(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888); // Create QImage from the OpenCV image
	_label->setPixmap(QPixmap::fromImage(img)); // Show the image at the label in the plugin
//    logTest();
}
void SamplePlugin::readFile(){

    double nr;
    int s=501;
    int f=50;
    int m=167;
    std::string runFile;
    /* Loading into the txt file to move frame*/
    std::string slow ="/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/motions/MarkerMotionSlow.txt";
    std::string medium ="/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/motions/MarkerMotionMedium.txt" ;
    std::string fast ="/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/motions/MarkerMotionFast.txt" ;


    /*MAN SKAL VÆLGE HVER GANG MAN VIL LÆSE EN NY FIL */
    if(file == "fast"){
        size = f;
        runFile = fast;
    }
    else if(file == "slow"){
        size = s;
        runFile = slow;
    }
    else if(file == "medium"){
        size = m;
        runFile = medium;
    }


    std::string line;



    /*MAN SKAL VÆLGE HVER GANG MAN VIL LÆSE EN NY FIL */
    std::ifstream myMoves(runFile);

    for(int i = 0;i<size;i++){
    if(myMoves.is_open() ==true ){

        std::getline(myMoves,line,'\t');
            nr = stod(line);
            X.push_back(nr);
            std::getline(myMoves,line,'\t');
                nr = stod(line);
                Y.push_back(nr);
                std::getline(myMoves,line,'\t');
                    nr = stod(line);
                    Z.push_back(nr);
                    std::getline(myMoves,line,'\t');
                        nr = stod(line);
                        Roll.push_back(nr);
                        std::getline(myMoves,line,'\t');
                            nr = stod(line);
                            Pitch.push_back(nr);
                            std::getline(myMoves,line,'\n');
                                nr = stod(line);
                                Yaw.push_back(nr);


    }
//    log().info()<<"x:"<<X[i]<<"\ty:"<<Y[i]<<"\tz:"<<Z[i]<<"\tr:"<<Roll[i]<<"\tp:"<<Pitch[i]<<"\ty:"<<Yaw[i]<<"\n";
    }
    myMoves.close();
    log().info()<<"size\t"<<X.size()<<"\n";
    log().info()<<"Data has been loaded\n";


}
void SamplePlugin::startTrack(){
    QObject *obj = sender();
    if(obj==_btn2){
        JointPosAndToolPos.open("JointPosAndToolPos.txt");
        errorLog.open("errorLog.txt");
        JointLimitAndVelocities.open("JointLimitAndVelocities.txt");
        JointPosAndToolPos3P.open("JointPosAndToolPos3P.txt");
        errorLog3P.open("errorLog3P.txt");
        JointLimitAndVelocities3P.open("JointLimitAndVelocities3P.txt");
        visionError.open("visionError.txt");
        markerError.open("markerError.txt");
    }

}
rw::math::Jacobian SamplePlugin::calcJacobianImage(double distance,double U,double V, double focalLenght){
    rw::math::Jacobian jar(2,6);
    const int f = focalLenght;
    const double u =U;
    const double v =V;
    const double z =distance;

    //First row
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
    jar(1,3)=(pow(f,2) + pow(v,2) ) / f;
    jar(1,4)=-(u*v)/f;
    jar(1,5)= -u;
    return jar;
}
void SamplePlugin::open(WorkCell* workcell)
{
    log().info() << "OPEN" << "\n";
    _wc = workcell;
    _state = _wc->getDefaultState();

    log().info() << workcell->getFilename() << "\n";

    if (_wc != NULL) {
	// Add the texture render to this workcell if there is a frame for texture
	Frame* textureFrame = _wc->findFrame("MarkerTexture");
	if (textureFrame != NULL) {
		getRobWorkStudio()->getWorkCellScene()->addRender("TextureImage",_textureRender,textureFrame);
	}
	// Add the background render to this workcell if there is a frame for texture
	Frame* bgFrame = _wc->findFrame("Background");
	if (bgFrame != NULL) {
		getRobWorkStudio()->getWorkCellScene()->addRender("BackgroundImage",_bgRender,bgFrame);
	}

	// Create a GLFrameGrabber if there is a camera frame with a Camera property set
	Frame* cameraFrame = _wc->findFrame("CameraSim");
	if (cameraFrame != NULL) {
		if (cameraFrame->getPropertyMap().has("Camera")) {
			// Read the dimensions and field of view
			double fovy;
			int width,height;
			std::string camParam = cameraFrame->getPropertyMap().get<std::string>("Camera");
			std::istringstream iss (camParam, std::istringstream::in);
			iss >> fovy >> width >> height;
			// Create a frame grabber
			_framegrabber = new GLFrameGrabber(width,height,fovy);
			SceneViewer::Ptr gldrawer = getRobWorkStudio()->getView()->getSceneViewer();
			_framegrabber->init(gldrawer);
		}
	}
    }
}
void SamplePlugin::setupBot(){
    _device = _wc->findDevice(_device_name);
    rw::math::Q q_initial(7,0,-0.65,0,1.80,0,0.42,0);
    _device->setQ(q_initial, _state);
    getRobWorkStudio()->setState(_state);

}
double SamplePlugin::findBiggestEuclidean(std::vector<double>anyVec){
    double tmp;
    std::vector<double>::iterator it;
    it=std::max_element(anyVec.begin(),anyVec.end());
    tmp=*it;
    return tmp;
}
void SamplePlugin::calcEuclidean(Eigen::VectorXd dudv){
    std::vector<double>tmp;
    if(dudv.size() >2){
        double largest = abs( sqrt(pow(dudv(0),2)+pow(dudv(1),2)));
        double scorePos2 = abs( sqrt(pow(dudv(2),2)+pow(dudv(3),2)));
        double scorePos3 = abs( sqrt(pow(dudv(4),2)+pow(dudv(5),2)));
        log().info()<<"scorePos1"<<largest<<"\n";
        log().info()<<"scorePos2"<<scorePos2<<"\n";
        log().info()<<"scorePos3"<<scorePos3<<"\n";
        if(largest > scorePos2){
            if(largest>scorePos3){
                dudvEuclideanDistance3P.push_back(largest);
            }
        }
        if(scorePos2>scorePos3){
            dudvEuclideanDistance3P.push_back(scorePos2);
        }
        else{
            dudvEuclideanDistance3P.push_back(scorePos3);
        }
    }
    else{
        double score = abs( sqrt(pow(dudv(0),2)+pow(dudv(1),2)));
        log().info()<<"score"<<score<<"\n";
        dudvEuclideanDistance.push_back(score);
    }
}

void SamplePlugin::close() {
    log().info() << "CLOSE" << "\n";

    // Stop the timer
    _timer->stop();
    // Remove the texture render
	Frame* textureFrame = _wc->findFrame("MarkerTexture");
	if (textureFrame != NULL) {
		getRobWorkStudio()->getWorkCellScene()->removeDrawable("TextureImage",textureFrame);
	}
	// Remove the background render
	Frame* bgFrame = _wc->findFrame("Background");
	if (bgFrame != NULL) {
		getRobWorkStudio()->getWorkCellScene()->removeDrawable("BackgroundImage",bgFrame);
	}
	// Delete the old framegrabber
	if (_framegrabber != NULL) {
		delete _framegrabber;
	}
	_framegrabber = NULL;
	_wc = NULL;
}

Mat SamplePlugin::toOpenCVImage(const Image& img) {
    Mat res(img.getHeight(),img.getWidth(), CV_8UC3);
	res.data = (uchar*)img.getImageData();
	return res;
}


void SamplePlugin::btnPressed() {
    QObject *obj = sender();
	if(obj==_btn0){
		log().info() << "Button 0\n";
		// Set a new texture (one pixel = 1 mm)
		Image::Ptr image;
        image = ImageLoader::Factory::load("/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/markers/Marker1.ppm");
		_textureRender->setImage(*image);
        image = ImageLoader::Factory::load("/mnt/hgfs/github/RoVi_My_Own/final_project/SamplePluginPA10/backgrounds/texture2.ppm");
		_bgRender->setImage(*image);
		getRobWorkStudio()->updateAndRepaint();
	} else if(obj==_btn1){
		log().info() << "Button 1\n";
		// Toggle the timer on and off
		if (!_timer->isActive())
            _timer->start(100); // run 10 Hz
		else
			_timer->stop();
	} else if(obj==_spinBox){
		log().info() << "spin value:" << _spinBox->value() << "\n";
	}
}

void SamplePlugin::timer() {
//    startTrack();

	if (_framegrabber != NULL) {
		// Get the image as a RW image
        Frame* cameraFrame = _wc->findFrame("CameraSim");
        _framegrabber->grab(cameraFrame, _state);
        const Image& image = _framegrabber->getImage();

        // Convert to OpenCV image
        Mat im = toOpenCVImage(image);
        Mat imflip;
        cv::flip(im, imflip, 0);

         //Show in QLabel
        QImage img(imflip.data, imflip.cols, imflip.rows, imflip.step, QImage::Format_RGB888);
        QPixmap p = QPixmap::fromImage(img);
        unsigned int maxW = 400;
        unsigned int maxH = 800;
        _label->setPixmap(p.scaled(maxW,maxH,Qt::KeepAspectRatio));


	}




    if(trackPoints ==1){                        //loops around tracking one point
        static int i = 0;                       //Index
        /******** Finding frames ********/
        MovableFrame* marker =(MovableFrame*)_wc->findFrame("Marker");
        MovableFrame* cameraF =(MovableFrame*)_wc->findFrame("Camera");
        MovableFrame* worldFrame = (MovableFrame*) _wc->findFrame("WORLD");
        /******** Constants *********/
        Mat imflip;
        Mat rgbOut;
        double half_width = 1024/2;                 // Half size of image width
        double half_height = 768/2;                 // Half size of images heigth
        std::vector<double>xy_container;            // Vector holding feature detector coordinates
        rw::math::Rotation3D<double>baseRot;        // Container for rotation matrix
        /******** Create transformation matrix for marker *********/
        const rw::math::Vector3D<double> pos(X[i],Y[i],Z[i]);                       // Load XYZ from .txt file
        const rw::math::RPY<double> rot(Roll[i],Pitch[i],Yaw[i]);                   // Load RPY from .txt file
        const rw::math::Transform3D<double> newPos(pos,rot.toRotation3D());         // Create transformation matrix for the marker

        marker->setTransform(newPos,_state);                                    // Set the marker to the new transformation matrix
        getRobWorkStudio()->setState(_state);                                   // Update RobWorkStudio
        log().info()<<"T\n"<<newPos.P()<<"\n"<<"R\n"<<newPos.R()<<"\n";         // debug


        const rw::math::Transform3D<double> postTrans = marker->getTransform(_state);   //Get the transform matrix after the update
        const rw::math::Transform3D<double> marker2world = Kinematics::frameTframe(marker, worldFrame,_state);  //TransMat for Marker to world frame
        const rw::math::Transform3D<double> camera2marker = Kinematics::frameTframe(cameraF, marker,_state);    //TransMat Camera to Marker


        rw::math::Vector3D<double> markerCenterMarkerFrame = marker2world*postTrans.P();            // Markerens center compared to Marker frame
        rw::math::Vector3D<double> markerCenterCameraFrame = camera2marker*markerCenterMarkerFrame; // Markerens center compared to Camera frame
        log().info()<<"Transform\n"<<postTrans.P()<<"\n";
        log().info()<<"markerTworld\n"<<marker2world<<"\n";
            log().info()<<"CameraTMarker\n"<<camera2marker<<"\n";
        log().info()<<"MarkerCenterinMarkerFrame\n"<<markerCenterMarkerFrame<<"\n";
        log().info()<<"MarkerCenterInCameraFrame\n"<<markerCenterCameraFrame<<"\n";
        /********* enter if vision is wanted *********/
        if(featureDetect == true){
        Frame* cameraFrame = _wc->findFrame("CameraSim");   // Find the simulated camera
        _framegrabber->grab(cameraFrame, _state);
        const Image& image = _framegrabber->getImage();
        Mat im = toOpenCVImage(image);                      // Convert to OpenCV image
        cv::flip(im, imflip, 0);                            // Flip image to counter mirror effect
        cv::cvtColor(imflip,rgbOut,COLOR_BGR2RGB);          // Convert to RGB domain
        imwrite("test.png",rgbOut);                         // debug

        xy_container = feature_methods::markerOneDetection(rgbOut); //running feature detection
        log().info()<<"im\nx: "<<xy_container[0]<<"\ty: "<<xy_container[1]<<"\n";
        log().info()<<"OFFSETS\nx: "<<half_width-xy_container[0]<<"\ty: "<<half_height-xy_container[1]<<"\n";

        u = xy_container[0]-half_width;         // Error between feature detection and real center
        v = xy_container[1]-half_height;        // Error between feature detection and real center
        visionError<<u<<","<<v<<"\n";
        }
        /******** If NOT using vision *********/
        else{
            u = fLenght*markerCenterCameraFrame[0]/z;       // Mapping to image domian
            v = fLenght*markerCenterCameraFrame[1]/z;       // Mapping to image domian
            markerError<<u<<","<<v<<"\n";
        }
        log().info()<<"u: "<<u<<"\tv:"<<v<<"\n";

        /*************************
         * Method from 4.9
         * *********************/
        /****** JACOBIAN ******/
        rw::math::Jacobian J = _device->baseJframe(cameraF,_state);     // Get the Jacobian from the robot

        /******* S(q) *******/
        const rw::math::Transform3D<> baseTtool= _device->baseTframe(cameraF,_state);   // Get the rotaion matrix for S(q)

        baseRot = baseTtool.R();
    //    log().info()<<"baseRot\n"<<baseRot<<"\n";
        baseRot.inverse();
        rw::math::Jacobian S(baseRot);
    //    log().info()<<"baseRot\n"<<baseRot<<"\n";
//        log().info()<<"S(q)\n"<<S<<"\n";

        /********* Jimage ***********/
        rw::math::Jacobian jimage=calcJacobianImage(z,u,v,fLenght);             // Calculate the image jacobian

        /********* Zimage **********/
        auto zimage = (jimage*S*J).e();                                         // Calculate Zimage with Morse-Penrose inverse
//        log().info()<<"zimage\n"<<zimage<<"\n";
        auto zimageT = zimage.transpose();
//        log().info()<<"JIMAGE\n"<<jimage<<"\n";
        auto zimage_tmp = zimageT * (zimage*zimageT).inverse();
        Eigen::VectorXd dudv(2);
        dudv(0)=u;
        dudv(1)=v;
        calcEuclidean(dudv);                        // Calculate the maximum Euclidaen
        auto dq = zimage_tmp*dudv;                  // Calculate displacement vector
        auto q_cur = _device->getQ(_state);         // Get current robot configuration
        log().info()<<"dq\n"<<dq<<"\n";
        const double wTau = dt-tau;                 // Account for Tau
        rw::math::Q dq_constrained = maxVel(rw::math::Q(dq), wTau);

        q_cur += rw::math::Q(-dq_constrained);      // Add the change in robot configuration

        _device->setQ(q_cur, _state);               // Set new state
        getRobWorkStudio()->setState(_state);       // Update

        log().info()<<i<<"\n";
        static int count =0;

        if(i!=size-1){
            log().info()<<"log data: "<<count<<"\n";
            JointPosAndToolPos<<q_cur<<","<<postTrans.P()<<"\n";
//            errorLog<<dudv(0)<<","<<dudv(1)<<"\n";
            count ++;
            i++;
        }
        if(i == size-1){
            std::pair<rw::math::Q,rw::math::Q> jLim;    //container for joint position limit
            jLim= _device->getBounds();
            log().info()<<"LOWER\t"<<jLim.first<<"\tUPPER\t"<<jLim.second<<"\n";
            log().info()<<"Biggest Euclideain "<<findBiggestEuclidean(dudvEuclideanDistance)<<"\n";
            errorLog<<findBiggestEuclidean(dudvEuclideanDistance);
            JointPosAndToolPos.close();
            errorLog.close();
            JointLimitAndVelocities.close();
            visionError.close();
            markerError.close();
            log().info()<<"closed file\n";

            if(featureDetect == false){
            trackPoints = 3;
            setupBot();
                }
        }

    }
    /********* Enter only if tracking 3 points**********/
    if(trackPoints == 3){
        static int i = 0;
        /******** Finding frames ********/
        MovableFrame* marker =(MovableFrame*)_wc->findFrame("Marker");
        MovableFrame* cameraF =(MovableFrame*)_wc->findFrame("Camera");
        MovableFrame* worldFrame = (MovableFrame*) _wc->findFrame("WORLD");
        /******** Constant ********/

        rw::math::Vector3D<> pos0;
        rw::math::Vector3D<> pos1;
        rw::math::Vector3D<> pos2;
        //Pos on markerframe
        pos0[0] = 0.15;
        pos0[1] = 0.15;
        pos0[2] = 0;

        pos1[0] = -0.15;
        pos1[1] = 0.15;
        pos1[2] = 0;
        pos2[0] = 0.15;
        pos2[1] = -0.15;
        pos2[2] = 0;
        rw::math::Transform3D<double> pos0Trans(pos0);
        rw::math::Transform3D<double> pos1Trans(pos1);
        rw::math::Transform3D<double> pos2Trans(pos2);
        double u0,v0,u1,v1,u2,v2;
        Eigen::MatrixXd Jtmp(6,6);
        const double wTau = dt-tau;
        /******** Create transformation matrix for marker *********/
        const rw::math::Vector3D<double> pos(X[i],Y[i],Z[i]);               // Load XYZ from .txt file
        const rw::math::RPY<double> rot(Roll[i],Pitch[i],Yaw[i]);           // Load RPY from .txt file
        const rw::math::Transform3D<double> newPos(pos,rot.toRotation3D()); // Set the marker to the new transformation matrix

        marker->setTransform(newPos,_state);        // update RobWorkStudio
        getRobWorkStudio()->setState(_state);       // debug



        const rw::math::Transform3D<double> postTrans = marker->getTransform(_state);//get the transform matrix after the update
        const rw::math::Transform3D<double> marker2world = Kinematics::frameTframe(marker, worldFrame,_state);     //TransMat for Marker to world frame
        const rw::math::Transform3D<double> camera2marker = Kinematics::frameTframe(cameraF, marker,_state);       //TransMat Camera to Marker




        rw::math::Vector3D<double> markerPos0MarkerF = pos0Trans * marker2world*postTrans.P();      // Position vector made of  Makerframe,CurrentPosition and a pos
        rw::math::Vector3D<double> markerPos1MarkerF = pos1Trans * marker2world*postTrans.P();      // Position vector made of  Makerframe,CurrentPosition and a pos
        rw::math::Vector3D<double> markerPos2MarkerF = pos2Trans * marker2world*postTrans.P();      // Position vector made of  Makerframe,CurrentPosition and a pos

        rw::math::Vector3D<double> markerPos0CameraF = camera2marker*markerPos0MarkerF;             // Position Vector made of new newPos vector and the pos between camera and marker
        rw::math::Vector3D<double> markerPos1CameraF = camera2marker*markerPos1MarkerF;             // Position Vector made of new newPos vector and the pos between camera and marker
        rw::math::Vector3D<double> markerPos2CameraF = camera2marker*markerPos2MarkerF;             // Position Vector made of new newPos vector and the pos between camera and marker



        double x0 =  markerPos0CameraF[0];      // Marker frames pos in cameraframe
        double y0 =  markerPos0CameraF[1];      // Marker frames pos in cameraframe
        double x1 =  markerPos1CameraF[0];      // Marker frames pos in cameraframe
        double y1 =  markerPos1CameraF[1];      // Marker frames pos in cameraframe
        double x2 =  markerPos2CameraF[0];      // Marker frames pos in cameraframe
        double y2 =  markerPos2CameraF[1];      // Marker frames pos in cameraframe
        u0 = fLenght*x0/z;                  // Mapping to image domian
        v0 = fLenght*y0/z;                  // Mapping to image domian
        u1 = fLenght*x1/z;                  // Mapping to image domian
        v1 = fLenght*y1/z;                  // Mapping to image domian
        u2 = fLenght*x2/z;                  // Mapping to image domian
        v2 = fLenght*y2/z;                  // Mapping to image domian
        double pos0u = fLenght*(-pos0(0))/z;    // Mapping to image domian
        double pos0v = fLenght*pos0(1)/z;       // Mapping to image domian
        double pos1u = fLenght*(-pos1(0))/z;    // Mapping to image domian
        double pos1v = fLenght*pos1(1)/z;       // Mapping to image domian
        double pos2u = fLenght*(-pos2(0))/z;    // Mapping to image domian
        double pos2v = fLenght*pos2(1)/z;       // Mapping to image domian
        Eigen::VectorXd dudv(6);
        dudv(0) =  - u0;                // "Error" / displacement
        dudv(1) =  - v0;                // "Error" / displacement
        dudv(0) = pos0u - u0;           // "Error" / displacement
        dudv(1) = pos0v - v0;           // "Error" / displacement
        dudv(2) = pos1u - u1;           // "Error" / displacement
        dudv(3) = pos1v - v1;           // "Error" / displacement
        dudv(4) = pos2u - u2;           // "Error" / displacement
        dudv(5) = pos2v - v2;           // "Error" / displacement
        calcEuclidean(dudv);
        auto Jimage0 = calcJacobianImage(z,u0,v0,fLenght).e();
        auto Jimage1 = calcJacobianImage(z,u1,v1,fLenght).e();
        auto Jimage2 = calcJacobianImage(z,u2,v2,fLenght).e();


        Jtmp.row(0) << Jimage0.row(0);
        Jtmp.row(1) << Jimage0.row(1);
        Jtmp.row(2) << Jimage1.row(0);
        Jtmp.row(3) << Jimage1.row(1);
        Jtmp.row(4) << Jimage2.row(0);
        Jtmp.row(5) << Jimage2.row(1);
        auto Jimage = rw::math::Jacobian(Jtmp);
        log().info()<<"Jimage\n"<<Jimage<<"\n";
        // Gets transform from base to tool
        auto base2cameraF = _device->baseTframe(cameraF, _state);

        /*********  S(q) ***************/
        auto RBaseTool = base2cameraF.R().inverse();
        auto S = rw::math::Jacobian(RBaseTool);

        /********* Robot Jacobian ********************/
        auto J = _device->baseJframe(cameraF, _state); // Returns jacobian from tool to base frame.

        /******** Zimage *******************/
        auto Zimage = (Jimage*S*J).e();                     // Calculate Zimage with Morse-Penrose inverse
        auto ZimageT = Zimage.transpose();
        auto Zimage_tmp = ZimageT * (Zimage*ZimageT).inverse();
        auto dq = Zimage_tmp*dudv;

        log().info()<<"J\n"<<J<<"\n";
        log().info()<<"Zimage\n"<<Zimage<<"\n";
        log().info()<<"dq\n"<<dq<<"\n";
        // Get current robot configuration
        auto q_cur = _device->getQ(_state);
        log().info()<<"q_cur\n"<<q_cur<<"\n";

        // Account for Tau

        // Set max vel
        rw::math::Q dq_constrained = maxVel(rw::math::Q(dq), wTau);

        // Add the change in robot configuration
        q_cur += rw::math::Q(dq_constrained);

        _device->setQ(q_cur, _state);
        getRobWorkStudio()->setState(_state);

        static int count =0;
        if(i!=size-1){
            log().info()<<"log data: "<<count<<"\n";
//            errorLog3P<<dudv(0)<<","<<dudv(1)<<dudv(2)<<","<<dudv(3)<<dudv(4)<<","<<dudv(5)<<"\n";
            JointPosAndToolPos3P<<q_cur<<","<<postTrans.P()<<"\n";
            count ++;
            i++;
        }
        if(i == size-1){

//            log().info()<<"Biggest Euclideain "<<findBiggestEuclidean(dudvEuclideanDistance3P)<<"\n";
            errorLog3P<<findBiggestEuclidean(dudvEuclideanDistance3P);

            errorLog3P.close();
            JointPosAndToolPos3P.close();
            JointLimitAndVelocities3P.close();
            _timer->stop();
        }

    }

}
rw::math::Q SamplePlugin::maxVel(rw::math::Q dq, float dt){

    auto maxQvel = _device->getVelocityLimits();
    auto cur_velocity = dq/dt;
    JointLimitAndVelocities<<maxQvel<<","<<cur_velocity<<"\n";
    JointLimitAndVelocities3P<<maxQvel<<","<<cur_velocity<<"\n";

    for(int i = 0; i < dq.size(); i++){
        if( abs(dq[i]/dt) >= abs(maxQvel[i]) ){
                dq[i] = (dq[i]/abs(dq[i]) )*maxQvel[i]*dt;
        }
    }
    return dq;
}
void SamplePlugin::stateChangedListener(const State& state) {
  _state = state;
}
