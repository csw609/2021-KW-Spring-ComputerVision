#include "imageform.h"
#include "ui_imageform.h"
#include "mainframe.h"

ImageForm::ImageForm(const QString& q_stFile, const QString& q_stID, MainFrame* owner) :  QWidget(0), ui(new Ui::ImageForm)
{
    ui->setupUi(this);

    this->setEnabled(true);

    //ImageForm의 ID
    _q_stID              = q_stID;
    setWindowTitle(KString(q_stFile.toStdString().c_str()).FileNameWithExt().Address());

    //MainForm의 주소를 저장
    _q_MainFrame    = owner;

    //이미지 읽어들임
    _q_bmpMain   = new QImage;   //디스플레이를 위한 이미지 생성
    _q_bmpMain->load(q_stFile);

    //영상처리용 메모리와 공유 설정
    if(_q_bmpMain->format() == QImage::Format_Indexed8)    
        _igMain.Create(_q_bmpMain->height(),_q_bmpMain->width(),_q_bmpMain->bits());

    else if(_q_bmpMain->format() == QImage::Format_RGB32)
        _icMain.Create(_q_bmpMain->height(),_q_bmpMain->width(), (KCOLOR32*)_q_bmpMain->bits());

    else if(_q_bmpMain->format() == QImage::Format_Grayscale8)
        _igMain.Create(_q_bmpMain->height(),_q_bmpMain->width(), _q_bmpMain->bits());

    //ImageForm의 출력 위치 및 크기 설정
    static int   nXo, nYo=-30;
    QRect       q_rcGeom = _q_MainFrame->geometry();

    setGeometry(q_rcGeom.left() - _q_bmpMain->width() -  (nXo+= 20), q_rcGeom.top()  + (nYo += 30),
                        _q_bmpMain->width(),_q_bmpMain->height());
    focusInEvent(0);
}

ImageForm::ImageForm(const KImageColor& icImg, const QString& q_stID, MainFrame* owner) :  QWidget(0),  ui(new Ui::ImageForm)
{
    ui->setupUi(this);

    //ImageForm의 ID
    _q_stID              = q_stID;
    setWindowTitle(_q_stID);

    //MainForm의 주소를 저장
    _q_MainFrame    = owner;

    //이미지 읽어들임
    _q_bmpMain      = new QImage(icImg.Col(), icImg.Row(), QImage::Format_RGB32);
    memcpy(_q_bmpMain->bits(), icImg.Address(), icImg.Size() * sizeof(KCOLOR32));

    //영상처리용 메모리와 공유 설정
    _icMain.Create(_q_bmpMain->height(), _q_bmpMain->width(), (KCOLOR32*)_q_bmpMain->bits());

    //ImageForm의 출력 위치 및 크기 설정
    static int   nXo, nYo=-30;
    QRect       q_rcGeom = _q_MainFrame->geometry();

    setGeometry(q_rcGeom.right() +  (nXo+= 20), q_rcGeom.top()  + (nYo += 30),
                        _q_bmpMain->width(),_q_bmpMain->height());
    focusInEvent(0);
}


ImageForm::ImageForm(const KImageGray& igImg, const QString& q_stID, MainFrame* owner) :  QWidget(0),  ui(new Ui::ImageForm)
{
    ui->setupUi(this);

    //ImageForm의 ID
    _q_stID              = q_stID;
    setWindowTitle(_q_stID);

    //MainForm의 주소를 저장
    _q_MainFrame    = owner;

    //이미지 읽어들임 & 칼라 테이블 설정
    _q_bmpMain      = new QImage( igImg.Col(), igImg.Row(), QImage::Format_Indexed8);
    if(igImg.Col()%4 == 0)
        memcpy(_q_bmpMain->bits(), igImg.Address(), igImg.Size());
    else
    {
        int nWidth = igImg.Col() +  4 - igImg.Col()%4;
        for(int i=0; i<igImg.Row(); i++)
            memcpy(_q_bmpMain->bits()+i*nWidth, igImg[i], igImg.Col());
    }
    for(int i=0; i<256; i++)
    {
        QRgb value = qRgb(i,i,i);
        _q_bmpMain->setColor(i,value);
    }

    //영상처리용 메모리
    _igMain = igImg;

    //ImageForm의 출력 위치 및 크기 설정
    static int   nXo, nYo=-30;
    QRect       q_rcGeom = _q_MainFrame->geometry();

    setGeometry(q_rcGeom.right() +  (nXo+= 20), q_rcGeom.top()  + (nYo += 30),
                        _q_bmpMain->width(),_q_bmpMain->height());
    focusInEvent(0);
}


ImageForm::~ImageForm()
{
    delete ui;
}

void ImageForm::Update(const KImageGray& igImg)
{
    //이미지 갱신
    if(_igMain.Row() != igImg.Row() || _igMain.Col() != igImg.Col())
        return;

    if(igImg.Col()%4 == 0)
        memcpy(_q_bmpMain->bits(), igImg.Address(), igImg.Size());
    else
    {
        int nWidth = igImg.Col() +  4 - igImg.Col()%4;
        for(int i=0; i<igImg.Row(); i++)
            memcpy(_q_bmpMain->bits()+i*nWidth, igImg[i], igImg.Col());
    }

    //표시
    repaint();
}

void ImageForm::Update()
{
    //이미지 갱신
    if(_igMain.Address())
    {
        if(_igMain.Col()%4 == 0)
            memcpy(_q_bmpMain->bits(), _igMain.Address(), _igMain.Size());
        else
        {
            int nWidth = _igMain.Col() +  4 - _igMain.Col()%4;
            for(int i=0; i<_igMain.Row(); i++)
                memcpy(_q_bmpMain->bits()+i*nWidth, _igMain[i], _igMain.Col());
        }
    }
    else
        memcpy(_q_bmpMain->bits(), _icMain.Address(), _icMain.Size()*sizeof(KCOLOR32));

    //표시
    repaint();
}

void ImageForm::Update(const KImageColor& icImg)
{
    //이미지 갱신
    if(_icMain.Row() != icImg.Row() || _icMain.Col() != icImg.Col())
        return;

    memcpy(_q_bmpMain->bits(), icImg.Address(), icImg.Size()*sizeof(KCOLOR32));

    //표시
    repaint();
}

void ImageForm::DrawEllipse(const QPoint& q_ptCenter,  int nRx, int nRy, const QColor& q_Color, int nWidth)
{
    QPainter  painter;
    QPen       pen;

    pen.setColor(q_Color);
    pen.setWidth(nWidth);

    painter.begin(_q_bmpMain);
    painter.setPen(pen);
    painter.drawEllipse(q_ptCenter, nRx, nRy);
    painter.end();

}

void ImageForm::DrawPolygon(QPolygonF* q_pPolygon, const QColor& q_Color, int nWidth)
{
    QPainter  painter;
    QPen      pen;

    pen.setColor(q_Color);
    pen.setWidth(nWidth);

    painter.begin(_q_bmpMain);
    painter.setPen(pen);
    painter.drawPolygon(*q_pPolygon);
    painter.end();
}

void ImageForm::DrawPoints(QPolygon* q_pPolygon, const QColor& q_Color, int nWidth)
{
    QPainter  painter;    
    QPen       pen;

    pen.setColor(q_Color);
    pen.setWidth(nWidth);

    painter.begin(_q_bmpMain);
    painter.setPen(pen);
    painter.drawPoints(*q_pPolygon);
    painter.end();
}

void ImageForm::DrawLine(int nXo,int nYo, int nX1, int nY1,const QColor& q_Color, int nWidth)
{
    QPainter  painter;
    QPen       pen;

    pen.setColor(q_Color);
    pen.setWidth(nWidth);

    painter.begin(_q_bmpMain);
    painter.setPen(pen);
    painter.drawLine(nXo,nYo,nX1,nY1);
    painter.end();
}


void ImageForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event) ;

    QPainter  painter;
    painter.begin(this);
    painter.drawImage(0, 0, *_q_bmpMain);

    painter.end();
}

void ImageForm::focusInEvent(QFocusEvent * event)
{
    Q_UNUSED(event) ;

    _q_MainFrame->ImageFormFocused(this);
}

void ImageForm::focusOutEvent(QFocusEvent * event)
{
    Q_UNUSED(event) ;
}

void ImageForm::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event) ;
    _q_MainFrame->CloseImageForm(this);
}

void ImageForm::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    _q_MainFrame->OnMousePos(x, y, this);
}
