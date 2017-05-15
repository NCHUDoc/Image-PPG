//#include "cal.h"
#include <math.h>
#include "common.h"
//#include <stdio.h>

#include "widget.h"
int counter=0;
double sum_avg=0;
//void fir64(double *in,int in_len,double *out,int out_len);


void Widget::rgb_average(){
       int x,y,i;
       int sum_r,sum_g,sum_b;
       double avg_r,avg_g,avg_b;
       double pixel;
       double s_mean,std_s;


       sum_r=0,sum_g=0,sum_b=0;
       avg_r=0,avg_g=0,avg_b=0;
       pixel=(b_x2-b_x1)*(b_y2-b_y1);

       for(x=(b_x1);x<(b_x2+1);x=x+1)
       {
               for(y=(b_y1);y<(b_y2+1);y=y+1)
               {  
                  sum_r+= r_buffer[x*640+y];
                }

        }



       avg_r=sum_r/pixel;
      // printf("sum=%d avg=%f\n",sum_g,avg_r);

       if(counter==30){
           updata=updata+1;
           //printf("%d \n",updata);
           f_time=f_time+1;
           s_mean=sum_avg/30;
           std_s=std(avg_buffer,s_mean,30);


           for(i=0;i<30;i++){
               //printf("i=%d avg=%f mean=%f std_s=%f \n",i,avg_buffer[i],s_mean,std_s);

               if(std_s==0){
                  avg_buffer[i]=0;
                   // avg_buffer[i]= (avg_buffer[i]-s_mean)/std_s;
               }
               else{
                  avg_buffer[i]= (avg_buffer[i]-s_mean)/std_s;
               }
               //printf("i=%d avg=%f std_s=%f \n",i,avg_buffer[i],std_s);

           }
           memmove(R_buffer,R_buffer+30,sizeof(double)*30*3);
           memcpy(R_buffer+90,avg_buffer,sizeof(double)*30*1);

           smooth(R_buffer,smooth_buffer);
           FIR(smooth_buffer,fir_out);
           wave_show(fir_out);

           //****************move wave************************

              memmove(wave30,wave30+30,sizeof(double)*(cal_time*framerate-30));
              memcpy(wave30+cal_time*framerate-30,fir_out,sizeof(double)*30);



           //********************************************

           counter=0;
           sum_avg=0;
       }
       else{

         avg_buffer[counter]= avg_r;
         counter=counter+1;
         sum_avg+=avg_r;
       }


       //printf("counter=%d avg=%f sum_avg=%f\n",counter,avg_buffer[counter],sum_avg);

}

void Widget::wave_show(double *fir_out){
    int i;

    for(i=0;i<120;i++){
        show_buffer[i]= show_buffer[i+30];
        time_data[i]=i;
    }
    for(i=0;i<30;i++){
        show_buffer[i+120]= fir_out[i];
        time_data[i+120]=i+120;
        //printf("i=%d avg=%f\n",i,avg_buffer[i]);
    }
}

void Widget::FIR(double *smooth_buffer,double *fir_out){
    int i,out_len;
    double fir_temp[55];


    memmove(FIR_buffer,FIR_buffer+30,sizeof(double)*30*3);
    memcpy(FIR_buffer+90,smooth_buffer,sizeof(double)*30);

    fir64(FIR_buffer, fir_temp, 120,out_len,65 );

    memcpy(fir_out,fir_temp+25,sizeof(double)*30);

}


double Widget::std(double in[],double avg,int len){
    int i;
    double out,temp,sum;
    sum=0;

    for(i=0;i<len;i++){
        temp=in[i]-avg;
        temp *=temp;
        sum += temp;
    }
    out=sqrt(sum/len);
    return out;




}

void Widget::smooth(double *R_buffer,double *smooth_buffer){
    int i,j,s=5,k;
    double sum;

    k=s/2+1;

    for(i=0;i<30*4;i++){

        sum=0;

        if( i>k  && 30*4-k>i ){

            for(j=0;j<s;j++){
                sum+=R_buffer[i-k+1+j];
            }
            smooth_buffer[i]=sum/s;

        }
        else{
            smooth_buffer[i]=R_buffer[i];
        }


        //printf("i=%d avg=%f\n",i,avg_buffer[i]);
    }
}

void Widget::hannig(double *in,double *out,int len){
//	int fs=2;
//	int cal_time=300;

   double ang,hann;

   int k,i;


//==================== hannig window ================================

  for(k=0;k<len;k++){  // double yyi=yi[k];

      ang = cos(((6.28*k)/len));
      hann=0.5-0.5*ang;//0.5*(1-cos(2*))
      out[k] = in[k]*hann;
      //printf("%f\n",yi[k]);
      //printf("%d %.4f %.4f %4f \n",k,ang,hann,in[k]);
      }
  if(k<nfft){
      for(i=k;i<nfft;i++){
           out[i]=0;
      }
  }



}



