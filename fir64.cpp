//#include <stdio.h>
//#include <string.h>
#include "widget.h"

//#define filterLength   65
//#define SAMPLES   150
//void firFloat( double *fir_coeffs, double *input, double *output,int in_length ,int out_length , int filterLength );
/*
const double fir_coeffs[ 65] =
{
0.001440,
0.001220,
0.000930,
0.000560,
0.000110,
-0.00036,
-0.00075,
-0.00089,
-0.00065,
0.000050,
0.001240,
0.002670,
0.003950,
0.004560,
0.003870,
0.001330,
-0.00343,
-0.01041,
-0.01919,
-0.02885,
-0.03807,
-0.04527,
-0.04885,
-0.04747,
-0.04033,
-0.02734,
-0.00927,
0.012290,
0.035120,
0.056640,
0.074270,
0.085830,
0.089860,
0.085830,
0.074270,
0.056640,
0.035120,
0.012290,
-0.00927,
-0.02734,
-0.04033,
-0.04747,
-0.04885,
-0.04527,
-0.03807,
-0.02885,
-0.01919,
-0.01041,
-0.00343,
0.001330,
0.003870,
0.004560,
0.003950,
0.002670,
0.001240,
0.000050,
-0.00065,
-0.00089,
-0.00075,
-0.00036,
0.000110,
0.000560,
0.000930,
0.001220,
0.001440
};
*/
void Widget::fir64(  double *input, double *output,int in_length ,int out_length , int filterLength )
{
    double acc;     // accumulator for MACs

    //double fir_coeffs[ 64];
    int n;
    int k;

    double fir_coeffs[ ] =
    {
    0.001440,
    0.001220,
    0.000930,
    0.000560,
    0.000110,
    -0.00036,
    -0.00075,
    -0.00089,
    -0.00065,
    0.000050,
    0.001240,
    0.002670,
    0.003950,
    0.004560,
    0.003870,
    0.001330,
    -0.00343,
    -0.01041,
    -0.01919,
    -0.02885,
    -0.03807,
    -0.04527,
    -0.04885,
    -0.04747,
    -0.04033,
    -0.02734,
    -0.00927,
    0.012290,
    0.035120,
    0.056640,
    0.074270,
    0.085830,
    0.089860,
    0.085830,
    0.074270,
    0.056640,
    0.035120,
    0.012290,
    -0.00927,
    -0.02734,
    -0.04033,
    -0.04747,
    -0.04885,
    -0.04527,
    -0.03807,
    -0.02885,
    -0.01919,
    -0.01041,
    -0.00343,
    0.001330,
    0.003870,
    0.004560,
    0.003950,
    0.002670,
    0.001240,
    0.000050,
    -0.00065,
    -0.00089,
    -0.00075,
    -0.00036,
    0.000110,
    0.000560,
    0.000930,
    0.001220,
    0.001440
    };

    //in_c= fopen("coffes.txt","rb");
    // put the new samples at the high end of the buffer
    //fread(fir_coeffs, sizeof(double), 65, in_c);


 
    // apply the filter to each input sample
    for ( n = 0; n < in_length-filterLength; n++ ) {
        // calculate output n

        acc = 0;
        for ( k = 0; k < filterLength; k++ ) {
            //acc += (*coeffp++) * (*inputp--);
            acc += fir_coeffs[k] * input[filterLength-k-1+n];
            
        }
        output[n] = acc;       
        //printf("n=%d output=%f\n",n,output[n]);
        
    }

    out_length=n;
    //fclose(in_c);

 
}
/*
void Widget::fir64(double *in,int in_len,double *out,int out_len){
	
    //int size=150;
    //float input[SAMPLES];
    //float output[SAMPLES];



	
        firFloat(  in, out, in_len,out_len,FILTER_LEN );

	    for(int i=0;i<size;i++){
		printf("i=%d output=%f\n",i,output[i]);
		}



	

   
	
}

*/
