//#include <stdio.h>
//#include <stdlib.h>
#include "common.h"
#include "widget.h"
void Widget::resample(double* x_in, double* y_in,double* y_out,double target,int inpoint,int resamplepoint){

    int i,j;
    //int fs=2;
    //int cal_time=300;

    double time_d,y_in_d,x_d;
    //double target;
    //int resamplepoint=cal_time*fs;

    double x_out[resamplepoint];


    //point= strlen(new_x_in);
    for(i=0;i<resamplepoint;i++){

        y_out[i]=0;
        x_out[i]=0;

    }
    x_out[0]  = x_in[0];
    //x_out[0]  = first_x_in;
    y_out[0] = y_in[0];
   //printf("%f", x_in[1]);
    i=1;

    //printf("====================== resample =============================\n");
   // printf("%d %.4f %.4f \n",0,y_out[0],x_out[0]);
    for (j=1;j<resamplepoint;j++){
       if (i<inpoint-1){
            x_out[j] = x_out[0]+j*target;
            time_d = x_out[j]- x_in[i-1];//(X-X1)
            y_in_d  = y_in[i] - y_in[i-1] ; //(Y2-Y1)
            x_d = x_in[i] - x_in[i-1] ; //(X2-X1)
            y_out[j] = y_in[i-1]+ ((time_d *y_in_d)/x_d) ;//Y=Y1+ {(X-X1)*(Y2-Y1)}/(X2-X1)

           // printf("%d %.4f %.4f %.4f\n",j,y_out[j],x_out[j],y_in[i]);

            if((x_out[j]+target) > x_in[i]){
                i=i+1;
               // printf("%.4f \n",x_out[j]);
            }
       }
    }

}


