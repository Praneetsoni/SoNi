#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

IplImage* ThresholdImage(IplImage* imgHSV){

	IplImage* imgThreshold = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U,1);
	cvInRangeS(imgHSV,cvScalar(38,80,50),cvScalar(75,256,256),imgThreshold);  // thresholds green color
	return imgThreshold;
}

int main(){

	CvCapture* capture=0;
	capture = cvCaptureFromCAM(0);

	if(!capture){
	cout<<"couldn't load the cam"<<endl;
	return -1;
	}

	IplImage* frame=0;
	cvNamedWindow("camfeed");
	cvNamedWindow("output");

	while(1){
	
	frame = cvQueryFrame(capture);

	frame= cvCloneImage(frame);	
	//Smooth(frame,frame,CV_GAUSSIAN,3,3);

	IplImage* imgHSV = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
	cvCvtColor(frame,imgHSV,CV_BGR2HSV);

	IplImage* imgThreshold = ThresholdImage(imgHSV);

	//cvSmooth(imgThreshold,imgThreshold,CV_GAUSSIAN,3,3);

	cvShowImage("camfeed",frame);
	cvShowImage("output",imgThreshold);

	cvReleaseImage(&imgThreshold);
	cvReleaseImage(&imgHSV);
	cvReleaseImage(&frame);

	int x= cvWaitKey(20);

	if((char)x==27){
	break;
	}
	}

	cvDestroyAllWindows();
	cvReleaseCapture(&capture);


}