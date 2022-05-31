//James Rogers Jan 2022 (c) Plymouth University
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

using namespace std;
using namespace cv;

int main(){
    string PathToFolder = "../Task1/Image/";
    string PathToImage = PathToFolder+"320x240.png";
    Mat Image=imread(PathToImage);
    int errorstack = 0, maxstack = 0, maxpostion = 0, stack[15];
    for(int i=0; i < 15; i++) stack[i] = 0;

    for(int y=0; y<=240; y++){
        for(int x=0; x<=320; x++){

            Vec3b PixelValue = Image.at<Vec3b>(y,x);
            int sort[3] = {(int)PixelValue[0], (int)PixelValue[1], (int)PixelValue[2]};
            for(int i=1; i<3; i++){
                if(sort[0] < sort[i]){
                    int sort_temp = sort[0];
                    sort[0] = sort[i], sort[i] = sort_temp;
                }
            }

            if(sort[0] - sort[2] > 50 && sort[0] == (int)PixelValue[0]){
                if(x <= 30 && x > 10) stack[0] += 1;
                else if(x <= 50 && x > 30) stack[1]++;
                else if(x <= 70 && x > 50) stack[2]++;
                else if(x <= 90 && x > 70) stack[3]++;
                else if(x <= 110 && x > 90) stack[4]++;
                else if(x <= 130 && x > 110) stack[5]++;
                else if(x <= 150 && x > 130) stack[6]++;
                else if(x <= 170 && x > 150) stack[7]++;//centre
                else if(x <= 190 && x > 170) stack[8]++;
                else if(x <= 210 && x > 190) stack[9]++;
                else if(x <= 230 && x > 210) stack[10]++;
                else if(x <= 250 && x > 230) stack[11]++;
                else if(x <= 270 && x > 250) stack[12]++;
                else if(x <= 290 && x > 270) stack[13]++;
                else if(x <= 310 && x > 290) stack[14]++;
                else errorstack++;
            }
        }
    }
    for (int x = 0; x < 15; x++){
        if (stack[x] > maxstack){
            maxstack = stack[x];
            maxpostion = x;
        }
    }
    cout<<"maxpostion ="<<maxpostion<<endl;
    cout<<"maxstack ="<<maxstack<<endl;
    while(waitKey(10)!='x'){
        imshow("Image",Image);
    }
}
