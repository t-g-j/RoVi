/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

#include <opencv2/opencv.hpp>

#include <iostream>
#include "visionmethods.h"

int main(int argc, char* argv[])
{
//    VisionMethods ex2("../ImagesForStudents/Image2.png");
//       //ex2.showImg(1);
//       ex2.greyIntensityTransform(-100, 1);
//       //ex2.showImg(2);
//       ex2.showAllImages();
       VisionMethods mini1("../ImagesForStudents/Image2.png");
       //mini1.showAllImages();
       //mini1.calcHistogram(1);
       mini1.dftFunc(1);
       mini1.showImg(2);
       //mini1.openCVfilter(1);

       return 0;
}
