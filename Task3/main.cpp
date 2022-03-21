//James Rogers Jan 2021 (c) Plymouth University
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){

    //Path to image file
    string Path = "../Task3/PCB Images/";

    //loop through component images
    for(int n=0; n<10; ++n){

        //read PCB and component images
        Mat PCB = imread(Path+"PCB.png");
        Mat Component = imread(Path+"Component"+to_string(n)+".png");

        //================Your code goes here=====================
        //Output match image
        Mat ImageMatch;
        matchTemplate(PCB, Component, ImageMatch, TM_SQDIFF_NORMED);

        //Location and values of matching section
        double MinVal, MaxVal;
        Point MinLoc, MaxLoc;
        minMaxLoc(ImageMatch, &MinVal, &MaxVal, &MinLoc, &MaxLoc);

        //Check if matched pixels are below acceptable minimum
        if(MinVal > 0.009) cout << "\nError: Component not found" << endl; //error if above
        else{
            Point CompRect(MinLoc.x + Component.cols, MinLoc.y + Component.rows); //find point to recreate component dimensions
            rectangle(PCB, MinLoc, CompRect, Scalar(0,0,255), 2);                 //trace component if below
        }

        //display the results until x is pressed
        while(waitKey(10)!='x'){
            imshow("Target", Component);
            imshow("PCB", PCB);
        }

    }

}
