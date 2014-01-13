//#include <pgrflycapture.h> // FlyCapture���C�u�����̃w�b�_
#include <stdio.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <winsock2.h>
#include <ws2tcpip.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <math.h>		
#include <windows.h>	//TIME
#include <time.h>		
#include<stdlib.h>              // rand()�֐����g�p���邽�߂ɕK�v�ȃw�b�_�t�@�C��
#include<omp.h>//masuda OpenMP(����)�̃w�b�_�t�@�C��
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
//�`��p�ǂݍ���//
#include <iostream>
#include <omp.h>

#include <GL/glut.h>

#define X_SIZE 640
#define Y_SIZE 480
#define label_max 15
//HOAP�̕����l���������p
#define Foot_width 100.0
#define Y_center 250.0

extern float Base_zx[16][Y_SIZE+1] ;
extern int occ_point[16][Y_SIZE+1] ;//�I�N���[�W��������
extern int hhh;
extern float pre_Base_zx[16][Y_SIZE+1];
extern int vsd[Y_SIZE];;
extern float Relative_disparity[16][Y_SIZE+1] ;
//extern float	A,B,C;  //�ŏI���蕽�ʃp�����[�^
extern int Obstacle[16][Y_SIZE+1]; //��Q���L���p

//Socket�ʐM�p
//extern int dstSocket;
//extern char buffer[2];

//������
extern double   Alpha[16][Y_SIZE+1],Kinf[16][Y_SIZE+1];
extern char gomic[128];
//double *Distance;//�Ԋu
extern double fdu,fdv;//forcal length per delta u & v
extern double Cu,Cv;//center point
extern double k1,k2;//distortion k1,k2
extern float  Xd,Yd,r2,r4,Xu,Yu;
extern double Z_Range_Data[16][Y_SIZE+1],X_Range_Data[16][Y_SIZE+1],Y_Range_Data[16][Y_SIZE+1];

extern int sockflag;

//���ʃp�����[�^
extern float dis_A,dis_B,dis_C ; 
extern double height,pan,tilt_1,tilt ;
//���W�ϊ�
extern double Move_Z_Range_Data[16][Y_SIZE+1],Move_X_Range_Data[16][Y_SIZE+1],Move_Y_Range_Data[16][Y_SIZE+1];

//�������摜�̕��ʕ`��p
extern float X_Range_MAX;
extern float X_Range_min;
extern float Y_Range_MAX;
extern float Y_Range_min;

//-------------------------------------OpenGL-------------------------------------------

#define gl_divi_st 5.0
#define gl_divi_r 5.0
#define ROTATE_STEP     50    // �}�E�X�ړ��ʂƃe�N�X�`����]�p�̒��x
#define ZOOM_RATE       3      // �}�E�X�h���b�O���̃Y�[���̒��x

extern char *GL_window_name[];

extern int window_width;         // �E�C���h�E��
extern int window_height;        // �E�C���h�E����

//�}�E�X����p
extern int ox, oy;     // �}�E�X���W
extern double lx, ly, lz;    // �e�N�X�`���̉�]�p�i�݂����Ȃ��́j

extern GLdouble vertex[][3] ;

extern int edge[][2] ;

//�t�H���g
extern void *font1 ;
extern void *font2 ;
extern void DrawString(const char *str,void *font,float x,float y,float z);
extern void ColoredRange(float Z);
//void *font = GLUT_STROKE_ROMAN;
extern void *font ;

//�v��
void idle();
//���W���̖��O�`��
void DrawString3D(const char *str,void *font,float Width);
//���낢��`��
void display_Re(void);
void display_Di(void);

void display_Di_2(void);


//���W���̐����`��
void DrawString(const char *str,void *font,float x,float y,float z);
// �E�C���h�E���T�C�Y�̃R�[���o�b�N
void resize(int w, int h);
// �}�E�X�ړ��i���h���b�O�j�̃R�[���o�b�N
void left_motionFunc(int x, int y) ;
// �}�E�X�ړ��i�E�h���b�O�j�̃R�[���o�b�N
void right_motionFunc(int x, int y) ;
// �N���b�N���̃R�[���o�b�N
void mouseFunc(int button, int state, int x, int y) ;
// �L�[�{�[�h���͎��̃R�[���o�b�N
void keyboard(unsigned char key, int x, int y);