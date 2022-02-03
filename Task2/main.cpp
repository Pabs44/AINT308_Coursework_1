//James Rogers Jan 2022 (c) Plymouth University
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    VideoCapture InputStream("../Task2/Video.mp4"); //Load in the video as an input stream
    const Point Pivot(592,52);                      //Pivot position in the video

    //Open output file for angle data
    ofstream DataFile;
    DataFile.open("../Task2/Data.csv");

    //Set boundaries for HSV
    int HueLower = 60, HueUpper = 90, SatLower = 50, SatUpper = 255, ValLower = 50, ValUpper = 255;

    //loop through video frames
    while(true){

        //load next frame
        Mat Frame;
        InputStream.read(Frame);

        //if frame is empty then the video has ended, so break the loop
        if(Frame.empty()){
            break;
        }

        //video is very high resolution, reduce it to 720p to run faster
        resize(Frame,Frame,Size(1280,720));

        //======================================================Your code goes here====================================================
        //this code will run for each frame of the video. your task is to find the location of the swinging green target, and to find
        //its angle to the pivot. These angles will be saved to a .csv file where they can be plotted in Excel.
        Mat FrameHSV;
        cvtColor(Frame,FrameHSV,COLOR_BGR2HSV);
        Mat FrameFiltered;
        Vec3b LowerBound(HueLower, SatLower, ValLower);
        Vec3b UpperBound(HueUpper, SatUpper, ValUpper);
        inRange(FrameHSV, LowerBound, UpperBound, FrameFiltered);

        imshow("Filter", FrameFiltered);

        //Calculate center of target
        Moments m = moments(FrameFiltered, true);
        Point p(p.x = m.m10/m.m00, p.y = m.m01/m.m00);
        Point Target(0,0);
        if(m.m00 != 0) Target = p;

        //Draw point and circle at pivot and center of target respectively
        circle(Frame, Target, 20, Scalar(0,255,0), 3);
        circle(Frame, Pivot, 5, Scalar(0,0,255), 5);
        //Draw crosshair on target circle and line between target and pivot
        line(Frame, Point(Target.x-30,Target.y), Point(Target.x+30,Target.y), Scalar(0,255,0), 2);
        line(Frame, Point(Target.x,Target.y-30), Point(Target.x,Target.y+30), Scalar(0,255,0), 2);
        line(Frame, Pivot, Target, Scalar(0,0,255), 2);

        //Calculate angle between target and pivot -> put into .csv
        double Angle = atan2(Target.x - Pivot.x, Target.y - Pivot.y);
        cout << Angle * 180 / M_PI << endl;     //print angle in degrees
        DataFile << Angle << endl;

        //==============================================================================================================================

        //display the frame
        imshow("Video", Frame);
        waitKey(10);
    }

    DataFile.close(); //close output file
}
