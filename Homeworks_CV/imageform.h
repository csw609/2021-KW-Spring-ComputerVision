#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "kfc.h"

namespace Ui {
class ImageForm;
}

class MainFrame;
class ImageForm : public QWidget
{
    Q_OBJECT

private:
    Ui::ImageForm   *ui;
    QString         _q_stID;
    MainFrame*      _q_MainFrame;

public:
    QImage*         _q_bmpMain;
    KImageGray      _igMain;
    KImageColor     _icMain;

public:
    explicit ImageForm(const QString& q_stFile,    const QString& q_stID, MainFrame* owner);
    explicit ImageForm(const KImageColor& icImg, const QString& q_stID, MainFrame* owner);
    explicit ImageForm(const KImageGray& igImg,  const QString& q_stID, MainFrame* owner);
    ~ImageForm();

    KImageGray&     ImageGray(){    return  _igMain;   }
    KImageColor&    ImageColor(){   return  _icMain;   }
    QString&        ID(){        return  _q_stID;   }
    void            Update();
    void            Update(const KImageGray&  igImg);
    void            Update(const KImageColor& icImg);

    void            DrawEllipse(const QPoint& q_ptCenter,  int nRx, int nRy, const QColor& qColor, int nWidth=1);
    void            DrawPolygon(QPolygonF* q_pPolygon,const QColor& q_Color, int nWidth=1);
    void            DrawPoints(QPolygon*  q_pPolygon, const QColor&, int nWidth=1);
    void            DrawLine(int nXo,int nYo, int nX1, int nY1,const QColor& q_Color, int nWidth=1);

protected:
    void            paintEvent(QPaintEvent* event);
    void            focusInEvent(QFocusEvent *);
    void            focusOutEvent(QFocusEvent *);
    void            closeEvent(QCloseEvent *event);
    void            mousePressEvent(QMouseEvent *event);

private slots:

};

#endif // IMAGEFORM_H
