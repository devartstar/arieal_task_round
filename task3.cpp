#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;
int radius=5;
//Mat img = imread("/home/devjit/Desktop/TaskRound ARK/flappy.png",1);
int check_block(Mat img)	//checking if there is a block present in the screen
{
	int i,j,count=0;
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<Vec3b>(i,j)[1]==255)
			{
				count=1;
			}
		}
	}
	return count;
}
void back_block(Mat img)		//BUIDING A BLOCK IN THE SCREEN WHENEVER THE BLOCK PRESENT GOES PAST
{
	int row=img.rows;
	int col=img.cols;
	int i,j;
	int random=rand();
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if( j>(col-20) && j<(col-5) )		//making block of width 15 pixels on the right end
			{									
				if(i<(random%(row/2)-30) && i>(random%(row/2)+30))	//the gap between the upeer and lower block varies
					img.at<Vec3b>(i,j)=(0,255,0);
			}

		}
	}
}
Mat move_screen(Mat img)	//moving the block from right to left
{
	int i,j;
	Mat img1(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(j==0)
			{
				img.at<Vec3b>(i,j)=img1.at<Vec3b>(i,img.cols-1);
			}
			else
			{
				img.at<Vec3b>(i,j)=img1.at<Vec3b>(i,j-1);	
			}
		}
	}
	return img1;
}
int check_collison(Mat img,int ci,int cj)	//checking if there id collision between the circle and the block
{											//checking for collision (0 IF NO COLLISION AND 1 FOR COLLISION)
	int i,j;
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			if(img.at<Vec3b>(i,j)[1]==255 && pow(ci-i,2)+pow(cj-j,2)<=pow(radius,2))
			{
				cout<<"collision";
				return 1;
			}
			else
				return 0;
		}
	}
}

//########################################################################################################
Mat detectAndDraw( Mat& img, CascadeClassifier& cascade,CascadeClassifier& nestedCascade,double scale) 
{ 										//using the sample code to detect and make circle at the eye position
    vector<Rect> faces, faces2; 
    Mat gray, smallImg; 
  
    cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale 
    double fx = 1 / scale; 
  
    // Resize the Grayscale Image  
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );  
    equalizeHist( smallImg, smallImg ); 
  
    // Detect faces of different sizes using cascade classifier  
    cascade.detectMultiScale( smallImg, faces, 1.1,  
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 
  
    // Draw circles around the faces 
    for ( size_t i = 0; i < faces.size(); i++ ) 
    { 
        Rect r = faces[i]; 
        Mat smallImgROI; 
        vector<Rect> nestedObjects; 
        Point center; 
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool 
        int radius,collision=0; 
  
        double aspect_ratio = (double)r.width/r.height; 
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 ) 
        { 
            center.x = cvRound((r.x + r.width*0.5)*scale); 
            center.y = cvRound((r.y + r.height*0.5)*scale); 
            radius = cvRound((r.width + r.height)*0.25*scale); 
            circle( img, center, radius, color, 3, 8, 0 ); 
        } 
        else
            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)), 
                    cvPoint(cvRound((r.x + r.width-1)*scale),  
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0); 
        if( nestedCascade.empty() ) 
            continue; 
        smallImgROI = smallImg( r ); 
          
        // Detection of eyes int the input image 
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2, 
                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) );  
          
        // Draw circles around eyes 
        for ( size_t j = 0; j < nestedObjects.size() && collision!=1 ; j++ )  
        { 
            Rect nr = nestedObjects[j]; 
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale); 
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale); 
            radius = cvRound((nr.width + nr.height)*0.25*scale); 
            circle( img, center, radius, color, 3, 8, 0 ); 

            collision=check_collision(img,center.x,center.y);	//checking for collision (0 IF NO COLLISION AND 1 FOR COLLISION)
			if(collision==1)
			{	
				waitKey(0);		//game stops if collision happens		
			}
			imshow("FLAPPY BIRD",img);
			waitKey(100);
	        } 
    } 
  
    return img; 
} 

//#########################################################################################################


int main(int argc, char const *argv[])
{
	int check,collision,score=0,count=0;
	namedWindow("FLAPPY BIRD",WINDOW_NORMAL);

	//######################################################################################################
	VideoCapture capture;  
    Mat frame, image; 
  
    // PreDefined trained XML classifiers with facial features 
    CascadeClassifier cascade, nestedCascade;  
    double scale=1; 
  
    // Load classifiers from "opencv/data/haarcascades" directory  
    nestedCascade.load( "../../haarcascade_eye_tree_eyeglasses.xml" ) ; 
  
    // Change path before execution  
    cascade.load( "../../haarcascade_frontalcatface.xml" ) ;  
  
    // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 
    capture.open(0);  
    if( capture.isOpened() ) 
    { 
        // Capture frames from video and detect faces 
        cout << "Face Detection Started...." << endl; 
        while(1) 
        { 
            capture >> frame; 
            if( frame.empty() ) 
                break; 
            Mat frame1 = frame.clone(); 
            image=detectAndDraw( frame1, cascade, nestedCascade, scale );  
            char c = (char)waitKey(10); 

        check=check_block(image);
		if(count!=1)
		{
			back_block(image);
			score+=1;	//everytime a new block generated then increasing the score
			cout<<"SCORE"<<score;
		}
		image=move_screen(image);

		
          
            // Press q to exit from window 
            if( c == 27 || c == 'q' || c == 'Q' )  
                break; 
        } 
    } 
    else
        cout<<"Could not Open Camera";
    
	return(0);
}

