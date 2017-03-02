
/////////////////////////////myself
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nod.h"
#include<time.h>
#include <string.h>
#include <qapplication.h>
#include <QtGui/QApplication>
//#include "mainwindow.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/types.h>
#include <sys/socket.h>
//#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/*-------------------------------------------------------------
                    Shi
-------------------------------------------------------------*/

/////initial
//void Initial_shih(unsigned char *y_color,unsigned char *cb_img,unsigned char *cr_img);
void Initial_shih(unsigned char *y_color);
const int outwhile_shi=150;//Lv1、Lv2在第一張frame搜尋150次，超過150次則跳出迴圈ZJU
int W_initial_shih;//Lv1理想寬

/////調整Resolution為320
void QVGA_Resolution_shi(unsigned char *input,unsigned char *output);
unsigned char y_color_out_shi[HXSIZE][WYSIZE];//320*240大小的灰階矩陣

/////影像前處理
//Sobel
void SQIchangeSobel_shih(unsigned char *input, unsigned char *output);
unsigned char Iresult[HXSIZE][WYSIZE];//除光後結果

/////integrate_image
void integrate_image_shih(unsigned char *input,int A,int B,int C,int D,int *output);
int Dintegrate(int *input,int II,int J,int H, int W);
int integrate[HXSIZE][WYSIZE]={0} ;//積分影像矩陣
int integrate_eye_HoriSob_cut[HXSIZE][WYSIZE]={0};

/////level1
int search_face(int frameLv1);
int PHmaxO;
int PHminO;
int PWmaxO;
int PWminO;

/////調整Lv1寬
void FaceRegion_Lv1_Modify(unsigned char *input,int B,int A,int D,int C,int line,int frame_FRLM,unsigned char *outsobv,unsigned char *outputIod);
unsigned char FaceLR_shi_sobv[HXSIZE][WYSIZE];
unsigned char FaceLR_shi_sobvIOD[HXSIZE][WYSIZE];
static int ideaW_Lv2_shi=0;
static int ideaW_Lv1_shi=0;

void histsmooth_shi(int *hist_in, int *hist_out);
/////level2
int innersearch_shih(unsigned char *input,int maxH,int minH,int maxW,int minW,int frame,unsigned char *output,unsigned char *outputIod);
int face_w_size=0;
int threshdiscrim_Shih(int hist[256], int disparity);
int middle_line=(WYSIZE>>1);//中心軸，初始為中間
unsigned char Iresult_Hsobel[HXSIZE][WYSIZE];
unsigned char Iresult_Hsobel_Iod[HXSIZE][WYSIZE];
bool nod_start_shi;//紀錄是否發生點頭情況，讓Lv2找不到
int PHmaxI;
int phminii;
int PWmaxI;
int PWminI;

unsigned char y_amplify_shi[HXSIZE][WYSIZE];
void ModifyEyePosition_shi();
//

static unsigned char Iresult_storemax2_shih[18][48]={0};
static unsigned char Iresult_storesec2_shih[18][48]={0};


/////draw
void drawout (int maxH,int minH,int maxW,int minW);
void drawoutspot_shi(int x,int y,int color);
unsigned char drawy_color[HXSIZE_in][WYSIZE_in];//轉介Ycolor 並畫YUV之Y
/*
unsigned char drawcb_color[HXSIZE_in/2][WYSIZE_in/2];
unsigned char drawcr_color[HXSIZE_in/2][WYSIZE_in/2];
*/
//lee



/*-------------------------------------------------------------
                    全域變數宣告
-------------------------------------------------------------*/
int frame=0;
int w_s,w_e,h_s,h_e;
/*-------------------------------------------------------------
                    全域變數宣告 end
-------------------------------------------------------------*/


///////////////////////QT
void outputqtimage(unsigned char *y_color,unsigned char *drawy_color);
//void outputqtimage(unsigned char *y_color,unsigned char *drawy_color,unsigned char *cb_img,unsigned char *drawcb_color,unsigned char *cr_img,unsigned char *drawcr_color);
///////////////////

////////////////////////////////////////////////////////////////////////////eyedetect
int drowsydetect(unsigned char y_color[0],unsigned char cb_img[0],unsigned char cr_img[0],int* hs,int* he,int* ws,int* we)
{
    /////shi
    int i,j;
    static int frame_shi=0;
    static int NOouter=1;
    static int NObridge=1;
    int position[3];



    /////浮點數型態，用來存總共花的時間
    static double spend_time1=0;
    static double spend_time2=0;
    static double spend_time3=0;
    static double spend_time4=0;
    static double spend_time5=0;
    static double spend_time6=0;
    static double spend_time7=0;
    static double spend_time8=0;
    static double spend_time9=0;
    static double spend_time10=0;
    static double spend_time11=0;
    static double spend_time12=0;
    static double totaltime=0;
    static double time;

    /////clock_t 是一個型態
    clock_t start,stop;//運算開始，取開始時間

    /////宣告pointer
    //FILE *fptr1,*fptr2,*fptr3,*fptr4,*outprt;
    FILE *fptr1,*fptr2,*glassptr3,*eyeptr;
    /////開檔
    //argv[1]="esc972.yuv";
    //argv[2]="152";
    //fptr1=fopen(argv[1],"rb");
    //fptr2=fopen("output.yuv","wb");
    //fptr3=fopen("output3.yuv","wb");
    //fptr4=fopen("output4.yuv","wb");
   // glassptr3=fopen("output3.raw","wb");

    /////Algorithm Start
        frame++;
        frame_shi=frame;

        start = clock();
        //printf("\n%d\n", frame_shi);

        /////Initial
       // Initial_shih(&y_color[0],&cb_img[0],&cr_img[0]);
        Initial_shih(&y_color[0]);
        stop = clock();
        time=(double)(stop-start)/CLOCKS_PER_SEC;
        spend_time1=time+spend_time1;

        /////調整Resolution為320
        start = clock();
        QVGA_Resolution_shi(&y_color[0],&y_color_out_shi[0][0]);
        //printf("QVGA_Resolution_shi OK\n");
        stop = clock();
        time=(double)(stop-start)/CLOCKS_PER_SEC;
        spend_time2=time+spend_time2;

        /////Sobel前處理
        start = clock();
        SQIchangeSobel_shih(&y_color_out_shi[0][0],&Iresult[0][0]);
        stop = clock();
        time=(double)(stop-start)/CLOCKS_PER_SEC;
        spend_time3=time+spend_time3;

        /////積分影像
        start = clock();
        integrate_image_shih(&Iresult[0][0],0,HXSIZE,0,WYSIZE,&integrate[0][0]);
       // printf("integrate_image_shih OK\n");
        stop = clock();
        time=(double)(stop-start)/CLOCKS_PER_SEC;
        spend_time4=time+spend_time4;

        /////人臉搜尋(Lv1)
        PHmaxO=0;
        PHminO=0;
        PWmaxO=0;
        PWminO=0;

        if (1)//Lv1有框到人臉
        {
            /////調整Lv1大小
            start = clock();
            FaceRegion_Lv1_Modify(&Iresult[0][0],PHmaxO,PHminO,PWmaxO,PWminO,middle_line,frame_shi,&FaceLR_shi_sobv[0][0],&FaceLR_shi_sobvIOD[0][0]);
           // printf("FaceRegion_Lv1_Modify OK\n");
            stop = clock();
            time=(double)(stop-start)/CLOCKS_PER_SEC;
            spend_time6=time+spend_time6;

            /////Lv2搜尋start
            start = clock();
            middle_line=innersearch_shih(&Iresult[0][0],PHmaxO,PHminO,PWmaxO,PWminO,frame,&Iresult_Hsobel[0][0],&Iresult_Hsobel_Iod[0][0]);
           // printf("innersearch_shih OK\n");
            stop = clock();
            time=(double)(stop-start)/CLOCKS_PER_SEC;
            spend_time7=time+spend_time7;




        }






       // outputqtimage(&y_color[0],&drawy_color[0][0],&cb_img[0],&drawcb_color[0][0],&cr_img[0],&drawcr_color[0][0]);
        outputqtimage(&y_color[0],&drawy_color[0][0]);

    totaltime=spend_time1+spend_time2+spend_time3+spend_time4+spend_time5+spend_time6+spend_time7+spend_time8+spend_time9+spend_time10+spend_time11/*+spend_time12*/;
    //printf("\n");
    //printf("開檔+Initial= %f s\n",spend_time1);
    //printf("QVGA= %f s\n",spend_time11);
    //printf("SQI= %f s\n",spend_time2);
    //printf("積分影像= %f s\n",spend_time3);
    //printf("Lv1= %f s\n",spend_time4);
    //printf("Lv1_Modify= %f s\n",spend_time5);
    //printf("Lv2= %f s\n",spend_time6);
    //printf("判斷有無戴眼鏡= %f s\n",spend_time7);
    //printf("眼睛偵測= %f s\n",spend_time8);
    //printf("微調眼睛位置= %f s\n",spend_time9);
    //printf("wei= %f s\n",spend_time10);
    //printf("totaltime= %f s\n",totaltime);
    //printf("h_s=%d h_e=%d w_s=%d w_e=%d\n",h_s,h_e,w_s,w_e);
    *ws=w_s;*we=w_e;*hs=h_s;*he=h_e;
    //printf("h_s=%d h_e=%d w_s=%d w_e=%d\n",hs,he,ws,we);


}
/////Initial初始化設定
//void Initial_shih(unsigned char* y_color,unsigned char* cb_img,unsigned char* cr_img)
void Initial_shih(unsigned char* y_color)
{
    //int i,j;



    /////copy
    memcpy(drawy_color,y_color,sizeof(unsigned char)*WYSIZE_in*HXSIZE_in);
   // memcpy(drawcb_color,cb_img,sizeof(unsigned char)*(WYSIZE_in/2)*(HXSIZE_in/2));
   // memcpy(drawcr_color,cr_img,sizeof(unsigned char)*(WYSIZE_in/2)*(HXSIZE_in/2));
    /////歸零
    memset((void *)Iresult, 0, sizeof(unsigned char)*WYSIZE*HXSIZE);
    memset((void *)Iresult_Hsobel, 0, sizeof(unsigned char)*WYSIZE*HXSIZE);
    memset((void *)Iresult_Hsobel_Iod, 0, sizeof(unsigned char)*WYSIZE*HXSIZE);

    nod_start_shi=0;//紀錄是否點頭(點頭時Lv2找無==1)

    //車內環境
    /////戴眼鏡判斷ratioTH值




}
/////調整Resolution為320
void QVGA_Resolution_shi(unsigned char *input,unsigned char *output)
{
    int i,j;

    if(Resolutiontype_shi==0)//QVGA
    {
        memcpy(output,input,sizeof(unsigned char)*WYSIZE_in*HXSIZE_in);
        //printf("1\n");
    }
    else if(Resolutiontype_shi==1)//VGA
    {
        for(i=0;i<HXSIZE;i++)
            for(j=0;j<WYSIZE;j++)
                *(output+i*WYSIZE+j)=*(input+(i<<1)*WYSIZE_in+(j<<1));
    }
    else
    {

    }
}
/*--- SQI --- SQI偵測 ----------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------*/
void SQIchangeSobel_shih(unsigned char *input, unsigned char *output)
{
    int i,j;
/////sobel
    int so=0;
    int so1=0;
    int mind;
/////yerotion
    int maxe;
/////
    unsigned char ysobel_shih[HXSIZE*WYSIZE]={0};
    unsigned char *ysobel =ysobel_shih;
    unsigned char Ydilation_shih[HXSIZE*WYSIZE]={0};
    unsigned char *Ydilation =Ydilation_shih;
/////
    FILE *outprt;
    //FILE *outprt3;
    FILE *outprt4;


    /////Sobel
    for(i=1;i<HXSIZE-1;i++)
    {	for(j=1;j<WYSIZE-1;j++)
        {
            so=(int)((((*(input+WYSIZE*(i+1)+(j)))-(*(input+WYSIZE*(i-1)+(j))))<<1)-(*(input+WYSIZE*(i-1)+(j-1)))-(*(input+WYSIZE*(i-1)+(j+1)))+(*(input+WYSIZE*(i+1)+(j-1)))+(*(input+WYSIZE*(i+1)+(j+1))));
            so=abs(so);

            so1=(int)((((*(input+WYSIZE*(i)+(j+1)))-(*(input+WYSIZE*(i)+(j-1))))<<1)-(*(input+WYSIZE*(i-1)+(j-1)))+(*(input+WYSIZE*(i-1)+(j+1)))-(*(input+WYSIZE*(i+1)+(j-1)))+(*(input+WYSIZE*(i+1)+(j+1))));
            so1=abs(so1);

            so=(so+so1);
            if(so>=255){so=0;}
            else{so=255-so;}

            *(ysobel+WYSIZE*i+j)=so;
        }

    }

    /*outprt=fopen("SQIchangeSobel.raw","wb");
    fwrite(ysobel,sizeof(unsigned char),ONE_SIZE,outprt);
    fclose(outprt);//*/

    //////Ydilation
    mind=255;
    for(j=1+2;j<(HXSIZE-1)-2;j++)
    {	for(i=1+2;i<(WYSIZE-1)-2;i++)
        {
            if((*(ysobel+WYSIZE*(j-2)+(i)))<mind)  {mind=*(ysobel+WYSIZE*(j-2)+(i));   *(Ydilation+WYSIZE*j+i)=mind;}

            if((*(ysobel+WYSIZE*(j-1)+(i-1)))<mind){mind=*(ysobel+WYSIZE*(j-1)+(i-1)); *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j-1)+(i)))<mind)  {mind=*(ysobel+WYSIZE*(j-1)+(i));	 *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j-1)+(i+1)))<mind){mind=*(ysobel+WYSIZE*(j-1)+(i+1)); *(Ydilation+WYSIZE*j+i)=mind;}

            if((*(ysobel+WYSIZE*(j)+(i-2)))<mind){mind=*(ysobel+WYSIZE*(j)+(i-2)); *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j)+(i-1)))<mind){mind=*(ysobel+WYSIZE*(j)+(i-1)); *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j)+(i)))<mind)  {mind=*(ysobel+WYSIZE*(j)+(i));   *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j)+(i+1)))<mind){mind=*(ysobel+WYSIZE*(j)+(i+1)); *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j)+(i+2)))<mind){mind=*(ysobel+WYSIZE*(j)+(i+2)); *(Ydilation+WYSIZE*j+i)=mind;}

            if((*(ysobel+WYSIZE*(j+1)+(i-1)))<mind){mind=*(ysobel+WYSIZE*(j+1)+(i-1)); *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j+1)+(i)))<mind)  {mind=(*(ysobel+WYSIZE*(j+1)+(i)));   *(Ydilation+WYSIZE*j+i)=mind;}
            if((*(ysobel+WYSIZE*(j+1)+(i+1)))<mind){mind=(*(ysobel+WYSIZE*(j+1)+(i+1))); *(Ydilation+WYSIZE*j+i)=mind;}

            if((*(ysobel+WYSIZE*(j+2)+(i)))<mind)  {mind=(*(ysobel+WYSIZE*(j+2)+(i)));   *(Ydilation+WYSIZE*j+i)=mind;}

            if(mind==255){*(Ydilation+WYSIZE*j+i)=(*(ysobel+WYSIZE*(j)+(i)));}

            mind=255;
        }
    }

    /*outprt3=fopen("SQIchangeSobelYdila.raw","wb");
    fwrite(Ydilation,sizeof(unsigned char),ONE_SIZE,outprt3);
    fclose(outprt3);//*/

    //////Yerotion
    maxe=0;
    for(j=(3)+2;j<(HXSIZE-3)-2;j++)
    {	for(i=(3)+2;i<(WYSIZE-3)-2;i++)
        {

            if(*(Ydilation+WYSIZE*(j-2)+(i))>maxe)  {maxe=*(Ydilation+WYSIZE*(j-2)+(i)); *(output+WYSIZE*j+i)=maxe;}

            if(*(Ydilation+WYSIZE*(j-1)+(i-1))>maxe){maxe=*(Ydilation+WYSIZE*(j-1)+(i-1)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j-1)+(i))>maxe)  {maxe=*(Ydilation+WYSIZE*(j-1)+(i)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j-1)+(i+1))>maxe){maxe=*(Ydilation+WYSIZE*(j-1)+(i+1)); *(output+WYSIZE*j+i)=maxe;}

            if(*(Ydilation+WYSIZE*(j)+(i-2))>maxe){maxe=*(Ydilation+WYSIZE*(j)+(i-2)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j)+(i-1))>maxe){maxe=*(Ydilation+WYSIZE*(j)+(i-1)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j)+(i))>maxe)  {maxe=*(Ydilation+WYSIZE*(j)+(i)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j)+(i+1))>maxe){maxe=*(Ydilation+WYSIZE*(j)+(i+1)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j)+(i+2))>maxe){maxe=*(Ydilation+WYSIZE*(j)+(i+2)); *(output+WYSIZE*j+i)=maxe;}

            if(*(Ydilation+WYSIZE*(j+1)+(i-1))>maxe){maxe=*(Ydilation+WYSIZE*(j+1)+(i-1)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j+1)+(i))>maxe)  {maxe=*(Ydilation+WYSIZE*(j+1)+(i)); *(output+WYSIZE*j+i)=maxe;}
            if(*(Ydilation+WYSIZE*(j+1)+(i+1))>maxe){maxe=*(Ydilation+WYSIZE*(j+1)+(i+1)); *(output+WYSIZE*j+i)=maxe;}

            if(*(Ydilation+WYSIZE*(j+2)+(i))>maxe)  {maxe=*(Ydilation+WYSIZE*(j+2)+(i)); *(output+WYSIZE*j+i)=maxe;}

            if(maxe==0){*(output+WYSIZE*j+i)=*(Ydilation+WYSIZE*(j)+(i));}


            maxe=0;
        }
    }
    /*
    outprt4=fopen("SobelIresult.raw","wb");
    fwrite(Iresult,sizeof(unsigned char),ONE_SIZE,outprt4);
    fclose(outprt4);
*/



}
void SQI(unsigned char *inputy,unsigned char *outputIresult)
{
    int i,j,m,n,sum;
    float sumI,sumF,min,max;
    //float G7[7][7]={1,2,3,4,3,2,1,2,3,4,5,4,3,2,3,4,5,6,5,4,3,4,5,6,7,6,5,4,3,4,5,6,5,4,3,2,3,4,5,4,3,2,1,2,3,4,3,2,1};//175;*/

    /*static float G7[7][7]={0.0057,0.0114,0.0171,0.0229,0.0171,0.0114,0.0057,
                 0.0114,0.0171,0.0229,0.0286,0.0229,0.0171,0.0114,
                 0.0171,0.0229,0.0286,0.0343,0.0286,0.0229,0.0171,
                 0.0229,0.0286,0.0343,0.04,0.0343,0.0286,0.0229,
                 0.0171,0.0229,0.0286,0.0343,0.0286,0.0229,0.0171,
                 0.0114,0.0171,0.0229,0.0286,0.0229,0.0171,0.0114,
                 0.0057,0.0114,0.0171,0.0229,0.0171,0.0114,0.0057};//*/

    /*int sumI,sumF,min,max;
    int G7[7][7]={748,1498,2247,2996,2247,1498,748,
                 1498,2247,2996,3745,2996,2247,1498,
                 2247,2996,3745,4494,3745,2996,2247,
                 2996,3745,4494,5243,4494,3745,2996,
                 2247,2996,3745,4494,3745,2996,2247,
                 1498,2247,2996,3745,2996,2247,1498,
                 748,1498,2247,2996,2247,1498,748,};//先將係數乘大*/
    int SQ,SQ2;

    /////
    float *I = new float [HXSIZE*WYSIZE];
    //int *thr = new int [HXSIZE*WYSIZE];
    int thr;
    int *integrate_SQI =new int [HXSIZE*WYSIZE];
    /////
    int a,b;
    static int G7[7][7]={1,2,3,4,3,2,1,2,3,4,5,4,3,2,3,4,5,6,5,4,3,4,5,6,7,6,5,4,3,4,5,6,5,4,3,2,3,4,5,4,3,2,1,2,3,4,3,2,1};//175;*/
    /////
    /*clock_t start,stop;//運算開始，取開始時間
    static double time1=0;
    static double time2=0;
    double time;*/
    /////


    SQ=7;
    SQ2=49;

    FILE *Iprt;

    min=0;
    max=0;

    /*for(m=0;m<SQ;m++)//
    {
        for(n=0;n<SQ;n++)
        {
            G7[m][n]=G7[m][n]/175;//7*7的高斯函數
            ////printf("%f\t",G7[m][n]);
        }
        ////printf("\n");
    }///*/

    //start = clock();
    integrate_image_shih(inputy,0,HXSIZE,0,WYSIZE,integrate_SQI);

    for(i=10;i<(HXSIZE-10);i=i+1)//SQI處理範圍
    {
        for(j=10;j<(WYSIZE-10);j=j+1)
        {
            sum=0;
            /*for(m=0;m<SQ;m++)//加總區域總值
            {
                for(n=0;n<SQ;n++)
                {

                    //sum=sum+y_color[i+m][j+n];
                    sum=sum+(*(inputy+WYSIZE*(i-3+m)+(j-3+n)));

                }
            }//*/

            sum=Dintegrate(integrate_SQI,i-3,j-3  ,SQ-1,SQ-1      );//區域總和

            ////printf("sum=%d\n\n",sum);
            //thr=sum/(SQ2);//得到區域平均
            thr=(sum*334)>>14;//得到區域平均
            ////printf("thr=%d\n\n",*(thr+WYSIZE*i+j));

            /*sumF=0;
            sumI=0;//*/
            a=0;
            b=0;
            for(m=0;m<SQ;m++)//得到權重矩陣
            {
                for(n=0;n<SQ;n++)
                {
                    if((*(inputy+WYSIZE*(i-3+m)+(j-3+n)))>=thr)
                    {
                        /*sumF=sumF+G7[m][n];//0~1之間
                        sumI=sumI+((float)(*(inputy+WYSIZE*(i-3+m)+(j-3+n)))*G7[m][n]);//0~255之間*/

                        a=a+G7[m][n];
                        b=b+((*(inputy+WYSIZE*(i-3+m)+(j-3+n)))*G7[m][n]);//*/

                    }
                }
            }

            //sumI=sumI/sumF;
            sumI=(float)b/(float)a;//0~255
            /*if(sumI>=250)
            {
                //printf("b=%d a=%d \n",b,a);
                //printf("sumI=%f\n",sumI);
            }*/
            *(I+WYSIZE*i+j)=(((float)(*(inputy+WYSIZE*(i)+(j))))/sumI);//


            if(*(I+WYSIZE*i+j)>max)
                max=*(I+WYSIZE*i+j);// => max=max/sumI
            if(*(I+WYSIZE*i+j)<min)
                min=*(I+WYSIZE*i+j);// => min=min/sumI
            ////printf("max=%d min=%d I=%d\n",max,min,I[i][j]);

        }
    }

    //stop = clock();
    //time=(double)(stop-start)/CLOCKS_PER_SEC;
    //time1=time+time1;


    //start = clock();
        for(i=10;i<(HXSIZE-10);i++)
        {
            for(j=10;j<(WYSIZE-10);j++)
            {
                *(outputIresult+WYSIZE*(i)+(j))=(unsigned char)((float)((*(I+WYSIZE*i+j)-min)*255)/(float)(max-min));
                ////printf("out=%d\n",*(outputIresult+WYSIZE*(i+3)+(j+3)));
            }
        }

    //stop = clock();
    //time=(double)(stop-start)/CLOCKS_PER_SEC;
    //time2=time+time2;


        ////printf("SQI finish\n");

        delete [] I;
        delete [] integrate_SQI;

        //Iprt=fopen("SQIresult.raw","wb");
        //fwrite(Iresult,sizeof(unsigned char),WYSIZE*HXSIZE,Iprt);
        //fclose(Iprt);//*/

        ////printf("SQI for time1= %f s\n",time1);
        ////printf("SQI for time2= %f s\n",time2);


}
/*--- integrate_image --- integrate_image偵測 ----------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------*/
void integrate_image_shih(unsigned char *input,int A,int B,int C,int D,int *output)
{

    int i ,j;
    int W;


    W=WYSIZE;
    for(i=A;i<B;i++)
    {
        for(j=C;j<D;j++)
        {
            if(i==0)
            {
             if(j==0)
             {
                 *(output+W*i+j)=*(input+W*i+j);//integrate[i][j]=Iresult[i][j];
             }
             else
             {
                  *(output+W*i+j)=*(input+W*i+j)+( *(output+W*i+(j-1)) );//integrate[i][j]=Iresult[i][j]+integrate[i][j-1];
             }
            }
            else //i!=0
            {
                if(j==0)
                {
                    *(output+W*i+j)=*(input+W*i+j)+( *(output+W*(i-1)+j) );//integrate[i][j]=Iresult[i][j]+integrate[i-1][j];
                }
                else
                {
                    *(output+W*i+j)=*(input+W*i+j) + (*(output+W*(i)+(j-1))) + (*(output+W*(i-1)+j)) - (*(output+W*(i-1)+(j-1)));//integrate[i][j]=Iresult[i][j]+integrate[i][j-1]+integrate[i-1][j]-integrate[i-1][j-1];
                }
            }
        }
    }
    /*for(i=0;i<HXSIZE;i++)
    {
        for(j=0;j<WYSIZE;j++)
        {
            if(i==0)
            {
             if(j==0)
             {
                 integrate[i][j]=Iresult[i][j];
             }
             else
             {
                  integrate[i][j]=Iresult[i][j]+integrate[i][j-1];
             }
            }
            else //i!=0
            {
                if(j==0)
                {
                    integrate[i][j]=Iresult[i][j]+integrate[i-1][j];
                }
                else
                {
                    integrate[i][j]=Iresult[i][j]+integrate[i][j-1]+integrate[i-1][j]-integrate[i-1][j-1];
                }
            }
        }
    }*/
////printf("intrgrate finish\n");

}
int Dintegrate(int *input,int II,int J,int H, int W)
{
    int Total;
    int w;

    w=WYSIZE;

        Total=*(input+w*(II+H)+(J+W))-*(input+w*(II+H)+(J-1))-*(input+w*(II-1)+(J+W))+*(input+w*(II-1)+(J-1));
      //Total=integrate[II+H][J+W]-integrate[II+H][J-1]-integrate[II-1][J+W]+integrate[II-1][J-1];

    return Total;

    /*int Total;

      Total=integrate[II+H][J+W]-integrate[II+H][J-1]-integrate[II-1][J+W]+integrate[II-1][J-1];

    return Total;*/
}
/*--- level1 --- level1偵測 ----------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------*/
void FaceRegion_Lv1_Modify(unsigned char *input,int B,int A,int D,int C,int line,int frame_FRLM,unsigned char *outsobv,unsigned char *outputIod)
{//FaceRegion_Lv1_Modify(&Iresult[0][0],PHmaxO,PHminO,PWmaxO,PWminO,middle_line,frame_shi,&FaceLR_shi_sobv[0][0],&FaceLR_shi_sobvIOD[0][0]);
    int i,j;
/////Sobv
    int so;
/////IOD
    int thresh;
/////水平投影
    int proh[WYSIZE]={0};
/////
    int maxL,maxR;
/////
    int hist[256]={0};
/////
    int WL,WR;
    //FILE *txtpr_hist;
/////
    static bool FaceRegion_Lv1_Modify_FirstIn=1;//用來判斷是否第一次進入函式
    int Face_L,Face_R;
    static int thresh_store_Lv1Modfy_shi=0;
/////
/////
    int soH;
    int prov[HXSIZE]={0};
    int maxU;
    int Face_U;
    unsigned char FaceLR_shi_sobh[HXSIZE*WYSIZE]={0};
    unsigned char *outsobh = FaceLR_shi_sobh;
    unsigned char FaceLR_shi_sobhIOD[HXSIZE*WYSIZE]={0};
    unsigned char *outputhIod = FaceLR_shi_sobhIOD;

/////
    int sumproh=0;
    int proh_smooth[WYSIZE]={0};
    static int Face_L_store=0;
    static int Face_R_store=0;
    int sumprohmax;
/////
    short int range;
/////
    memset((void *)FaceLR_shi_sobv, 0, sizeof(unsigned char)*WYSIZE*HXSIZE);
    memset((void *)FaceLR_shi_sobvIOD, 0, sizeof(unsigned char)*WYSIZE*HXSIZE);

    if(line=0)
    {line=(180);
    }
    else
    {

        /////sobelv
        for(i=0;i<HXSIZE;i++)
        {	for(j=(0+30);j<(320-30);j++)
            {

                so=(int)((*(input+WYSIZE*(i-1)+(j+1)))-(*(input+WYSIZE*(i-1)+(j-1)))-(*(input+WYSIZE*(i+1)+(j-1)))+(*(input+WYSIZE*(i+1)+(j+1)))-((*(input+WYSIZE*(i)+(j-1)))<<1)+((*(input+WYSIZE*(i)+(j+1)))<<1));
                so=abs(so);
                //if(so<0){so=0;printf("3\t");}
                if(so>255){so=255;}

                *(outsobv+WYSIZE*i+j)=so;

                hist[so]+=1;
            }
        }
        /*FILE *sobelv;//
        sobelv=fopen("sobelv.raw","wb");
        fwrite(FaceLR_shi_sobv,sizeof(unsigned char),HXSIZE*WYSIZE,sobelv);
        fclose(sobelv);
        */
        /////Iod thresh二質化臨界值取得(約1秒更新一次TH值)

        if((frame_FRLM-(frame_FRLM>>5<<5))==1 || FaceRegion_Lv1_Modify_FirstIn==1)
        {
            if(FaceRegion_Lv1_Modify_FirstIn==1)
            {
                FaceRegion_Lv1_Modify_FirstIn=0;
            }
            thresh = threshdiscrim_Shih(hist, 0);
            thresh_store_Lv1Modfy_shi=thresh;//存thresh
            //printf("thresh=%d\n",thresh);
        }
        else
        {
            thresh=thresh_store_Lv1Modfy_shi;
        }
        //printf("thresh=%d\n",thresh);

        //////垂直sobelIod
        for(i=0;i<HXSIZE;i++)
        {	for(j=30;j<290;j++)
            {

                if ((int)(*(outsobv+WYSIZE*i+j)) > thresh || (int)(*(outsobv+WYSIZE*i+(j-1))) > thresh || (int)(*(outsobv+WYSIZE*i+(j+1))) > thresh)
                {
                    *(outputIod+WYSIZE*i+j) = 255;
                    proh[j]++;/////水平投影
                }
                else
                {
                    *(outputIod+WYSIZE*i+j) =  0;
                }
            }
        }
        /*
        FILE *sobelvIod;
        sobelvIod=fopen("sobelvIod.raw","wb");
        fwrite(FaceLR_shi_sobvIOD,sizeof(unsigned char),HXSIZE*WYSIZE,sobelvIod);
        fclose(sobelvIod);
        */


        histsmooth_shi(&proh[0],&proh_smooth[0]);
        memcpy(proh,proh_smooth,sizeof(int)*WYSIZE);

        Face_L=0;
        Face_R=0;
        range=4;
            /////找左邊界最大值當作人臉邊界
            sumprohmax=0;
            for(i=(160-range);i>(30)+range;i--)
            {
                sumproh=proh[i-4]+proh[i-3]+proh[i-2]+proh[i-1]+proh[i]+proh[i+1]+proh[i+2]+proh[i+3]+proh[i+4];
                //sumproh=proh[i-1]+proh[i]+proh[i+1];
                if(sumproh>sumprohmax)
                {
                    sumprohmax=sumproh;
                    Face_L=i-1;
                }
            }
            if(Face_L==0)//還是0
                Face_L=Face_L_store;
            else
                Face_L_store=Face_L;


            /////找右邊界最大值當作人臉邊界
            sumprohmax=0;
            for(i=160+range;i<(290)-range;i++)
            {
                //sumproh=proh[i-2]+proh[i-1]+proh[i]+proh[i+1]+proh[i+2];
                sumproh=proh[i-3]+proh[i-2]+proh[i-1]+proh[i]+proh[i+1]+proh[i+2]+proh[i+3];
                if(sumproh>sumprohmax)
                {
                    sumprohmax=sumproh;
                    Face_R=i+1;
                }
            }
            if(Face_R==0)
                Face_R=Face_R_store;
            else
                Face_R_store=Face_R;

        if((abs(Face_R-Face_L))>100)
        {
        ideaW_Lv2_shi=abs(Face_R-Face_L);
        }
        else
        {
        ideaW_Lv2_shi=100;
        }

            for(i=0;i<30;i++)
            {

                drawoutspot_shi(Face_L,i,255);
                drawoutspot_shi(Face_R,i,255);
                drawoutspot_shi(30,i,255);

                drawoutspot_shi(290,i,255);
            }
                for(j=0;j<30;j++)
            {

                drawoutspot_shi(j,30,255);
                drawoutspot_shi(j,210,255);

            }
    }

}
void histsmooth_shi(int *hist_in, int *hist_out)
{
    int  m, n, i;
    int sum;

    for (n = 0; n < WYSIZE; n++)
    {
        sum = 0;
        for (m = -2; m <= 2; m++)
        {
            i = n + m;
            if (i <   0) i =   0;
            if (i > (WYSIZE-1) ) i = (WYSIZE-1);
            //sum += hist_in[i];
            sum += *(hist_in+i);
        }

        //*(hist_out+n) = (int)((double)sum / 5.0 + 0.5);
        *(hist_out+n) = (int)(sum / 5 );
        //printf("2 %d\n",*(hist_out+n));
    }
}
void drawout (int H2 ,int H1 ,int W2,int W1 )//BADC
{
    int x=0;
    int	y=0;


    if(Resolutiontype_shi==0)//QVGA
    {
        if(H1<0)
            H1=0;
        if(H2>HXSIZE)
            H2=HXSIZE;
        if(W1<0)
            W1=0;
        if(W2>WYSIZE)
            W2=WYSIZE;
    }
    else if(Resolutiontype_shi==1)//VGA
    {
        H1=(H1<<1);
        H2=(H2<<1);
        W1=(W1<<1);
        W2=(W2<<1);
        if(H1<0)
            H1=0;
        if(H2>HXSIZE_in)
            H2=HXSIZE_in;
        if(W1<0)
            W1=0;
        if(W2>WYSIZE_in)
            W2=WYSIZE_in;
    }
    else
    {
    }



    for(x=H1;x<=H2;x++)
    {
        if((x==H1)||(x==H2))
        {
            for(y=W1;y<=W2;y++)
            {
                drawy_color[x][y]=255;
                drawy_color[x+1][y]=255;

            }
                ////printf("draw inner\n");
        }
        else
        {
            drawy_color[x][W1]=255;
            drawy_color[x][W2]=255;
            drawy_color[x][W1+1]=255;
            drawy_color[x][W2+1]=255;

        }
    }
}
void drawoutspot_shi(int x,int y,int color)
{

    if(Resolutiontype_shi==0)//QVGA
    {
        if(x<0)
            x=0;
        if(x>WYSIZE)
            x=WYSIZE;
        if(y<0)
            y=0;
        if(y>HXSIZE)
            y=HXSIZE;
    }
    else if(Resolutiontype_shi==1)//VGA
    {
        x=(x<<1);
        y=(y<<1);

        if(x<0)
            x=0;
        if(x>WYSIZE_in)
            x=WYSIZE_in;
        if(y<0)
            y=0;
        if(y>HXSIZE_in)
            y=HXSIZE_in;
    }
    else
    {
    }

    drawy_color[y][x]=color;
}
/*--- level2 --- level2偵測 ----------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------*/
int innersearch_shih(unsigned char *input ,int maxH,int minH,int maxW,int minW,int frameLv2,unsigned char *output,unsigned char *outputIod) // 傳入search range 的4個座標
{//innersearch_shih(&Iresult[0][0],PHmaxO,PHminO,PWmaxO,PWminO,frame,&Iresult_Hsobel[0][0],&Iresult_Hsobel_Iod[0][0]);
   const int Lv2TrainFrame=1;		// (1)第一次進入Lv2就找理想的TH2 (0)否
/////
    int i,j,SBHI,SBHID,SBWID;
    int innerH1,innerH2,innerW1,innerW2;
    int sumUP,sumDN,sumLF,sumRT,sumDL,sumDR,sumComp,sumLF1,sumRT1,sumDN1;
    int LFIi,LFIj,RTIi,RTIj,DNIi,DNIj;
    int count1;
    int x=0;
    int y=0;
    int H,W;
/////
    int THLevel2;

    int WLevel2;
/////
    int hist[256]={0};
    //int sobelH[9]={-1,-2,-1,0,0,0,1,2,1};
    int so;
    int thresh;
/////
    int sum,total,mean;
    int proh[WYSIZE]={0};
/////
    int HLevel2;
/////

/////
    bool Lv2WhileIn=1;
    unsigned char Lv2WhileOut;
    unsigned char countLv2While=0;
/////
    static bool innersearch_FirstIn_shi=1;//判斷是否第一次進入Lv2
    static int TH2Record_shih=0;
    static int frame_count_lv2_shi=0;//決定10張做一次二值化TH
    static int thresh_store_shi=0;//存Iod thresh
    static int PHmaxIRecord_shih=0;
    static int phminiiRecord_shih=0;
    static int PWmaxIRecord_shih=0;
    static int PWminIRecord_shih=0;
/////
    static int centerpointX=0,centerpointY=0;
    //static unsigned char Lv2_block_store[33][142]={0};//((SBHI>>1)+1)*(SBWI+1)
    static unsigned char Lv2_block_store[HXSIZE][WYSIZE]={0};//((SBHI>>1)+1)*(SBWI+1)
    int Lv2_block_sizeX;
    int Lv2_block_sizeY;
    int searchup=0;//設定search range
    int searchdown=0;
    int searchlf=0;
    int searchrt=0;
    int j1,i1,k;
    int AD,SAD,SADmin;
/////
    int maxv=0;
    int prov[HXSIZE]={0};
    int newphminii=0;

/////
    static int ideaLv2=0;
/////
    int W2,H2;
    static int PHmaxI_store=0;
    static int phminii_store=0;
    static int PWmaxI_store=0;
    static int PWminI_store=0;
/////
    int H3=0;
    int W3=0;
    FILE *txtpr_hist;
/////
    static int train_face_count=0;
    static int SBWI=0;


    /////判斷是否第一次進入innersearch
    if(innersearch_FirstIn_shi==1)
    {
        THLevel2=TH2first_shih;
        innersearch_FirstIn_shi=0;
        Lv2WhileOut=1;
    }
    else
    {
        THLevel2=TH2Record_shih;
        Lv2WhileOut=2;
    }

    /////
    /*PHmaxI=200;
    phminii=30;
    PWmaxI=100;
    PWminI=310;
*/
    //printf("face insearch start \n");

        //車內環境or Lab環境
            /*SBWI=(ideaW_Lv2_shi/4)*3;
            SBHI=(SBWI/4)*3;
            SBHID=(SBHI)/2;
            SBWID=(SBWI)/5;*/

            //int SBMAX_SIZE;
            int SBMIN_SIZE;
            /*SBMAX_SIZE=SBHID*SBWID*2;
            SBMIN_SIZE=SBHID*SBWID;*/
            int sum_face_score;

            /////設定理想Lv2寬
            if(frameLv2>=150)
            {
                if(frameLv2==150)
                {
                    SBWI=((train_face_count/150));
                    face_w_size=SBWI;
                    SBHI=(SBWI/4)*3;
                    SBHID=(SBHI)/2;
                    SBWID=(SBWI)/3;
                    //SBMAX_SIZE=SBHID*SBWID*2;
                    SBMIN_SIZE=SBHID*SBWID;
                }
                else
                {	//SBWI=((train_face_count/150)/4*3);
                    SBWI=SBWI;
                    face_w_size=SBWI;
                    SBHI=(SBWI/4)*3;
                    SBHID=(SBHI)/2;
                    SBWID=(SBWI)/3;
                  // SBMAX_SIZE=SBHID*SBWID*2;
                    SBMIN_SIZE=SBHID*SBWID;

                }
            }
            else
            {		train_face_count=ideaW_Lv2_shi+train_face_count;
                    SBWI=ideaW_Lv2_shi;
                    face_w_size=SBWI;
                    SBHI=(SBWI/4)*3;
                    SBHID=(SBHI)/2;
                    SBWID=(SBWI)/3;
                  //  SBMAX_SIZE=SBHID*SBWID*2;
                    SBMIN_SIZE=SBHID*SBWID;
            }



            /////設定Motion 區域大小
            Lv2_block_sizeX=(SBWI+1);//91
            Lv2_block_sizeY=(SBHI>>1)+1;//46


        innerH1=30;
        innerH2=210;
        innerW1=30;
        innerW2=290;
    static int temp_face_score=0;
    temp_face_score=0;
    /////Lv2搜尋開始
        //while(Lv2WhileIn==1)
        //{
        count1=0;
         for(i=innerH1;i<(innerH2)-SBHI;i++) //Search 範圍
         {
            for(j=innerW1;j<(innerW2)-SBWI;j++)
            {

              sumUP=0;
              sumDN=0;
              sumLF=0;
              sumRT=0;

              sumDN1=0;
              sumLF1=0;
              sumRT1=0;

              LFIi=i;
              LFIj=j;

              RTIi=i;
              RTIj=j+(SBWID*2);

              DNIi=i+SBHID;
              DNIj=j+(SBWID);

              sumLF=Dintegrate(&integrate[0][0],LFIi,LFIj,(SBHID-1),(SBWID-1));
              sumRT=Dintegrate(&integrate[0][0],RTIi,RTIj,(SBHID-1),(SBWID-1));

              sumDL=Dintegrate(&integrate[0][0],DNIi,LFIj,(SBHID-1),(SBWID-1));
              sumDR=Dintegrate(&integrate[0][0],DNIi,RTIj,(SBHID-1),((SBWID)-1));
            //取灰階值大的(較白的)
              if (sumDL>sumDR)
                  sumComp=sumDL;
              else
                  sumComp=sumDR;

              sumDN=Dintegrate(&integrate[0][0],DNIi,DNIj,(SBHID-1),(SBWID-1));
            //SBMAX_SIZE=SBHID*SBWID*2;
            //SBMIN_SIZE=SBHID*SBWID;
            sumRT1=(SBMIN_SIZE*255)-sumRT;
            sumLF1=(SBMIN_SIZE*255)-sumLF;
            sumDN1=(SBMIN_SIZE*255)-sumDN;



            if(((sumComp)>sumRT)&&(sumComp>sumLF)&&((sumComp)>sumDN))
            {
                count1=count1+1;
                sum_face_score=sumRT1+sumLF1+sumDN1+sumDL+sumDR;
                if(sum_face_score>temp_face_score)
                    {temp_face_score=sum_face_score;
                        PHmaxI=i;
                        phminii=i;
                        PWmaxI=j;
                        PWminI=j;
                        //PHmaxI=PHmaxI+SBHI;
                        //PWmaxI=PWmaxI+SBWI;
                    }
                else
                    {
                    }
            }
            else
            {
            }


              }


         }//search範圍 end




     PHmaxI=PHmaxI+SBHI;
     PWmaxI=PWmaxI+SBWI;
     //printf("countLv2=%d\n",count1);
    // drawout(PHmaxI,phminii,PWmaxI,PWminI);


     if(frame_count_lv2_shi>1 && count1==0)
     {
         nod_start_shi=1;//點頭發生,找眼睛做ME
         //printf("nod?=%d\n",nod_start_shi);
     }

    /////調整TH2
    WLevel2=(PWmaxI-PWminI);
    HLevel2=(PHmaxI-phminii);








            PHmaxI_store=PHmaxI;
            phminii_store=phminii;
            PWmaxI_store=PWmaxI;
            PWminI_store=PWminI;

        //////劃出Lv2範圍

            /////////////
            int h_len,w_len;
            h_len=PHmaxI-phminii;
            w_len=PWmaxI-PWminI;
            //h_len=h_len/5;
            w_len=w_len/6;
            PHmaxI=PHmaxI-h_len/5;
            phminii=phminii+h_len/2;
            PWmaxI=PWmaxI-w_len;
            PWminI=PWminI+w_len;
            h_s=PHmaxI;h_e=phminii; w_s=PWmaxI; w_e=PWminI;
            /////////////


        drawout(PHmaxI,phminii,PWmaxI,PWminI);



//////////////12_8 add_midle_line
            mean=PWminI+((PWmaxI-PWminI)/2);

            for(i=phminii;i<phminii+10;i++)
            {
            drawoutspot_shi(mean,i,0);
            }
            return mean;

///////////////////////////////

        /*FILE *outprtLv2;
        outprtLv2=fopen("Lv2_block_store.raw","wb");
        fwrite(Lv2_block_store,sizeof(unsigned char),HXSIZE*WYSIZE,outprtLv2);
        fclose(outprtLv2);*/



    /*	return mean;
     }
     else
     {

         return 0;
     }*/


}


int Modify_Position_shih(int X,int odd,int Even)
{
    if(odd==1)			//X要為奇數
    {
        if(X%2==0)		//偶數
            X=X+1;
        else			//奇數
            return X;
    }
    else if(Even==1)	//X要為偶數
    {
        if(X%2==1)		//奇數
            X=X+1;
        else			//偶數
            return X;
    }
    else
        return X;

    return X;
}

//void outputqtimage(unsigned char *y_color,unsigned char *drawy_color,unsigned char *cb_img,unsigned char *drawcb_color,unsigned char *cr_img,unsigned char *drawcr_color)
void outputqtimage(unsigned char *y_color,unsigned char *drawy_color)

{
    for (int i=0;i<ONE_SIZE_in;i++)
       { y_color[i]=drawy_color[i];
        }
 }
int threshdiscrim_Shih(int hist[256], int disparity)
{
    int i, k;
    int n0, n1, n2, m0, m1, m2;
    int v[256], vmax, v0;
    int Thup,Thdown;

    Thup=246;
    Thdown=10;
    n0 = 0;
    m0 = 0;
    for (i = 0; i < 256; i++) {
        n0 += hist[i];//直方圖總數
        m0 += i * hist[i];//總灰階值
    }
    //printf("m0=%d,n0=%d\n",m0,n0);
    if (n0 == 0)
        m0 = 0;
    else
        m0 = m0 / n0;//全體平均灰階值


    //printf("m0=%d\n",m0);//6009
    v0 = 0;
    for (i = 0; i < 256; i++)
        v0 = v0 + (hist[i] * (i - m0) * (i - m0) / n0);//


    //v0=v0/10000;
    //printf("v0=%d\n",v0);
    for (k = Thdown; k < Thup; k++)
    {
        n1 = 0;
        m1 = 0;
        for (i = 0; i < k; i++)
        {
            n1 += hist[i];
            m1 += i * hist[i];
        }
        if (n1 == 0)
            m1 = 0;
        else
            m1 =m1/ n1;

        n2 = 0;
        m2 = 0;
        for (i = k; i < 256; i++)
        {
            n2 += hist[i];
            m2 += i * hist[i];
        }
        if (n2 == 0)
            m2 = 0;
        else
            m2 =m2/ n2;

        v[k] = (n1 * (m1 - m0) * (m1 - m0) + n2 * (m2 - m0) * (m2 - m0)) / n0;//兩物體之間的離散值
        //v[k]=v[k]/10000;
        //printf("v[%d]=%d\n",k,v[k]);
    }

    vmax = 0;
    for (i = Thdown; i < Thup; i++)
    {
        if (vmax <= v[i])
        {
            vmax = v[i];
            k = i;
        }
    }
    //printf("k=%d\n",k);


    //printf("vmax=%f v0=%f vmax/v0=%f\n",vmax,v0,(vmax/v0));
    if (v0 == 0)
        return 0;
    if ((vmax / v0) >= disparity)
        return k;
    else
        return 0;
}
