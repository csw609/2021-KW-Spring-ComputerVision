#include <QFileDialog>
#include <QPainter>

#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include "sw_vision.h"
#include "QDebug"
MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _plpImageForm       = new KPtrList<ImageForm*>(10,false,false);
    _q_pFormFocused     = 0;

    //객체 맴버의 초기화

    //get a current directory
    char st[100];
    GetCurrentDirectoryA(100,st);

    //리스트 출력창을 안보이게
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{ 
    delete ui;         
    delete _plpImageForm;


}

void MainFrame::CloseImageForm(ImageForm *pForm)
{
    //ImageForm 포인터 삭제
    _plpImageForm->Remove(pForm);

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //관련 객체 삭제

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        ui->buttonSepiaTone->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );    

    }
    else if(ui->tabWidget->currentIndex() == 1)
    {

    }
    else if(ui->tabWidget->currentIndex() == 2)
    {

    }    
}

void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{

    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}


void MainFrame::on_buttonOpen_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성    
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "OPEN", this);

    _plpImageForm->Add(q_pForm);

    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}

void MainFrame::on_buttonSepiaTone_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
        KImageColor   icMain;
        if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
            icMain = _q_pFormFocused->ImageColor();
        else
            return;

        //hue, saturation 값 가져오기
        double dHue = ui->spinHue->value();
        double dSat = ui->spinSaturation->value(); // 위와 같은 식으로
        if (dHue == 360)
            dHue = 0;
        //
        //icMain 변환
        //:
        SW_vision temp;

        KImageGray hueImage(icMain.Row(),icMain.Col());
        KImageGray satImage(icMain.Row(),icMain.Col());
        KImageGray valImage(icMain.Row(),icMain.Col());

        temp.RGBtoH(icMain, hueImage);
        temp.RGBtoS(icMain, satImage);
        temp.RGBtoV(icMain, valImage);

        temp.RGBContHS(icMain, dHue, dSat);

        //출력을 위한 ImageForm 생성
        ImageForm*  q_pForm = new ImageForm(icMain, "Sepia Tone", this);
        ImageForm*  q_pFormHue = new ImageForm(hueImage, "Hue", this);
        ImageForm*  q_pFormSat = new ImageForm(satImage, "Saturation", this);
        ImageForm*  q_pFormVal = new ImageForm(valImage, "Value", this);

        _plpImageForm->Add(q_pForm);
        _plpImageForm->Add(q_pFormHue);
        _plpImageForm->Add(q_pFormSat);
        _plpImageForm->Add(q_pFormVal);

        q_pForm->show();
        q_pFormHue->show();
        q_pFormSat->show();
        q_pFormVal->show();

        //UI 활성화 갱신
        UpdateUI();
}


void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {        
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}

void MainFrame::on_spinHue_valueChanged(const QString &arg1)
{
    //출력창 탐색
    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Sepia Tone"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    KImageColor   icMain;

        icMain = q_pForm->ImageColor();
        //hue, saturation 값 가져오기
        double dHue = ui->spinHue->value();
        double dSat = ui->spinSaturation->value(); // 위와 같은 식으로
        if (dHue == 360)
            dHue = 0;
        //
        //icMain 변환
        //:
        SW_vision temp;
        temp.RGBContHS(icMain, dHue, dSat);
        //출력을 위한 ImageForm 생성

        //ImageForm*  q_pForm = new ImageForm(icMain, "Sepia Tone", this);
        //q_pForm->show();
        if(q_pForm)
            q_pForm->Update(icMain);
        else{
            q_pForm = new ImageForm(icMain,"Sepia Tone",this);
            q_pForm -> show();
            _plpImageForm->Add(q_pForm);
        }
        //UI 활성화 갱신
        UpdateUI();
}

void MainFrame::on_spinHue_textChanged(const QString &arg1)
{

}

void MainFrame::on_spinHue_valueChanged(int arg1)
{

}

void MainFrame::on_spinSaturation_textChanged(const QString &arg1)
{
    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Sepia Tone"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    KImageColor   icMain;
    icMain = q_pForm->ImageColor();
    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->value();
    double dSat = ui->spinSaturation->value(); // 위와 같은 식으로
    if (dHue == 360)
        dHue = 0;
    //
    //icMain 변환
    //:
    SW_vision temp;
    temp.RGBContHS(icMain, dHue, dSat);
    //출력을 위한 ImageForm 생성

    //ImageForm*  q_pForm = new ImageForm(icMain, "Sepia Tone", this);
    //q_pForm->show();
    if(q_pForm)
        q_pForm->Update(icMain);
    else{
        q_pForm = new ImageForm(icMain,"Sepia Tone",this);
        q_pForm -> show();
        _plpImageForm->Add(q_pForm);
    }
    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_ButtonOtsu_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    KImageGray gray(icMain.Row(),icMain.Col());
    KImageColor labeled(icMain.Row(), icMain.Col());

        SW_vision temp;
        temp.RGBThreshHolding(icMain, gray);
        if(ui->neighbor_4->isChecked()){
            temp.GrayLabeling_4(gray,labeled);
        }
        else if(ui->neighbor_8->isChecked()){
            temp.GrayLabeling_8(gray,labeled);
        }
            ImageForm*  q_pForm1 = new ImageForm(gray, "Otsu ThreshHolding", this);
            ImageForm*  q_pForm2 = new ImageForm(labeled, "Image Labeling", this);

            _plpImageForm->Add(q_pForm1);
            _plpImageForm->Add(q_pForm2);

            q_pForm1->show();
            q_pForm2->show();

            UpdateUI();
}

void MainFrame::on_pushButton_clicked()
{
    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Image Labeling"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }

    KImageColor   icMain;
    icMain = q_pForm->ImageColor();

    KImageColor eroded(icMain.Row(),icMain.Col());
    KImageColor dilated(icMain.Row(),icMain.Col());

    SW_vision temp;
    unsigned char kernelSize = 3;
    if(ui->kernel_3->isChecked()){
        kernelSize = 3;
    }
    else if(ui->kernel_5->isChecked()){
        kernelSize = 5;
    }

    temp.Erosion_color(icMain, eroded,kernelSize);
    temp.Dilation_color(icMain, dilated,kernelSize);

    ImageForm* q_pForm1 = new ImageForm(eroded, "Erosion", this);
    ImageForm* q_pForm2 = new ImageForm(dilated, "Dilation", this);

    q_pForm1 -> show();
    q_pForm2 -> show();

    _plpImageForm->Add(q_pForm1);
    _plpImageForm->Add(q_pForm2);

    UpdateUI();
}

void MainFrame::on_HistoEqu_clicked()
{
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor equalized(icMain.Row(),icMain.Col());

    SW_vision::HistoEqu(icMain, equalized);

    ImageForm* q_pForm1 = new ImageForm(equalized, "Histogram Equalization", this);

    q_pForm1 -> show();

    _plpImageForm->Add(q_pForm1);

    UpdateUI();
}

void MainFrame::on_HistoMatch_clicked()
{
    KImageColor   icT, icS;

    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->windowTitle() == "sigol-t.bmp"){
            q_pForm = (*_plpImageForm)[i];
            qDebug() << q_pForm->windowTitle();
            icT = q_pForm->ImageColor();
            break;
        }
        else{
            qDebug() << "none_t";
        }
    }


    ImageForm *q_pForm0 =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->windowTitle() == "sigol-s.bmp"){
            q_pForm0 = (*_plpImageForm)[i];
            qDebug() << q_pForm0->windowTitle();
             icS = q_pForm0->ImageColor();
            break;
        }
        else{
            qDebug() << "none_s";
        }
    }


    KImageColor matched(icT.Row(),icT.Col());

    SW_vision::HistoMatch(icT,icS,matched);

    ImageForm* q_pForm1 = new ImageForm(matched, "Histogram Matching", this);

    q_pForm1 -> show();

    _plpImageForm->Add(q_pForm1);

    UpdateUI();
}

void MainFrame::on_noiseButton_clicked()
{
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor G_Noise(icMain.Row(),icMain.Col());
    KImageColor SP_Noise(icMain.Row(),icMain.Col());
    // filter는 버튼 따로 만들기
    KImageColor G_BoxFilter(icMain.Row(),icMain.Col());
    KImageColor SP_BoxFilter(icMain.Row(),icMain.Col());
    KImageColor G_MedianFilter(icMain.Row(),icMain.Col());
    KImageColor SP_MedianFilter(icMain.Row(),icMain.Col());
    KImageColor G_GaussFilter(icMain.Row(),icMain.Col());
    KImageColor SP_GaussFilter(icMain.Row(),icMain.Col());


    SW_vision::GaussianNoise(icMain, G_Noise);
    SW_vision::SaltPepper(icMain,SP_Noise);

    char maskSize = ui->spinSize->value();
    double sigma = ui->spinSigma->value();

    SW_vision::BoxFilter(G_Noise, G_BoxFilter, maskSize);
    SW_vision::BoxFilter(SP_Noise, SP_BoxFilter, maskSize);

    SW_vision::MedianFilter(G_Noise, G_MedianFilter, maskSize);
    SW_vision::MedianFilter(SP_Noise, SP_MedianFilter, maskSize);

    SW_vision::GaussianFilter(G_Noise, G_GaussFilter, sigma, maskSize);
    SW_vision::GaussianFilter(G_Noise, SP_GaussFilter, sigma, maskSize);

    ImageForm* q_pForm1 = new ImageForm(G_Noise, "Gaussian Noise", this);
    ImageForm* q_pForm2 = new ImageForm(SP_Noise, "Salt and Pepper Noise", this);


    ImageForm* q_pForm3 = new ImageForm(G_BoxFilter, "Gaussian Noise - box", this);
    ImageForm* q_pForm4 = new ImageForm(SP_BoxFilter, "Salt and Pepper Noise - box", this);

    ImageForm* q_pForm5 = new ImageForm(G_MedianFilter, "Gaussian Noise - Median", this);
    ImageForm* q_pForm6 = new ImageForm(SP_MedianFilter, "Salt and Pepper Noise - Median", this);

    ImageForm* q_pForm7 = new ImageForm(G_GaussFilter, "Gaussian Noise - Gauss", this);
    ImageForm* q_pForm8 = new ImageForm(SP_GaussFilter, "Salt and Pepper Noise - Gauss", this);

    q_pForm1 -> show();
    q_pForm2 -> show();

    q_pForm3 -> show();
    q_pForm4 -> show();

    q_pForm5 -> show();
    q_pForm6 -> show();

    q_pForm7 -> show();
    q_pForm8 -> show();

    _plpImageForm->Add(q_pForm1);
    _plpImageForm->Add(q_pForm2);

    _plpImageForm->Add(q_pForm3);
    _plpImageForm->Add(q_pForm4);

    _plpImageForm->Add(q_pForm5);
    _plpImageForm->Add(q_pForm6);

    _plpImageForm->Add(q_pForm7);
    _plpImageForm->Add(q_pForm8);

    UpdateUI();


}

void MainFrame::on_Canny_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageGray cannyEdge(igMain.Row(),igMain.Col());

    double sigma = ui->SpinCannySigma->value();
    int ThreshHigh = ui->spinHigh->value();
    int ThreshLow = ui->spinLow->value();
    SW_vision::CannyEdge(igMain, cannyEdge, sigma,ThreshHigh,ThreshLow);

    ImageForm* q_pForm1 = new ImageForm(cannyEdge, "Canny Edge Operators", this);

    q_pForm1 -> show();

    _plpImageForm->Add(q_pForm1);

    UpdateUI();
}

void MainFrame::on_GenHough_button_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageGray GHough(igMain.Row(), igMain.Col());

    SW_vision::GHoughTransform(igMain, GHough,"plug.txt");

    ImageForm* q_pForm1 = new ImageForm(GHough, "Generalized Hough Transform", this);

    q_pForm1 -> show();

    _plpImageForm->Add(q_pForm1);

    UpdateUI();
}

void MainFrame::on_CHough_button_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageGray CHough(igMain.Row(), igMain.Col());

    SW_vision::CHoughTransform(igMain, CHough, 51.5);

    ImageForm* q_pForm1 = new ImageForm(CHough, "Circle Hough Transform", this);

    q_pForm1 -> show();

    _plpImageForm->Add(q_pForm1);

    UpdateUI();
}

void MainFrame::on_SIFT_button_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN"){

        igMain = _q_pFormFocused->ImageGray();
        qDebug() << _q_pFormFocused->windowTitle();
    }
    else
        return;
    KImageGray igSample2;
    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->windowTitle() == "Sample.pgm"){
            q_pForm = (*_plpImageForm)[i];
            qDebug() << q_pForm->windowTitle();
            igSample2 = q_pForm->ImageGray();
            //qDebug() << "There is Sample";
            break;
        }

    }




    int row = igMain.Row();
    int col = igMain.Col();

    double sigma = ui->spinSIFT_sigma->value();

    int nDim = std::min(row,col);
    int nOctaves = std::min( (int)log((double)nDim/ log(2.0)) - 2, 3);

    KImageGray **s_space;
    KImageGray **d_space;
    KImageDouble **tmp;
    KImageGray **keypoint;
    KImageGray **keypoint_sam;

    SW_vision::Gaussian_DOG_scale_retD(igMain, s_space,d_space,tmp,sigma);

    //stick place
    KImageGray scale_sum(1080,1920);
    KImageGray dog_sum(1080,1920);

    KImageGray keypoint_sum(1080,1920);
    KImageGray keypoint_sam_sum(1080,1920);
    //scale, dog image stick
    SW_vision::stick_gray(s_space,scale_sum,nOctaves,6);
    SW_vision::stick_gray(d_space,dog_sum,nOctaves,5);

    //debug image
    KImageGray **debg;
    KImageGray **debg_sam;
    KImageGray debug_sum(1080,1920);

    //descriptor vector
    std::vector<KeyPoint_descriptor> des_vec_org;
    std::vector<KeyPoint_descriptor> des_vec_sam;
    KImageGray igSample;
    KPoint a;
    a._dX = 320;
    a._dY = 150;
    igSample = igSample2.Rotate(0.785398*2,a);
    //igSample = igSample2.Crop(100,100,200,200);
    //igSample = igSample2;
    SW_vision::DoG_Keypoint(igMain,keypoint,debg, des_vec_org);
    SW_vision::DoG_Keypoint(igSample,keypoint_sam,debg_sam,des_vec_sam);


    SW_vision::stick_gray(debg_sam,debug_sum,nOctaves,3);
    SW_vision::stick_gray(keypoint,keypoint_sum,nOctaves,3);
    SW_vision::stick_gray(keypoint_sam,keypoint_sam_sum,nOctaves,3);


    KImageColor iStk(igMain.Row() + igSample.Row(),_MAX(igMain.Col(),igSample.Col()));
    SW_vision::Match_KeyPoint(igMain, igSample, des_vec_org,des_vec_sam,iStk);

    SW_vision::Make_DB(des_vec_org,"mountain.txt");
    //image print
    ImageForm* q_pForm1 = new ImageForm(scale_sum, "scale Space", this);
    ImageForm* q_pForm2 = new ImageForm(dog_sum, "DoG Space", this);
    ImageForm* q_pForm3 = new ImageForm(keypoint_sum, "keyPoint", this);
    ImageForm* q_pForm4 = new ImageForm(iStk, "Matching Image", this);
    ImageForm* q_pForm5 = new ImageForm(keypoint_sam_sum, "Sample keyPoint", this);


    q_pForm1 -> show();
    q_pForm2 -> show();
    q_pForm3 -> show();
    q_pForm4 -> show();
    q_pForm5 -> show();

    _plpImageForm->Add(q_pForm1);
    _plpImageForm->Add(q_pForm2);
    _plpImageForm->Add(q_pForm3);
    _plpImageForm->Add(q_pForm4);
    _plpImageForm->Add(q_pForm5);

    UpdateUI();
    delete [] tmp;
    delete [] debg;
    delete [] s_space;
    delete [] d_space;
}

void MainFrame::on_Optical_button_clicked()
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    QString ig1 = QString::fromStdString("./hw08/yos.01.pgm");
    QString ig2 = QString::fromStdString("./hw08/yos.02.pgm");

    ImageForm *q_pForm = new ImageForm(ig1,"ig1", this);
    qDebug() << "file open";
    igMain1 = q_pForm->ImageGray();

    ImageForm * q_pForm1 = new ImageForm(ig2,"ig2",this);
    igMain2 = q_pForm1->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    SW_vision::OpticalFlow(igMain1,igMain2,Optical,ui->spinWSize->value());

    qDebug() << "Optical Complete";
    ImageForm* q_pForm2 = new ImageForm(Optical, "Optical Flow", this);

    _plpImageForm->Add(q_pForm2);
    q_pForm2 -> show();
    UpdateUI();
}

void MainFrame::on_OptcNext_button_clicked()
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Optical Flow"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    int num = ui->spinOptc->value();

    std::string optcNum = std::to_string(num);
    std::string optcNum2 = std::to_string(num-1);
    std::string name1, name2;

    if(num > 9){
        name1 = optcNum;
    }
    else{
        name1 = "0" + optcNum;
        name2 = "0" + optcNum2;
    }
    if(num > 10){
        name2 = optcNum2;
    }

    QString ig1 = QString::fromStdString("./hw08/yos." + name1 + ".pgm");
    QString ig2 = QString::fromStdString("./hw08/yos." + name2 + ".pgm");

    ImageForm *q_pForm1 = new ImageForm(ig1,"OPEN", this);
    //qDebug() << "file open";
    igMain1 = q_pForm1->ImageGray();

    ImageForm *q_pForm2 = new ImageForm(ig2,"OPEN",this);
    igMain2 = q_pForm2->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    SW_vision::OpticalFlow(igMain1,igMain2,Optical,ui->spinWSize->value());


    if(q_pForm)
        q_pForm->Update(Optical);
    else{
        q_pForm = new ImageForm(Optical,"Optical Flow",this);
        q_pForm -> show();
        _plpImageForm->Add(q_pForm);
    }
    //UI 활성화 갱신
    UpdateUI();
    ui->spinOptc->setValue(num+1);
    delete q_pForm1;
}

void MainFrame::on_spinOptc_textChanged(const QString &arg1)
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Optical Flow"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    int num = ui->spinOptc->value();

    std::string optcNum = std::to_string(num);
    std::string optcNum2 = std::to_string(num-1);
    std::string name1, name2;

    if(num > 9){
        name1 = optcNum;
    }
    else{
        name1 = "0" + optcNum;
        name2 = "0" + optcNum2;
    }
    if(num > 10){
        name2 = optcNum2;
    }

    QString ig1 = QString::fromStdString("./hw08/yos." + name1 + ".pgm");
    QString ig2 = QString::fromStdString("./hw08/yos." + name2 + ".pgm");

    ImageForm *q_pForm1 = new ImageForm(ig1,"OPEN", this);
    //qDebug() << "file open";
    igMain1 = q_pForm1->ImageGray();

    ImageForm *q_pForm2 = new ImageForm(ig2,"OPEN",this);
    igMain2 = q_pForm2->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    SW_vision::OpticalFlow(igMain1,igMain2,Optical,ui->spinWSize->value());

    if(q_pForm)
        q_pForm->Update(Optical);
    else{
        q_pForm = new ImageForm(Optical,"Optical Flow",this);
        q_pForm -> show();
        _plpImageForm->Add(q_pForm);
    }
    //UI 활성화 갱신
    UpdateUI();
    //ui->spinOptc->setValue(num+1);
    delete q_pForm1;
}
