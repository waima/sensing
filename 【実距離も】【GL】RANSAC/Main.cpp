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
#define occ_threshold 0.0 //�I�N���[�W��������

	
char window_name[] = "Camera image";

CArtCamSdk	g_CArtCamSdk;


//�������Ԍv��
LARGE_INTEGER nFreq, nBefore, nAfter, anFreq, anBefore, anAfter;
DWORD dwTime, alldwTime;

unsigned char image_in[Y_SIZE][X_SIZE];
float  X_zyuusin[16][Y_SIZE], X_kido_sum[16][Y_SIZE], kido_moment_x_sum[16][Y_SIZE];//�錾
int Y_max[16],Y_min[16];
//int q = 0;

int X=0,Y=0;
unsigned char	Lgvalue[(int)L_SEARCH+ (int)R_SEARCH + 1];
float	a=0.0,b=0.0;
unsigned char max_kido = 0;
float threshold = 0.0;

float oc_threshold = 0.0;
int count = 0.0;//�I�N���[�W�����̃J�E���g�p



float Base_zx[16][Y_SIZE+1] = {0.0};
int occ_point[16][Y_SIZE+1] ={0};//�I�N���[�W��������
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


//������
double  Alpha[16][Y_SIZE+1]={0.0},Kinf[16][Y_SIZE+1]={0.0};
char gomic[128];
double fdu,fdv;//forcal length per delta u & v
double Cu,Cv;//center point
double k1,k2;//distortion k1,k2
float  Xd,Yd,r2,r4,Xu,Yu;
double Z_Range_Data[16][Y_SIZE+1]={0.0},X_Range_Data[16][Y_SIZE+1]={0.0},Y_Range_Data[16][Y_SIZE+1]={0.0};

//�c�ݕ␳
unsigned char *bgr_buffer;
IplImage *distortion_image; // ���摜
IplImage *undistortion_image; // �Ђ��ݕ␳�摜
IplImage *draw_image; // �`��p�摜

//�s��쐬
CvMat *intrinsic;
CvMat *distortion;

float Intrinsic_mat[9];
float Distortion_mat[4];


//�������摜�̕��ʕ`��p
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


int window_width = 800;         // �E�C���h�E��
int window_height = 800;        // �E�C���h�E����

//�}�E�X����p
int ox=0, oy=0;     // �}�E�X���W
double lx=0, ly=0, lz=48;    // �e�N�X�`���̉�]�p�i�݂����Ȃ��́j

int Re, Di,Di2;

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },//0
  { 4*gl_divi_st, 0.0, 0.0 },//x���[�_
  { 0.0, 4*gl_divi_st, 0.0 },//y���[�_
  { 0.0, 0.0, 6*gl_divi_st },//z���[�_


  { 4*gl_divi_st, 4*gl_divi_st, 0.0 },//4
  //Z���̐��`��
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

  //x���̐��`��
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

  //Y���̐��`��
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
  //Y����5�Ԋu��6�Ԋu�ɑ���
  { 0.0, 0.0, 5*gl_divi_r },//49
  { 4*gl_divi_st, 0.0, 5*gl_divi_r },
  { 0.0, 4*gl_divi_st, 5*gl_divi_r },

  ////X����Z����5�Ԋu��6�Ԋu�ɑ���
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

  //Y����5/*�Ԋu��6�Ԋu�ɑ���
  { 49, 50 },
  { 49, 51 },

  //X����Z����5�Ԋu��6�Ԋu�ɑ���
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

//�t�H���g
void *font1 = GLUT_BITMAP_HELVETICA_18;
void *font2 = GLUT_BITMAP_TIMES_ROMAN_24;
void DrawString(const char *str,void *font,float x,float y,float z);

//void *font = GLUT_STROKE_ROMAN;
void *font = GLUT_STROKE_MONO_ROMAN;


/////////////////////////////////////////////////////////////////////////////////main�֐�//////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	
	//CAMERA�̐ݒ肨���CV�E�B���h�E�̍쐬//


	cvNamedWindow( window_name, CV_WINDOW_AUTOSIZE); // OpenCV�̃E�C���h�E���쐬����B�E�C���h�E�ւ̃A�N�Z�X�ɂ�window_name�Ŏw�肵�����O���g���܂�
	IplImage *cv_image2 = cvCreateImage( cvSize(640,480), IPL_DEPTH_8U, 1 ); // OpenCV�摜�̍쐬(8�r�b�g1�`���l���j


   
    distortion_image = cvCreateImage( cvSize(X_SIZE,Y_SIZE), IPL_DEPTH_8U, 1); // OpenCV�摜�̍쐬(8�r�b�g3�`���l���j
	undistortion_image = cvCreateImage( cvSize( X_SIZE,Y_SIZE), IPL_DEPTH_8U, 1); // OpenCV�摜�̍쐬(8�r�b�g3�`���l���j
	draw_image = cvCreateImage( cvSize( X_SIZE,Y_SIZE ), IPL_DEPTH_8U, 3); // OpenCV�摜�̍쐬(8�r�b�g3�`���l���j

	int kekka_dll = g_CArtCamSdk.LoadLibrary("ArtCamSdk_036MI.dll");//dll�̃��[�h
	int kekka_shokika = g_CArtCamSdk.Initialize(NULL);//������

	g_CArtCamSdk.SetExposureTime(400);
	g_CArtCamSdk.SetGlobalGain(0);
	
	g_CArtCamSdk.SetSamplingRate(3);//�t���[�����[�g�Ǝ�荞�݃T�C�Y�̐ݒ� 3:640�~480 15fps




//��������X�^�[�g//


errno_t err;


 if ((err=fopen_s(&dd,"Analysis.csv","w"))!=0)
  {
   printf("�t�@�C�����J���܂���2\n");
   getchar();
   return (-1);
  }


 if ((err=fopen_s(&ff,"Time.csv","w"))!=0)
  {
   printf("�t�@�C�����J���܂���4\n");
   getchar();
   return (-1);
  }


if ((err=fopen_s(&gr,"�d�S.csv","w"))!=0)
  {
   printf("�t�@�C�����J���܂���6\n");
   getchar();
   return (-1);
  }


if ((err=fopen_s(&pval,"��f�l�̏o��.csv","w"))!=0)//OpenCV�E�C���h�E�̉����ɏo��
  {
   printf("�t�@�C�����J���܂���\n");
   getchar();
   return (-1);
  }




//�e���v���̓ǂݍ���//
if ((err=fopen_s(&tmp,"Template.csv","r"))!=0)
  {
   printf("�t�@�C�����J���܂���\n");
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
   printf("�t�@�C�����J���܂���\n");
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

	//�s��쐬
	CvMat *intrinsic = cvCreateMat (3, 3, CV_32FC1);
	CvMat *distortion = cvCreateMat (1, 4, CV_32FC1);

	//�t�@�C���̓ǂݍ���
	if ((err=fopen_s(&fp,"M_Distrotion.csv","r"))!=0)
	{
		printf("�t�@�C�����J���܂���\n");
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

	printf("�ǂݍ��݂܂���\n");

printf("�e���v���[�g�ǂݍ��݊���\n");
		

//////////////////////////////////////////////////////////�����GET////////////////////////////////////////////////////////////////////////////
// //�d�S���Z�J�n
printf("����ʂ��擾���܂�\n");

			
	for(int freq=1; freq<=Base_freq; freq++)
    {



		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
		Sleep(50);
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);



		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCV�̉摜�o�b�t�@��RGB�o�b�t�@���R�s�[

		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 





		 for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if(pre_Base_zx[label][v] != 0.0) 
		            { 
						X=(int)( floor(pre_Base_zx[label][v]+0.5) );//�l�̌ܓ�

						for (int k=0; k<=(int)L_SEARCH + (int)R_SEARCH; k++ )//������
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
					threshold = 0;//������
					threshold = max_kido / denomi;
					//threshold = 30.0;
					a=0.0;
			        b=0.0;

			for(int h=0; h<=(int)SEARCH +(int)R_SEARCH; h++ )			// ���W�̌v�Z
			{
				if( (float)Lgvalue[h] > threshold) //臒l�ȏ�ɏd�S���Z
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
						Base_zx[label][v] = sum_Base_zx[label][v] / (float)Base_freq; //Base_freq�����߂�����
						fprintf(gr,"%d,%d,%f\n",label,v,Base_zx[label][v]);
					}
					else{
						fprintf(gr,"%d,%d,%f\n",label,v,zero);
					}
					
				}




//////////////////////////////////////////////////////////�����GET�I��////////////////////////////////////////////////////////////////////////////

printf("���Ύ������Z�o���܂�\n");



//////////////////////////////////////////////////////////////////OpenCV///////////////////////////////////////////////////////////////////////////////////////
	
	while ( cvWaitKey( 10) == -1)// �L�[���͂�����܂ŌJ��Ԃ�
	{ 




		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);


		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCV�̉摜�o�b�t�@��RGB�o�b�t�@���R�s�[

		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 

		//���͉摜��񎟂̔z��ɂ���
	    for(int y=0; y<Y_SIZE; y++)
		    for(int x=0; x<X_SIZE; x++)
		    {
		        image_in[y][x] = (unsigned char)undistortion_image->imageData[ X_SIZE * y + ( x - 1 ) ];
	     	}

	 	cvCvtColor(undistortion_image, draw_image, CV_GRAY2BGR); //�J���[�摜�ϊ�(3�`�����l���ɕϊ�)



//////////////////////////////////////////////////////////////realTIME���Ύ���////////////////////////////////////////////////////////

		
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
						X=(int)( floor(Base_zx[label][v]+0.5) );//�l�̌ܓ�

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
							occ_point[label][v] = 1;//�I�N���[�W��������
						}
						else
						{
							occ_point[label][v] = 0;//�I�N���[�W�����Ȃ�

						}


			
					threshold = 0;//������
					threshold = max_kido / denomi;
					//threshold = 30.0;
					a=0.0;
			        b=0.0; 

			      if(occ_point[label][v] == 0)
	    	      {

			for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// ���W�̌v�Z
			{
				if( (float)Lgvalue[h] > threshold) //臒l�ȏ�ɏd�S���Z
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
						X=(int)( floor(Base_zx[label][v]+0.5) );//�l�̌ܓ�
					}
				}


//////////////////////////////////////////////////////////////realTIME���Ύ����I��////////////////////////////////////////////////////////


		 for (int label=1; label<=label_max; label++)//�d�S���Z�ƃt�@�C���o��
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


		cvShowImage( window_name, draw_image); // �E�C���h�E��`��
		

	}

    cvSaveImage("output.bmp", draw_image);
    cvReleaseImage( &draw_image); // OpenCV�摜�̉��
	cvDestroyWindow(window_name); // OpenCV�E�C���h�E�̉��

	//��f�l�̏o��
	for(int y=1; y<=Y_SIZE; y++)
	{
		for(int x=1; x<=X_SIZE; x++)
		{
          fprintf(pval,"%d,",image_in[y][x]);
		}
		  fprintf(pval,"\n");
	}
	fclose(pval);
    

//////////////////////////////////////////////////////////////////OpenCV�I��////////////////////////////////////////////////////////////////////////////////

    
  //OpenGL������
	glutInit(&argc, argv);


	//---------����---------
	glutInitWindowPosition(200, 220);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Di = glutCreateWindow(GL_window_name_Di[0]);
	//glutCreateWindow(GL_window_name_Di[0]);
	glutDisplayFunc(display_Di);

	//�R�[���o�b�N
	glutReshapeFunc(resize);
	glutMouseFunc(mouseFunc); 
	//glutMotionFunc(motionFunc); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);


	//glutMainLoop();

	//---------����---------
	glutInitWindowPosition(1000, 220);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Di2 = glutCreateWindow(GL_window_name_Di_2[0]);
    //glutCreateWindow(GL_window_name_Di_2[0]);

	glutDisplayFunc(display_Di_2);

	//�R�[���o�b�N
	glutReshapeFunc(resize);
	glutMouseFunc(mouseFunc); 
	//glutMotionFunc(motionFunc); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

  
   //���C�����[�v�Ƀh�[���I
  glutMainLoop();



//�g�p�t�@�C���̃N���[�Y
fclose(ff);

// �I������


	cvReleaseImage( &distortion_image); // OpenCV�摜�̉��
	cvReleaseImage( &undistortion_image); // OpenCV�摜�̉��
	cvDestroyWindow(window_name); // OpenCV�E�C���h�E�̉��

	return 0;

}




/////////////////////////////////////////////////////////////////////////////////////main�֐��I��//////////////////////////////////////////////////////////////////////////////////////

/*----�ȉ��g�p����Ă���֐�---------------------------------------------------------------------------------------------------------------*/

//�s�񏉊���
void matzero(float *a, int m, int n)
{
	int i,j;
	j = m * n;
	
	for (i=0;i<j;i++)
		a[i] = 0.0;
}

//3�~3�̋t�s��	
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

		dh[0][0]=9999.0;//���ʂƂ��킹�v�Q�ƁI�I�I
		dh[0][1]=9999.0;
		dh[0][2]=9999.0;
		dh[1][1]=9999.0;
		dh[1][2]=9999.0;
		dh[2][2]=9999.0;
		dh[1][0]=9999.0;		
		dh[2][0]=9999.0;		
		dh[2][1]=9999.0;		
			}

		dh[0][0]=(dt[1][1]*dt[2][2]-dt[1][2]*dt[2][1])/det;//���ʂƂ��킹�v�Q�ƁI�I�I
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

	sprintf_s(fname, "������/Distance_Image%02d.csv",hhh);
	if ((err=fopen_s(&dis,fname,"w"))!=0)
	{
	 printf("�t�@�C�����J���܂���9\n");
	//return (-1);
	}
	fprintf(dis,"�f�[�^�`��,102\n��i�q�f�[�^\nX,Y,Z\n");



	/////�������̏�����/////////////
	for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					pre_Relative_disparity[label][v]=0.0;
					Relative_disparity[label][v]=0.0;
					zx[label][v] = 0.0;
				}
	

		//���ԕϐ��̏�����
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);






		IplImage *cv_image2 = cvCreateImage( cvSize(640,480), IPL_DEPTH_8U, 1 ); // OpenCV�摜�̍쐬(8�r�b�g1�`���l���j

		int kekka = g_CArtCamSdk.CallBackPreview(NULL,(BYTE*)cv_image2->imageData,307200,1);
		Sleep(30);//RSJ���e�_���@�v����
	    HWND hwnd = FindWindow(NULL,"Active Window");
        DestroyWindow(hwnd);



		memcpy( distortion_image->imageData, (BYTE*)cv_image2->imageData, X_SIZE * Y_SIZE); // OpenCV�̉摜�o�b�t�@��RGB�o�b�t�@���R�s�[	



		//�s��쐬
		CvMat *intrinsic = cvCreateMat (3, 3, CV_32FC1);
		CvMat *distortion = cvCreateMat (1, 4, CV_32FC1);

		intrinsic->data.fl[0] = Intrinsic_mat[0]; intrinsic->data.fl[1] = Intrinsic_mat[1]; intrinsic->data.fl[2] = Intrinsic_mat[2]; 
		intrinsic->data.fl[3] = Intrinsic_mat[3]; intrinsic->data.fl[4] = Intrinsic_mat[4]; intrinsic->data.fl[5] = Intrinsic_mat[5]; 
		intrinsic->data.fl[6] = Intrinsic_mat[6]; intrinsic->data.fl[7] = Intrinsic_mat[7]; intrinsic->data.fl[8] = Intrinsic_mat[8]; 

		distortion->data.fl[0] = Distortion_mat[0]; distortion->data.fl[1] = Distortion_mat[1]; distortion->data.fl[2] = Distortion_mat[2]; distortion->data.fl[3] = Distortion_mat[3]; 

		//���Ԍv�Z
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"�c�ݕ␳����,%d,",dwTime);

		//���ԕϐ��̏�����
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);

		
		cvUndistort2(distortion_image, undistortion_image, intrinsic, distortion); 


		//���Ԍv�Z
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"cvUndistort2�̂�,%d,",dwTime);


//�����̎Z�o

		//���ԕϐ��̏�����
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
						X=(int)( floor(Base_zx[label][v]+0.5) );//�l�̌ܓ�

						//������
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
						oc_threshold = max_kido / 1.5 ;//�I�N���[�W������臒l

				    for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// ���W�̌v�Z
		            {

						if((float)Lgvalue[h] > oc_threshold)
						{
							count++;
						}
					}


						//�I�N���[�W��������
						if( count < 5 || count > 70 )
						{

							occ_point[label][v] = 1;//�I�N���[�W��������
						}
						else
						{
							occ_point[label][v] = 0;//�I�N���[�W�����Ȃ�

							measure_num++;
						}

						threshold = 0;//������
						threshold = max_kido / denomi;
						a=0.0;
						b=0.0;

						if(occ_point[label][v] == 0)
						{
							for(int h=0; h<=(int)L_SEARCH + (int)R_SEARCH; h++ )			// ���W�̌v�Z
							{
								if( (float)Lgvalue[h] > threshold ) //臒l�ȏ�ɏd�S���Z
								{
									a+=(float)Lgvalue[h];
									b+=(float)(h-(int)L_SEARCH+X)*(float)Lgvalue[h];
								}
							}

							zx[label][v]=b/a;


						}//end if(occ_point[label][v] == 0)

					}//end if(Base_zx[label][v] != 0.0) 
				}//end for for



		//���Ԍv�Z
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"�d�S���Z,%d,",dwTime);


		////���ԕϐ��̏�����
		//memset(&nFreq,   0x00, sizeof nFreq);
		//memset(&nBefore, 0x00, sizeof nBefore);
		//memset(&nAfter,  0x00, sizeof nAfter);
		//dwTime = 0;
		//QueryPerformanceFrequency(&nFreq);
		//QueryPerformanceCounter(&nBefore);



//////////////////////////////////////////////////////////����GET�I��////////////////////////////////////////////////////////////////////////////

		////���Ԍv�Z
	 //   QueryPerformanceCounter(&nAfter);
	 //   dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	 //   fprintf(ff,"���Ύ����̕�����,%d,",dwTime);

		//���ԕϐ��̏�����
		memset(&nFreq,   0x00, sizeof nFreq);
		memset(&nBefore, 0x00, sizeof nBefore);
		memset(&nAfter,  0x00, sizeof nAfter);
		dwTime = 0;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBefore);

	//�������Z�o
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

						//�X�|�b�g�����̈ʒu�C�␳����
						Z_Range_Data[label][v] = Alpha[label][v] / (zx[label][v] - Kinf[label][v]);          //�P��[mm]
						X_Range_Data[label][v] = Z_Range_Data[label][v] * Xd;			//�P��[mm]
						Y_Range_Data[label][v] = -Z_Range_Data[label][v] * Yd;			//�P��[mm]//���ӁI���](������W�n)

						fprintf(dis,"%lf,%lf,%lf\n",X_Range_Data[label][v],Y_Range_Data[label][v],Z_Range_Data[label][v]);	

					}//end if

			}//end for for

		fclose(dis);	

		//���Ԍv�Z
	    QueryPerformanceCounter(&nAfter);
	    dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);
	    fprintf(ff,"�������Z�o,%d,",dwTime);




//�y�������z�s�N�Z���P�ʂł̕W���΍��Z�o

			PP[0][0]=0.0,PP[0][1]=0.0,PP[0][2]=0.0;
			PP[1][0]=-0.0,PP[1][1]=0.0,PP[1][2]=0.0;
			PP[2][0]=0.0,PP[2][1]=0.0,PP[2][2]=0.0;
			YY[0]=0.0,YY[1]=0.0,YY[2]=0.0;

			QQ[0][0]=0.0,QQ[0][1]=0.0,QQ[0][2]=0.0;
			QQ[1][0]=0.0,QQ[1][1]=0.0,QQ[1][2]=0.0;
			QQ[2][0]=0.0,QQ[2][1]=0.0,QQ[2][2]=0.0;
			A = 0.0, B = 0.0, C = 0.0; //������

			N = 0;
			sum_u = 0.0, sum_v = 0.0, sum_uu = 0.0, sum_vv = 0.0, sum_uv = 0.0, sum_zu = 0.0, sum_zv = 0.0, sum_z = 0.0;//������

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
//�c���̕W���΍��̎Z�o

//������////////////////////////////////////////
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
//������/////////////////////////////////////

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
					z[label][v] = (float)A * zx[label][v] + (float)B * v + (float)C;
					res_z[label][v] = (zx[label][v] - Kinf[label][v]) - z[label][v]; //�c��
					squ_res_z[label][v] = res_z[label][v] * res_z[label][v]; //�c�����		
					sum_squ_res_z += squ_res_z[label][v]; //�c�����a
					sum_res_z += res_z[label][v]; //�c���a
					//printf("����=%f,zx=%f,Kinf=%f,�c��=%f\n",z[label][v],zx[label][v] , Kinf[label][v],res_z[label][v]);
					}
				}

			avg_res_z = sum_res_z / (float)N;

			sum_squ_devi_res_z = 0.0;

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 	
						devi_res_z[label][v] = res_z[label][v] - avg_res_z; //�c���̕΍�
						sum_squ_devi_res_z += devi_res_z[label][v] * devi_res_z[label][v]; //�c���̕΍����a
					}
				}

			avg_squ_devi_res_z = sum_squ_devi_res_z / (float)N; //�c���̕΍����a�̕���
			STdevi_res_z = sqrt(avg_squ_devi_res_z); //�c���̕W���΍�
			
			printf("D_pixel_STdevi_res_z=�w%f�x�C",STdevi_res_z);
			fprintf(dd,"[Real_pixel]STdevi_res_z=,%f,",STdevi_res_z);
			
//END�y�������z�s�N�Z���P�ʂł̕W���΍��Z�o



//�y�������z�W���΍��Z�o

			PP[0][0]=0.0,PP[0][1]=0.0,PP[0][2]=0.0;
			PP[1][0]=-0.0,PP[1][1]=0.0,PP[1][2]=0.0;
			PP[2][0]=0.0,PP[2][1]=0.0,PP[2][2]=0.0;
			YY[0]=0.0,YY[1]=0.0,YY[2]=0.0;

			QQ[0][0]=0.0,QQ[0][1]=0.0,QQ[0][2]=0.0;
			QQ[1][0]=0.0,QQ[1][1]=0.0,QQ[1][2]=0.0;
			QQ[2][0]=0.0,QQ[2][1]=0.0,QQ[2][2]=0.0;
			A = 0.0, B = 0.0, C = 0.0; //������

			N = 0;
			sum_u = 0.0, sum_v = 0.0, sum_uu = 0.0, sum_vv = 0.0, sum_uv = 0.0, sum_zu = 0.0, sum_zv = 0.0, sum_z = 0.0;//������

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
//�c���̕W���΍��̎Z�o

//������////////////////////////////////////////
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
//������/////////////////////////////////////

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 
					z[label][v] = (float)A * X_Range_Data[label][v] + (float)B * Y_Range_Data[label][v] + (float)C;
					res_z[label][v] = Z_Range_Data[label][v] - z[label][v]; //�c��
					squ_res_z[label][v] = res_z[label][v] * res_z[label][v]; //�c�����		
					sum_squ_res_z += squ_res_z[label][v]; //�c�����a
					sum_res_z += res_z[label][v]; //�c���a
					}
				}

			avg_res_z = sum_res_z / (float)N;

			sum_squ_devi_res_z = 0.0;

			for (int label=1; label<=label_max; label++)
				for (int v=0; v<=Y_SIZE-1; v++)
				{
					if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		            { 	
						devi_res_z[label][v] = res_z[label][v] - avg_res_z; //�c���̕΍�
						sum_squ_devi_res_z += devi_res_z[label][v] * devi_res_z[label][v]; //�c���̕΍����a
					}
				}

			avg_squ_devi_res_z = sum_squ_devi_res_z / (float)N; //�c���̕΍����a�̕���
			STdevi_res_z = sqrt(avg_squ_devi_res_z); //�c���̕W���΍�
			
			printf("D_STdevi_res_z=�w%f�x�C",STdevi_res_z);
			fprintf(dd,"[Real]STdevi_res_z=,%f,\n",STdevi_res_z);

			}//�T���v�����O�񐔏I��(q���[�v)



void idle()
{

	//�S�̎��ԕϐ��̏�����
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

		//�y�S�́z���Ԍv�Z
		QueryPerformanceCounter(&anAfter);
	    alldwTime = (DWORD)((anAfter.QuadPart - anBefore.QuadPart) * 1000 / anFreq.QuadPart);
        fprintf(ff,"�S�̂̎���,%d\n",alldwTime);
	glutSetWindow(Re);
    glutPostRedisplay();

	glutSetWindow(Di);
    glutPostRedisplay();

	glutSetWindow(Di2);
    glutPostRedisplay();
}
