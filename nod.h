/////設定環境
#define isBolymin		0		// (1)Bolymin環境(臉較大) (0)Lab or esc_car影像 (2)ZJU Database

/////設定影像輸入格式
 #define VGA						//640*480
 //#define QVGA					//320*240

#ifdef VGA
#define Resolutiontype_shi 1    //640*480
#define WYSIZE_in		640		//輸入影像大小
#define HXSIZE_in		480
#define ONE_SIZE_in		WYSIZE_in*HXSIZE_in
#endif

#ifdef QVGA
#define Resolutiontype_shi 0    //320*240
#define WYSIZE_in		320		//輸入影像大小
#define HXSIZE_in		240
#define ONE_SIZE_in		WYSIZE_in*HXSIZE_in
#endif

#define WYSIZE			320		//處理320*240	
#define HXSIZE			240
#define ONE_SIZE		WYSIZE*HXSIZE
/////level 1 
#define TH1first_shih	10000	//TH1初始值，範圍500~500000

/////level2
#define TH2first_shih	25000	//ZJU由2500開始 //esc972g 20000開始//
