#include "visionmethods.h"

VisionMethods::VisionMethods(std::string pathToImage)
{
    cv::Mat originalImage = cv::imread(pathToImage);
    if (originalImage.empty())
        {
           std::cout << "Input image not found at '" << pathToImage << "'\n";
        }
    imageVersions.push_back(originalImage);
    imageDescription.push_back("Image 0. Original image");
    cv::Mat greyImg;
    cvtColor(originalImage, greyImg, CV_BGR2GRAY);
    cout << "Stored original image at 0" << endl;
    imageVersions.push_back(greyImg);
    imageDescription.push_back("Image 1. Original image in greyscale");
    cout << "Stored greyscale version of image at 1" << endl;
    imgCounter = 1;

}

VisionMethods::~VisionMethods()
{
}

void VisionMethods::greyIntensityTransform(int intensityC, int whichImage)
{
    uchar tmp;
    int tmpInt;
    cv::Mat img = imageVersions[1].clone();
    int width = img.cols;
    int height = img.rows;

    for (int x = 0 ; x<width; x++)
        for (int y = 0; y<height; y++)
        {
            tmpInt = img.at<uchar>(x, y);
            if (-1<tmpInt+intensityC<256)
                img.at<uchar>(x, y) = tmpInt+intensityC;
            if (tmpInt + intensityC > 255)
                img.at<uchar>(x, y) = 255;
            if (tmpInt+intensityC < 0)
                img.at<uchar>(x, y) = 0;
        }
    imageVersions.push_back(img);
    imgCounter++;
    ostringstream oss;
    oss << "Image " << imgCounter <<" . Intensity transformed image: " << whichImage << " by a constant of: " << intensityC << endl;
    string description = oss.str();
    cout << description << endl;
    imageDescription.push_back(description);

}

void VisionMethods::calcHistogram(int whichImage)
{

    /*
     * This code is stolen from stack overflow
     */

    cv::Mat tmp = imageVersions[whichImage];
    cv::Mat grayHist;
    int histSize = 256;
    int nimages = 1; // Only 1 image, that is the Mat scene.
    int channels[] = {0} ;// Index for hue channel
    int dims = 1 ;// Only 1 channel, the hue channel
    float hranges[] = { 0, 256 }; // hue varies from 0 to 179, see cvtColor
    const float* ranges = {hranges};
    bool uniform = true;
    bool accumulate = false;

                // Compute the histogram.
     // No mask
    //hist, dims, histSize, ranges, uniform=true);

    // Now hist will contain the counts in each bin.



    cv::calcHist(&tmp,1,0,cv::Mat(),grayHist,1,&histSize,&ranges,uniform,accumulate);
//    cv::imshow("Grey hist",grayHist);
//    cv::waitKey(0);
    const int hist_w = 1024;    //Width of my histogram
    const int hist_h = 500;     //height of my histogram
    const int bin_w = cvRound( (double) hist_w/histSize );//Setting the width of my bin
    cv::Mat histImage(hist_h,hist_w,CV_8UC3,cv::Scalar(255,255,255) );    //Image to contain histogram
    cv::normalize(grayHist,grayHist,0,histImage.rows,cv::NORM_MINMAX,-1,cv::Mat() );//Normalize the "first" histogram

    /*
     * This for loop draws the rettangles that makes up our histogram
     * */
    for(int i = 1; i<histSize+1;i++){
        /* This is a histogram with lines */
        //        cv::line(histImage, cv::Point( bin_w*(i-1), hist_h-cvRound(grayHist.at<float>(i-1))  ),
        //                            cv::Point( bin_w*(i),hist_h - cvRound(grayHist.at<float>(i))  ),
        //                            cv::Scalar(255,0,0),
        //                            1,
        //                            8,
        //                            0);

        /*A retangular histogram */
        cv::rectangle(histImage,    cv::Point(bin_w*(i-1),hist_h-cvRound(grayHist.at<float>(i-1)) ),
                                    cv::Point(bin_w*i,hist_h),
                                    cv::Scalar(255,0,0),
                                    1,8,0 );
    }
    cv::imshow("calcHist",histImage);
    cv::waitKey(0);
}

void VisionMethods::ShowSizedImg(string imgName, int index)
{
    cv::Mat img = imageVersions[index];         //Load the decied image into dummie Mat
    cv::namedWindow(imgName,cv::WINDOW_NORMAL); //Names the output window
    cv::resizeWindow(imgName,1024,720);         //Resizes the windows in the decied size
    cv::imshow(imgName, img);                   // Shows the image

}

void VisionMethods::dftFunc(int index){
    cv::Mat img = imageVersions[index];     //Create a dummie image container

    cv::imshow("original",img);

    //Zero pad for easier DFT
    cv::Mat padded;                            //expand input image to optimal size
    const int m = cv::getOptimalDFTSize( img.rows );
    const int n = cv::getOptimalDFTSize( img.cols ); // on the border add zero pixels
    cv::copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::imshow("padded",padded);

    //Make place for both imagninary and real part
    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    //Make DFT
    dft(complexI, complexI);                    //Making the DFT

    //make imaginary and real values
    cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat magI = planes[0];

    //swith to logarithm scale
    magI += cv::Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    //Crop and rearrange
    magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));
    const int cx = magI.cols/2;
    const int cy = magI.rows/2;

    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);


    //Normalize
    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    //cv::imshow("plane[1]- maybe phase",planes[1]);
    cv::imshow("magI",magI);

    butterWorth(magI,2,300,0);

    cv::waitKey(0);

}
void VisionMethods::butterWorth(cv::Mat paddedImage,int order, int circleRadius, bool filterType){

    cv::Mat tmp = paddedImage;
    cv::Mat filtered;
    //cv::Mat tmp (400,400,CV_8UC1,cv::Scalar(0) );

    cv::Mat filter(tmp.rows,tmp.cols,CV_8UC1,cv::Scalar(0));

    int n = order;                  // The order of filter / "slope of change"
    int D_zero = circleRadius;      //Radius for were the filter should be applied
    float D = 0;                    //Initialze D distance number
    float tmpVar= 0;                //Redundant variable used for math

    /*
     * The double for loops iterate over the whole image
     * */
    if(filterType == 0){
    for(int i = 0 ; i < tmp.rows ; i++){
        for(int j = 0 ; j<tmp.cols; j++){
            D = sqrt(  pow( i - (tmp.rows/2) , 2 )+pow( j - (tmp.cols/2) ,2 ) ); //eq 4.8-2 from Digital proccesing book
            //varTmp = 1 / pow((D_zero/D),2*n) ;
            tmpVar = 1 / pow((D/D_zero),2*n) ;          //Filter variable

            /*
             * This if catches any variables higher then allowed for 8-bit image
             * */
            if(tmpVar > 255){
                tmpVar = 255;
            }
            //filter.at<uchar>(i,j)=    int(varTmp);
            filter.at<uchar>(i,j) = (int)(tmpVar);
            //std::cout<< (int)varTmp<<"  ";
            //std::cout<<D<<"  ";
        }
      //  std::cout<<std::endl;
        }
    //filtered = applyFilter(tmp,filter);
    // Used soley for debugging purposes
//    cv::namedWindow("butterworth filter",cv::WINDOW_NORMAL);
//    cv::imshow("butterworth filter",filtered);
//    cv::waitKey(0);

    }
    else if (filterType == 1){
      for(int i = 0 ; i < tmp.rows ; i++){
        for(int j = 0 ; j<tmp.cols; j++){
            D = sqrt(  pow( i - (tmp.rows/2) , 2 )+pow( j - (tmp.cols/2) ,2 ) ); //eq 4.8-2 from Digital proccesing book

            tmpVar = 1 / 1 / pow((D_zero/D),2*n) ;          //Filter variable
            /*
             * This if catches any variables higher then allowed for 8-bit image
             * */
            if(tmpVar > 255){
                tmpVar = 255;
            }
            //filter.at<uchar>(i,j)=    int(varTmp);
            filter.at<uchar>(i,j) = (int)(tmpVar);
            //std::cout<< (int)varTmp<<"  ";
            //std::cout<<D<<"  ";
        }
      //  std::cout<<std::endl;
        }
    /*
     * Used soley for debugging purposes
    cv::namedWindow("butterworth filter",cv::WINDOW_NORMAL);
    cv::imshow("butterworth filter",filter);
    cv::waitKey(0);
    */
      }
    else{
        std::cout<<"Something went wrong with the choosing of high/low pass choosing"<<std::endl;
    }
}
cv::Mat VisionMethods::applyFilter(cv::Mat originalImage, cv::Mat filter){
    cv::Mat Merged;         //Returned merged image
//    int tmp= 0;             //tmp variable for catching numbers above 255
//    for(int i = 1; i<originalImage.rows-1; i++){
//        for(int j = 1 ; j<originalImage.cols-1; j++){
//            tmp = originalImage.at<uchar>(i,j) * filter.at<uchar>(i,j);
//            if(tmp > 255){
//                tmp = 255;
//            }
//            std::cout<<tmp<<"  ";
////            Merged.at<uchar>(i,j)=tmp;
//        }
//        std::cout<<std::endl;
//    }
    Merged = originalImage.mul(filter);
    return Merged;
}

void VisionMethods::openCVfilter(int index){

    cv::Mat img = imageVersions[index];     //load image into container
    cv::Mat filtred;                        //Empty container for filtered image

    const int kernel_size = 9; // needs to be either 3,5,7 or 9 etc
    cv::Mat my_kernel = (cv::Mat_<double>(kernel_size,kernel_size) << 1, 1, 1, 1, 1, 1, 1, 1, 1) / ( kernel_size * kernel_size);
    const int depth = 0;
    cv::Point anchor = cv::Point(-1,-1);
    double delta = 0;
    int borderType = cv::BORDER_DEFAULT;

    cv::filter2D(img,filtred,-1,my_kernel,cv::Point(-1,-1),0,cv::BORDER_DEFAULT);
    cv::imshow("openCV filter2D", filtred);
    cv::waitKey(0);
}

//General purpose methods
void VisionMethods::showImg(int index)
{
    cout << "Showing image at index: " << index << endl;
    cv::imshow(imageDescription[index], imageVersions[index]);
    cv::waitKey();
}


void VisionMethods::showAllImages()
{
    for (int i = 0; i < imageVersions.size(); i++)
    {
        cv::namedWindow(imageDescription[i], cv::WINDOW_NORMAL);
        cv::imshow(imageDescription[i], imageVersions[i]);
    }
    cv::waitKey();
}
