#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "kfc.h"

namespace Ui {
class MainFrame;

}

class ImageForm;
class KVoronoiDgm;
class KPotentialField;

class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    KPtrList<ImageForm*>*   _plpImageForm;
    ImageForm*              _q_pFormFocused;


public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void            ImageFormFocused(ImageForm* q_pImageForm)
                    {   _q_pFormFocused  = q_pImageForm;   //활성화된 창의 포인터를 저장함
                        UpdateUI();                        //UI 활성화 갱신
                    }
    void            UpdateUI();
    void            CloseImageForm(ImageForm* pForm);

public:
    void            OnMousePos(const int& nX, const int& nY, ImageForm* q_pForm);

private slots:
    void on_buttonOpen_clicked();
    void on_buttonDeleteContents_clicked();    
    void on_buttonSepiaTone_clicked();
    void on_buttonShowList_clicked();

    void on_spinHue_textChanged(const QString &arg1);

    void on_spinHue_valueChanged(const QString &arg1);

    void on_spinHue_valueChanged(int arg1);

    void on_spinSaturation_textChanged(const QString &arg1);

    void on_ButtonOtsu_clicked();

    void on_pushButton_clicked();

    void on_HistoEqu_clicked();

    void on_pushButton_2_clicked();

    void on_buttonOpen_triggered(QAction *arg1);

    void on_HistoMatch_clicked();

    void on_noiseButton_clicked();

    void on_Canny_clicked();

    void on_GenHough_button_clicked();

    void on_CHough_button_clicked();

    void on_SIFT_button_clicked();

    void on_Optical_button_clicked();

    void on_OptcNext_button_clicked();

    void on_spinOptc_textChanged(const QString &arg1);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
