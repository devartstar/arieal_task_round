#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;
using namespace cv;
int radius = 50;
int rows=1000,cols=1000;

// making an image on which the program works

/*

void make_center_line(int xr,int yr,int xg,int yg,int xb,int yb)
{
		img2.at<Vec3b>(xr,yr)={255,0,0};
		img2.at<Vec3b>(xg,yg)={0,255,0};
		img2.at<Vec3b>(xb,yb)={0,0,255};
}
*/
Mat make_ball(int xr,int yr,int xg,int yg,int xb,int yb) // make the images of the ball at evrey moment of time
{
	int i,j;
	Mat img3(rows,cols,CV_8UC3,Scalar(0,0,0));
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			if(((i-yr)*(i-yr)+(j-xr)*(j-xr)) < radius*radius)	//making the red circle(ball)
				img3.at<Vec3b>(i,j)={255,0,0};	
			if(((i-yg)*(i-yg)+(j-xg)*(j-xg)) < radius*radius)	//maknig the green circle(bal)
				img3.at<Vec3b>(i,j)={0,255,0};
			if(((i-yb)*(i-yb)+(j-xb)*(j-xb)) < radius*radius)	//making the blue circle(bal)
				img3.at<Vec3b>(i,j)={0,0,255};
		}
	}
	return img3;
}
int rng_collision(int xr,int yr,int xg,int yg,int rm,int gm)
{
	int angle = 0;
	if(rm==1)//red ball is moving)
	{
		angle=atan((yg-yr)/(xg-xr));	//this is for red collide with green and red stops green moves
	}
	//similarly for green collide with red
	if(gm==1)//green ball moving
	{
		angle=atan((yr-yg)/(xr-xg));	//this is for red collide with green and red stops green moves
	}
	return angle;

}
int gnb_collision(int xg,int yg,int xb,int yb,int gm,int bm)
{
	int angle = 0;
	if(gm==1)//green ball is moving)
	{
		angle=atan((yb-yg)/(xb-xg));	//this is for green collide with blue and green stops blue moves
	}
	//similarly for blue collide with green
	if(bm==1)//blue ball is moving)
	{
		angle=atan((yg-yb)/(xg-xb));	//this is for blue collide with green and blue stops green moves
	}
	return angle;
	
}
int bnr_collision(int xb,int yb,int xr,int yr,int bm,int rm)
{
	int angle = 0;
	if(rm==1)//red ball is moving)
	{
		angle=atan((yb-yr)/(xb-xr));	//this is for red collide with blue and red stops blue moves
	}
	//similarly for blue collide with red
	if(bm==1)//blue ball is moving)
	{
		angle=atan((yr-yb)/(xr-xb));	//this is for blue collide with red and blue stops red moves
	}
	return angle;
	
}
int vertwall_collision(int angle) // ball collidin with the wall on left and right
{
	if(angle<=180)
	{
		angle=180-angle;	//the new angle with which the ball moves
	}
	if(angle>180 && angle<360)
	{
		angle=angle-180;
	}
	return angle;
}
int horiwall_collision(int angle)	// ball colliding with the wall on the top and the bottom
{

	angle=360-angle;			//the new angle with which the ball moves
	return angle;
}

// 1--RED AND GREEN BALL COLLISION
// 2--GREEN AND BLUE BALL COLLISION
// 3--BLUE AND RED BALL COLLISION

int check_ball_collision(int xr,int yr,int xg,int yg,int xb,int yb)
{
	if(pow((xr-xg),2)+pow((yr-yg),2) < 4*pow(radius,2))
	{	cout << "RED AND GREEN BALL COLLISION";
		return 1;	
	}
	if(pow((xg-xb),2)+pow((yg-yb),2) < 4*pow(radius,2))
	{
		cout << "GREEN AND BLUE BALL COLLISION";
		return 2;
	}
	if(pow((xb-xr),2)+pow((yb-yr),2) < 4*pow(radius,2))
	{
		cout << "BLUE AND RED BALL COLLISION";
		return 3;
	}
	else 
		return 0;

}


										
void ball_motion(int *angle,int *x,int *y)	//	finding the nest closest pixtel from the line formlae tan(angle)=y/x
{												//(0 to 180)---upward motion
												//(180 to 360)---downward motion 
	if(*angle<=90 && *angle>=270)
	{	
						//considering the unit length to be of 3 units(can be changed) ie the circle moves by 3 units 
		if(*x+1+radius>=cols)
		{
			*angle=vertwall_collision(*angle);	//right vertical wall collision
		}
		*x=*x+1;
		if(*angle>=0 && *angle<=180)			//using pointer so that all the values of x,y,angle gets changed
		{
			
			
			if(*y-1*abs(tan(*angle))-radius<=0)
			{
				*angle=horiwall_collision(*angle);
			}
			*y=*y-1*abs(tan(*angle));
		}
		else
		{
			
			if(*y+1*abs(tan(*angle))+radius>=rows)
			{
				*angle=horiwall_collision(*angle);
			}
			*y=*y+1*abs(tan(*angle));
		}
	}
	if(*angle>=90 && *angle<=270)
	{
					//considering the unit length to be of 1 units(can be changed) ie the circle moves by 1 units 
		if(*x-1-radius<=0)
		{
			*angle=vertwall_collision(*angle);	//left vertical wall collision
		}
		*x=*x-1;
		if(*angle>=0 && *angle<=180)
		{
			
			if(*y-1*abs(tan(*angle))-radius<=0)
			{
				*angle=horiwall_collision(*angle);
			}
			*y=*y-1*abs(tan(*angle));

		}
		else
		{
			
			if(*y+1*abs(tan(*angle))+radius>=rows)
			{
				*angle=horiwall_collision(*angle);
			}
			*y=*y+1*abs(tan(*angle));
		}
	}
	

}


int main()
{
	int xr,yr,xb,yb,xg,yg,collision_no=0,a,angle;
	Mat img3(rows,cols,CV_8UC3,Scalar(0,0,0));

	xr=600;yr=500;  //intializing the positions of the balls
	xg=700;yg=400;
	xb=300;yb=100;
  	angle=90;

  	int rm,gm,bm;
  	rm=1;gm=0;bm=0;

  	namedWindow("billard1",WINDOW_NORMAL);
	

  	while(collision_no!=8000)
  	{
  		
  		img3=make_ball(xr,yr,xg,yg,xb,yb);
  		a=check_ball_collision(xr,yr,xg,yg,xb,yb); //a contains the value of the ball which has collided

// a=1--RED AND GREEN BALL COLLISION
// a=2--GREEN AND BLUE BALL COLLISION
// a=3--BLUE AND RED BALL COLLISION

  		if(a==1)
  		{
  			collision_no++;
  			angle=rng_collision(xr,yr,xg,yg,rm,gm);
  			if(rm==1)
  			{
  				rm=0;gm=1;bm=0;
  				xg+=1;
  				yg+=1;
  				ball_motion(&angle,&xg,&yg);
  			}
  			else
  			{
  				rm=1;gm=0;bm=0;
  				xr+=1;
  				yr+=1;
  				ball_motion(&angle,&xr,&yr);
  			}
  		}

  		if(a==2)
  		{
  			collision_no++;
  			angle=gnb_collision(xg,yg,xb,yb,gm,bm);
  			if(gm==1)
  			{
  				rm=0;gm=0;bm=1;
  				xb+=1;
  				yb+=1;
  				ball_motion(&angle,&xb,&yb);
  			}
  			else
  			{
  				rm=0;gm=1;bm=0;
  				xg+=1;
  				yg+=1;
  				ball_motion(&angle,&xg,&yg);
  			}
  		}

  		if(a==3)
  		{
  			collision_no++;
  			angle=bnr_collision(xb,yb,xr,yr,bm,rm);
  			if(bm==1)
  			{
  				rm=1;gm=0;bm=0;
  				xr+=1;
  				yr+=1;
  				ball_motion(&angle,&xr,&yr);
  			}
  			else
  			{
  				rm=0;gm=0;bm=1;
  				xb+=1;
  				yb+=1;
  				ball_motion(&angle,&xb,&yb);
  			}
  		}
  		if(a==0)
  		{
  			if(rm==1)
  			{
  				cout<<angle;
  				ball_motion(&angle,&xr,&yr);	
  			}
  			if(bm==1)
  			{
  				ball_motion(&angle,&xb,&yb);	
  			}
  			if(gm==1)
  			{
  				ball_motion(&angle,&xg,&yg);	
  			}
  		}
  		imshow("billard1",img3 );
  		
  		waitKey(1);

  	}

}
