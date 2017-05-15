#include "ui_widget.h"
#include "widget.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <QtGui/QApplication>
#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_grid.h>
#include <QTime>
#include <qtimer.h>
#include <QMessageBox>
#include <qcolor.h>
#include <qwt_plot_zoomer.h>
#include <qfile.h>
#include <qtextstream.h>
#include "cal.cpp"
//#include "resampleA.cpp"
//#include "R_peak.cpp"


#define TOTALFRAMES 151
#define CAPTURE_IDLE 0
#define CAPTURE_START 1
#define CAPTURE_STOP 2
#define CAPTURE_COMPRESS 3

#define X_SIZE 640 //640*480 sequence
#define Y_SIZE 480 //640*480 sequence


char last_state = 2;
char state = 0;
long framecnt=0;
char yuvfilename[11] = {'r','c','q','0','0','0','.','y','u','v','\0'};

//void resample(double* x_in, double* y_in,double* y_out,int fs,int inpoint,int resamplepoint);


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//***********************LCD***************************************
    ui->RRI_LCD->setSegmentStyle(QLCDNumber::Flat);
    ui->RRI_LCD->display(0);
    ui->HR_LCD->setSegmentStyle(QLCDNumber::Flat);
    ui->HR_LCD->display(0);
    ui->ration_LCD->setSegmentStyle(QLCDNumber::Flat);

    connect(ui->pushButton_1,SIGNAL(clicked()), this,SLOT(cal_start()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this,SLOT(close()));

//***********************wave***************************************************
    ui->qwtPlot->setCanvasBackground( QColor(0,0,0));
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,30*5);
    ui->qwtPlot->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,-3,3);
    ui->qwtPlot->setAxisMaxMinor(QwtPlot::yLeft,0.2);
    p_adplot = new QwtPlotCurve();
    p_adplot->setPen(QPen(Qt::green,1,Qt::SolidLine));
    p_adplot->attach(ui->qwtPlot);
    //time = 0.0;
    //adPlotTimer = new QTimer();
    //adPlotTimer->start();//1000
    //connect(adPlotTimer, SIGNAL(timeout()),this, SLOT(plotAdCurve()));
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    grid->enableX(ui->qwtPlot);
    grid->enableXMin(ui->qwtPlot);
    grid->enableY(ui->qwtPlot);
    grid->enableYMin(ui->qwtPlot);
    grid->attach(ui->qwtPlot);
//*************************************************
//*********************psd*************************

    ui->psdPlot->setCanvasBackground( QColor(0,0,0));
    ui->psdPlot->setAxisScale(QwtPlot::xBottom,0,0.5);
    ui->psdPlot->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
    ui->psdPlot->setAxisScale(QwtPlot::yLeft,0,0.15);
    ui->psdPlot->setAxisMaxMinor(QwtPlot::yLeft,0.2);
    p_psdplot = new QwtPlotCurve();
    p_psdplot->setPen(QPen(Qt::green,1,Qt::SolidLine));
    p_psdplot->attach(ui->psdPlot);
    //time = 0.0;
    //psdPlotTimer = new QTimer();
    //psdPlotTimer->start();//1000
    //connect(psdPlotTimer, SIGNAL(timeout()),this, SLOT(plotPSDCurve()));

    QwtPlotGrid *grid2 = new QwtPlotGrid();
    grid2->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    grid2->enableX(ui->psdPlot);
    grid2->enableXMin(ui->psdPlot);
    grid2->enableY(ui->psdPlot);
    grid2->enableYMin(ui->psdPlot);
    grid2->attach(ui->psdPlot);


//*************************************************

    vd = new VideoDevice(tr("/dev/video0"));
    //video_ptr = fopen("/opt/zedboard/offline_im/444heng1117.yuv","rb");
    frame = new QImage(rgb_buffer,640,480,QImage::Format_RGB888);

}

Widget::~Widget()
{
    delete ui;


    //delete frame;
    //delete [] Y_frame;
    //delete [] Cr_frame;
    //delete [] Cb_frame;
}

void Widget::paintEvent(QPaintEvent *)
{
    int i;
    double t30 [cal_time*framerate],tRRI[fs*cal_time],sumRRI,meanRRI;
    int ONE_SIZE= X_SIZE* Y_SIZE;//640*480 sequence

    //fread(yuv_buffer_pointer, sizeof(unsigned char), ONE_SIZE*3, video_ptr);
    rs = vd->get_frame(&yuv_buffer_pointer,len);


    convert_yuv_to_rgb_buffer();

    if(enable==1){
            rgb_average();
            plotAdCurve();

            if(f_time>=cal_time){
                if(updata==updata_time ||updata==cal_time){

                        updata=0;


                        memset(t30, 0, cal_time*framerate*sizeof(double));
                        for(i=0;i<cal_time*framerate;i++){
                            t30[i+1]= t30[i]+0.0333;
                            //printf("%d %.4f %.4f \n",i,t30[i],wave30[i]);
                        }


                        resample(t30, wave30,wave256,0.0039,30*60,256*60);
                        R_peak(wave256,RRI_a,rR_peak);

                        memset(tRRI, 0, fs*cal_time*sizeof(double));
                        for(i=0;i<fs*cal_time;i++){
                            tRRI[i+1]= tRRI[i]+0.5;//0.5=1/fs
                            //printf("%d %.4f %.4f \n",i,t30[i],wave30[i]);
                        }
                        int time_RRI_a=rR_peak[len_RRI_a]*fs-2;
                        resample(rR_peak, RRI_a,RRI_b,0.5,len_RRI_a,time_RRI_a);
                        for(i=0;i<time_RRI_a;i++){
                            sumRRI= sumRRI+RRI_b[i];
                            //printf("%d %.4f %.4f \n",i,t30[i],wave30[i]);
                        }
                        meanRRI=sumRRI/time_RRI_a;
                        for(i=0;i<time_RRI_a;i++){
                            RRI_b[i]= RRI_b[i]-meanRRI;
                            //printf("%d %.4f %.4f \n",i,t30[i],wave30[i]);
                        }
                        hannig(RRI_b,RRI_c,time_RRI_a);

                        PSD (RRI_c,128,60,freq,power);

                        plotPSDCurve();

                       // printf("time=%4f \n",rR_peak[len_RRI_a-3]);


            }

                ui->RRI_LCD->display(RRI_mean);
                ui->HR_LCD->display(HR);
                ui->ration_LCD->display(ration);

        }
    }


    Box();

    frame->loadFromData(rgb_buffer,640 * 480 * 3);
    ui->label->setPixmap(QPixmap::fromImage(*frame,Qt::AutoColor));

    rs = vd->unget_frame();
}


/*yuv格式转换为rgb格式*/
int Widget::convert_yuv_to_rgb_buffer()
{
    unsigned long in, out = 0,g_out=0;
    int y0, u, y1, v;
    int r, g, b;
    for(in = 0; in < X_SIZE* Y_SIZE*2; in += 4)
    {


        y0 = yuv_buffer_pointer[in + 0];
        u  = yuv_buffer_pointer[in + 1];
        y1 = yuv_buffer_pointer[in + 2];
        v  = yuv_buffer_pointer[in + 3];

        r = y0 + (1.370705 * (v-128));
        g = y0 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y0 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;
        r_buffer[g_out++]= r;

        r = y1 + (1.370705 * (v-128));
        g = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y1 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;

        r_buffer[g_out++]= r;

    }

    return 0;
}




void Widget::Box(){
    int x,y;
    //int x1,x2,y1,y2;

 //    x1=90;x2=390;y1=170;y2=470;

    for(x=(b_x1-2)*3;x<(b_x2+3)*3;x=x+3)
    {
            for(y=(b_y1-2)*3;y<(b_y2+3)*3;y=y+3)
            {
                if(x==(b_x1-1)*3 || x==(b_x1-2)*3  || x==(b_x2+1)*3 || x==(b_x2+2)*3 || y==(b_y1-1)*3 || y==(b_y1-2)*3 || y==(b_y2+1)*3 || y==(b_y2+2)*3 ){
                rgb_buffer[x*640+y] = 0;
                rgb_buffer[x*640+y+1] = 0;
                rgb_buffer[x*640+y+2] = 255;
                }

            }
    }
}

void Widget::readAdData(QVector< double > &xData,  QVector<double> &yData){

    xData.clear();
    yData.clear();


    for(int i=0;i<30*5;i++){//寫入新的ECG
        xData.append(time_data[i]);
        yData.append(show_buffer[i]);
        //printf("show=%f ecg_data=%f\n",show_buffer[i],yData[i]);
    }
}

void Widget::plotAdCurve(){


    readAdData(xData,yData);
    p_adplot->setSamples(xData,yData);

    p_adplot->attach(ui->qwtPlot);
    ui->qwtPlot->replot();
    //adPlotTimer->start(1000);//畫圖的速度

}

void Widget::readPSDData(QVector< double > &freqData,  QVector<double> &powerData){
    int i;
    freqData.clear();
    powerData.clear();

    for(i=0;i<120;i++){
        freqData.append(freq[i]);
        powerData.append(power[i]);
    }
}

void Widget::plotPSDCurve(){



    readPSDData(freqData,powerData);
    p_psdplot->setSamples(freqData,powerData);

    p_psdplot->attach(ui->psdPlot);
    ui->psdPlot->replot();
    //adPlotTimer->start(1000);//畫圖的速度

}

void Widget::cal_start(){
    enable=1;
}



