#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include "videodevice.h"
#include <qwt_plot_curve.h>
#include "common.h"


namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    //int get_frame(unsigned char *yuv_buffer_pointer, size_t* len);
    explicit Widget(QWidget *parent = 0);
    ~Widget();

   unsigned char rgb_buffer[640*480*3];
   unsigned char r_buffer[640*480];
   double show_buffer[30*5];
   double avg_buffer[30];
   double time_data[30*5];
   double FIR_buffer[30*4];
   double smooth_buffer[30*4];
   double R_buffer[30*4];

   double fir_out[30];
   QVector< double > xData;
   QVector< double > yData;
   QVector< double > freqData;
   QVector< double > powerData;

   void readAdData(QVector<double> &xData,  QVector<double> &yData);
   void readPSDData(QVector<double> &freqData,  QVector<double> &powerData);
   void rgb_average();
   void smooth(double*,double*);
   void wave_show(double*);
   void FIR(double*,double*);
   void fir64( double *input, double *output,int in_length ,int out_length , int filterLength );
   void resample(double* , double* ,double*,double,int,int);
   void R_peak(double *wave,double *RRI_a, double *rR_peak );
   void hannig(double *in,double *out,int len);
   void PSD (double*yi,int lent,double time,double*f,double*pow);
   double std(double in[],double avg,int len);



   double wave30[30*60];
   double wave256[256*60];
   double RRI_a[150],RRI_b[fs*cal_time],rR_peak[150],RRI_c[fs*cal_time],freq[128],power[128];
   double RRI_mean,ration;
   int f_time,updata,HR,len_RRI_a,enable;




private:


    Ui::Widget *ui;

    QImage *frame;
    QwtPlotCurve *p_adplot;
    QwtPlotCurve *p_psdplot;
    int rs;
    unsigned int len;
    int convert_yuv_to_rgb_buffer();
    void print_quartet(unsigned int i);
    void Box();

    VideoDevice *vd;
    FILE * yuvfile;
    FILE *video_ptr;
    FILE *in_c;

    unsigned char *yuv_buffer_pointer;
    //unsigned char  yuv_buffer_pointer[640*480*3];

    char Y_frame[640*480];
    char Cr_frame[240*320];
    char Cb_frame[240*320];

    int write420();
    QTimer *adPlotTimer;
    QTimer *psdPlotTimer;


private slots:
    //void on_pushButton_start_clicked();
    void paintEvent(QPaintEvent *);
    void cal_start();

public slots:

   void plotAdCurve();
   void plotPSDCurve();

};
#endif // WIDGET_H
