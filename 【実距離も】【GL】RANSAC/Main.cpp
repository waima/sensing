#include "stdafx.h"
#include "extern.h"
#include "CArtCamSdk.hpp"

#include <tisudshl.h>




#define SEARCH 50.0

#define L_SEARCH 40.0
#define R_SEARCH 35.0


#define denomi 1.8//


#define Base_freq 10
#define zero    0.0
#define occ_threshold 0.0 //オクルージョン判定

	
char window_name[] = "Camera image";

CArtCamSdk	g_CArtCamSdk;


//処理時間計測
LARGE_INTEGER nFreq, nBefore, nAfter, anFreq, anBefore, anAfter;
DWORD dwTime, alldwTime;

unsigned char image_in[Y_SIZE][X_SIZE];
float  X_zyuusin[16][Y_SIZE], X_kido_sum[16][Y_SIZE], kido_moment_x_sum[16][Y_SIZE];//宣言
int Y_max[16],Y_min[16];
//int q = 0;

int X=0,Y=0;
unsigned char	Lgvalue[(int)L_SEARCH+ (int)R_SEARCH + 1];
float	a=0.0,b=0.0;
unsigned char max_kido = 0;
float threshold = 0.0;

float oc_threshold = 0.0;
int count = 0.0;//オクルージョンのカウント用



float Base_zx[16][Y_SIZE+1] = {0.0};
int occ_point[16][Y_SIZE+1] ={0};//オクルージョン判定
float pre_Base_zx[16][Y_SIZE+1] = {0.0};
float sum_Base_zx[16][Y_SIZE+1] = {0.0};
float zx[16][Y_SIZE+1] = {0.0};
float Relative_disparity[16][Y_SIZE+1] = {0.0};
float pre_Relative_disparity[16][Y_SIZE+1] = {0.0};
float sum_u = 0.0, sum_v = 0.0, sum_uu = 0.0, sum_vv = 0.0, sum_uv = 0.0, sum_zu = 0.0, sum_zv = 0.0, sum_z = 0.0;
int N = 0;
int hhh = 0;
float PP[3][3] = {0.0}, QQ[3][3] = {0.0}, YY[3] = {0.0}, CAns[3] = {0.0};
float A = 0.0, B = 0.0, C = 0.0; 
float z[16][Y_SIZE] = {0.0}, res_z[16][Y_SIZE] = {0.0}, squ_res_z[16][Y_SIZE] = {0.0}, devi_res_z[16][Y_SIZE] = {0.0};
float sum_squ_res_z= 0.0, sum_res_z = 0.0, avg_res_z = 0.0, sum_xzs = 0.0, sum_squ_devi_res_z = 0.0, avg_squ_devi_res_z = 0.0, STdevi_res_z = 0.0;
int slit_no[16],vsd[Y_SIZE];


//実距離
double  Alpha[16][Y_SIZE+1]={0.0},Kinf[16][Y_SIZE+1]={0.0};
char gomic[128];
double fdu,fdv;//forcal length per delta u & v
double Cu,Cv;//center point
double k1,k2;//distortion k1,k2
float  Xd,Yd,r2,r4,Xu,Yu;
double Z_Range_Data[16][Y_SIZE+1]={0.0},X_Range_Data[16][Y_SIZE+1]={0.0},Y_Range_Data[16][Y_SIZE+1]={0.0};

//歪み補正
unsigned char *bgr_buffer;
IplImage *distortion_image; // 生画像
IplImage *undistortion_image; // ひずみ補正画像
IplImage *draw_image; // 描画用画像

//行列作成
CvMat *intrinsic;
CvMat *distortion;

float Intrinsic_mat[9];
float Distortion_mat[4];


//実距離画像の平面描画用
int measure_num;
float *X_All_range;
float *Y_All_range;
float X_Range_MAX;
float X_Range_min;
float Y_Range_MAX;
float Y_Range_min;

char fname[128];
char input[128];


FILE *fp;
FILE *cc;
FILE *dd;
FILE *ee;
FILE *ff;

FILE *BB;
FILE *CC;
FILE *EE;
FILE *tmp;
FILE *obsn;
FILE *dis;
FILE *para;
FILE *M_dis;
FILE *gr;
FILE *pval;

void matzero(float *a, int m, int n);
void inverse(float	dt[][3],float	dh[][3]);










//-------------------------------------OpenGL-------------------------------------------

char *GL_window_name_Re[] = {"Relative_disparity_image"};
char *GL_window_name_Di[] = {"Distance_image"};
char *GL_window_name_Di_2[] = {"Distance_image_2"};


int window_width = 800;         // ウインドウ幅
int window_height = 800;        // ウインドウ高さ

//マウス制御用
int ox=0, oy=0;     // マウス座標
double lx=0, ly=0, lz=48;    // テクスチャの回転角（みたいなもの）

int Re, Di,Di2;

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },//0
  { 4*gl_divi_st, 0.0, 0.0 },//x軸端点
  { 0.0, 4*gl_divi_st, 0.0 },//y軸端点
  { 0.0, 0.0, 6*gl_divi_st },//z軸端点


  { 4*gl_divi_st, 4*gl_divi_st, 0.0 },//4
  //Z軸の線描画
  {   gl_divi_st, 0.0, 0.0 },//5
  { 2*gl_divi_st, 0.0, 0.0 },
  { 3*gl_divi_st, 0.0, 0.0 },
  { 4*gl_divi_st, 0.0, 0.0 },
  { 5*gl_divi_st, 0.0, 0.0 },
  {   gl_divi_st, 4*gl_divi_st, 0.0 },//10
  { 2*gl_divi_st, 4*gl_divi_st, 0.0 },
  { 3*gl_divi_st, 4*gl_divi_st, 0.0 },
  { 4*gl_divi_st, 4*gl_divi_st, 0.0 },
  { 5*gl_divi_st, 4*gl_divi_st, 0.0 },

  //x軸の線描画
  { 0.0,   gl_divi_st, 0.0 },//15
  { 0.0, 2*gl_divi_st, 0.0 },
  { 0.0, 3*gl_divi_st, 0.0 },
  { 0.0, 4*gl_divi_st, 0.0 },
  { 0.0, 5*gl_divi_st, 0.0 },
  { 4*gl_divi_st,   gl_divi_st, 0.0 },
  { 4*gl_divi_st, 2*gl_divi_st, 0.0 },
  { 4*gl_divi_st, 3*gl_divi_st, 0.0 },
  { 4*gl_divi_st, 4*gl_divi_st, 0.0 },
  { 4*gl_divi_st, 5*gl_divi_st, 0.0 },

  //Y軸の線描画
  { 4*gl_divi_st, 0.0, 6*gl_divi_r },//25
  { 0.0, 4*gl_divi_st, 6*gl_divi_r },

  { 0.0, 0.0,   gl_divi_r },//27
  { 0.0, 0.0, 2*gl_divi_r },
  { 0.0, 0.0, 3*gl_divi_r },
  { 0.0, 0.0, 4*gl_divi_r },
  { 4*gl_divi_st, 0.0,   gl_divi_r },
  { 4*gl_divi_st, 0.0, 2*gl_divi_r },
  { 4*gl_divi_st, 0.0, 3*gl_divi_r },
  { 4*gl_divi_st, 0.0, 4*gl_divi_r },
  { 0.0, 4*gl_divi_st,   gl_divi_r },
  { 0.0, 4*gl_divi_st, 2*gl_divi_r },
  { 0.0, 4*gl_divi_st, 3*gl_divi_r },
  { 0.0, 4*gl_divi_st, 4*gl_divi_r },

  {   gl_divi_st, 0.0, 6*gl_divi_r },//39
  { 2*gl_divi_st, 0.0, 6*gl_divi_r },
  { 3*gl_divi_st, 0.0, 6*gl_divi_r },
  { 4*gl_divi_st, 0.0, 6*gl_divi_r },//42
  { 5*gl_divi_st, 0.0, 6*gl_divi_r },
  { 0.0,   gl_divi_st, 6*gl_divi_r },
  { 0.0, 2*gl_divi_st, 6*gl_divi_r },
  { 0.0, 3*gl_divi_st, 6*gl_divi_r },
  { 0.0, 4*gl_divi_st, 6*gl_divi_r },
  //{ 0.0, 4*gl_divi_st, 6*gl_divi_r },
  { 0.0, 5*gl_divi_st, 6*gl_divi_r },
  //Y軸を5間隔→6間隔に増加
  { 0.0, 0.0, 5*gl_divi_r },//49
  { 4*gl_divi_st, 0.0, 5*gl_divi_r },
  { 0.0, 4*gl_divi_st, 5*gl_divi_r },

  ////X軸とZ軸を5間隔→6間隔に増加
  { 6*gl_divi_st, 0.0, 0.0 },//52
  { 6*gl_divi_st, 0.0, 1*gl_divi_r },
  { 6*gl_divi_st, 0.0, 2*gl_divi_r },
  { 6*gl_divi_st, 0.0, 3*gl_divi_r },
  { 6*gl_divi_st, 0.0, 4*gl_divi_r },
  { 6*gl_divi_st, 0.0, 5*gl_divi_r },
  { 6*gl_divi_st, 0.0, 6*gl_divi_r },

  { 6*gl_divi_st, 1*gl_divi_st, 0.0 },//59
  { 6*gl_divi_st, 2*gl_divi_st, 0.0 },
  { 6*gl_divi_st, 3*gl_divi_st, 0.0 },
  { 6*gl_divi_st, 4*gl_divi_st, 0.0 },
  { 6*gl_divi_st, 5*gl_divi_st, 0.0 },

  { 6*gl_divi_st, 6*gl_divi_st, 0.0 },//64

  { 0.0, 6*gl_divi_st, 0.0 },//65
  { 0.0, 6*gl_divi_st, 1*gl_divi_r },
  { 0.0, 6*gl_divi_st, 2*gl_divi_r },
  { 0.0, 6*gl_divi_st, 3*gl_divi_r },
  { 0.0, 6*gl_divi_st, 4*gl_divi_r },
  { 0.0, 6*gl_divi_st, 5*gl_divi_r },
  { 0.0, 6*gl_divi_st, 6*gl_divi_r },

  { 1*gl_divi_st, 6*gl_divi_st, 0.0 },//72
  { 2*gl_divi_st, 6*gl_divi_st, 0.0 },
  { 3*gl_divi_st, 6*gl_divi_st, 0.0 },
  { 4*gl_divi_st, 6*gl_divi_st, 0.0 },
  { 5*gl_divi_st, 6*gl_divi_st, 0.0 },//76

};

int edge[][2] = {
  { 0, 1 },//0
  { 0, 2 },
  { 0, 3 },

  { 1, 4 },
  { 5, 10 },
  { 6, 11 },
  { 7, 12 },
  /*{ 8, 13 },*/
  //{ 9, 14 },
 /* { 2, 4 },*/
  { 15, 20 },
  { 16, 21 },//10
  { 17, 22 },
  { 18, 23 },
  //{ 19, 24 },

  { 3, 25 },
  { 3, 26 },
  { 27, 31 },
  { 28, 32 },
  { 29, 33 },
  { 30, 34 },
  { 27, 35 },
  { 28, 36 },//20
  { 29, 37 },
  { 30, 38 },

  //{ 1, 25 },
  //{ 2, 26 },
  { 5, 39 },
  { 6, 40 },
  { 7, 41 },
  { 8, 42 },
  { 9, 43 },
  { 15, 44 },//30
  { 16, 45 },
  { 17, 46 },
  { 18, 47 },
  { 19, 48 },

  //Y軸を5/*間隔→6間隔に増加
  { 49, 50 },
  { 49, 51 },

  //X軸とZ軸を5間隔→6間隔に増加
  { 52, 58 },
  { 52, 64 },
  { 64, 65 },
  { 65, 71 },//40
  {  0, 52 },
  { 27, 53 },
  { 28, 54 },
  { 29, 55 },
  { 30, 56 },
  { 49, 57 },
  {  3, 58 },
  { 15, 59 },
  { 16, 60 },
  { 17, 61 },//50
  { 18, 62 },
  { 19, 63 },
  { 0, 65 },
  { 27, 66 },
  { 28, 67 },
  { 29, 68 },
  { 30, 69 },
  { 49, 70 },
  { 3, 71 },
  { 5, 72 },//60
  { 6, 73 },
  { 7, 74 },
  { 8, 75 },
  { 9, 76 },//64
  
};

//フォント
void *font1 = GLUT_BITMAP_HELVETICA_18;
void *font2 = GLUT_BITMAP_TIMES_ROMAN_24;
void DrawString(const char *str,void *font,float x,float y,float z);

//void *font = GLUT_STROKE_ROMAN;
void *font = GLUT_STROKE_MONO_ROMAN;


/////////////////////////////////////////////////////////////////////////////////main関数//////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	
	//CAMERAの設定およびCVウィンドウの作成//


	cvNamedWindow( window_name, CV_WINDOW_AUTOSIZE); // OpenCVのウインドウを作成する。ウインドウへのアクセスにはwindow_nameで指定した名前を使います
	IplImage *cv_image2 = cvCreateImage( cvSize(640,480), IPL_DEPTH_8U, 1 ); // OpenCV画像の作成(8ビット1チャネル）


   
    distortion_image = cvCreateImage( cvSize(X_SIZE,Y_SIZE), IPL_DEPTH_8U, 1); // OpenCV画像の作成(8ビット3チャネル）
	undistortion_image = cvCreateImage( cvSize( X_SIZE,Y_SIZE), IPL_DEPTH_8U, 1); // OpenCV画像の作成(8ビット3チャネル）
	draw_image = cvCreateImage( cvSize( X_SIZE,Y_SIZE ), IPL_DEPTH_8U, 3); // OpenCV画像の作成(8ビット3チャネル）

	int kekka_dll = g_CArtCamSdk.LoadLibrary("ArtCamSdk_036MI.dll");//dllのロード
	int kekka_shokika = g_CArtCamSdk.Initialize(NULL);//初期化

	g_CArtCamSdk.SetExposureTime(400);
	g_CArtCamSdk.SetGlobalGain(0);
	
	g_CArtCamSdk.SetSamplingRate(3);//フレームレートと取り込みサイズの設定 3:640×480 15fps




//ここからスタート//


errno_t err;


 if ((err=fopen_s(&dd,"Analysis.csv","w"))!=0)
  {
   printf("ファイルが開けません2\n");
   getchar();
   return (-1);
  }


 if ((err=fopen_s(&ff,"Time.csv","w"))!=0)
  {
   printf("ファイルが開けません4\n");
   getchar();
   return (-1);
  }


if ((err=fopen_s(&gr,"重心.csv","w"))!=0)
  {
   printf("ファイルが開けません6\n");
   getchar();
   return (-1);
  }


if ((err=fopen_s(&pval,"画素値の出力.csv","w"))!=0)//OpenCVウインドウの解放後に出力
  {
   printf("ファイルが開けません\n");
   getchar();
   return (-1);
  }




//テンプレの読み込み//
if ((err=fopen_s(&tmp,"Template.csv","r"))!=0)
  {
   printf("ファイルが開けません\n");
   return (-1); 
  }

	for (int label=1; label<=label_max; label++)
		for (int v=0; v<=Y_SIZE-1; v++)
		{
			fscanf_s(tmp,"%d,%d,%f\n",&slit_no[label],&vsd[v],&pre_Base_zx[label][v]);
			if(feof(tmp)!=0)
				break;
		}

fclose(tmp);

if ((err=fopen_s(&fp,"AlphaKinf.csv","r"))!=0)
  {
   printf("ファイルが開けません\n");
   return (-1);
  }
	for (int label=1; label<=label_max; label++)
		for (int v=0; v<=Y_SIZE-1; v++)
		{
			fscanf(fp,"%d,%d,%lf,%lf\n",&slit_no[label],&vsd[v],&Alpha[label][v],&Kinf[label][v]);
			if(feof(fp)!=0)
				break;
		}

	fclose(fp);

	//行列作成
	CvMat *intrinsic = cvCreateMat (3, 3, CV_32FC1);
	CvMat *distortion = cvCreateMat (1, 4, CV_32FC1);

	//ファイルの読み込み
	if ((err=fopen_s(&fp,"M_Distrotion.csv","r"))!=0)
	{
		printf("ファイルが開けません\n");
		return (-1);
	}
	
		fscanf_s(fp,"%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
			&intrinsic->data.fl[0],&intrinsic->data.fl[1],&intrinsic->data.fl[2],&intrinsic->data.fl[3],&intrinsic->data.fl[4],
			&intrinsic->data.fl[5],&intrinsic->data.fl[6],&intrinsic->data.fl[7],&intrinsic->data.fl[8]);
		fscanf_s(fp,"%f, %f, %f, %f\n",
			&distortion->data.fl[0],&distortion->data.fl[1],&distortion->data.fl[2],&distortion->data.fl[3]);

		fdu = intrinsic->data.fl[0];
		fdv = intrinsic->data.fl[4];
		Cu  = intrinsic->data.fl[2];
		Cv  = intrinsic->data.fl[5];
		k1  = distortion->data.fl[0];
		k2  = distortion->data.fl[1];

		Intrinsic_mat[0] = intrinsic->data.fl[0];Intrinsic_mat[1] = intrinsic->data.fl[1];Intrinsic_mat[2] = intrinsic->data.fl[2];
		Intrinsic_mat[3] = intrinsic->data.fl[3];Intrinsic_mat[4] = intrinsic->data.fl[4];Intrinsic_mat[5] = intrinsic->data.fl[5];
		Intrinsic_mat[6] = intrinsic->data.fl[6];Intrinsic_mat[7] = intrinsic->data.fl[7];Intrinsic_mat[8] = intrinsic->data.fl[8];

		Distortion_mat[0] = distortion->data.fl[0];Distortion_mat[1] = distortion->data.fl[1];Distortion_mat[2] = distortion->data.fl[2];Distortion_mat[3] = distortion->data.fl[3];

	fclose(fp);
	//printf("%f",intrinsic->data.fl[0]);

	printf("読み込みました\n");

printf("テンプレート読み込み完了\n");
		

//////////////////////////////////////////////////////////基準平面GET////////////////////////////////////////////////////////////////////////////
// //重心演算開始
printf("基準平面を取得します\n");

			
	for(int freq=1; freq<=Base_freq; freq++)
    {



		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
		Sleep(50);
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);



		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCVの画像バッファにRGBバッファをコピー

		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 





		 for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(pre_Base_zx[label][v] != 0.0) 
		            { 
						X=(int)( floor(pre_Base_zx[label][v]+0.5) );//四捨五入

						for (int k=0; k<=(int)L_SEARCH + (int)R_SEARCH; k++ )//初期化
						{
							Lgvalue[k] = 0;
						}

						max_kido=0;

						for (int k=-(int)L_SEARCH; k<=(int)R_SEARCH; k++ )
						{
							if(X_SIZE*v < (X-1)+(int)k+(X_SIZE*v) && (X-1)+(int)k+(X_SIZE*v) < X_SIZE*(v+1) )
							{
							Lgvalue[k+(int)L_SEARCH]=(unsigned char)undistortion_image->imageData[(X-1)+(int)k+(X_SIZE*v)];
							
							}
							else
							{
								Lgvalue[k+(int)L_SEARCH] = 0;
							}

							if (Lgvalue[k+(int)L_SEARCH] >= max_kido)
								max_kido = Lgvalue[k+(int)L_SEARCH];
						}
					threshold = 0;//初期化
					threshold = max_kido / denomi;
					//threshold = 30.0;
					a=0.0;
			        b=0.0;

			for(int h=0; h<=(int)SEARCH +(int)R_SEARCH; h++ )			// 座標の計算
			{
				if( (float)Lgvalue[h] > threshold) //閾値以上に重心演算
					{
						a+=(float)Lgvalue[h];
						b+=(float)(h-(int)L_SEARCH+X)*(float)Lgvalue[h];
					}
			}
				Base_zx[label][v] = b/a;
				sum_Base_zx[label][v] += Base_zx[label][v];

					}//end if
				}//end for for
				
	}//end for
for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(Base_zx[label][v] != 0.0) 
		            { 
						Base_zx[label][v] = sum_Base_zx[label][v] / (float)Base_freq; //Base_freq回基準求めた平均
						fprintf(gr,"%d,%d,%f\n",label,v,Base_zx[label][v]);
					}
					else{
						fprintf(gr,"%d,%d,%f\n",label,v,zero);
					}
					
				}




//////////////////////////////////////////////////////////基準平面GET終了////////////////////////////////////////////////////////////////////////////

printf("相対視差を算出します\n");



//////////////////////////////////////////////////////////////////OpenCV///////////////////////////////////////////////////////////////////////////////////////
	
	while ( cvWaitKey( 10) == -1)// キー入力があるまで繰り返す
	{ 




		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);


		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCVの画像バッファにRGBバッファをコピー

		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 

		//入力画像を二次の配列にする
	    for(int y=0; y<Y_SIZE; y++)
		    for(int x=0; x<X_SIZE; x++)
		    {
		        image_in[y][x] = (unsigned char)undistortion_image->imageData[ X_SIZE * y + ( x - 1 ) ];
	     	}

	 	cvCvtColor(undistortion_image, draw_image, CV_GRAY2BGR); //カラー画像変換(3チャンネルに変換)



//////////////////////////////////////////////////////////////realTIME相対視差////////////////////////////////////////////////////////

		
		for (int label=1; label<=label_max; label++)
			for (int v=0; v<=Y_SIZE-1; v++)
			{
				zx[label][v] = 0.0;
			}
		
		for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(Base_zx[label][v] != 0.0) 
		            { 
						X=(int)( floor(Base_zx[label][v]+0.5) );//四捨五入

						for (int k=0; k<=(int)L_SEARCH + (int)R_SEARCH; k++ )
						{
							Lgvalue[k] = 0;
						}

						max_kido=0;

						for (int k=-(int)L_SEARCH; k<=(int)R_SEARCH; k++ )
						{
							if(X_SIZE*v < (X-1)+(int)k+(X_SIZE*v) && (X-1)+(int)k+(X_SIZE*v) < X_SIZE*(v+1) )
							{
							Lgvalue[k+(int)L_SEARCH]=(unsigned char)undistortion_image->imageData[(X-1)+(int)k+(X_SIZE*v)];
							
							}
							else
							{
								Lgvalue[k+(int)L_SEARCH] = 0;
							}

							if (Lgvalue[k+(int)L_SEARCH] >= max_kido)
								max_kido = Lgvalue[k+(int)L_SEARCH];
						}



					if( max_kido < occ_threshold )
						{
							occ_point[label][v] = 1;//オクルージョンあり
						}
						else
						{
							occ_point[label][v] = 0;//オクルージョンなし

						}


			
					threshold = 0;//初期化
					threshold = max_kido / denomi;
					//threshold = 30.0;
					a=0.0;
			        b=0.0; 

			      if(occ_point[label][v] == 0)
	    	      {

			for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// 座標の計算
			{
				if( (float)Lgvalue[h] > threshold) //閾値以上に重心演算
					{
						a+=(float)Lgvalue[h];
						b+=(float)(h-(int)L_SEARCH+X)*(float)Lgvalue[h];
					}
			}

				zx[label][v]=b/a;

				pre_Relative_disparity[label][v] = Base_zx[label][v] - zx[label][v];

			           }//end if(occ_point[label][v] == 0)

					}//end if
				}//end for for

for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(Base_zx[label][v] != 0.0) 
		            { 
						X=(int)( floor(Base_zx[label][v]+0.5) );//四捨五入
					}
				}


//////////////////////////////////////////////////////////////realTIME相対視差終了////////////////////////////////////////////////////////


		 for (int label=1; label<=label_max; label++)//重心演算とファイル出力
				for (int v=1; v<=Y_SIZE; v++)
				{
					if(Base_zx[label][v] != 0.0)
		            { 
						 if(occ_point[label][v] == 0)
						 {
						//CvPoint p1={Base_zx[label][v],v};
						//CvPoint p2={zx[label][v],v};

						//cvLine( draw_image,p1,p2,CV_RGB(0,255,0),1,4 ,0);
						//cvLine( draw_image,p1,p1,CV_RGB(255,0,0),3,4 ,0);
						CvPoint p1={ Base_zx[label][v],v };
					    CvPoint p2={ zx[label][v],v };
                        CvPoint p3={ Base_zx[label][v],v };
					    CvPoint p4={ zx[label][v],v };
						if(v%2==0)
						{

                            cvLine( draw_image,p1,p2,CV_RGB(255,255,0),1,4 ,0);
						    
						}
						else{
						
                            cvLine( draw_image,p1,p2,CV_RGB(255,153,0),1,4 ,0);
						    
						}

							cvLine( draw_image,p3,p3,CV_RGB(0,0,255),3,4 ,0);
					  	    cvLine( draw_image,p4,p4,CV_RGB(255,0,0),3,4 ,0);
						
						

						 }
						  }

				}


		cvShowImage( window_name, draw_image); // ウインドウを描画
		

	}

    cvSaveImage("output.bmp", draw_image);
    cvReleaseImage( &draw_image); // OpenCV画像の解放
	cvDestroyWindow(window_name); // OpenCVウインドウの解放

	//画素値の出力
	for(int y=1; y<=Y_SIZE; y++)
	{
		for(int x=1; x<=X_SIZE; x++)
		{
          fprintf(pval,"%d,",image_in[y][x]);
		}
		  fprintf(pval,"\n");
	}
	fclose(pval);
    

//////////////////////////////////////////////////////////////////OpenCV終了////////////////////////////////////////////////////////////////////////////////

    
  //OpenGL初期化
	glutInit(&argc, argv);


	//---------正面---------
	glutInitWindowPosition(200, 220);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Di = glutCreateWindow(GL_window_name_Di[0]);
	//glutCreateWindow(GL_window_name_Di[0]);
	glutDisplayFunc(display_Di);

	//コールバック
	glutReshapeFunc(resize);
	glutMouseFunc(mouseFunc); 
	//glutMotionFunc(motionFunc); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);


	//glutMainLoop();

	//---------側面---------
	glutInitWindowPosition(1000, 220);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Di2 = glutCreateWindow(GL_window_name_Di_2[0]);
    //glutCreateWindow(GL_window_name_Di_2[0]);

	glutDisplayFunc(display_Di_2);

	//コールバック
	glutReshapeFunc(resize);
	glutMouseFunc(mouseFunc); 
	//glutMotionFunc(motionFunc); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

  
   //メインループにドーン！
  glutMainLoop();



//使用ファイルのクローズ
fclose(ff);

// 終了処理


	cvReleaseImage( &distortion_image); // OpenCV画像の解放
	cvReleaseImage( &undistortion_image); // OpenCV画像の解放
	cvDestroyWindow(window_name); // OpenCVウインドウの解放

	return 0;

}




/////////////////////////////////////////////////////////////////////////////////////main関数終了//////////////////////////////////////////////////////////////////////////////////////

/*----以下使用されている関数---------------------------------------------------------------------------------------------------------------*/

//行列初期化
void matzero(float *a, int m, int n)
{
	int i,j;
	j = m * n;
	
	for (i=0;i<j;i++)
		a[i] = 0.0;
}

//3×3の逆行列	
void inverse(float	dt[][3],float	dh[][3])	
{
	int	i=0,j=0;
	float	det=0.0;

			det=dt[0][0]*dt[1][1]*dt[2][2]+
				dt[1][0]*dt[2][1]*dt[0][2]+
				dt[2][0]*dt[0][1]*dt[1][2]-
				dt[0][0]*dt[2][1]*dt[1][2]-
				dt[2][0]*dt[1][1]*dt[0][2]-
				dt[1][0]*dt[0][1]*dt[2][2];
			if(det==0.0){

		dh[0][0]=9999.0;//結果とあわせ要参照！！！
		dh[0][1]=9999.0;
		dh[0][2]=9999.0;
		dh[1][1]=9999.0;
		dh[1][2]=9999.0;
		dh[2][2]=9999.0;
		dh[1][0]=9999.0;		
		dh[2][0]=9999.0;		
		dh[2][1]=9999.0;		
			}

		dh[0][0]=(dt[1][1]*dt[2][2]-dt[1][2]*dt[2][1])/det;//結果とあわせ要参照！！！
		dh[0][1]=(dt[0][2]*dt[2][1]-dt[0][1]*dt[2][2])/det;
		dh[0][2]=(dt[0][1]*dt[1][2]-dt[0][2]*dt[1][1])/det;
		dh[1][1]=(dt[0][0]*dt[2][2]-dt[0][2]*dt[2][0])/det;
		dh[1][2]=(dt[0][2]*dt[1][0]-dt[0][0]*dt[1][2])/det;
		dh[2][2]=(dt[0][0]*dt[1][1]-dt[0][1]*dt[1][0])/det;
		dh[1][0]=(dt[1][2]*dt[2][0]-dt[1][0]*dt[2][2])/det;		
		dh[2][0]=(dt[1][0]*dt[2][1]-dt[1][1]*dt[2][0])/det;		
		dh[2][1]=(dt[2][0]*dt[0][1]-dt[2][1]*dt[0][0])/det;		
}



void Sensing()
{

	//getchar();
	hhh++;

	errno_t err;

	sprintf_s(fname, "実距離/Distance_Image%02d.csv",hhh);
	if ((err=fopen_s(&dis,fname,"w"))!=0)
	{
	 printf("ファイルが開けません9\n");
	//return (-1);
	}
	fprintf(dis,"データ形式,102\n非格子データ\nX,Y,Z\n");



	/////視差情報の初期化/////////////
	for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					pre_Relative_disparity[label][v]=0.0;
					Relative_disparity[label][v]=0.0;
					zx[label][v] = 0.0;
				}
	

		//時間変数の初期化
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);






		IplImage *cv_image2 = cvCreateImage( cvSize(640,480), IPL_DEPTH_8U, 1 ); // OpenCV画像の作成(8ビット1チャネル）

		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
		Sleep(30);//RSJ投稿論文　計測時
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);



		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCVの画像バッファにRGBバッファをコピー	



		//行列作成
		CvMat *intrinsic = cvCreateMat (3, 3, CV_32FC1);
		CvMat *distortion = cvCreateMat (1, 4, CV_32FC1);

		intrinsic->data.fl[0] = Intrinsic_mat[0]; intrinsic->data.fl[1] = Intrinsic_mat[1]; intrinsic->data.fl[2] = Intrinsic_mat[2]; 
		intrinsic->data.fl[3] = Intrinsic_mat[3]; intrinsic->data.fl[4] = Intrinsic_mat[4]; intrinsic->data.fl[5] = Intrinsic_mat[5]; 
		intrinsic->data.fl[6] = Intrinsic_mat[6]; intrinsic->data.fl[7] = Intrinsic_mat[7]; intrinsic->data.fl[8] = Intrinsic_mat[8]; 

		distortion->data.fl[0] = Distortion_mat[0]; distortion->data.fl[1] = Distortion_mat[1]; distortion->data.fl[2] = Distortion_mat[2]; distortion->data.fl[3] = Distortion_mat[3]; 

		//時間計算
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"歪み補正準備,%d,",dwTime);

		//時間変数の初期化
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);

		
		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 


		//時間計算
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"cvUndistort2のみ,%d,",dwTime);


//視差の算出

		//時間変数の初期化
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);

		measure_num = 0;

		 for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(Base_zx[label][v] != 0.0) 
		            { 
						X=(int)( floor(Base_zx[label][v]+0.5) );//四捨五入

						//初期化
						for (int k=0; k<=(int)L_SEARCH + (int)R_SEARCH; k++ )
						{
							Lgvalue[k] = 0;
						}

						max_kido=0;

						for (int k=-(int)L_SEARCH; k<=(int)R_SEARCH; k++ )
						{
							if(X_SIZE*v < (X-1)+(int)k+(X_SIZE*v) && (X-1)+(int)k+(X_SIZE*v) < X_SIZE*(v+1) )
							{
							Lgvalue[k+(int)L_SEARCH]=(unsigned char)undistortion_image->imageData[(X-1)+(int)k+(X_SIZE*v)];
							
							}
							else
							{
								Lgvalue[k+(int)L_SEARCH] = 0;
							}

							if (Lgvalue[k+(int)L_SEARCH] >= max_kido)
								max_kido = Lgvalue[k+(int)L_SEARCH];
						}



						count = 0;
						oc_threshold = max_kido / 1.5 ;//オクルージョンの閾値

				    for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// 座標の計算
		            {

						if((float)Lgvalue[h] > oc_threshold)
						{
							count++;
						}
					}


						//オクルージョン判定
						if( count < 5 || count > 70 )
						{

							occ_point[label][v] = 1;//オクルージョンあり
						}
						else
						{
							occ_point[label][v] = 0;//オクルージョンなし

							measure_num++;
						}

						threshold = 0;//初期化
						threshold = max_kido / denomi;
						a=0.0;
						b=0.0;

						if(occ_point[label][v] == 0)
						{
							for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// 座標の計算
							{
								if( (float)Lgvalue[h] > threshold ) //閾値以上に重心演算
								{
									a+=(float)Lgvalue[h];
									b+=(float)(h-(int)L_SEARCH+X)*(float)Lgvalue[h];
								}
							}

							zx[label][v]=b/a;


						}//end if(occ_point[label][v] == 0)

					}//end if(Base_zx[label][v] != 0.0) 
				}//end for for



		//時間計算
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"重心演算,%d,",dwTime);


		////時間変数の初期化
		//memset(&nFreq,   0x00, sizeof nFreq);
		//memset(&nBefore, 0x00, sizeof nBefore);
		//memset(&nAfter,  0x00, sizeof nAfter);
		//dwTime = 0;
		//QueryPerformanceFrequency(&nFreq);
		//QueryPerformanceCounter(&nBefore);



//////////////////////////////////////////////////////////視差GET終了////////////////////////////////////////////////////////////////////////////

		////時間計算
	 //   QueryPerformanceCounter(&nAfter);
	 //   dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	 //   fprintf(ff,"相対視差の平滑化,%d,",dwTime);

		//時間変数の初期化
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);

	//実距離算出
	for (int label=1; label<=label_max; label++)
		for (int v=0; v<=Y_SIZE-1; v++)
			{
				if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) )
					{
						Xd = (zx[label][v] - Cu)/fdu;
						Yd = (v - Cv)/fdv;
						r2 = pow(Xd,2)+pow(Yd,2);
						r4 = r2*r2;
						Xu = Xd/((float)1.0 + k1*r2 + k2*r4);
						Yu = Yd/((float)1.0 + k1*r2 + k2*r4);

						//スポット光像の位置，補正完了
						Z_Range_Data[label][v] = Alpha[label][v] / (zx[label][v] - Kinf[label][v]);          //単位[mm]
						X_Range_Data[label][v] = Z_Range_Data[label][v] * Xd;			//単位[mm]
						Y_Range_Data[label][v] = -Z_Range_Data[label][v] * Yd;			//単位[mm]//注意！反転(左手座標系)

						fprintf(dis,"%lf,%lf,%lf\n",X_Range_Data[label][v],Y_Range_Data[label][v],Z_Range_Data[label][v]);	

					}//end if

			}//end for for

		fclose(dis);	

		//時間計算
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"実距離算出,%d,",dwTime);




//【実距離】ピクセル単位での標準偏差算出

			PP[0][0]=0.0,PP[0][1]=0.0,PP[0][2]=0.0;
			PP[1][0]=-0.0,PP[1][1]=0.0,PP[1][2]=0.0;
			PP[2][0]=0.0,PP[2][1]=0.0,PP[2][2]=0.0;
			YY[0]=0.0,YY[1]=0.0,YY[2]=0.0;

			QQ[0][0]=0.0,QQ[0][1]=0.0,QQ[0][2]=0.0;
			QQ[1][0]=0.0,QQ[1][1]=0.0,QQ[1][2]=0.0;
			QQ[2][0]=0.0,QQ[2][1]=0.0,QQ[2][2]=0.0;
			A = 0.0, B = 0.0, C = 0.0; //初期化

			N = 0;
			sum_u = 0.0, sum_v = 0.0, sum_uu = 0.0, sum_vv = 0.0, sum_uv = 0.0, sum_zu = 0.0, sum_zv = 0.0, sum_z = 0.0;//初期化

		for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
		            sum_u  += zx[label][v];
					sum_v  += (float)v;
					sum_uu += zx[label][v] * zx[label][v];
					sum_vv += (float)v * (float)v;
					sum_uv += zx[label][v] * (float)v ;
					sum_zu += zx[label][v] * (zx[label][v] - Kinf[label][v]) ;
					sum_zv += (float)v * (zx[label][v] - Kinf[label][v]);
					sum_z  += (zx[label][v] - Kinf[label][v]);
					N++;
					}
				}//label & v

		    PP[0][0]=sum_uu;	PP[0][1]=sum_uv;	PP[0][2]=sum_u;
			PP[1][0]=sum_uv;	PP[1][1]=sum_vv;	PP[1][2]=sum_v;
			PP[2][0]=sum_u;   	PP[2][1]=sum_v;  	PP[2][2]=(float)N;

			YY[0]=sum_zu;	YY[1]=sum_zv;	YY[2]=sum_z;

			inverse(PP,QQ);	

			matzero(CAns,1,3);

			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
				{
					CAns[i]+=(QQ[i][j]*YY[j]);
			    }

			A=CAns[0];
			B=CAns[1];
			C=CAns[2];
//printf("A=%f,B=%f,C=%f\n",A,B,C);
//残差の標準偏差の算出

//初期化////////////////////////////////////////
			sum_squ_res_z = 0.0;
			sum_res_z = 0.0;
			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					res_z[label][v] = 0;
					devi_res_z[label][v] = 0;
					z[label][v] = 0;
					squ_res_z[label][v] = 0;
				}
				 avg_res_z = 0.0;
		avg_squ_devi_res_z = 0.0;
//初期化/////////////////////////////////////

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
					z[label][v] = (float)A * zx[label][v] + (float)B * v + (float)C;
					res_z[label][v] = (zx[label][v] - Kinf[label][v]) - z[label][v]; //残差
					squ_res_z[label][v] = res_z[label][v] * res_z[label][v]; //残差二乗		
					sum_squ_res_z += squ_res_z[label][v]; //残差二乗和
					sum_res_z += res_z[label][v]; //残差和
					//printf("平面=%f,zx=%f,Kinf=%f,残差=%f\n",z[label][v],zx[label][v] , Kinf[label][v],res_z[label][v]);
					}
				}

			avg_res_z = sum_res_z / (float)N;

			sum_squ_devi_res_z = 0.0;

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 	
						devi_res_z[label][v] = res_z[label][v] - avg_res_z; //残差の偏差
						sum_squ_devi_res_z += devi_res_z[label][v] * devi_res_z[label][v]; //残差の偏差二乗和
					}
				}

			avg_squ_devi_res_z = sum_squ_devi_res_z / (float)N; //残差の偏差二乗和の平均
			STdevi_res_z = sqrt(avg_squ_devi_res_z); //残差の標準偏差
			
			printf("D_pixel_STdevi_res_z=『%f』，",STdevi_res_z);
			fprintf(dd,"[Real_pixel]STdevi_res_z=,%f,",STdevi_res_z);
			
//END【実距離】ピクセル単位での標準偏差算出



//【実距離】標準偏差算出

			PP[0][0]=0.0,PP[0][1]=0.0,PP[0][2]=0.0;
			PP[1][0]=-0.0,PP[1][1]=0.0,PP[1][2]=0.0;
			PP[2][0]=0.0,PP[2][1]=0.0,PP[2][2]=0.0;
			YY[0]=0.0,YY[1]=0.0,YY[2]=0.0;

			QQ[0][0]=0.0,QQ[0][1]=0.0,QQ[0][2]=0.0;
			QQ[1][0]=0.0,QQ[1][1]=0.0,QQ[1][2]=0.0;
			QQ[2][0]=0.0,QQ[2][1]=0.0,QQ[2][2]=0.0;
			A = 0.0, B = 0.0, C = 0.0; //初期化

			N = 0;
			sum_u = 0.0, sum_v = 0.0, sum_uu = 0.0, sum_vv = 0.0, sum_uv = 0.0, sum_zu = 0.0, sum_zv = 0.0, sum_z = 0.0;//初期化

		for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
		            sum_u  += X_Range_Data[label][v];
					sum_v  += Y_Range_Data[label][v];
					sum_uu += X_Range_Data[label][v] * X_Range_Data[label][v];
					sum_vv += Y_Range_Data[label][v] * Y_Range_Data[label][v];
					sum_uv += X_Range_Data[label][v] * Y_Range_Data[label][v];
					sum_zu += X_Range_Data[label][v] * Z_Range_Data[label][v];
					sum_zv += Y_Range_Data[label][v] * Z_Range_Data[label][v];
					sum_z  += Z_Range_Data[label][v];
					N++;
					}
				}//label & v

		    PP[0][0]=sum_uu;	PP[0][1]=sum_uv;	PP[0][2]=sum_u;
			PP[1][0]=sum_uv;	PP[1][1]=sum_vv;	PP[1][2]=sum_v;
			PP[2][0]=sum_u;   	PP[2][1]=sum_v;  	PP[2][2]=(float)N;

			YY[0]=sum_zu;	YY[1]=sum_zv;	YY[2]=sum_z;

			inverse(PP,QQ);	

			matzero(CAns,1,3);

			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
				{
					CAns[i]+=(QQ[i][j]*YY[j]);
			    }

			A=CAns[0];
			B=CAns[1];
			C=CAns[2];
//printf("A=%f,B=%f,C=%f\n",A,B,C);
//残差の標準偏差の算出

//初期化////////////////////////////////////////
			sum_squ_res_z = 0.0;
			sum_res_z = 0.0;
			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					res_z[label][v] = 0;
					devi_res_z[label][v] = 0;
					z[label][v] = 0;
					squ_res_z[label][v] = 0;
				}
				 avg_res_z = 0.0;
		avg_squ_devi_res_z = 0.0;
//初期化/////////////////////////////////////

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
					z[label][v] = (float)A * X_Range_Data[label][v] + (float)B * Y_Range_Data[label][v] + (float)C;
					res_z[label][v] = Z_Range_Data[label][v] - z[label][v]; //残差
					squ_res_z[label][v] = res_z[label][v] * res_z[label][v]; //残差二乗		
					sum_squ_res_z += squ_res_z[label][v]; //残差二乗和
					sum_res_z += res_z[label][v]; //残差和
					}
				}

			avg_res_z = sum_res_z / (float)N;

			sum_squ_devi_res_z = 0.0;

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 	
						devi_res_z[label][v] = res_z[label][v] - avg_res_z; //残差の偏差
						sum_squ_devi_res_z += devi_res_z[label][v] * devi_res_z[label][v]; //残差の偏差二乗和
					}
				}

			avg_squ_devi_res_z = sum_squ_devi_res_z / (float)N; //残差の偏差二乗和の平均
			STdevi_res_z = sqrt(avg_squ_devi_res_z); //残差の標準偏差
			
			printf("D_STdevi_res_z=『%f』，",STdevi_res_z);
			fprintf(dd,"[Real]STdevi_res_z=,%f,\n",STdevi_res_z);

			}//サンプリング回数終了(qループ)



void idle()
{

	//全体時間変数の初期化
		memset(&anFreq,   0x00, sizeof anFreq);
		memset(&anBefore, 0x00, sizeof anBefore);
		memset(&anAfter,  0x00, sizeof anAfter);
		alldwTime = 0;
		QueryPerformanceFrequency(&anFreq);
		QueryPerformanceCounter(&anBefore);

	Sensing();

	//getchar();

	//scanf("%d", &a);

	//if (a == 0)
	//{
	//	
	//	fclose(dd);
	//	fclose(ff);
	//}
	//else
	//{
	//	
	//}

		//【全体】時間計算
		QueryPerformanceCounter(&anAfter);
	    alldwTime = (DWORD)((anAfter.QuadPart - anBefore.QuadPart) * 1000 / anFreq.QuadPart);
        fprintf(ff,"全体の時間,%d\n",alldwTime);
	glutSetWindow(Re);
    glutPostRedisplay();

	glutSetWindow(Di);
    glutPostRedisplay();

	glutSetWindow(Di2);
    glutPostRedisplay();
}
