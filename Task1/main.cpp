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
    for(int n=0; n<30; ++n){

        //Each image is named 0.png, 1.png, 2.png, etc. So generate the image file path based on n and the folder path
        string PathToImage = PathToFolder+to_string(n)+".png";

        cout<<PathToImage<<endl;

        //Load car image at the file paths location
        Mat Car=imread(PathToImage);

        //Your code goes here. The example code below shows you how to read the red, green, and blue colour values of the
        //pixel at position (0,0). Modify this section to check not just one pixel, but all of them in the 640x480 image
        //(using for-loops), and using the RGB values classifiy if a given pixel looks red, green, blue, or other.
        int PixelsR = 0, PixelsG = 0, PixelsB = 0, Other = 0;

        for(int ydx=0; ydx<y+1; ydx++){
            for(int xdx=0; xdx<x+1; xdx++){
                Vec3b PixelValue = Car.at<Vec3b>(ydx,xdx); //check current pixel RGBs
                int sort[3] = {(int)PixelValue[0], (int)PixelValue[1], (int)PixelValue[2]};
                for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
                    if(sort[0] < sort[i]){
                        int sort_temp = sort[0];
                        sort[0] = sort[i];    //check if bigger than previous, if so, becomes new max
                        sort[i] = sort_temp;
                    }
                }
                if(sort[0]-sort[2] >= 50){                 //check if max is much larger than min, if so check which color is max
                    if(sort[0] == (int)PixelValue[0]) PixelsB++;
                    else if(sort[0] == (int)PixelValue[1]) PixelsG++;
                    else if(sort[0] == (int)PixelValue[2]) PixelsR++;
                }else Other++;                               //if max and min close together, pixel is not R, G or B
            }
        }

        for(int ydx=y*0.25; ydx<(y+1)*0.75; ydx++){
            for(int xdx=x*0.25; xdx<(x+1)*0.75; xdx++){
                Vec3b PixelValue = Car.at<Vec3b>(ydx,xdx); //check current pixel RGBs
                int sort[3] = {(int)PixelValue[0], (int)PixelValue[1], (int)PixelValue[2]};
                for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
                    if(sort[0] < sort[i]){
                        int sort_temp = sort[0];
                        sort[0] = sort[i];    //check if bigger than previous, if so, becomes new max
                        sort[i] = sort_temp;
                    }
                }
                if(sort[0]-sort[2] >= 50){                 //check if max is much larger than min, if so check which color is max
                    if(sort[0] == (int)PixelValue[0]) PixelsB++;
                    else if(sort[0] == (int)PixelValue[1]) PixelsG++;
                    else if(sort[0] == (int)PixelValue[2]) PixelsR++;
                }else Other++;                               //if max and min close together, pixel is not R, G or B
            }
        }

        cout<<"PixelsR "<<PixelsR<<endl;
        cout<<"PixelsG "<<PixelsG<<endl;
        cout<<"PixelsB "<<PixelsB<<endl;
        cout<<"Other "<<Other<<endl;

        int sort[3] = {PixelsB, PixelsG, PixelsR};
        for(int i=1; i<3; i++){                    //sort with 0 as max and 2 as min
            if(sort[0] < sort[i]){
                int sort_temp = sort[0];
                sort[0] = sort[i];    //check if bigger than previous, if so, becomes new max
                sort[i] = sort_temp;
            }
        }
        if(sort[0]-sort[2] >= 50){                 //check if max is much larger than min, if so check which color is max
            if(sort[0] == PixelsB) cout<<"The car is blue"<<endl;
            else if(sort[0] == PixelsG) cout<<"The car is green"<<endl;
            else if(sort[0] == PixelsR) cout<<"The car is red"<<endl;
        }

        //display the car image until x is pressed
        while(waitKey(10)!='x'){
            imshow("Car", Car);
        }

    }

}




















