//#include "widget.h"
#include "common.h"
#include "widget.h"

double sort(double*in,int begin,int end);

void Widget::R_peak (double *wave,double *RRI_a,double *rR_peak ){
double RRI[150];
double slope,max,RRI_t,sum_RRI,minRRI=0.5,maxRRI=1,dx,dy,r_m;
int i,det,ii;
int range=50,k1,RRI_rcont,ei;
int R_peak[150];

    memset(R_peak, 0, 150*sizeof(int));

k1=0;
    for(i=2;i<cal_time*samplerate-2;i++){
        if(det<2){
            slope=-2*wave[i-2]-wave[i-1]+wave[i+1]+2*wave[i+2];
            //printf(" %.4f  \n",slope);
            if(slope>0) det=det+1;
            else det=0;
        }
        else{
            if(wave[i]>wave[i+1]){
                if(i<=range){

                    max=sort(wave,1,i+range);
                }
                else if(i+range>=cal_time*samplerate){
                    max=sort(wave,i-range,cal_time*samplerate);
                }
                else{
                    max=sort(wave,i-range,i+range);
                }
                //printf(" %.4f  \n",max);
                if (wave[i]==max){

                    R_peak[k1]=i;
                    k1=k1+1;
                    //printf("%d %d  \n",k1,R_peak[k1]);
                }
                det=0;

            }
        }

    }
    if (k1>120){
        k1=120;
    }

    memset(RRI, 0, 150*sizeof(double));
    sum_RRI=0;

    for(i=0;i<k1-1;i++){

        RRI_t=(R_peak[i+1]-R_peak[i])*0.0039;
        RRI[i]=RRI_t;
        sum_RRI=sum_RRI+RRI_t;

        //printf("%d %4f  \n",i,RRI[i]);
    }

    //RRI_mean = sum_RRI/(k1-1);

    //sum_RRI=0;

//******emtopic RRI repair*****************
    memset(RRI_a, 0, 150*sizeof(double));
    memset(rR_peak, 0, 150*sizeof(double));


    if(minRRI<RRI[0] && RRI[0] <maxRRI){
        RRI_a[0]=RRI[0];
        len_RRI_a=1;
        sum_RRI=RRI_a[0];
    }
    else len_RRI_a=0;

    for(i=1;i<k1-1;i++){
        if(minRRI<=RRI[i] && RRI[i]< maxRRI){
            RRI_a[len_RRI_a]=RRI[i];
            //sum_RRI=sum_RRI+RRI_a[len_RRI_a];
            //printf("%d %4f  \n",len_RRI_a,RRI_a[len_RRI_a]);
            len_RRI_a=len_RRI_a+1;

        }
        else{
            if(i>ii){
                ii=i; dx=0; dy=0;
                while(minRRI>RRI[ii] || RRI[ii]>maxRRI){
                    ii=ii+1;
                    if(ii==k1)break;
                }

                if (ii<k1){
                    for(ei=i;ei<ii+1;ei++){
                        dx=dx+RRI[ei];
                    }

                    RRI_rcont = dx/RRI_mean;
                    dy=RRI[ii]-RRI[i-1];
                    r_m=dy/RRI_rcont;

                    for(ei=1;ei<RRI_rcont;ei++){
                        RRI_a[len_RRI_a]=RRI[i-1]+r_m*ei;
                        //sum_RRI= sum_RRI + RRI_a[len_RRI_a];

                        //printf("r %d %4f  \n",len_RRI_a,RRI_a[len_RRI_a]);
                        len_RRI_a=len_RRI_a+1;

                    }

                }
            }
        }
    }

//******************************************


    for(i=0;i<len_RRI_a;i++){
        rR_peak[i+1]=rR_peak[i]+RRI_a[i];
        //printf("i= %d %4f  \n",i+1,rR_peak[i+1]);
    }
    RRI_mean = rR_peak[i]/(len_RRI_a);

    HR = 60/RRI_mean;
    //printf(" RRI_mean= %f HR%d  \n", RRI_mean,HR);

}



double sort(double*in,int begin,int end){

    double number[end-begin] ;
    int i = 0, j = 0,len=end-begin;
    double temp = 0;
    for( i = 0; i < len; i++) {
        number[i]=in[begin+i];
    }

    for( i = 0; i < len; i++) {
        for( j = i; j < len; j++) {
            if( number[j] > number[i] ) {
                temp = number[j];
                number[j] = number[i];
                number[i] = temp;
            }
        }
    }
    return number[0];
}


