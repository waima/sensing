//#include <pgrflycapture.h> // FlyCaptureライブラリのヘッダ
#include <stdio.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <winsock2.h>
#include <ws2tcpip.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <math.h>		
#include <windows.h>	//TIME
#include <time.h>		
#include<stdlib.h>              // rand()関数を使用するために必要なヘッダファイル
#include<omp.h>//masuda OpenMP(並列化)のヘッダファイル
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
//描画用読み込み//
#include <iostream>
#include <omp.h>

#include <GL/glut.h>

#define X_SIZE 640
#define Y_SIZE 480
#define label_max 15
//HOAPの幅を考慮した回避用
#define Foot_width 100.0
#define Y_center 250.0

extern float Base_zx[16][Y_SIZE+1] ;
extern int occ_point[16][Y_SIZE+1] ;//オクルージョン判定
extern int hhh;
extern float pre_Base_zx[16][Y_SIZE+1];
extern int vsd[Y_SIZE];;
extern float Relative_disparity[16][Y_SIZE+1] ;
//extern float	A,B,C;  //最終推定平面パラメータ
extern int Obstacle[16][Y_SIZE+1]; //障害物記憶用

//Socket通信用
//extern int dstSocket;
//extern char buffer[2];

//実距離
extern double   Alpha[16][Y_SIZE+1],Kinf[16][Y_SIZE+1];
extern char gomic[128];
//double *Distance;//間隔
extern double fdu,fdv;//forcal length per delta u & v
extern double Cu,Cv;//center point
extern double k1,k2;//distortion k1,k2
extern float  Xd,Yd,r2,r4,Xu,Yu;
extern double Z_Range_Data[16][Y_SIZE+1],X_Range_Data[16][Y_SIZE+1],Y_Range_Data[16][Y_SIZE+1];

extern int sockflag;

//平面パラメータ
extern float dis_A,dis_B,dis_C ; 
extern double height,pan,tilt_1,tilt ;
//座標変換
extern double Move_Z_Range_Data[16][Y_SIZE+1],Move_X_Range_Data[16][Y_SIZE+1],Move_Y_Range_Data[16][Y_SIZE+1];

//実距離画像の平面描画用
extern float X_Range_MAX;
extern float X_Range_min;
extern float Y_Range_MAX;
extern float Y_Range_min;

//-------------------------------------OpenGL-------------------------------------------

#define gl_divi_st 5.0
#define gl_divi_r 5.0
#define ROTATE_STEP     50    // マウス移動量とテクスチャ回転角の程度
#define ZOOM_RATE       3      // マウスドラッグ時のズームの程度

extern char *GL_window_name[];

extern int window_width;         // ウインドウ幅
extern int window_height;        // ウインドウ高さ

//マウス制御用
extern int ox, oy;     // マウス座標
extern double lx, ly, lz;    // テクスチャの回転角（みたいなもの）

extern GLdouble vertex[][3] ;

extern int edge[][2] ;

//フォント
extern void *font1 ;
extern void *font2 ;
extern void DrawString(const char *str,void *font,float x,float y,float z);
extern void ColoredRange(float Z);
//void *font = GLUT_STROKE_ROMAN;
extern void *font ;

//計測
void idle();
//座標軸の名前描画
void DrawString3D(const char *str,void *font,float Width);
//いろいろ描画
void display_Re(void);
void display_Di(void);

void display_Di_2(void);


//座標軸の数字描画
void DrawString(const char *str,void *font,float x,float y,float z);
// ウインドウリサイズのコールバック
void resize(int w, int h);
// マウス移動（左ドラッグ）のコールバック
void left_motionFunc(int x, int y) ;
// マウス移動（右ドラッグ）のコールバック
void right_motionFunc(int x, int y) ;
// クリック時のコールバック
void mouseFunc(int button, int state, int x, int y) ;
// キーボード入力時のコールバック
void keyboard(unsigned char key, int x, int y);