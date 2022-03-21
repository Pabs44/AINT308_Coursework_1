//James Rogers Jan 2022 (c) Plymouth University
#include <iostream>

#include<opencv2/opencv.hpp>
#include<opencv2/opencv_modules.hpp>

using namespace std;
using namespace cv;

const int y = 480;
const int x = 640;

int main(){

    //Path of image folder
    string PathToFolder = "../Task1/Car Images/";

    //Loop through the 30 car images
    for(int n=0; n<50; ++n){

        //Each image is named 0.png, 1.png, 2.png, etc. So generate the image file path based on n and the folder path
        string PathToImage = PathToFolder+to_string(n)+".png";

        cout<<PathToImage<<endl;

        //Load car image at the file paths location
        Mat Car=imread(PathToImage);

        //Your code goes here. The example code below shows you how to read the red, green, and blue colour values of the
        //pixel at position (0,0). Modify this section to check not just one pixel, but all of them in the 640x480 image
        //(using for-loops), and using the RGB values classifiy if a given pixel looks red, green, blue, or other.

        //3 stacks of RGB pixels, 1 stack for other colors, car color is decided on largest RGB stack
        int PixelsR = 0, PixelsG = 0, PixelsB = 0, Other = 0;

        //Sweep whole image for RGB values of pixels
        for(int ydx=0; ydx<y+1; ydx++){
            for(int xdx=0; xdx<x+1; xdx++){
                Vec3b PixelValue = Car.at<Vec3b>(ydx,xdx); //check current pixel RGBs
                //Sort RGB from max to min to check color with highest value
                int sort[3] = {(int)PixelValue[0], (int)PixelValue[1], (int)PixelValue[2]};
                for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
                    if(sort[0] < sort[i]){                 //check if bigger than previous -> becomes new max
                        int sort_temp = sort[0];           //store old values
                        sort[0] = sort[i];
                        sort[i] = sort_temp;
                    }
                }
                //check if color is distinctively R, G or B -> add to corresponding stack
                if(sort[0]-sort[2] >= 50){
                    if(sort[0] == (int)PixelValue[0]) PixelsB++;
                    else if(sort[0] == (int)PixelValue[1]) PixelsG++;
                    else if(sort[0] == (int)PixelValue[2]) PixelsR++;
                }else Other++;                             //if strongest and weakest colors are too close -> pixel is not R, G or B
            }
        }

        //Sweep center of image (50%) for RGB values of pixels (this weighs the area where the car is by another point)
        for(int ydx=y*0.25; ydx<(y+1)*0.75; ydx++){
            for(int xdx=x*0.25; xdx<(x+1)*0.75; xdx++){
                Vec3b PixelValue = Car.at<Vec3b>(ydx,xdx); //check current pixel RGBs
                //Sort RGB from max to min to check color with highest value
                int sort[3] = {(int)PixelValue[0], (int)PixelValue[1], (int)PixelValue[2]};
                for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
                    if(sort[0] < sort[i]){                 //check if bigger than previous -> becomes new max
                        int sort_temp = sort[0];           //store old values
                        sort[0] = sort[i];
                        sort[i] = sort_temp;
                    }
                }
                //check if color is distinctively R, G or B -> weigh corresponding stack
                if(sort[0]-sort[2] >= 50){
                    if(sort[0] == (int)PixelValue[0]) PixelsB++;
                    else if(sort[0] == (int)PixelValue[1]) PixelsG++;
                    else if(sort[0] == (int)PixelValue[2]) PixelsR++;
                }else Other++;                             //if strongest and weakest colors are too close -> pixel is not R, G or B
            }
        }

        //Print stack sizes to check if conclusion is correct
        cout<<"PixelsR "<<PixelsR<<endl<<"PixelsG "<<PixelsG<<endl<<"PixelsB "<<PixelsB<<endl<<"Other "<<Other<<endl;

        //Sort RGB stacks from max to min to check color with highest value
        int sort[3] = {PixelsB, PixelsG, PixelsR};
        for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
            if(sort[0] < sort[i]){                 //check if bigger than previous -> becomes new max
                int sort_temp = sort[0];           //store old values
                sort[0] = sort[i];
                sort[i] = sort_temp;
            }
        }
        //check if car is distinctively R, G or B -> check which stack is max
        string colorSelect;
        if(sort[0]-sort[2] >= 50){
            if(sort[0] == PixelsB){
                cout<<"The car is blue"<<endl;
                colorSelect = "The car is blue";
            }
            else if(sort[0] == PixelsG){
                cout<<"The car is green"<<endl;
                colorSelect = "The car is green";
            }
            else if(sort[0] == PixelsR){
                cout<<"The car is red"<<endl;
                colorSelect = "The car is red";
            }
        }else cout << "Error: Car is not red, green or blue" << endl;   //return error if car is not R, G or B

        //display the car image until x is pressed
        while(waitKey(10)!='x'){
            putText(Car, colorSelect, Point(10,25),FONT_HERSHEY_COMPLEX,1.0,Scalar(0,0,0),2);
            imshow("Car", Car);
        }

    }

}




















