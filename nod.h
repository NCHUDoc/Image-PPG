/////�]�w����
#define isBolymin		0		// (1)Bolymin����(�y���j) (0)Lab or esc_car�v�� (2)ZJU Database

/////�]�w�v����J�榡
 #define VGA						//640*480
 //#define QVGA					//320*240

#ifdef VGA
#define Resolutiontype_shi 1    //640*480
#define WYSIZE_in		640		//��J�v���j�p
#define HXSIZE_in		480
#define ONE_SIZE_in		WYSIZE_in*HXSIZE_in
#endif

#ifdef QVGA
#define Resolutiontype_shi 0    //320*240
#define WYSIZE_in		320		//��J�v���j�p
#define HXSIZE_in		240
#define ONE_SIZE_in		WYSIZE_in*HXSIZE_in
#endif

#define WYSIZE			320		//�B�z320*240	
#define HXSIZE			240
#define ONE_SIZE		WYSIZE*HXSIZE
/////level 1 
#define TH1first_shih	10000	//TH1��l�ȡA�d��500~500000

/////level2
#define TH2first_shih	25000	//ZJU��2500�}�l //esc972g 20000�}�l//
