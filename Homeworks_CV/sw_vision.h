#ifndef SW_VISION_H
#define SW_VISION_H
#include "kfc.h"
#include <string>
#include <vector>

struct KeyDes{
    int pX;
    int pY;
    int Octave_idx;
    int scale_idx;
    double ori_deg;
};

struct KeyPoint_descriptor{
    int pX;
    int pY;
    int Octave_idx;
    int scale_idx;
    double ori_deg;
    int dscrpt[2][2][8];
};


class SW_vision
{
public:
    SW_vision();

    static void RGBContHS(KImageColor &icMain , double dHue, double dSat);
    static void RGBtoH(KImageColor &icMain, KImageGray &hueImage); //RGB에서 Hue추출
    static void RGBtoS(KImageColor &icMain, KImageGray &satImage); //RGB에서 Saturation추출
    static void RGBtoV(KImageColor &icMain, KImageGray &valImage); //RGB에서 Value추출

    static void RGBThreshHolding(KImageGray &icMain, KImageGray &gray);//RGB영상 otsuThresh holding

    static void GrayLabeling_8(KImageGray &gray, KImageColor &color); //Gray영상 8 neighbor labeling
    static void GrayLabeling_4(KImageGray &gray, KImageColor &color); //Gray영상 4 neighbor labeling

    static void Erosion_color(KImageColor &color, KImageColor &erosion, unsigned char kernelSize);
    static void Dilation_color(KImageColor &color, KImageColor &erosion, unsigned char kernelSize);

    static void HistoEqu(KImageColor &color, KImageColor &equalize);
    static void HistoMatch(KImageColor &color_t, KImageColor &color_s, KImageColor &match);

    static void GaussianNoise(KImageColor &icMain, KImageColor &noise);
    static void SaltPepper(KImageColor &icMain, KImageColor &noise);

    static void BoxFilter(KImageColor &icMain, KImageColor &filter, char maskSize=3);
    static void GaussianFilter(KImageColor &icMain, KImageColor &filter, double sigma=1, char maskSize=3);
    static void MedianFilter(KImageColor &icMain, KImageColor &filter, char maskSize=3);



    static void CannyEdge(KImageGray &igMain, KImageGray &edge, double sigma, int high, int low);
    static void CannyEdge_retEdgeDir(KImageGray &igMain, KImageGray &edge, unsigned char **&direction, double sigma, int high, int low);
    static void CannyEdge_retGrad(KImageGray &igMain, KImageGray &edge, int **&dX, int **&dY, double sigma, int high, int low);

    static void GHoughTransform(KImageGray &igMain, KImageGray &output, std::string table); //Generalized houghtransform
    static void CHoughTransform(KImageGray &igMain, KImageGray &output, double radius); //circle hough trangsform

    static void GaussianFilter_gray(KImageGray &igMain, KImageGray &output, double sigma=1);
    static void GaussianFilter_double(KImageGray &igMain, KImageDouble &output, double sigma=1);

    static void Gaussian_DOG_scale_retD(KImageGray &igMain,KImageGray **&output_scale, KImageGray **&output_DoG, KImageDouble **&d_output_DoG, double dSigma = 2.0);

    static void stick_gray(KImageGray **&input_arr, KImageGray &output, int a, int b); // a => num of octaves, b => num of scale space

    static void DoG_Extrema(KImageDouble **&idDoG, bool ****&idExt_DoG,int a, int b); // a => num of octaves, b => num of DoG space

    static void Mark_KeyPoint(KImageGray &igScale, double mag, double ori_deg,int pX, int pY);

    static void DoG_Keypoint(KImageGray &igMain, KImageGray **&output_key, KImageGray **&debg, std::vector<KeyPoint_descriptor> &des_vec);

    static void Match_KeyPoint(KImageGray &igMain, KImageGray &igSample, std::vector<KeyPoint_descriptor> &des_vec_org,std::vector<KeyPoint_descriptor> &des_vec_sam, KImageColor &iStk);

    static void Make_DB(std::vector<KeyPoint_descriptor> &des_vec_org, std::string fn);

    static void Window_weight(KImageDouble &Window, int size, double sigma = 1.0);
    static void ImageSub_double(KImageGray &igMain, KImageGray &igSub, KImageDouble &output);
    static void diff_double(KImageGray &igMain, KImageDouble &d_dx, KImageDouble &d_dy);
    static void crop_double(KImageDouble &idMain, KImageDouble &output, int pX, int pY, int width, int height);
    static void MakeMat_2Col(KImageDouble &id0, KImageDouble &id1, KImageDouble &output, int size);
    static void MakeMat_1Col(KImageDouble &idMain, KImageDouble &output, int size);
    static void TranMat(KImageDouble &idMain, KImageDouble &output);
    static void MultiMat(KImageDouble &id0, KImageDouble &id1, KImageDouble &output);
    static void InvMat22(KImageDouble &idMain, KImageDouble &output);

    static void DrawLine(KImageColor &igMain, int pX, int pY, double u, double v);

    static void OpticalFlow(KImageGray &igMain_0,KImageGray &igMain_1, KImageColor &output, int size);
};

#endif // SW_VISION_H
