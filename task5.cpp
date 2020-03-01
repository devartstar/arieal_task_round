#include "/usr/local/include/opencv2/objdetect.hpp" 
#include "/usr/local/include/opencv2/highgui.hpp" 
#include "/usr/local/include/opencv2/imgproc.hpp" 
#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
  
using namespace std; 
using namespace cv;
Mat img1(2000,2000,CV_8UC1,Scalar(0));
Mat img2(2000,2000,CV_8UC1,Scalar(0));
Mat img3(2000,2000,CV_8UC1,Scalar(0));

int main()
{
	ifstream data;
	data.open("/home/devjit/ip/radar_dump.xlsx");

	namedWindow("x vs y",WINDOW_NORMAL);
	namedWindow("y vs z",WINDOW_NORMAL);
	namedWindow("z vs x",WINDOW_NORMAL);

	while(data.good())
	{
		string cordx;	//for storing the x,y,z coordinate which we will get in the form of string
		string cordy;
		string cordz;

		getline(data,cordx,',');	//the text document seperated by ',' or ' ' 
		getline(data,cordy,',');	//reads the value of the string before the comma
		getline(data,cordz,',');

		cout<<cordx<<",";	//displaying the coordinates
		cout<<cordy<<",";
		cout<<cordz<<",";

		float x,y,z;
		x=stof(cordx)*100;	//converting the coordinates to float  
		y=stof(cordy)*100;	//multiplying by 100 as approimated upto 3 places after decimal 
		z=stof(cordz)*100;
		//sscanf(cordx,"%f",&x);
		//sscanf(cordy,"%f",&y);
		//sscanf(cordz,"%f",&z);

		int x1,y1,z1;
		x1=x*100;	//convering into intiger with center of axis at middle to display in iamge
		y1=y*100;
		z1=z*100;

		img1.at<uchar>(1000+x,1000-y)=255;	//displaying the coordinate of aircraft with white pixel
		img2.at<uchar>(1000+y,1000-z)=255;
		img3.at<uchar>(1000+z,1000-x)=255;

		imshow("x vs y",img1);	//plotting three graph to get better view
		imshow("y vs z",img2);	//X vs Y    Y vs Z    Z vs X
		imshow("z vs x",img3);
		waitKey(10);            //the waitkey of 10 millisec gives an idea of the graphs beling plotted as time goes on
	}							//like a video it gives some points in trajectory and some other randomly alloted points

	
} 
