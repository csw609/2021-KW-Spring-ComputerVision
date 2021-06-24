#include "sw_vision.h"
#include <iostream>
#include "kfc.h"
#include "algorithm"
#include "QDebug"
#include <random>
#include <fstream>
#include <vector>
#include <queue>
#include <charconv>

SW_vision::SW_vision()
{

}
//RGB영상을 HS값으로 컨트롤 하는 함수
void SW_vision::RGBContHS(KImageColor &icMain, double dHue = 0, double dSat = 0){
    double v;
    double rgbMax;
    double c, x, m;
    double r, g, b;
    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            rgbMax = std::max(std::max(icMain[i][j].r,icMain[i][j].g),icMain[i][j].b);

            v = rgbMax / 255;

            c = v * dSat;
            x = c*(1-std::abs(fmod(dHue/60,2) - 1 ));
            m = v - c;

            if(dHue >= 0 && dHue < 60){
                r = c; g = x; b = 0;
            }
            else if(dHue >= 60 && dHue < 120){
                r = x; g = c; b = 0;
            }
            else if(dHue >= 120 && dHue < 180){
                r = 0; g = c; b = x;
            }
            else if(dHue >= 180 && dHue < 240){
                r = 0; g = x; b = c;
            }
            else if(dHue >= 240 && dHue < 300){
                r = x; g = 0; b = c;
            }
            else if(dHue >= 300 && dHue < 360){
                r = c; g = 0; b = x;
            }
            icMain[i][j].r = (r + m) * 255;
            icMain[i][j].g = (g + m) * 255;
            icMain[i][j].b = (b + m) * 255;

        }
    }
}
void SW_vision::RGBtoH(KImageColor &icMain, KImageGray &hueImage){
    double rgbMax;
    double rgbMin;
    double r,g,b;

    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            double dHue = 0.0;
            r = (double)icMain[i][j].r;
            g = (double)icMain[i][j].g;
            b = (double)icMain[i][j].b;
            rgbMax = (double)std::max(std::max(r,g),b);
            rgbMin = (double)std::min(std::min(r,g),b);
            if(rgbMax == r){
                dHue = 60.0 * (g - b) / (rgbMax-rgbMin) + 0.0;
            }
            else if(rgbMax == g){
                dHue = 60.0 * (b - r) / (rgbMax-rgbMin) + 120.0;
            }
            else if(rgbMax == b){
                dHue = 60.0 * (r - g) / (rgbMax-rgbMin) + 240.0;
            }
            dHue = dHue / 360.0;
            dHue = dHue * 255.0;
            hueImage[i][j] = dHue;
        }
    }
}

void SW_vision::RGBtoS(KImageColor &icMain, KImageGray &satImage){
    double rgbMax;
    double rgbMin;
    double r,g,b;
    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            double dSat = 0.0;
            r = (double)icMain[i][j].r;
            g = (double)icMain[i][j].g;
            b = (double)icMain[i][j].b;
            rgbMax = (double)std::max(std::max(r,g),b);
            rgbMin = (double)std::min(std::min(r,g),b);

            dSat = (rgbMax - rgbMin) / rgbMax;
            satImage[i][j] = dSat * 255;
        }
    }
}
void SW_vision::RGBtoV(KImageColor &icMain, KImageGray &valImage){
    double rgbMax;
    //double rgbMin;
    double r,g,b;
    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            //double dSat = 0.0;
            r = (double)icMain[i][j].r;
            g = (double)icMain[i][j].g;
            b = (double)icMain[i][j].b;
            rgbMax = (double)std::max(std::max(r,g),b);
            //rgbMin = (double)std::min(std::min(r,g),b);
            valImage[i][j] = rgbMax;
        }
    }
}
void SW_vision::RGBThreshHolding(KImageGray &icMain, KImageGray &gray){

    double T[256] = {0,}, mean1[256]= {0,}, mean2[256]= {0,}, cov1[256]= {0,}, cov2[256] = {0,};
    double NoP = icMain.Row() * icMain.Col();
    double BCV[256] ={0,};
    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            gray[i][j] = icMain[i][j];
            T[gray[i][j]]++;
       }
    }
    //평균
    for(int i = 0; i < 256; i++){
        int num1 = 0, num2 =0;

        for(int j = 0; j < 256; j++){
            if(j+1 > i){
                mean1[i] += T[j] * (j);
                num1 += T[j];
            }
            else{
                mean2[i] += T[j] * (j);
                num2 += T[j];
            }
        }
        mean1[i] /= num1;
        mean2[i] /= num2;
        //qDebug() << mean1[i] << "/" << mean2[i];
        //between-Class Variance
        BCV[i] = (num1/NoP) * (num2/NoP) * (mean1[i] - mean2[i]) * (mean1[i] - mean2[i]);
    }

    unsigned char t = 0;
    double tmp = 0;

    //Between-Class Variance 최대값 탐색
    for(int i = 0; i < 256; i++){

        if(BCV[i] > tmp){
            t = i;
            tmp = BCV[i];
        }
    }

    for(unsigned int i  = 0; i < icMain.Row(); i++){
        for(unsigned int j = 0; j < icMain.Col(); j++){
            if(gray[i][j] > t) gray[i][j] = 255;
            else gray[i][j] = 0;
       }
    }


}

void SW_vision::GrayLabeling_8(KImageGray &gray, KImageColor &color){
    unsigned char fore = 255;
    unsigned char back = 0;

    for(unsigned int i = 1; i < gray.Row()-1 ;i++){
        for(unsigned int j = 1; j < gray.Col()-1 ;j++){
            // foreground case
            if(gray[i][j] == fore){
                //solo foreground case
                if(gray[i-1][j-1] == back && gray[i-1][j] == back && gray[i][j-1] == back){
                    color[i][j].r = (i * 22 + j) % 256;
                    color[i][j].g = (i * 37 + j) % 256;
                    color[i][j].b = (i * 13 + j) % 256;
                    if(color[i][j].r == 0 && color[i][j].g == 0 && color[i][j].b == 0){
                        color[i][j].r = 140;
                    }
                }
                //top right foreground case
                else if(gray[i-1][j-1] == back && gray[i-1][j] == fore && gray[i][j-1] == back){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                }
                //bottom left foreground case
                else if(gray[i-1][j-1] == back && gray[i-1][j] == back && gray[i][j-1] == fore){
                    if(color[i][j-1].r == 0 && color[i][j-1].g == 0 && color[i][j-1].b == 0)
                    {
                        color[i][j-1].r = (i * 22 + j) % 256;
                        color[i][j-1].g = (i * 37 + j) % 256;
                        color[i][j-1].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i][j-1].r;
                    color[i][j].g = color[i][j-1].g;
                    color[i][j].b = color[i][j-1].b;
                }
                //bottom left, top right foreground case
                else if(gray[i-1][j-1] == back && gray[i-1][j] == fore && gray[i][j-1] == fore){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                        color[i][j-1].r = color[i-1][j].r;
                        color[i][j-1].g = color[i-1][j].g;
                        color[i][j-1].b = color[i-1][j].b;
                        color[i][j].r = color[i-1][j].r;
                        color[i][j].g = color[i-1][j].g;
                        color[i][j].b = color[i-1][j].b;
                }
                //top left foreground case
                else if(gray[i-1][j-1] == fore && gray[i-1][j] == back && gray[i][j-1] == back){
                    if(color[i-1][j-1].r == 0 && color[i-1][j-1].g == 0 && color[i-1][j-1].b == 0)
                    {
                        color[i-1][j-1].r = (i * 22 + j) % 256;
                        color[i-1][j-1].g = (i * 37 + j) % 256;
                        color[i-1][j-1].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i-1][j-1].r;
                    color[i][j].g = color[i-1][j-1].g;
                    color[i][j].b = color[i-1][j-1].b;
                }
                //all foreground case
                else if(gray[i-1][j-1] == fore && gray[i-1][j] == fore && gray[i][j-1] == fore){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                    color[i-1][j-1].r = color[i-1][j].r;
                    color[i-1][j-1].g = color[i-1][j].g;
                    color[i-1][j-1].b = color[i-1][j].b;
                    color[i][j-1].r = color[i-1][j].r;
                    color[i][j-1].g = color[i-1][j].g;
                    color[i][j-1].b = color[i-1][j].b;
                }

                //top left, bottom left fore case
                else if(gray[i-1][j-1] == fore && gray[i-1][j] == back && gray[i][j-1] == fore){
                    if(color[i][j-1].r == 0 && color[i][j-1].g == 0 && color[i][j-1].b == 0)
                    {
                        color[i][j-1].r = (i * 22 + j) % 256;
                        color[i][j-1].g = (i * 37 + j) % 256;
                        color[i][j-1].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i][j-1].r;
                    color[i][j].g = color[i][j-1].g;
                    color[i][j].b = color[i][j-1].b;
                    color[i-1][j].r = color[i][j-1].r;
                    color[i-1][j].g = color[i][j-1].g;
                    color[i-1][j].b = color[i][j-1].b;
                    color[i-1][j-1].r = color[i][j-1].r;
                    color[i-1][j-1].g = color[i][j-1].g;
                    color[i-1][j-1].b = color[i][j-1].b;
                }

                //top left, top right fore case
                else if(gray[i-1][j-1] == fore && gray[i-1][j] == fore && gray[i][j-1] == back){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                    color[i][j-1].r = color[i-1][j].r;
                    color[i][j-1].g = color[i-1][j].g;
                    color[i][j-1].b = color[i-1][j].b;
                }
            }
        }
    }
    //Second Pass
        for(unsigned int i = 1 ; i < gray.Row()-1; i++){
            for(unsigned int j = gray.Col()-2; j > 1 ;j--){
                if(gray[i][j] == fore){
                    //bottom left foreground case
                    if(gray[i-1][j-1] == back && gray[i-1][j] == back && gray[i][j-1] == fore){
                                    color[i][j-1].r = color[i][j].r;
                                    color[i][j-1].g = color[i][j].g;
                                    color[i][j-1].b = color[i][j].b;
                    }
                    //top left, top right foreground case
                    else if(gray[i-1][j-1] == fore && gray[i-1][j] == fore && gray[i][j-1] == back){
                        color[i][j].r = color[i-1][j].r;
                        color[i][j].g = color[i-1][j].g;
                        color[i][j].b = color[i-1][j].b;
                        color[i][j-1].r = color[i-1][j].r;
                        color[i][j-1].g = color[i-1][j].g;
                        color[i][j-1].b = color[i-1][j].b;
                    }
                    //all foreground case
                    else if(gray[i-1][j-1] == fore && gray[i-1][j] == fore && gray[i][j-1] == fore){
                        color[i][j].r = color[i-1][j].r;
                        color[i][j].g = color[i-1][j].g;
                        color[i][j].b = color[i-1][j].b;
                        color[i-1][j-1].r = color[i-1][j].r;
                        color[i-1][j-1].g = color[i-1][j].g;
                        color[i-1][j-1].b = color[i-1][j].b;
                        color[i][j-1].r = color[i-1][j].r;
                        color[i][j-1].g = color[i-1][j].g;
                        color[i][j-1].b = color[i-1][j].b;
                    }
                }
            }
        }
        //Third Pass
        for(unsigned int i = gray.Row()-2 ; i > 1; i--){
            for(unsigned int j = gray.Col()-2; j > 1 ;j--){
                if(gray[i][j] == fore){
                    //bottom left foreground case
                    if(gray[i-1][j-1] == back && gray[i-1][j] == back && gray[i][j-1] == fore){
                                    color[i][j-1].r = color[i][j].r;
                                    color[i][j-1].g = color[i][j].g;
                                    color[i][j-1].b = color[i][j].b;
                    }
                    //top right foreground case
                    else if(gray[i-1][j-1] == back && gray[i-1][j] == fore && gray[i][j-1] == back){
                        color[i-1][j].r = color[i][j].r;
                        color[i-1][j].g = color[i][j].g;
                        color[i-1][j].b = color[i][j].b;
                    }
                    //all foreground case
                    else if(gray[i-1][j-1] == fore && gray[i-1][j] == fore && gray[i][j-1] == fore){
                        color[i-1][j].r = color[i][j].r;
                        color[i-1][j].g = color[i][j].g;
                        color[i-1][j].b = color[i][j].b;
                        color[i-1][j-1].r = color[i][j].r;
                        color[i-1][j-1].g = color[i][j].g;
                        color[i-1][j-1].b = color[i][j].b;
                        color[i][j-1].r = color[i][j].r;
                        color[i][j-1].g = color[i][j].g;
                        color[i][j-1].b = color[i][j].b;
                    }
                }
            }
        }
}
void SW_vision::GrayLabeling_4(KImageGray &gray, KImageColor &color){
    unsigned char fore = 255;
    unsigned char back = 0;

    for(unsigned int i = 1; i < gray.Row()-1 ;i++){
        for(unsigned int j = 1; j < gray.Col()-1 ;j++){
            // foreground case
            if(gray[i][j] == fore){
                //solo foreground case
                if(gray[i-1][j] == back && gray[i][j-1] == back){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = (i * 37 + j) % 256;
                    color[i][j].g = (i * 41 + j) % 256;
                    color[i][j].b = (i * 29 + j) % 256;
                }
                //top right foreground case
                else if(gray[i-1][j] == fore && gray[i][j-1] == back){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                }
                //bottom left foreground case
                else if(gray[i-1][j] == back && gray[i][j-1] == fore){
                    if(color[i][j-1].r == 0 && color[i][j-1].g == 0 && color[i][j-1].b == 0)
                    {
                        color[i][j-1].r = (i * 22 + j) % 256;
                        color[i][j-1].g = (i * 37 + j) % 256;
                        color[i][j-1].b = (i * 13 + j) % 256;
                    }
                    color[i][j].r = color[i][j-1].r;
                    color[i][j].g = color[i][j-1].g;
                    color[i][j].b = color[i][j-1].b;
                }
                //bottom left, top right foreground case
                else if(gray[i-1][j] == fore && gray[i][j-1] == fore){
                    if(color[i-1][j].r == 0 && color[i-1][j].g == 0 && color[i-1][j].b == 0)
                    {
                        color[i-1][j].r = (i * 22 + j) % 256;
                        color[i-1][j].g = (i * 37 + j) % 256;
                        color[i-1][j].b = (i * 13 + j) % 256;
                    }
                    color[i][j-1].r = color[i-1][j].r;
                    color[i][j-1].g = color[i-1][j].g;
                    color[i][j-1].b = color[i-1][j].b;
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                    }
                }
            }
        }
    //Second Pass
    for(unsigned int i = 1 ; i < gray.Row()-1; i++){
        for(unsigned int j = gray.Col()-2; j > 1 ;j--){
            if(gray[i][j] == fore){
                //bottom left foreground case
                if(gray[i-1][j] == back && gray[i][j-1] == fore){
                        color[i][j-1].r = color[i][j].r;
                        color[i][j-1].g = color[i][j].g;
                        color[i][j-1].b = color[i][j].b;
                }
                //top right foreground case
                else if(gray[i-1][j] == fore && gray[i][j-1] == back){
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                    color[i][j-1].r = color[i-1][j].r;
                    color[i][j-1].g = color[i-1][j].g;
                    color[i][j-1].b = color[i-1][j].b;
                }
                // all foreground case
                else if(gray[i-1][j] == fore && gray[i][j-1] == fore){
                    color[i][j].r = color[i-1][j].r;
                    color[i][j].g = color[i-1][j].g;
                    color[i][j].b = color[i-1][j].b;
                    color[i][j-1].r = color[i-1][j].r;
                    color[i][j-1].g = color[i-1][j].g;
                    color[i][j-1].b = color[i-1][j].b;
                }
            }
        }
    }
}

void SW_vision::Erosion_color(KImageColor &color, KImageColor &erosion, unsigned char kernelSize){
    KImageColor temp_color(color);
    for(unsigned int i = 1; i < color.Row(); i++){
        for(unsigned int j = 1; j < color.Col(); j++){
            erosion[i][j] = color[i][j];
        }
    }
    if(kernelSize == 3){
        for(unsigned int i = 1; i < color.Row() - 1; i++){
            for(unsigned int j = 1; j < color.Col() - 1; j++){
                if(temp_color[i-1][j-1].r == 0 || temp_color[i-1][j].r == 0 || temp_color[i-1][j+1].r == 0 || temp_color[i][j-1].r == 0 || temp_color[i][j+1].r == 0 || temp_color[i+1][j-1].r == 0 ||
                        temp_color[i+1][j].r == 0 || temp_color[i+1][j+1].r == 0)
                {
                    erosion[i][j].r = 0;
                    erosion[i][j].g = 0;
                    erosion[i][j].b = 0;
                }
            }
        }
    }
    else if(kernelSize == 5){
        for(unsigned int i = 2; i < color.Row() - 2; i++){
            for(unsigned int j = 2; j < color.Col() - 2; j++){
                if(temp_color[i-2][j-2].r == 0 || temp_color[i-2][j-1].r == 0 || temp_color[i-2][j].r == 0 || temp_color[i-2][j+1].r == 0 || temp_color[i-2][j+2].r == 0 ||
                        temp_color[i-1][j-2].r == 0 || temp_color[i-1][j-1].r == 0 || temp_color[i-1][j].r == 0 || temp_color[i-1][j+1].r == 0 || temp_color[i-1][j+2].r == 0 ||
                        temp_color[i][j-2].r == 0 || temp_color[i][j-1].r == 0 || temp_color[i][j+1].r == 0 || temp_color[i+1][j-1].r == 0 ||
                        temp_color[i+1][j-2].r == 0 || temp_color[i+1][j-1].r == 0 || temp_color[i+1][j].r == 0 || temp_color[i+1][j+1].r == 0 || temp_color[i+1][j+2].r == 0 ||
                        temp_color[i+2][j-2].r == 0 || temp_color[i+2][j-1].r == 0 || temp_color[i+2][j].r == 0 || temp_color[i+2][j+1].r == 0 || temp_color[i+1][j+2].r == 0 )
                {
                    erosion[i][j].r = 0;
                    erosion[i][j].g = 0;
                    erosion[i][j].b = 0;
                }
            }
        }
    }

}
void SW_vision::Dilation_color(KImageColor &color, KImageColor &erosion, unsigned char kernelSize){
    KImageColor temp_color(color);
    for(unsigned int i = 1; i < color.Row(); i++){
        for(unsigned int j = 1; j < color.Col(); j++){
            erosion[i][j] = color[i][j];
        }
    }
    if(kernelSize == 3){
        for(unsigned int i = 1; i < color.Row() - 1; i++){
            for(unsigned int j = 1; j < color.Col() - 1; j++){
                if(temp_color[i-1][j-1].r != 0 || temp_color[i-1][j].r != 0 || temp_color[i-1][j+1].r != 0 || temp_color[i][j-1].r != 0 || temp_color[i][j+1].r != 0 || temp_color[i+1][j-1].r != 0 ||
                        temp_color[i+1][j].r != 0 || temp_color[i+1][j+1].r != 0)
                {
                    for(int k = -1; k < 2; k++){
                        for(int u = -1; u < 2; u++){
                            if(temp_color[i-k][j-u].r != 0)
                            {
                                erosion[i][j].r = temp_color[i-k][j-u].r;
                                erosion[i][j].g = temp_color[i-k][j-u].g;
                                erosion[i][j].b = temp_color[i-k][j-u].b;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(kernelSize == 5){
        for(unsigned int i = 2; i < color.Row() - 2; i++){
            for(unsigned int j = 2; j < color.Col() - 2; j++){
                if(temp_color[i-2][j-2].r != 0 || temp_color[i-2][j-1].r != 0 || temp_color[i-2][j].r != 0 || temp_color[i-2][j+1].r != 0 || temp_color[i-2][j+2].r != 0 ||
                        temp_color[i-1][j-2].r != 0 || temp_color[i-1][j-1].r != 0 || temp_color[i-1][j].r != 0 || temp_color[i-1][j+1].r != 0 || temp_color[i-1][j+2].r != 0 ||
                        temp_color[i][j-2].r != 0 || temp_color[i][j-1].r != 0 || temp_color[i][j+1].r != 0 || temp_color[i+1][j-1].r != 0 ||
                        temp_color[i+1][j-2].r != 0 || temp_color[i+1][j-1].r != 0 || temp_color[i+1][j].r != 0 || temp_color[i+1][j+1].r != 0 || temp_color[i+1][j+2].r != 0 ||
                        temp_color[i+2][j-2].r != 0 || temp_color[i+2][j-1].r != 0 || temp_color[i+2][j].r != 0 || temp_color[i+2][j+1].r != 0 || temp_color[i+1][j+2].r != 0 )
                {
                    for(int k = -2; k < 3; k++){
                        for(int u = -2; u < 3; u++){
                            if(temp_color[i-k][j-u].r != 0)
                            {
                                erosion[i][j].r = temp_color[i-k][j-u].r;
                                erosion[i][j].g = temp_color[i-k][j-u].g;
                                erosion[i][j].b = temp_color[i-k][j-u].b;
                            }
                        }
                    }
                }
            }
        }
    }
}

void SW_vision::HistoEqu(KImageColor &color, KImageColor &equalize){
    int T_r[256] = {0,}, T_g[256] = {0,}, T_b[256]= {0,};
    // make histogram
    int row = color.Row();
    int col = color.Col();
    for(int i  = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            T_r[color[i][j].r]++;
            T_g[color[i][j].g]++;
            T_b[color[i][j].b]++;
       }
    }
    double equ[256];
    double tmp = color.Row() * color.Col() / 256;
    for(int i = 0; i < 256; i++){
        equ[i] = tmp * (i+1);
    }

    //make cumulative
    for(int i = 0; i < 255; i++){
        T_r[i+1] += T_r[i];
        T_g[i+1] += T_g[i];
        T_b[i+1] += T_b[i];
    }

    //matching
    int HEQ_r[256] ={0,}, HEQ_g[256] ={0,}, HEQ_b[256] ={0,};

    for(int i = 0; i < 256; i++){
        int j = 1;
        int k = 1;
        int u = 1;
        while(T_r[i] > equ[j] && j < 255){
            j++;
        }
        while(T_g[i] > equ[k] && k < 255){
            k++;
        }
        while(T_b[i] > equ[u] && u < 255){
            u++;
        }

        HEQ_r[i] = (equ[j] - T_r[i] > std::abs(equ[j-1] - T_r[i])) ? j-1 : j;
        HEQ_g[i] = (equ[k] - T_g[i] > std::abs(equ[k-1] - T_g[i])) ? k-1 : k;
        HEQ_b[i] = (equ[u] - T_b[i] > std::abs(equ[u-1] - T_b[i])) ? u-1 : u;
    }

    for(int i = 0; i < row; i++){
        for(int j =0; j < col; j++){
            equalize[i][j].r = HEQ_r[color[i][j].r];
            equalize[i][j].g = HEQ_g[color[i][j].g];
            equalize[i][j].b = HEQ_b[color[i][j].b];
        }
    }
}

void SW_vision::HistoMatch(KImageColor &color_t, KImageColor &color_s, KImageColor &match){
    int Tt_r[256] = {0,}, Tt_g[256] = {0,}, Tt_b[256]= {0,};
    int Ts_r[256] = {0,}, Ts_g[256] = {0,}, Ts_b[256]= {0,};
    // make histogram
    int row = color_t.Row();
    int col = color_t.Col();
    for(int i  = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            Tt_r[color_t[i][j].r]++;
            Tt_g[color_t[i][j].g]++;
            Tt_b[color_t[i][j].b]++;

            Ts_r[color_s[i][j].r]++;
            Ts_g[color_s[i][j].g]++;
            Ts_b[color_s[i][j].b]++;
       }
    }

    //make cumulative
    for(int i = 0; i < 255; i++){
        Tt_r[i+1] += Tt_r[i];
        Tt_g[i+1] += Tt_g[i];
        Tt_b[i+1] += Tt_b[i];

        Ts_r[i+1] += Ts_r[i];
        Ts_g[i+1] += Ts_g[i];
        Ts_b[i+1] += Ts_b[i];
    }

    //matching
    int HEQ_r[256] ={0,}, HEQ_g[256] ={0,}, HEQ_b[256] ={0,};

    for(int i = 0; i < 256; i++){
        int j = 1;
        int k = 1;
        int u = 1;
        while(Tt_r[i] > Ts_r[j] && j < 255){
            j++;
        }
        while(Tt_g[i] > Ts_g[k] && k < 255){
            k++;
        }
        while(Tt_b[i] > Ts_b[u] && u < 255){
            u++;
        }

        HEQ_r[i] = (Ts_r[j] - Tt_r[i] > std::abs(Ts_r[j-1] - Tt_r[i])) ? j-1 : j;
        HEQ_g[i] = (Ts_g[j] - Tt_g[i] > std::abs(Ts_g[j-1] - Tt_g[i])) ? k-1 : k;
        HEQ_b[i] = (Ts_b[j] - Tt_b[i] > std::abs(Ts_b[j-1] - Tt_b[i])) ? u-1 : u;
        qDebug() << i << HEQ_r[i] <<","<< Tt_r[i] << "," << Ts_r[i];
    }

    for(int i = 0; i < row; i++){
        for(int j =0; j < col; j++){
            match[i][j].r = HEQ_r[color_t[i][j].r];
            match[i][j].g = HEQ_g[color_t[i][j].g];
            match[i][j].b = HEQ_b[color_t[i][j].b];
        }
    }
}

void SW_vision::GaussianNoise(KImageColor &icMain, KImageColor &noise){
    int row = icMain.Row();
    int col = icMain.Col();

    std::random_device rn;
    std::mt19937_64 rnd(rn());

    for(int i  = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            noise[i][j].r = icMain[i][j].r;
            noise[i][j].g = icMain[i][j].g;
            noise[i][j].b = icMain[i][j].b;
        }
    }

    int i = 0;
    int j = 0;
    for(int k = 0 ; k < row * col / 10 ; k++){
        std::uniform_int_distribution <int> range_row(0, row-1);
        std::uniform_int_distribution <int> range_col(0, col-1);
        i = range_row(rnd);
        j = range_col(rnd);

        std::uniform_int_distribution <int> range_r(0, (int)(255-icMain[i][j].r) /2);
        std::uniform_int_distribution <int> range_g(0, (int)(255-icMain[i][j].g) /2);
        std::uniform_int_distribution <int> range_b(0, (int)(255-icMain[i][j].b) /2);
        noise[i][j].r = icMain[i][j].r + (unsigned char)range_r(rnd);
        noise[i][j].g = icMain[i][j].g + (unsigned char)range_g(rnd);
        noise[i][j].b = icMain[i][j].b + (unsigned char)range_b(rnd);
    }

}

void SW_vision::SaltPepper(KImageColor &icMain, KImageColor &noise){
    int row = icMain.Row();
    int col = icMain.Col();

    std::random_device rn;
    std::mt19937_64 rnd(rn());

    noise = icMain;

    int i = 0;
    int j = 0;
    for(int k = 0 ; k < row * col / 100 ; k++){
        std::uniform_int_distribution <int> range_row(0, row-1);
        std::uniform_int_distribution <int> range_col(0, col-1);
        i = range_row(rnd);
        j = range_col(rnd);

        std::uniform_int_distribution <int> range(0, 255);
        if(range(rnd) > 127){
            noise[i][j].r = 255;
            noise[i][j].g = 255;
            noise[i][j].b = 255;
        }
        else{
            noise[i][j].r = 0;
            noise[i][j].g = 0;
            noise[i][j].b = 0;
        }

    }
}

void SW_vision::BoxFilter(KImageColor &icMain, KImageColor &filter, char maskSize){
    int row = icMain.Row();
    int col = icMain.Col();

    char half = maskSize / 2;

    int value_r,value_g,value_b;
    for(int i = half;i < row-half ; i++){
        for(int j = half;j < col-half ; j++){
            value_r = 0; value_g = 0; value_b = 0;

            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    value_r += icMain[i+rp][j+cp].r;
                    value_g += icMain[i+rp][j+cp].g;
                    value_b += icMain[i+rp][j+cp].b;
                }
            }

            filter[i][j].r = value_r / (maskSize*maskSize);
            filter[i][j].g = value_g / (maskSize*maskSize);
            filter[i][j].b = value_b / (maskSize*maskSize);
        }
    }
}

void SW_vision::GaussianFilter(KImageColor &icMain, KImageColor &filter, double sigma,char maskSize){
    int row = icMain.Row();
    int col = icMain.Col();
    double r, g, b;
    double scale = 0;
    double** mask = new double*[maskSize];
    char half = maskSize/2;
    for(int i = 0; i < maskSize; i++){
        mask[i] = new double[maskSize];
    }

    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] = (1 / (2*3.14*sigma*sigma) ) * pow(2.7184,(-1.0/2.0) * ( ((double)(i-1)*(double)(i-1) + (double)(j-1)*(double)(j-1)) / (sigma * sigma)));
            scale += mask[i][j];
        }
    }

    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] /= scale;
        }
    }

    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            r = 0;
            g = 0;
            b = 0;
            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    r += mask[rp+half][cp+half] * icMain[i+rp][j+cp].r;
                    g += mask[rp+half][cp+half] * icMain[i+rp][j+cp].g;
                    b += mask[rp+half][cp+half] * icMain[i+rp][j+cp].b;
                }
            }
            //qDebug() << scale;
            filter[i][j].r = (unsigned char)r;
            filter[i][j].g = (unsigned char)g;
            filter[i][j].b = (unsigned char)b;
        }
    }

    for(int i = 0; i < maskSize; i++){
        delete[] mask[i];
    }
    delete[] mask;
}

void SW_vision::MedianFilter(KImageColor &icMain, KImageColor &filter, char maskSize){
    int row = icMain.Row();
    int col = icMain.Col();

    char half = maskSize / 2;

    unsigned char* arr_r = new unsigned char[maskSize*maskSize];
    unsigned char* arr_g = new unsigned char[maskSize*maskSize];
    unsigned char* arr_b = new unsigned char[maskSize*maskSize];

    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){

            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    arr_r[(rp+half) * maskSize + (cp+half)] = icMain[i+cp][j+cp].r;
                    arr_g[(rp+half) * maskSize + (cp+half)] = icMain[i+cp][j+cp].g;
                    arr_b[(rp+half) * maskSize + (cp+half)] = icMain[i+cp][j+cp].b;
                }
            }
            std::sort(arr_r, arr_r + maskSize*maskSize);
            std::sort(arr_g, arr_g + maskSize*maskSize);
            std::sort(arr_b, arr_b + maskSize*maskSize);

            filter[i][j].r = arr_r[4];
            filter[i][j].g = arr_g[4];
            filter[i][j].b = arr_b[4];
        }
    }

    delete[] arr_r;
    delete[] arr_g;
    delete[] arr_b;
}

void SW_vision::CannyEdge(KImageGray &igMain, KImageGray &edge, double sigma, int high, int low){
    int row = igMain.Row();
    int col = igMain.Col();
    KImageGray tmpG(row,col);

    int half = (int)(3.0 * sigma+0.3);
    qDebug() << half;
    int maskSize = half * 2 + 1;
    qDebug() << maskSize;
    double** mask = new double*[maskSize];
    double sobelMaskX3[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    double sobelMaskY3[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};

    //double sobelMaskX5[5][5] = {{-1,-2,0,2,1}, {-2,-3,0,3,2}, {-3,-5,0,5,3}, {-2,-3,0,3,2}, {-1,-2,0,2,1}};

    //edge information container
    int** dX = new int*[row];
    int** dY = new int*[row];
    int** norm = new int*[row];
    unsigned char** direction = new unsigned char*[row];
    for(int i = 0; i < row; i++){
        dX[i] = new int[col];
        dY[i] = new int[col];
        norm[i] = new int[col];
        direction[i] = new unsigned char[col];
    }

    for(int i = 0; i < maskSize; i++){
        mask[i] = new double[maskSize];
    }
    double scale = 0.0;
    double sigma2 = 2.0*sigma*sigma;
    double con = 1.0 / (2 * 3.141592) / (sigma*sigma);
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] = con * exp(-((i-1)*(i-1)+(j-1)*(j-1))/sigma2);
            scale += mask[i][j];
        }
    }

    qDebug() << scale;
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] /= scale;
        }
    }
    double gray;

    //gaussian blurring
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            gray = 0;
            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    gray += mask[rp+half][cp+half] * igMain[i+rp][j+cp];
                }
            }
            //qDebug() << scale;
            tmpG[i][j] = (unsigned char)gray;
        }
    }
    qDebug() << "active2";
    //edge detect

    int X;
    int Y;

    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            X = 0;
            Y = 0;
            for(int rp = -1; rp < 2; rp++){
                for(int cp = -1; cp < 2; cp++){
                    X += sobelMaskX3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                    Y += sobelMaskY3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                }
            }
            dX[i][j] = X;
            dY[i][j] = Y;
            //Norm
            norm[i][j] = std::abs(X) + std::abs(Y);
            direction[i][j] = (unsigned char)(((int)(atan2(X,Y) * 2.546 + 1)>>1)& 0x00000003); //2.546 = 180 / pi / 22.5
            //qDebug() << norm[i][j];
        }
    }
    int nDx[4] = {0, 1, 1, -1};
    int nDy[4] = {1, 1, 0, 1};

    //non-maxima subpression
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if(norm[i][j] > norm[i + nDy[ direction[i][j] ]][j + nDx[ direction[i][j] ]] && norm[i][j] > norm[i - nDy[ direction[i][j] ]][j - nDx[ direction[i][j] ]] ){
                if(norm[i][j] > high)
                {
                    edge[i][j] = 255;
                }
                else if(norm[i][j] > low){
                    edge[i][j] = 1;
                }
            }
        }
    }
    //hyteresis Thresh holding
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if( edge[i][j] == 1 && (norm[i-1][j+1] == 255 || norm[i-1][j] == 255 || norm[i-1][j+1]
                                    || norm[i][j+1] == 255|| norm[i][j+1] ||
                                    norm[i+1][j+1] == 255 || norm[i+1][j] == 255 || norm[i+1][j+1]) ){
                edge[i][j] = 255;
            }
        }
    }


    delete[] dX;
    delete[] dY;
    delete[] mask;
    delete[] norm;
    delete[] direction;
}

void SW_vision::CannyEdge_retEdgeDir(KImageGray &igMain, KImageGray &edge, unsigned char **&direction, double sigma, int high, int low){
    int row = igMain.Row();
    int col = igMain.Col();
    KImageGray tmpG(row,col);

    int half = (int)(3.0 * sigma+0.3);
    qDebug() << half;
    int maskSize = half * 2 + 1;
    qDebug() << maskSize;
    double** mask = new double*[maskSize];
    double sobelMaskX3[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    double sobelMaskY3[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};

    //double sobelMaskX5[5][5] = {{-1,-2,0,2,1}, {-2,-3,0,3,2}, {-3,-5,0,5,3}, {-2,-3,0,3,2}, {-1,-2,0,2,1}};

    //edge information container
    int** dX = new int*[row];
    int** dY = new int*[row];
    int** norm = new int*[row];
    direction = new unsigned char*[row];
    for(int i = 0; i < row; i++){
        dX[i] = new int[col];
        dY[i] = new int[col];
        norm[i] = new int[col];
        direction[i] = new unsigned char[col];
    }

    for(int i = 0; i < maskSize; i++){
        mask[i] = new double[maskSize];
    }
    double scale = 0.0;
    double sigma2 = 2.0*sigma*sigma;
    double con = 1.0 / (2 * 3.141592) / (sigma*sigma);
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] = con * exp(-((i-1)*(i-1)+(j-1)*(j-1))/sigma2);
            scale += mask[i][j];
        }
    }

    qDebug() << scale;
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] /= scale;
        }
    }
    double gray;

    //gaussian blurring
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            gray = 0;
            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    gray += mask[rp+half][cp+half] * igMain[i+rp][j+cp];
                }
            }
            //qDebug() << scale;
            tmpG[i][j] = (unsigned char)gray;
        }
    }
    qDebug() << "active3";
    //edge detect

    int X;
    int Y;

    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            X = 0;
            Y = 0;
            for(int rp = -1; rp < 2; rp++){
                for(int cp = -1; cp < 2; cp++){
                    X += sobelMaskX3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                    Y += sobelMaskY3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                }
            }
            dX[i][j] = X;
            dY[i][j] = Y;
            //Norm
            norm[i][j] = std::abs(X) + std::abs(Y);
            direction[i][j] = (unsigned char)(((int)(atan2(X,Y) * 2.546 + 1)>>1)& 0x00000003); //2.546 = 180 / pi / 22.5
            //qDebug() << norm[i][j];
        }
    }
    int nDx[4] = {0, 1, 1, -1};
    int nDy[4] = {1, 1, 0, 1};
    qDebug() << "active2";
    //non-maxima subpression
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if(norm[i][j] > norm[i + nDy[ direction[i][j] ]][j + nDx[ direction[i][j] ]] && norm[i][j] > norm[i - nDy[ direction[i][j] ]][j - nDx[ direction[i][j] ]] ){
                if(norm[i][j] > high)
                {
                    edge[i][j] = 255;
                }
                else if(norm[i][j] > low){
                    edge[i][j] = 1;
                }
            }
        }
    }
    //hyteresis Thresh holding
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if( edge[i][j] == 1 && (norm[i-1][j+1] == 255 || norm[i-1][j] == 255 || norm[i-1][j+1]
                                    || norm[i][j+1] == 255|| norm[i][j+1] ||
                                    norm[i+1][j+1] == 255 || norm[i+1][j] == 255 || norm[i+1][j+1]) ){
                edge[i][j] = 255;
            }
        }
    }

    qDebug() << "active1";
    delete[] dX;
    delete[] dY;
    delete[] mask;
    delete[] norm;
    //delete[] direction;
}

void SW_vision::CannyEdge_retGrad(KImageGray &igMain, KImageGray &edge, int **&dX, int **&dY, double sigma, int high, int low){
    int row = igMain.Row();
    int col = igMain.Col();
    KImageGray tmpG(row,col);

    int half = (int)(3.0 * sigma+0.3);
    qDebug() << half;
    int maskSize = half * 2 + 1;
    qDebug() << maskSize;
    double** mask = new double*[maskSize];
    double sobelMaskX3[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    double sobelMaskY3[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};

    //double sobelMaskX5[5][5] = {{-1,-2,0,2,1}, {-2,-3,0,3,2}, {-3,-5,0,5,3}, {-2,-3,0,3,2}, {-1,-2,0,2,1}};

    //edge information container

    int** norm = new int*[row];
    unsigned char** direction = new unsigned char*[row];
    for(int i = 0; i < row; i++){
        norm[i] = new int[col];
        direction[i] = new unsigned char[col];
    }

    for(int i = 0; i < maskSize; i++){
        mask[i] = new double[maskSize];
    }
    double scale = 0.0;
    double sigma2 = 2.0*sigma*sigma;
    double con = 1.0 / (2 * 3.141592) / (sigma*sigma);
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] = con * exp(-((i-1)*(i-1)+(j-1)*(j-1))/sigma2);
            scale += mask[i][j];
        }
    }

    qDebug() << scale;
    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] /= scale;
        }
    }
    double gray;

    //gaussian blurring
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            gray = 0;
            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    gray += mask[rp+half][cp+half] * igMain[i+rp][j+cp];
                }
            }
            //qDebug() << scale;
            tmpG[i][j] = (unsigned char)gray;
        }
    }
    qDebug() << "active2";
    //edge detect

    int X;
    int Y;

    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            X = 0;
            Y = 0;
            for(int rp = -1; rp < 2; rp++){
                for(int cp = -1; cp < 2; cp++){
                    X += sobelMaskX3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                    Y += sobelMaskY3[rp+half][cp+half] * tmpG[i+rp][j+cp] / 8;
                }
            }
            dX[i][j] = X;
            dY[i][j] = Y;
            //Norm
            norm[i][j] = std::abs(X) + std::abs(Y);
            direction[i][j] = (unsigned char)(((int)(atan2(X,Y) * 2.546 + 1)>>1)& 0x00000003); //2.546 = 180 / pi / 22.5
            //qDebug() << norm[i][j];
        }
    }
    int nDx[4] = {0, 1, 1, -1};
    int nDy[4] = {1, 1, 0, 1};

    //non-maxima subpression
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if(norm[i][j] > norm[i + nDy[ direction[i][j] ]][j + nDx[ direction[i][j] ]] && norm[i][j] > norm[i - nDy[ direction[i][j] ]][j - nDx[ direction[i][j] ]] ){
                if(norm[i][j] > high)
                {
                    edge[i][j] = 255;
                }
                else if(norm[i][j] > low){
                    edge[i][j] = 1;
                }
            }
        }
    }
    //hyteresis Thresh holding
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            if( edge[i][j] == 1 && (norm[i-1][j+1] == 255 || norm[i-1][j] == 255 || norm[i-1][j+1]
                                    || norm[i][j+1] == 255|| norm[i][j+1] ||
                                    norm[i+1][j+1] == 255 || norm[i+1][j] == 255 || norm[i+1][j+1]) ){
                edge[i][j] = 255;
            }
        }
    }

    delete[] mask;
    delete[] norm;
    delete[] direction;
}

void SW_vision::GHoughTransform(KImageGray &igMain, KImageGray &output, std::string table){

    //Accumulator Array
    int** acc= new int*[igMain.Row()];
    for(unsigned int i = 0; i < igMain.Row(); i++){
        acc[i] = new int[igMain.Col()];
    }
    qDebug() << "start";
    std::ifstream fin(table);

    // File open
    if(fin.is_open())
    {
        qDebug() << "file open";
    }
    else{
        qDebug() << "file undetected";
    }
    int data_num;
    fin >> data_num;
    // Table read
    qDebug() << data_num;
    std::vector<std::pair<int,int>> objectTable;
    std::vector<std::pair<double,double>> Iptable[8][4]; // 4 direction //first => dist, second=> angle
    int tmpX, tmpY;
    while(!fin.eof()){
        fin >> tmpX >> tmpY;
        objectTable.push_back(std::make_pair(tmpX,tmpY));
    }
    fin.close();


    // Find Center Point
    int cX = 0, cY = 0;
    for(unsigned int i =0; i < objectTable.size(); i++){
        cX += objectTable[i].first;
        cY += objectTable[i].second;
    }

    cX /= objectTable.size();
    cY /= objectTable.size();

    // Make shape Table
    double dTmp, dDist, dAng;
    int dir;
    for(int i = 0; i < (int)objectTable.size() - 2; i++){
        for(int j = 0; j < 8; j++){ //make Iptable every 45 degree rotate
            //compute edge
            dTmp = (180.0 / 3.141592) * std::atan2(objectTable[i+1].first - objectTable[i-1].first,
                    objectTable[i+1].second - objectTable[i-1].second);
            dTmp += 45*j; //make Iptable every 45 degree rotate
            qDebug() << dTmp;

            //edge direction 0~3
            dir = (((int)(dTmp + 1)>>1)& 0x00000003);
            //qDebug() << dir;

            //distance from center cX, cY
            dDist = std::sqrt( (objectTable[i].first-cX) * (objectTable[i].first-cX) + (objectTable[i].second-cY) * (objectTable[i].second-cY) );

            //Angle with center cX, cY
            dAng = std::atan2(objectTable[i].second - cY, objectTable[i].first - cX);

            Iptable[j][dir].push_back(std::make_pair(dDist,dAng)); //first => dist, second=> angle
        }
    }

    //main Image edge detect
    KImageGray edge(igMain.Row(),igMain.Col());
    //KImageGray igTmp(igMain.Row(),igMain.Col());

    unsigned char **igMainEdgeDir;

    //SW_vision::RGBThreshHolding(igMain,igTmp);

    SW_vision::CannyEdge_retEdgeDir(igMain,edge,igMainEdgeDir,0.5,100,10);

    //voting
    double ***vote = new double**[igMain.Row()];
    for(unsigned int i = 0; i < igMain.Row(); i++){
        vote[i] = new double*[igMain.Col()];
        for(unsigned int j = 0; j < igMain.Col(); j++){
            vote[i][j] = new double[8];
        }
    }

    double weight = 4.0; //voting weight
    for(unsigned int i = 2; i < igMain.Row()-2; i++){
        for(unsigned int j = 2 ; j < igMain.Row()-2; j++){
            if(edge[i][j] == 255){
                //vote rotating Iptable
                for(int u = 0; u < 7; u++){//vote using Iptable every 45degree rotate
                    int igDir = igMainEdgeDir[i][j];
                    for(int k = 0; k < (int)Iptable[u][igDir].size(); k++ ){
                        //find vote list
                        tmpX = i - Iptable[u][igDir][k].first * std::cos(Iptable[u][igDir][k].second);
                        tmpY = j - Iptable[u][igDir][k].first * std::sin(Iptable[u][igDir][k].second);
                        if(tmpX > 1 && tmpX < (int)igMain.Row()-1 && tmpY > 1 && tmpY < (int)igMain.Row()-1 && vote[tmpX][tmpY][u] < 255.0 ){
                            //vote

                            vote[tmpX][tmpY][u] += weight * 1.0;
                            //solve noise problem => weighted voting widely
                            vote[tmpX-1][tmpY-1][u] += weight * 0.7; vote[tmpX-1][tmpY][u] += weight * 0.7; vote[tmpX-1][tmpY+1][u] += weight * 0.7;
                            vote[tmpX][tmpY-1][u] += weight * 0.7;                                       vote[tmpX][tmpY+1][u] += weight * 0.7;
                            vote[tmpX+1][tmpY-1][u] += weight * 0.7; vote[tmpX+1][tmpY][u] += weight * 0.7; vote[tmpX+1][tmpY+1][u] += weight * 0.7;
                        }
                    }

                }
            }
        }
    }
    int iMax,jMax,uMax;
    unsigned char spot = 0;
    //voting visualization & find max spot
    for(unsigned int i = 0; i < igMain.Row(); i++){
        for(unsigned int j = 0 ; j < igMain.Row(); j++){
            for(unsigned int u = 0; u < 7; u++){
                output[i][j] = (unsigned char)vote[i][j][u];
                if(vote[i][j][u] > spot ){
                    spot = vote[i][j][u];
                    iMax = i;
                    jMax = j;
                    uMax = u;
                }
            }
        }
    }
        //Draw object
        for(int i =0; i < 4; i++){
            for(int k = 0; k < (int)Iptable[uMax][i].size(); k++ ){
                //find vote list
                tmpX = iMax - Iptable[uMax][i][k].first * std::cos(Iptable[uMax][i][k].second);
                tmpY = jMax - Iptable[uMax][i][k].first * std::sin(Iptable[uMax][i][k].second);
                if(tmpX > 1 && tmpX < (int)igMain.Row()-1 && tmpY > 1 && tmpY < (int)igMain.Row()-1 ){
                   output[tmpX][tmpY] = 255;
                }
            }
        }


    qDebug() << "u : " << uMax;
//    int x, y;
//    for(int i = 0; i < objectTable.size() - 2; i++){
//        x = iMax + objectTable[i].first - cX; y = jMax + objectTable[i].second - cY;
//        if( x > 0 && x < igMain.Row() && y > 0 && y < igMain.Col() )
//            output[x][y] = 255;
//        }



//    for(unsigned int i = 2; i < igMain.Row()-2; i++){
//        for(unsigned int j = 2 ; j < igMain.Row()-2; j++){

//        }
//    }

    //edge debug
    //output = edge;

    delete[] acc;
    delete[] igMainEdgeDir;
    delete[] vote;
}

void SW_vision::CHoughTransform(KImageGray &igMain, KImageGray &output, double radius){
    //main Image edge detect

    //KImageGray igTmp(igMain.Row(),igMain.Col());
    KImageGray edge(igMain.Row(),igMain.Col());

    //SW_vision::RGBThreshHolding(igMain,igTmp); // make binary image for edge detect

    SW_vision::CannyEdge(igMain,edge,0.5,100,10);
    int row = igMain.Row();
    int col = igMain.Col();

    //voting
    double **vote = new double*[igMain.Row()];
    for(unsigned int i = 0; i < igMain.Row(); i++){
        vote[i] = new double[igMain.Col()];
        for(unsigned int j = 0; j < igMain.Col(); j++){
            vote[i][j] = 0;
        }
    }
    double weight = 3
            ;
    //int a_in;
    int a_out;
    //int b_in;
    int b_out;

    //double a_in_tmp, b_in_tmp;
    double a_out_tmp, b_out_tmp;
    double theta;
    int samp_deg = 5;
    //qDebug() << "row : " << row << " col : " << col;
    qDebug() << "active 3";
    for(unsigned int i = 2; i < igMain.Row()-2; i++){
        for(unsigned int j = 2 ; j < igMain.Col()-2; j++){
            if(edge[i][j] == 255){ //IS EDGE
                //vote[i][j] = 255;
                for(int angle = 0; angle <= 360; angle += samp_deg){
                    theta = (double)angle * 0.01745329; // 0.017453..=>1 / 180 * 3.14592;
                    a_out_tmp = (double)j - (double)(radius * cos(theta)); //outward
                    b_out_tmp = (double)i - (double)(radius * sin(theta));
                    a_out = (int)a_out_tmp; b_out = (int)b_out_tmp;
                    //qDebug()  << a_out_tmp << " " << a_out;
                    //qDebug()  << " theta : " << theta;
                    //qDebug() << "i : " << i << " cos : " << cos(theta);
                    if(a_out > 1 && a_out < col-1 && b_out > 1 && b_out < row-1){
                       vote[b_out][a_out] += weight * 1.0;
                       //solve noise problem => weighted voting widely
                       vote[b_out-1][a_out-1] += weight * 0.7; vote[b_out][a_out-1] += weight * 0.7; vote[b_out+1][a_out-1] += weight * 0.7;
                       vote[b_out-1][a_out] += weight * 0.7;                                         vote[b_out+1][a_out] += weight * 0.7;
                       vote[b_out-1][a_out+1] += weight * 0.7; vote[b_out][a_out+1] += weight * 0.7; vote[b_out+1][a_out+1] += weight * 0.7;
                    }
//                    a_in_tmp = (double)j + (double)(radius * cos(theta)) ; //57.295... => 180 / pi  //inward
//                    b_in_tmp = (double)i + (double)(radius * sin(theta)) ; //57.295... => 180 / pi
//                    a_in = (int)a_in_tmp; b_in = (int)b_in_tmp;
//                    if(a_in > 1 && a_in < col-1 && b_in > 1 && b_in < row-1){
//                       vote[b_in][a_in] += weight * 1;
//                       //solve noise problem => weighted voting widely
//                       vote[b_in-1][a_in-1] += weight * 0.7; vote[b_in][a_in-1] += weight * 0.7; vote[b_in+1][a_in-1] += weight * 0.7;
//                       vote[b_in-1][a_in] += weight * 0.7;                                       vote[b_in+1][a_in] += weight * 0.7;
//                       vote[b_in-1][a_in+1] += weight * 0.7; vote[b_in][a_in+1] += weight * 0.7; vote[b_in+1][a_in+1] += weight * 0.7;
//                    }
//                    //qDebug() << a_out << " " << b_out << " " << a_out << " " << b_out ;
                }
            }
        }
    }
    qDebug() << "active 4";
    int iMax,jMax;
    unsigned char spot = 0;
    //voting visualization & find max spot
    for(unsigned int i = 0; i < igMain.Row(); i++){
        for(unsigned int j = 0 ; j < igMain.Col(); j++){
            if(vote[i][j] < 255){
                output[i][j] = (unsigned char)vote[i][j];
            }
            else if(vote[i][j] > 255){
                output[i][j] = 255;
            }
            //if(vote[i][j] > 0)  qDebug() << vote[i][j];
            if(vote[i][j] > spot ){
                spot = vote[i][j];
                iMax = i;
                jMax = j;
            }
        }
    }

    //Draw circle
    for(int angle = 0; angle <= 360; angle+= 1){
        theta = (double)angle * 0.01745329; // 0.017453..=>1 / 180 * 3.14592;
        a_out_tmp = (double)jMax - (double)(radius * cos(theta)); //outward
        b_out_tmp = (double)iMax - (double)(radius * sin(theta));
        a_out = (int)a_out_tmp; b_out = (int)b_out_tmp;

        output[b_out][a_out] = 255;
    }

    //output = edge;
    delete[] vote;
}

void SW_vision::GaussianFilter_gray(KImageGray &igMain, KImageGray &output, double sigma){
    int row = igMain.Row();
    int col = igMain.Col();

    int half = (int)(3.0 * sigma+0.3);
    int maskSize = half * 2 + 1;

    double** mask = new double*[maskSize];
    for(int i = 0; i < maskSize; i++){
        mask[i] = new double[maskSize];
    }
    //qDebug() << "active 1";

    double scale = 0.0;
    double sigma2 = 2.0*sigma*sigma;
    double con = 1.0 / (2.0 * 3.141592) / (sigma*sigma);

    //qDebug() << "active 2";


    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] = con * std::exp(-(((double)i-1)*((double)i-1)+((double)j-1)*((double)j-1))/sigma2);
            scale += mask[i][j];
        }
    }

    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            mask[i][j] /= scale;
        }
    }

    double gray;
    //qDebug() << "active 3";
    for(int i = half;i < row-half ; i++){
        for(int j = half ;j < col-half ; j++){
            gray = 0;
            for(int rp = -half; rp < half+1; rp++){
                for(int cp = -half; cp < half+1; cp++){
                    gray += mask[rp+half][cp+half] * igMain[i+rp][j+cp];
                }
            }
            //qDebug() << scale;
            output[i][j] = (unsigned char)gray;
        }
    }
    //qDebug() << "active 4";
    delete[] mask;
}
void SW_vision::GaussianFilter_double(KImageGray &igMain, KImageDouble &output, double sigma){
        output.Create(igMain.Row(),igMain.Col());

        sigma = sqrt(sigma);

        //create the conv. mask
        int nHalf = (int)(3.0*sigma+0.3);

        double* dGMask = new double[nHalf*2 + 1];

        double dScale = 0.0;
        double dConst = 1.0 / (2.0 * _PI * pow(sigma, 2));

        for(int i = -nHalf; i<=nHalf; i++){
            dGMask[i+nHalf] = dConst * exp( -(i*i) / (2*pow(sigma, 2) ) );
            dScale += dGMask[i+nHalf];
        }

        // Scaling
        for(int i = -nHalf; i<=nHalf; i++){
            dGMask[i+nHalf] /= dScale;
        }

        // Convolution
        // Col(x축) convolution 연산
        for(int i = nHalf;i < (int)igMain.Row()-nHalf;i++){
            for(int j = nHalf; j < (int)igMain.Col()-nHalf;j++){
                double pixVal = 0.0;
                for(int n = -nHalf; n <= nHalf; n++){
                    pixVal += igMain[i][j + n] * dGMask[n + nHalf];
                }
                output[i][j] = pixVal;
            }
        }

        // Row(y축) convolution 연산
        for(int i = nHalf; i<(int)igMain.Row()-nHalf;i++){
            for(int j = nHalf; j<(int)igMain.Col()-nHalf;j++){
                double pixVal = 0.0;
                for(int n = -nHalf; n <= nHalf; n++){
                    pixVal += igMain[i + n][j] * dGMask[n + nHalf];
                }
                output[i][j] = pixVal;
            }
        }

        delete[] dGMask;
    }
void SW_vision::Gaussian_DOG_scale_retD(KImageGray &igMain, KImageGray **&output_scale, KImageGray **&output_DoG, KImageDouble **&d_output_DoG, double dSigma){
    int row = igMain.Row();
    int col = igMain.Col();

    int nDim = std::min(row,col);
    int nOctaves = std::min( (int)log((double)nDim/ log(2.0)) - 2, 3);

    int nScale = 6;
    qDebug() << "octave : " << nOctaves;
    KImageDouble **d_scale;
    output_scale = new KImageGray*[nOctaves];
    output_DoG = new KImageGray*[nOctaves];
    d_output_DoG = new KImageDouble*[nOctaves];
    d_scale = new KImageDouble*[nOctaves];
    int o_row = row;
    int o_col = col;

    KImageGray sample(igMain);
    //KImageGray sample_tmp;
    for(int i = 0; i < nOctaves; i++){
        output_scale[i] = new KImageGray[nScale];
        output_DoG[i] = new KImageGray[nScale-1];
        d_output_DoG[i] = new KImageDouble[nScale-1];
        d_scale[i] = new KImageDouble[nScale];

        for(int k = 0; k < nScale-1; k++){
            output_DoG[i][k].Create(o_row,o_col);
            d_output_DoG[i][k].Create(o_row,o_col);
        }

        for(int k = 0; k < nScale; k++){
            output_scale[i][k].Create(o_row,o_col);
            d_scale[i][k].Create(o_row,o_col);

            SW_vision::GaussianFilter_double(sample,d_scale[i][k],pow(cbrt(2),k)*dSigma);// 이후 효율적인 코드로 변경하기 강의자료 반영
            output_scale[i][k] = d_scale[i][k].ToGray();
//            if(k = 3){
//                sample_tmp = output_scale[i]
//            }
        }

        sample = output_scale[i][2].HalfSize();
        o_row /= 2;
        o_col /= 2;


    }

    for(int i = 0; i < nOctaves; i++){
        for(int k = 0; k < nScale-1; k++){
            for(int u = 0; u < (int)output_DoG[i][k].Row(); u++){
                for(int v = 0; v < (int)output_DoG[i][k].Col(); v++){
                    d_output_DoG[i][k][u][v] = d_scale[i][k+1][u][v] - d_scale[i][k][u][v];
                }
            }
            output_DoG[i][k] = d_output_DoG[i][k].ToGray();
        }
    }
    delete[] d_scale;
}

void SW_vision::stick_gray(KImageGray **&input_arr, KImageGray &output, int a, int b){
    const int out_row = output.Row();
    const int out_col = output.Col();

    int fill_row  = 0;
    int fill_col  = 0;

    int set_row = 0;
    int set_col = 0;
    for(int i = 0 ; i < a; i++){
        fill_row += input_arr[i][0].Row();
        for(int j = 0; j < b; j++){

            fill_col += input_arr[i][j].Col();

            if(out_col < fill_col){
                if(out_row <= fill_row){
                    break;
                }
                set_row += input_arr[i][j].Row();
                fill_row += input_arr[i][j].Row();

                set_col = 0;
                fill_col = 0;
            }
            for(int u = 0; u < (int)input_arr[i][j].Row(); u++){
                for(int v = 0; v < (int)input_arr[i][j].Col(); v++){
                    output[u+set_row][v+set_col] = input_arr[i][j][u][v];
                }
            }
            set_col += input_arr[i][j].Col();
        }

        set_col = 0;
        fill_col =0;

        set_row += input_arr[i][0].Row();

    }
}

void SW_vision::DoG_Extrema(KImageDouble **&idDoG, bool ****&idExt_DoG, int a, int b){
    //qDebug() << "extrema1";
    idExt_DoG = new bool***[a];

    for(int i = 0 ; i < a; i++){
        idExt_DoG[i] = new bool**[b-2];
        for(int j = 0; j < b-2; j++){
            //qDebug() << "extrema1.5";
            idExt_DoG[i][j] = new bool*[idDoG[i][j].Row()];
            for(int u = 0; u < (int)idDoG[i][j].Row(); u++){
                idExt_DoG[i][j][u] = new bool[idDoG[i][j].Col()];
                for(int v = 0; v < (int)idDoG[i][j].Col(); v++){
                    idExt_DoG[i][j][u][v] = false;

                }
            }
        }
    }

    double ck  = 0.0;
    //Extrema Detection
    if(b > 2){
        for(int i = 0; i < a; i++){
            for(int j = 1; j < b - 1; j++){
                //qDebug() << "extrema2";
                for(int u = 1; u < (int)idDoG[i][j].Row() - 1; u++){
                    for(int v = 1; v < (int)idDoG[i][j].Col() - 1; v++){
                        ck =  idDoG[i][j][u][v];
                        if(ck > 0.0){
                            if(ck > idDoG[i][j-1][u-1][v-1] && ck > idDoG[i][j-1][u-1][v] && ck > idDoG[i][j-1][u-1][v+1] &&
                            ck > idDoG[i][j-1][u][v-1]   && ck > idDoG[i][j-1][u][v]   && ck > idDoG[i][j-1][u][v+1]   &&
                            ck > idDoG[i][j-1][u+1][v-1] && ck > idDoG[i][j-1][u+1][v] && ck > idDoG[i][j-1][u+1][v+1] &&

                            ck > idDoG[i][j][u-1][v-1]   && ck > idDoG[i][j][u-1][v]   && ck > idDoG[i][j][u-1][v+1]   &&
                            ck > idDoG[i][j][u][v-1]     &&                              ck > idDoG[i][j][u][v+1]     &&
                            ck > idDoG[i][j][u+1][v-1]   && ck > idDoG[i][j][u+1][v]   && ck > idDoG[i][j][u+1][v+1]   &&

                            ck > idDoG[i][j+1][u-1][v-1]   && ck > idDoG[i][j+1][u-1][v] && ck > idDoG[i][j+1][u-1][v+1] &&
                            ck > idDoG[i][j+1][u][v-1]     && ck > idDoG[i][j+1][u][v]   && ck > idDoG[i][j+1][u][v+1]   &&
                            ck > idDoG[i][j+1][u+1][v-1]   && ck > idDoG[i][j+1][u+1][v] && ck > idDoG[i][j+1][u+1][v+1]  ){

                            idExt_DoG[i][j-1][u][v] = true;
                                //qDebug() << " ck  : " << ck;
                            }
                        }
                        else {
                            if(ck < idDoG[i][j-1][u-1][v-1] && ck < idDoG[i][j-1][u-1][v] && ck < idDoG[i][j-1][u-1][v+1] &&
                               ck < idDoG[i][j-1][u][v-1]   && ck < idDoG[i][j-1][u][v]   && ck < idDoG[i][j-1][u][v+1]   &&
                               ck < idDoG[i][j-1][u+1][v-1] && ck < idDoG[i][j-1][u+1][v] && ck < idDoG[i][j-1][u+1][v+1] &&

                               ck < idDoG[i][j][u-1][v-1]   && ck < idDoG[i][j][u-1][v]   && ck < idDoG[i][j][u-1][v+1]   &&
                               ck < idDoG[i][j][u][v-1]     &&                              ck < idDoG[i][j][u][v+1]     &&
                               ck < idDoG[i][j][u+1][v-1]   && ck < idDoG[i][j][u+1][v]   && ck < idDoG[i][j][u+1][v+1]   &&

                               ck < idDoG[i][j+1][u-1][v-1]   && ck < idDoG[i][j+1][u-1][v] && ck < idDoG[i][j+1][u-1][v+1] &&
                               ck < idDoG[i][j+1][u][v-1]     && ck < idDoG[i][j+1][u][v]   && ck < idDoG[i][j+1][u][v+1]   &&
                               ck < idDoG[i][j+1][u+1][v-1]   && ck < idDoG[i][j+1][u+1][v] && ck < idDoG[i][j+1][u+1][v+1]  ){
                                idExt_DoG[i][j-1][u][v] = true;
                            }
                        }
                    }
                }

            }
        }
    }
}

void SW_vision::Mark_KeyPoint(KImageGray &igScale, double mag, double ori_deg, int pX, int pY){
    double dX_circle , dY_circle;
    int iX_circle, iY_circle;

    double radius = 0;

    int iX_dir, iY_dir;
    double dX_dir, dY_dir;

    double custom = 4;

    int tmp = (int)(mag / custom);
    if(tmp < 2 ){
        radius = 5;
    }
    else if(tmp < 5){
        radius = 7;
    }
    else if(tmp < 10){
        radius = 8;
    }
    else{
        radius = 10;
    }

    double theta_rad;
    //Draw circle
    for(int angle = 0; angle <= 360; angle+= 1){

        theta_rad = (double)angle * 0.01745329; // 0.017453..=>1 / 180 * 3.14592; degree to rad

        dX_circle = (double)pX - (double)(radius * cos(theta_rad));
        dY_circle = (double)pY - (double)(radius * sin(theta_rad));

        iX_circle = (int)dX_circle; iY_circle = (int)dY_circle;

        if(iX_circle > 0 && iY_circle > 0 && iX_circle < (int)igScale.Row() && iY_circle < (int)igScale.Col()){
           igScale[iX_circle][iY_circle] = 255;
        }
    }

    //Draw Direction
    for(int range = 0; range <= radius; range++){
        theta_rad = ori_deg * 0.01745329; // 0.017453..=>1 / 180 * 3.14592; degree to rad

        dX_dir = (double)pX - (double)(range * cos(theta_rad));
        dY_dir = (double)pY - (double)(range * sin(theta_rad));

        iX_dir = (int)dX_dir; iY_dir = (int)dY_dir;

        if(iX_dir > 0 && iY_dir > 0 && iX_dir < (int)igScale.Row() && iY_dir < (int)igScale.Col()){
           igScale[iX_dir][iY_dir] = 255;
        }

    }

}

void SW_vision::DoG_Keypoint(KImageGray &igMain, KImageGray **&output_key, KImageGray **&debg, std::vector<KeyPoint_descriptor> &des_vec){
    KImageGray **igDoG;
    KImageDouble **idDoG;
    KImageGray **igScale;
    int nScale = 6;
    int row = igMain.Row();
    int col = igMain.Col();

    int nDim = std::min(row,col);
    int nOctaves = std::min( (int)log((double)nDim/ log(2.0)) - 2, 3);

    int a = nOctaves;
    int b = nScale - 1; // num of dog space

    SW_vision::Gaussian_DOG_scale_retD(igMain,igScale,igDoG,idDoG






                                       );
    qDebug() << "dog complete";

    bool ****idExt_DoG;
    SW_vision::DoG_Extrema(idDoG,idExt_DoG,a,b);
    KImageGray debg_sam(igMain);

    debg = new KImageGray*[a];
    for(int i =0; i < a; i++){
        debg[i] = new KImageGray[b-2];
        for(int j =0; j < b-2; j++){
            debg[i][j] = debg_sam;
            for(int u = 1; u < (int)igDoG[i][j].Row() - 1; u++){
                for(int v = 1; v < (int)igDoG[i][j].Col() - 1; v++){
                    if(idExt_DoG[i][j][u][v]){
                        debg[i][j][u-1][v-1] = 255; debg[i][j][u-1][v] = 255; debg[i][j][u-1][v+1] = 255;
                        debg[i][j][u][v-1] = 255; debg[i][j][u][v] = 255; debg[i][j][u][v+1] = 255;
                        debg[i][j][u+1][v-1] = 255; debg[i][j][u+1][v] = 255; debg[i][j][u+1][v+1] = 255;
                    }
                }
            }
        }
        debg_sam = debg_sam.HalfSize();
    }


    KImageGray sample(igMain);
    KImageGray **isKey;

    //qDebug() << "key1";
    output_key = new KImageGray*[a];
    isKey = new KImageGray*[a];

    for(int i =0; i < a; i++){
        output_key[i] = new KImageGray[b-2];
        isKey[i] = new KImageGray[b-2];
        for(int j = 0; j < b-2; j++){
            output_key[i][j] = igScale[i][j+1];
            isKey[i][j].Create(output_key[i][j].Row(),output_key[i][j].Col());
        }

    }

    //remove bad contrast
    for(int k = 0; k < a; k++){
        for(int p = 0; p < b - 2; p++){
            for(int i = 1; i < (int)igDoG[k][p].Row() - 1; i++){
                for(int j = 1; j < (int)igDoG[k][p].Col() - 1; j++){
                    if(idDoG[k][p][i][j] < 0.3)
                        idExt_DoG[k][p][i][j] = false; //remove bad contrast
                }
            }
        }
    }

    //Reject strong edge
    double r, D, Dxx, Dyy, Dxy, TrH, DetH, c,th;
    KImageDouble sample2(igMain);
    th = 10;

    int flag = 0;
    for(int k = 0; k < a; k++){
        for(int p = 0; p < b-2; p++){
            for(int i = 1; i < (int)igDoG[k][p].Row() - 1; i++){
                for(int j = 1; j < (int)igDoG[k][p].Col() - 1; j++){
                    if(idExt_DoG[k][p][i][j]){
                        //reject strong edge
                        //qDebug() << "DoG : " << idExt_DoG[k][p][i][j];
                        r = pow(th+1.0, 2.0) / th; // (11*11) / 10 = 12.1;
                        D = igScale[k][p+1][i][j];
                        Dxx = igScale[k][p+1][i][j+1] + igScale[k][p+1][i][j-1] - 2*D;
                       // qDebug() << "Dxx : " << Dxx;
                        Dyy = igScale[k][p+1][i+1][j] + igScale[k][p+1][i-1][j] - 2*D;
                        //qDebug() << "Dyy : " << Dyy;
                        Dxy = ( (igScale[k][p+1][i+1][j+1] - igScale[k][p+1][i+1][j-1]) - (igScale[k][p+1][i-1][j+1] - igScale[k][p+1][i-1][j-1]) ) / 4.0 ;
                        TrH = Dxx+Dyy;

                        DetH = Dxx*Dyy - Dxy * Dxy;
                        c = TrH * TrH / DetH;
                       // qDebug() << "c : " << c;

                        (c < r ? isKey[k][p][i][j] = 0: isKey[k][p][i][j] = 255);//output_key[k][p][i][j] = igExt_DoG[k][p][i][j]);
                        //flag = 1;   //debug pass all
                        if(flag){
                            isKey[k][p][i][j] = 255;
//                            output_key[k][p][i-1][j-1] = 255; output_key[k][p][i-1][j] = 255; output_key[k][p][i-1][j+1] = 255;
//                            output_key[k][p][i][j-1] = 255; output_key[k][p][i][j] = 255; output_key[k][p][i][j+1] = 255;
//                            output_key[k][p][i+1][j-1] = 255; output_key[k][p][i+1][j] = 255; output_key[k][p][i+1][j+1] = 255;
                            flag = 0;
                        }
                    }
                }
            }
        }
        sample2.HalfSize();
    }

    //KImageDouble **grad_mag;
    //KImageDouble **grad_ori;
    //KImageDouble **grad_mag_sum;
    //KImageDouble **grad_ori_peak;
    double ****grad_mag;
    double ****grad_ori;
    double ****grad_mag_sum;
    double ****grad_ori_peak;
    grad_mag = new double***[a];
    grad_ori = new double***[a];
    grad_mag_sum = new double***[a];
    grad_ori_peak = new double***[a];
    for(int i = 0; i < a; i++){
        grad_mag[i] = new double **[b-2];
        grad_ori[i] = new double **[b-2];
        grad_mag_sum[i] = new double **[b-2];
        grad_ori_peak[i] = new double **[b-2];
        for(int j = 0; j < b-2; j++){
            grad_mag[i][j] = new double *[isKey[i][j].Row()];
            grad_ori[i][j] = new double *[isKey[i][j].Row()];
            grad_mag_sum[i][j] = new double *[isKey[i][j].Row()];
            grad_ori_peak[i][j] = new double *[isKey[i][j].Row()];
            for(int k = 0; k < (int)isKey[i][j].Row();k++){
                grad_mag[i][j][k] = new double[isKey[i][j].Col()];
                grad_ori[i][j][k] = new double[isKey[i][j].Col()];
                grad_mag_sum[i][j][k] = new double[isKey[i][j].Col()];
                grad_ori_peak[i][j][k] = new double[isKey[i][j].Col()];
            }
        }
    }

//    grad_mag= new KImageDouble*[a];
//    grad_ori= new KImageDouble*[a];
//    grad_mag_sum= new KImageDouble*[a];
//    grad_ori_peak= new KImageDouble*[a];
//    for(int i = 0; i < a; i++){
//        grad_mag[i] = new KImageDouble[b-2];
//        grad_ori[i] = new KImageDouble[b-2];
//        grad_mag_sum[i] = new KImageDouble[b-2];
//        grad_ori_peak[i] = new KImageDouble[b-2];
//        for(int j= 0; j < b-2; j++){
//            grad_mag[i][j].Create(isKey[i][j].Row(),isKey[i][j].Col());
//            grad_ori[i][j].Create(isKey[i][j].Row(),isKey[i][j].Col());
//            grad_mag_sum[i][j].Create(isKey[i][j].Row(),isKey[i][j].Col());
//            grad_ori_peak[i][j].Create(isKey[i][j].Row(),isKey[i][j].Col());
//        }
//    }




    double sigma = 2.57; //= => masksize 17
    int half = (int)(3.0 * sigma+0.3);
    qDebug() << "half : " << half;
    int maskSize = half * 2 + 1;

    //gaussian weighted mask
    double scale = 0.0;
    double sigma2 = 2.0*sigma*sigma;
    double con = 1.0 / (2.0 * 3.141592) / (sigma*sigma);

    double g_wMask[17][17];

    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
            g_wMask[i][j] = con * std::exp(-(((double)i-1.0)*((double)i-1.0)+((double)j-1.0)*((double)j-1.0))/sigma2);
            scale += g_wMask[i][j];
        }
    }


    for(int i = 0; i < maskSize; i++){
        for(int j = 0; j < maskSize; j++){
           g_wMask[i][j] *= 255;
        }
    }

    //orientation assignment
    //qDebug() << "grad";
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> key;

    //KImageGray sample3(igMain);

    //
    double dx,dy;
    for(int k = 0; k < a; k++){
        for(int p = 0; p < b - 2; p++){
            for(int i = half+1; i < (int)isKey[k][p].Row() - half - 2; i++){
                for(int j = half+1; j < (int)isKey[k][p].Col() - half - 2; j++){
                    if(isKey[k][p][i][j] == 255){
                        //qDebug() << "grad cal";
                        for(int u = -half; u < half+1; u++){
                            for(int v = -half; v < half+1; v++){
                                dx = (double)igScale[k][p+1][i+u][j+v+1] - (double)igScale[k][p+1][i+u][j+v-1];
                                dy = (double)igScale[k][p+1][i+u+1][j+v] - (double)igScale[k][p+1][i+u-1][j+v];
                                grad_mag[k][p][i+u][j+v] = sqrt(pow(dx,2) + pow(dy,2));
                                grad_ori[k][p][i+u][j+v] = atan2(dy,dx);
                                //qDebug() << " mag" << grad_mag[k][p][i+u][j+v];
                                //qDebug() << " ori" << grad_ori[k][p][i+u][j+v];

                            }
                        }
                        //qDebug() << "work";
                        key.push_back({{k,p},{i,j}});
                    }
                }
            }
        }
    }


    double ang_tmp;
    int vec_idx = 0;
    std::vector<KeyDes> key_vec;
    struct KeyDes desTmp;
    while((int)key.size()!=vec_idx){
        double ang_bucket[36] = {};

        int k = key[vec_idx].first.first;
        int p = key[vec_idx].first.second;
        int i = key[vec_idx].second.first;
        int j = key[vec_idx].second.second;

        for(int u = -half; u < half+1; u++){
            for(int v = -half; v < half+1; v++){
                grad_mag_sum[k][p][i][j] += grad_mag[k][p][i+u][i+v];
                //qDebug() << grad_ori[k][p][i][j] * 57.295779;
                if(grad_ori[k][p][i+u][j+v] >0){
                     ang_tmp = grad_ori[k][p][i+u][j+v] * 57.295779;
                }
                else{
                     ang_tmp = grad_ori[k][p][i+u][j+v] * 57.295779 + 360;
                }
                // =>57.295...  = 1/ 3.141592 * 180;  rad to degree
                ang_bucket[(int)(ang_tmp / 10)] += g_wMask[u+half][v+half]; //gaussian weighted mask
                //grad_ori[k][p][i+u][j+v] = atan2(dy,dx);
            }
        }
        int aMax = 0;
        int MaxIdx = 0;
        for(int u = 0; u < 36; u++){
            if(ang_bucket[u] > aMax){
                aMax = ang_bucket[u];
                MaxIdx = u;
            }
        }
        grad_ori_peak[k][p][i][j] = (double)MaxIdx * 10.0 + 5.0;

        //keypoint orientation peak max 80% add
        for(int u = 0; u < 36; u++){
            if(ang_bucket[u] > aMax * 0.8 && u != MaxIdx){
                desTmp.pX = i;
                desTmp.pY = j;
                desTmp.Octave_idx = k;
                desTmp.scale_idx = p;
                desTmp.ori_deg = (double)u * 10.0 + 5.0;
                key_vec.push_back(desTmp);

                SW_vision::Mark_KeyPoint(output_key[k][p],grad_mag_sum[k][p][i][j],desTmp.ori_deg,i,j);
            }
        }

        //qDebug() << "sum : " <<grad_mag_sum[k][p][i][j];
        //qDebug() << "peak : " << grad_ori_peak[k][p][i][j];


        desTmp.pX = i;
        desTmp.pY = j;
        desTmp.Octave_idx = k;
        desTmp.scale_idx = p;
        desTmp.ori_deg = grad_ori_peak[k][p][i][j];
        key_vec.push_back(desTmp);
        SW_vision::Mark_KeyPoint(output_key[k][p],grad_mag_sum[k][p][i][j],grad_ori_peak[k][p][i][j],i,j);

        vec_idx++;
    }

    int dscrpt_half = 4;
    //int dscrpt_size = 9;
    //descriptor
    double tmp_deg;
    int dir;
    //int peak_dir;
    //std::vector<KeyPoint_descriptor> des_vec;
    KeyPoint_descriptor des_tmp;
    for(int z = 0; z < (int)key_vec.size(); z++ ){
        //qDebug() << key_vec[u].pX;

        int k = key_vec[z].Octave_idx;
        int p = key_vec[z].scale_idx;
        int i = key_vec[z].pX;
        int j = key_vec[z].pY;

        //key_vec Debug
        //SW_vision::Mark_KeyPoint(output_key[k][p],10,key_vec[i].ori_deg,u,j);
        //make descriptor
        //left up
        //180도를 더하는게 맞는지 고려해보기
        int peak_dir;
        peak_dir = (int)(key_vec[z].ori_deg / 45); peak_dir %= 8;
        //peak_dir = 0;
        int patchI, patchJ;
        for(int u = -dscrpt_half; u < 0; u++){
            for(int v = -dscrpt_half; v < 0; v++){
                patchI = (int)((double)v * sin(key_vec[z].ori_deg * 0.017453) + (double)u * cos(key_vec[z].ori_deg * 0.017453)); // 0.017453 => deg to rad
                patchJ = (int)((double)v * cos(key_vec[z].ori_deg * 0.017453) - (double)u * sin(key_vec[z].ori_deg * 0.017453));

                dx = (double)igScale[k][p+1][i+patchI][j+patchJ+1] - (double)igScale[k][p+1][i+patchI][j+patchJ-1];
                dy = (double)igScale[k][p+1][i+patchI+1][j+patchJ] - (double)igScale[k][p+1][i+patchI-1][j+patchJ];
                tmp_deg = atan2(dy,dx);
                if(tmp_deg > 0){
                     tmp_deg = tmp_deg * 57.295779;
                }
                else{
                    tmp_deg = tmp_deg * 57.295779 + 360;
                }

                //tmp_deg = tmp_deg - key_vec[z].ori_deg;
                dir = (int)(tmp_deg  / 45);
                dir = dir - peak_dir;

                if(dir < 0)
                    dir += 8;

                dir %= 8;
                des_tmp.dscrpt[0][0][dir]++;

                //qDebug() << "dir : " << dir;
            }
        }

        //right up
        for(int u = -dscrpt_half; u < 0; u++){
            for(int v = 1; v < dscrpt_half+1; v++){
                patchI = (int)((double)v * sin(key_vec[z].ori_deg * 0.017453) + (double)u * cos(key_vec[z].ori_deg * 0.017453)); // 0.017453 => deg to rad
                patchJ = (int)((double)v * cos(key_vec[z].ori_deg * 0.017453) - (double)u * sin(key_vec[z].ori_deg * 0.017453));

                dx = (double)igScale[k][p+1][i+patchI][j+patchJ+1] - (double)igScale[k][p+1][i+patchI][j+patchJ-1];
                dy = (double)igScale[k][p+1][i+patchI+1][j+patchJ] - (double)igScale[k][p+1][i+patchI-1][j+patchJ];
                tmp_deg = atan2(dy,dx);
                if(tmp_deg > 0){
                     tmp_deg = tmp_deg * 57.295779;
                }
                else{
                    tmp_deg = tmp_deg * 57.295779 + 360;
                }

                //tmp_deg = tmp_deg - key_vec[z].ori_deg;
                dir = (int)(tmp_deg  / 45);
                dir = dir - peak_dir;

                if(dir < 0)
                    dir += 8;

                dir %= 8;
                des_tmp.dscrpt[0][0][dir]++;

                //qDebug() << "dir : " << dir;
            }
        }

        //left down
        for(int u = 1; u < dscrpt_half+1; u++){
             for(int v = -dscrpt_half; v < 0; v++){
                 patchI = (int)((double)v * sin(key_vec[z].ori_deg * 0.017453) + (double)u * cos(key_vec[z].ori_deg * 0.017453)); // 0.017453 => deg to rad
                 patchJ = (int)((double)v * cos(key_vec[z].ori_deg * 0.017453) - (double)u * sin(key_vec[z].ori_deg * 0.017453));

                 dx = (double)igScale[k][p+1][i+patchI][j+patchJ+1] - (double)igScale[k][p+1][i+patchI][j+patchJ-1];
                 dy = (double)igScale[k][p+1][i+patchI+1][j+patchJ] - (double)igScale[k][p+1][i+patchI-1][j+patchJ];
                 tmp_deg = atan2(dy,dx);
                 if(tmp_deg > 0){
                      tmp_deg = tmp_deg * 57.295779;
                 }
                 else{
                     tmp_deg = tmp_deg * 57.295779 + 360;
                 }

                 //tmp_deg = tmp_deg - key_vec[z].ori_deg;
                 dir = (int)(tmp_deg  / 45);
                 dir = dir - peak_dir;

                 if(dir < 0)
                     dir += 8;

                 dir %= 8;
                 des_tmp.dscrpt[0][0][dir]++;

                 //qDebug() << "dir : " << dir;
            }
        }
        //right down
        for(int u = 1; u < dscrpt_half+1; u++){
             for(int v = 1; v < dscrpt_half+1; v++){
                 patchI = (int)((double)v * sin(key_vec[z].ori_deg * 0.017453) + (double)u * cos(key_vec[z].ori_deg * 0.017453)); // 0.017453 => deg to rad
                 patchJ = (int)((double)v * cos(key_vec[z].ori_deg * 0.017453) - (double)u * sin(key_vec[z].ori_deg * 0.017453));

                 dx = (double)igScale[k][p+1][i+patchI][j+patchJ+1] - (double)igScale[k][p+1][i+patchI][j+patchJ-1];
                 dy = (double)igScale[k][p+1][i+patchI+1][j+patchJ] - (double)igScale[k][p+1][i+patchI-1][j+patchJ];
                 tmp_deg = atan2(dy,dx);
                 if(tmp_deg > 0){
                      tmp_deg = tmp_deg * 57.295779;
                 }
                 else{
                     tmp_deg = tmp_deg * 57.295779 + 360;
                 }

                 //tmp_deg = tmp_deg - key_vec[z].ori_deg;
                 dir = (int)(tmp_deg  / 45);
                 dir = dir - peak_dir;

                 if(dir < 0)
                     dir += 8;

                 dir %= 8;
                 des_tmp.dscrpt[0][0][dir]++;

                 //qDebug() << "dir : " << dir;
            }
        }

        des_tmp.Octave_idx = k;
        des_tmp.scale_idx = p;
        des_tmp.pX = i;
        des_tmp.pY = j;
        des_tmp.ori_deg = key_vec[z].ori_deg;

        des_vec.push_back(des_tmp);
        for(int h = 0; h < 8; h++){
            des_tmp.dscrpt[0][0][h] = 0;
            des_tmp.dscrpt[0][1][h] = 0;
            des_tmp.dscrpt[1][0][h] = 0;
            des_tmp.dscrpt[1][1][h] = 0;
        }

        //qDebug() << des_vec[z].dscrpt[0][0][0];
        //qDebug() << "num : " << z;
    }

    delete[] grad_ori_peak;
    delete[] grad_mag_sum;
    delete[] grad_ori;
    delete[] grad_mag;
    delete[] idDoG;
    delete[] isKey;
    delete[] igScale;
    delete[] igDoG;
    delete[] idExt_DoG;
}

void SW_vision::Match_KeyPoint(KImageGray &igMain, KImageGray &igSample, std::vector<KeyPoint_descriptor> &des_vec_org, std::vector<KeyPoint_descriptor> &des_vec_sam, KImageColor &iStk){

    int MatchThreshHold = 100;
    int sY = -1;
    double dTmp = 0;
    int *match_arr = new int[des_vec_org.size()];
    double *matVal_arr = new double[des_vec_org.size()];
    double MS= MatchThreshHold;
    //qDebug() << des_vec_sam.size();
    for(int z = 0; z < (int)des_vec_org.size(); z++){
        //qDebug() << des_vec_org[z].dscrpt[0][0][0];
        for(int y = 0; y <(int)des_vec_sam.size(); y++){
            for(int dir = 0; dir < 8; dir++){
                dTmp += pow(des_vec_org[z].dscrpt[0][0][dir] - des_vec_sam[y].dscrpt[0][0][dir],2);
                dTmp += pow(des_vec_org[z].dscrpt[0][1][dir] - des_vec_sam[y].dscrpt[0][1][dir],2);
                dTmp += pow(des_vec_org[z].dscrpt[1][0][dir] - des_vec_sam[y].dscrpt[1][0][dir],2);
                dTmp += pow(des_vec_org[z].dscrpt[1][1][dir] - des_vec_sam[y].dscrpt[1][1][dir],2);
            }

            if(dTmp < MS){
                MS = dTmp;
                sY = y;
                //qDebug() << "dTmp : " << dTmp;
                //qDebug() << "sY : " << sY;
                //qDebug() << "dTmp : " << dTmp;
                //qDebug() << "MS : " << MS;
            }
            dTmp = 0;

        }
        match_arr[z] = sY;
        matVal_arr[z] = MS;
       // qDebug() << " MS : " << MS;
        MS = MatchThreshHold;
        sY = -1;
        qDebug() << "match " << z << " :" << match_arr[z];

    }


    //overlap matching consider
    //double val_tmp;
    for(int z = 0; z < (int)des_vec_org.size(); z++){
        for(int zz = z+1; zz < (int)des_vec_org.size(); zz++){
            if(match_arr[z] != -1 && match_arr[z] == match_arr[zz]){
                if(matVal_arr[z] > matVal_arr[zz]){
                    match_arr[z] = -1;
                }
                else if(matVal_arr[z] < matVal_arr[zz]){
                    match_arr[zz] = -1;
                }
            }
        }
        //matVal_arr[z]
    }


    //visualization
    KImageColor icTmp1 = igMain.GrayToRGB();
    KImageColor icTmp2 = igSample.GrayToRGB();

    for(int i = 0; i < (int)igMain.Row(); i++){
        for(int j = 0; j < (int)igMain.Col(); j++){
            iStk[i][j] = icTmp1[i][j];
        }

    }
    for(int i = 0; i < (int)igSample.Row(); i++){
        for(int j = 0; j < (int)igSample.Col(); j++){
            iStk[i+igMain.Row()][j] = icTmp2[i][j];
        }

    }


    double theta_rad, dX_circle,dY_circle,pX,pY,pX_s,pY_s;
    int iX_circle,iY_circle;
    double radius = 5;
    for(int z = 0; z < (int)des_vec_org.size(); z = z+10){// z = z+10 => keypoint sampling
        if(match_arr[z] != -1){
            pX = des_vec_org[z].pX;
            pY = des_vec_org[z].pY;

            //octave position consider
            pX = pX * pow(2,des_vec_org[z].Octave_idx);
            pY = pY * pow(2,des_vec_org[z].Octave_idx);
            //draw origin feature
            for(int angle = 0; angle <= 360; angle+= 1){

                theta_rad = (double)angle * 0.01745329; // 0.017453..=>1 / 180 * 3.14592; degree to rad

                dX_circle = (double)pX - (double)(radius * cos(theta_rad));
                dY_circle = (double)pY - (double)(radius * sin(theta_rad));

                iX_circle = (int)dX_circle; iY_circle = (int)dY_circle;

                if(iX_circle > 0 && iY_circle > 0 && iX_circle < (int)iStk.Row() && iY_circle < (int)iStk.Col()){
                   iStk[iX_circle][iY_circle].r = (z * 35 + 51) % 256;
                   iStk[iX_circle][iY_circle].g = (z * 10 + 51) % 256;
                   iStk[iX_circle][iY_circle].b = (z * 49 + 51) % 256;
                }
            }


            pX_s = des_vec_sam[match_arr[z]].pX;
            pY_s = des_vec_sam[match_arr[z]].pY;

            //octave position consider
            pX_s = pX_s * pow(2,des_vec_sam[match_arr[z]].Octave_idx) + (double)igMain.Row();
            pY_s = pY_s * pow(2,des_vec_sam[match_arr[z]].Octave_idx);
            //draw sample feature
            for(int angle = 0; angle <= 360; angle+= 1){

                theta_rad = (double)angle * 0.01745329; // 0.017453..=>1 / 180 * 3.14592; degree to rad

                dX_circle = (double)pX_s - (double)(radius * cos(theta_rad));
                dY_circle = (double)pY_s - (double)(radius * sin(theta_rad));

                iX_circle = (int)dX_circle; iY_circle = (int)dY_circle;

                if(iX_circle > 0 && iY_circle > 0 && iX_circle < (int)iStk.Row() && iY_circle < (int)iStk.Col()){
                   iStk[iX_circle][iY_circle].r = (z * 35 + 51) % 256;
                   iStk[iX_circle][iY_circle].g = (z * 10 + 51) % 256;
                   iStk[iX_circle][iY_circle].b = (z * 49 + 51) % 256;
                }
            }

            double gx, gy, dist, ang_rad;
            gx = pX - pX_s;
            gy = pY - pY_s;
            dist = sqrt(pow(gx,2) + pow(gy,2));

            ang_rad = atan2(gy,gx);

            //Draw Direction
            double dX_dir,dY_dir;
            int iX_dir, iY_dir;
            for(int range = 0; range <= dist; range++){
                dX_dir = (double)pX - (double)(range * cos(ang_rad));
                dY_dir = (double)pY - (double)(range * sin(ang_rad));

                iX_dir = (int)dX_dir; iY_dir = (int)dY_dir;

                if(iX_dir > 0 && iY_dir > 0 && iX_dir < (int)iStk.Row() && iY_dir < (int)iStk.Col()){
                   iStk[iX_dir][iY_dir].r = (z * 35 + 51) % 256;
                   iStk[iX_dir][iY_dir].g = (z * 10 + 51) % 256;
                   iStk[iX_dir][iY_dir].b = (z * 49 + 51) % 256;
                }
            }
        }
    }

    delete[] match_arr;
    delete[] matVal_arr;
}

void SW_vision::Make_DB(std::vector<KeyPoint_descriptor> &des_vec_org, std::string fn){

    std::ofstream DB;
    DB.open(fn);
    if(DB.is_open()){
        qDebug() << "SIFT DB WRITE";
    }

    //std::to_chars(pX,)
    //DB.write(,3);
    DB << des_vec_org.size() << "\n";
    for(int i =0 ; i < (int)des_vec_org.size(); i++){
        //des_vec_org[i].
        DB << des_vec_org[i].Octave_idx << "\n";
        //qDebug() << des_vec_org[i].ori_deg;
        DB << des_vec_org[i].ori_deg << "\n";
        DB << des_vec_org[i].pX << "\n";
        DB << des_vec_org[i].pY << "\n";
        DB << des_vec_org[i].scale_idx << "\n";
        //DB << des_vec_org[i].dscrpt[0][0][1];
        //DB.write("\n",1);
    }
}

void SW_vision::Window_weight(KImageDouble &Window, int size, double sigma){
    KMatrix kernel = KGaussianMulti::Kernel_2D(sigma, size);
    Window.Create(size*size, size*size);

    int j = -1;
    for(int i = 0; i < size*size; i++){
        if( (i % size) == 0) j++;
        Window[i][i] = kernel[j][i%size];

        //qDebug() << Window[i][i];
    }


}

void SW_vision::ImageSub_double(KImageGray &igMain, KImageGray &igSub, KImageDouble &output){
    output.Create(igMain.Row(),igMain.Col());

    if(igMain.Row() != igSub.Row() || igMain.Col() != igSub.Col()) return;

    for(int i = 0; i < (int)igMain.Row(); i++){
        for(int j = 0; j < (int)igMain.Col(); j++){
            output[i][j] = igMain[i][j] - igSub[i][j];
        }
    }
}
void SW_vision::crop_double(KImageDouble &idMain, KImageDouble &output, int pX, int pY, int width, int height){
    //qDebug() << "crop start";
    output.Create(height,width);
    for(int i = pY, ii= 0; i < pY+height; i++,ii++){
        for(int j = pX,jj = 0; j < pX+width;j++,jj++){
            output[ii][jj] = idMain[i][j];
        }
    }

    //qDebug() << "crop End";
}

void SW_vision::diff_double(KImageGray &igMain, KImageDouble &d_dx, KImageDouble &d_dy){
    d_dx.Create(igMain.Row(),igMain.Col());
    d_dy.Create(igMain.Row(),igMain.Col());

    for(int i = 1; i < (int)igMain.Row()-1; i++){
        for(int j = 1; j < (int)igMain.Col()-1; j++){
            d_dx[i][j] = igMain[i][j+1] - igMain[i][j-1];
            d_dy[i][j] = igMain[i+1][j] - igMain[i-1][j];
        }
    }
}

void SW_vision::MakeMat_2Col(KImageDouble &id0, KImageDouble &id1, KImageDouble &output, int size){
    output.Create(size*size, 2);
    //qDebug() << "MakeMat";
    for(int i = 0; i < size*size; i++){
        //qDebug() << "1" << i;
        output[i][0] = id0[(int)(i/size)][i%size];
        output[i][1] = id1[(int)(i/size)][i%size];
        //qDebug() << output[i][0] << output[i][1];
    }
    //qDebug() << "MakeMat End";
}

void SW_vision::MakeMat_1Col(KImageDouble &idMain, KImageDouble &output, int size){
    output.Create(size*size, 1);

    for(int i = 0; i < size*size; i++){
        //qDebug() << "1col" << i;
        output[i][0] = idMain[(int)(i/size)][i%size];
        //qDebug() << output[i][0];
    }
}
void SW_vision::TranMat(KImageDouble &idMain, KImageDouble &output){
    output.Create(idMain.Col(),idMain.Row());

    for(int i =0; i < (int)idMain.Row();i++ ){
        for(int j = 0; j < (int)idMain.Col(); j++){
            output[j][i] = idMain[i][j];
        }
    }
}
void SW_vision::MultiMat(KImageDouble &id0, KImageDouble &id1, KImageDouble &output){
    if(id0.Col() != id1.Row()) return; // multiply condition consider

    output.Create(id0.Row(),id1.Col());
    //qDebug() << "multi start";
    for(int i = 0; i < (int)id0.Row(); i++){
        for(int j =0; j < (int)id1.Col(); j++){
           for(int k = 0; k < (int)id1.Row(); k++){
                output[i][j] += id0[i][k] * id1[k][j];
           }
        }
    }
    //qDebug() << "multi End";
}

void SW_vision::InvMat22(KImageDouble &idMain, KImageDouble &output){
    if(idMain.Row() != idMain.Col() || idMain.Row() != 2) return; //Inverse condition condider
    double det = idMain[0][0] * idMain[1][1] - idMain[0][1]*idMain[1][0];
    //qDebug() << "id " << idMain[0][0] << idMain[1][1] << idMain[0][1] << idMain[1][0];
    //qDebug() << "det" << det;

    output.Create(2,2);

    if(det == 0){
        output[0][0] = 0;
        output[0][1] = 0;
        output[1][0] = 0;
        output[1][1] = 0;
        //qDebug() << "det 0 ";
        return; //Inverse condition consider
    }



    output[0][0] = idMain[1][1] * (1 / det);
    output[0][1] = -idMain[1][0] * (1 / det);
    output[1][0] = -idMain[0][1] * (1 / det);
    output[1][1] = idMain[0][0] * (1 / det);



}

void SW_vision::DrawLine(KImageColor &igMain, int pX, int pY, double u, double v){
    int magWeight = 2;
    double mag = (std::abs(u) + std::abs(v));
    //qDebug() << "mag" <<mag;
    //qDebug() << "u" << u << "v" << v;

    igMain._ppA[pY][pX] = {50, 240, 150};
    int i,y,x;
    for( i = 0; i<(int)mag*magWeight; i++){
        y = (int)((double)pY+v*(double)i/mag);
        x = (int)((double)pX+u*(double)i/mag);

        if(y > (int)igMain.Row()-1 || y < 0|| x > (int)igMain.Col()-1 || x < 0) return;

        igMain[y][x] = {50, 250, 150};
    }
}

void SW_vision::OpticalFlow(KImageGray &igMain_0, KImageGray &igMain_1, KImageColor &output, int size){
    KImageDouble Window, subContain, d_dx, d_dy;

    subContain.Create(igMain_0.Row(),igMain_1.Col());
    int half = (int)(size/2);

    //qDebug() << "window";
    SW_vision::Window_weight(Window,size,1);
    //qDebug() << "Sub";
    SW_vision::ImageSub_double(igMain_0,igMain_1,subContain);
    //qDebug() << "diff";
    SW_vision::diff_double(igMain_0,d_dx,d_dy);

    KImageDouble Ix, Iy, It;
    KImageDouble A, At, d, b, AtW,AtWb,AtWA, AtWAi;
    output.Create(igMain_0.Row(),igMain_0.Col());
    output = igMain_0.GrayToRGB();
    double u, v;
    for(int i = half; i < (int)igMain_0.Row()-half; i = i + 5){
        //qDebug() << i;
        for(int j = half; j < (int)igMain_0.Col()-half; j = j + 5){
            SW_vision::crop_double(d_dx, Ix, j-half, i-half, size, size);
            SW_vision::crop_double(d_dy,Iy,j-half,i-half,size,size);
            SW_vision::crop_double(subContain,It,j-half,i-half,size,size);

            SW_vision::MakeMat_2Col(Ix,Iy,A,size);
            SW_vision::MakeMat_1Col(It,b,size);
            //qDebug() << "tran";
            SW_vision::TranMat(A,At);

            //qDebug() << "multi";
            SW_vision::MultiMat(At,Window,AtW);
            SW_vision::MultiMat(AtW,b,AtWb);
            SW_vision::MultiMat(AtW,A,AtWA);
            //qDebug() << "inv";
            SW_vision::InvMat22(AtWA,AtWAi);
            //qDebug() << "d";
            SW_vision::MultiMat(AtWAi,AtWb,d);
            u = d[0][0];
            v = d[1][0];
            //qDebug() << "draw";
            SW_vision::DrawLine(output,j,i,u,v);
        }
    }


    qDebug() << "End";
}
