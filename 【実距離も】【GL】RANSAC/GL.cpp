#include "stdafx.h" // Visual Studioのプリコンパイルヘッダを使うため。他の環境ではなくてもよい。
#include "extern.h"

#define X_among 1.2
#define Y_among 15.0
#define Y_move 100.0
double R = 0.0,		//距離画像用Rチャンネル
	   G = 0.0,		//距離画像用Gチャンネル
	   B = 0.0;		//距離画像用Bチャンネル

void DrawString3D(const char *str,void *font,float Width)
{
	glPushAttrib(GL_LINE_BIT);
	glLineWidth(Width);
	while(*str){
		glutStrokeCharacter(font, *str);
		glutSolidCube(1.0);
		++str;
	}
	glPopAttrib();
}


void display_Di(void)
{
  // 再描画に際する初期化
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLoadIdentity();

  // 視点（ビューポイント）変更
  //gluLookAt(60.0, 55.0, lz, -2.0, 0.0, -2.0, 0.0, 0.0, 1.0);
  gluLookAt(110.0, 15.0,  15.0, 15.0, 15.0, 15.0, 0.0, 0.0, 1.0);

  //オブジェクトを回転させる
  //glPushMatrix();
  //glTranslated( -3*gl_divi_st, -3*gl_divi_st, -3*gl_divi_r );
  glRotated(lx, 0.0, 1.0, 0.0);
  glRotated(ly, 1.0, 0.0, 0.0);
  //glTranslated( 3*gl_divi_st, 3*gl_divi_st, 3*gl_divi_r );
  //glPopMatrix();

  //線の描画(グリッドの描画)
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_LINES);

  for (int i = 0; i <= 64; ++i) {
    glVertex3dv(vertex[edge[i][0]]);
    glVertex3dv(vertex[edge[i][1]]);
  }

  glEnd();


//点を描画(各相対視差の描画)
  glPointSize(5);
  glBegin(GL_POINTS);

  for (int label=1; label<=label_max; label++)
	for (int v=0; v<=Y_SIZE-1; v++)
	{
		if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		{
            ColoredRange(Z_Range_Data[label][v]);
			glColor3d(R, G, B);

			glVertex3d( 6*gl_divi_r  - Z_Range_Data[label][v]*1/100*gl_divi_r ,//100～600用
			          3*gl_divi_st + X_Range_Data[label][v]*1/25*gl_divi_st,
					  3*gl_divi_st + Y_Range_Data[label][v]*1/25*gl_divi_st );



	  }//end if 
     }//end for 
  
  glEnd();

 

  


  //フォントを描画
  //①座標軸名前の描画
  //Y
  glColor3d(0,0,0);
  glPushMatrix();
  glTranslated(6*gl_divi_st, -4.0, 2.5*gl_divi_r + 0.0); 
  glRotated(-90.0, 0.0, 1.0, 0.0);
  glRotated(180.0, 1.0, 0.0, 0.0);
  glRotated(50.0, 1.0, 0.0, 0.0);
  //glScaled(0.012, 0.012, 0.012);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("Y [mm]",font,3);
  glPopMatrix();

  //X
  glPushMatrix();
  glTranslated(6*gl_divi_st+ 6.0, 2.5*gl_divi_st, -2.0);
  glRotated(90.0, 0.0, 0.0, 1.0);
  glRotated(50.0, 1.0, 0.0, 0.0);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("X [mm]",font,3);
  glPopMatrix();

  //Z
  glPushMatrix();
  glTranslated(4*gl_divi_st, 6*gl_divi_st+ 6.0, 0.0);
  glRotated(180.0, 0.0, 0.0, 1.0);
  glRotated(30.0, 1.0, 0.0, 0.0);
  //glRotated(30.0, 0.0, 1.0, 0.0);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("Z [mm]",font,3);
  glPopMatrix();

  //②座標軸数値の描画
  glColor3d(0,0,0);
  //X軸
  //DrawString("s", font2,6*gl_divi_st + 4.0, 3*gl_divi_st, 0.0);
  DrawString("-75", font1,6*gl_divi_st + 3,  1.0, -1.0);
  DrawString("-50",font1,6*gl_divi_st + 3, 1*gl_divi_st, -1.0);
  DrawString("-25",font1,6*gl_divi_st + 3, 2*gl_divi_st, -1.0);
  DrawString("0",font1,6*gl_divi_st + 2.5, 3*gl_divi_st, -1.0);
  DrawString("25",font1,6*gl_divi_st + 2.5, 4*gl_divi_st, -1.0);
  DrawString("50",font1,6*gl_divi_st + 2.5, 5*gl_divi_st, -1.0);
  DrawString("75",font1,6*gl_divi_st + 2.5, 6*gl_divi_st, -1.0);

    // Z軸
  DrawString("600", font1, 0.0, 6*gl_divi_st + 1.0, 0.0);
  DrawString("500",font1,1*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);
  DrawString("400",font1,2*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);
  DrawString("300",font1,3*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);
  DrawString("200",font1,4*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);
  DrawString("100",font1,5*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);
  DrawString("0",font1,6*gl_divi_st, 6*gl_divi_st + 1.0, 0.0);


  // Y軸
  DrawString("-75", font1,6*gl_divi_st + 2, -2.0, 0*gl_divi_r);
  DrawString("-50", font1,6*gl_divi_st + 2, -2.0, 1*gl_divi_r);
  DrawString("-25", font1,6*gl_divi_st + 2, -2.0, 2*gl_divi_r);
  DrawString("0", font1,6*gl_divi_st + 2, -1.0, 3*gl_divi_r);
  DrawString("25", font1,6*gl_divi_st + 2, -1.0, 4*gl_divi_r);
  DrawString("50", font1,6*gl_divi_st + 2, -1.0, 5*gl_divi_r);
  DrawString("75", font1,6*gl_divi_st + 2, -1.0, 6*gl_divi_r);
  glutSwapBuffers();

}





void display_Di_2(void)
{
  // 再描画に際する初期化
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLoadIdentity();

  // 視点（ビューポイント）変更
  //gluLookAt(60.0, 55.0, lz, -2.0, 0.0, -2.0, 0.0, 0.0, 1.0);
  gluLookAt(15.0, 90.0,  15.0, 15.0, 15.0, 15.0, 0.0, 0.0, 1.0);
  //glOrtho(150.0,150.0,150.0,150.0,150.0,150.0) ;

  //オブジェクトを回転させる
  //glPushMatrix();
  glTranslated( 0.0*gl_divi_st, 0.0*gl_divi_st, 0.0*gl_divi_r );
  glRotated(lx, 0.0, 1.0, .0);
  glRotated(ly, 1.0, 0.0, 0.0);
  //glTranslated( 3*gl_divi_st, 3*gl_divi_st, 3*gl_divi_r );
  //glPopMatrix();

  //線の描画(グリッドの描画)
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_LINES);

  for (int i = 0; i <= 64; ++i) {
    glVertex3dv(vertex[edge[i][0]]);
    glVertex3dv(vertex[edge[i][1]]);
  }

  glEnd();


//点を描画(各相対視差の描画)
  glPointSize(5);
  glBegin(GL_POINTS);

  for (int label=1; label<=label_max; label++)
	for (int v=0; v<=Y_SIZE-1; v++)
	{
		if( (Base_zx[label][v] != 0.0) && (occ_point[label][v] == 0) ) 
		{
            ColoredRange(Z_Range_Data[label][v]);
			glColor3d(R, G, B);



		  glVertex3d( 6*gl_divi_r  - Z_Range_Data[label][v]*1/100*gl_divi_r ,//100～600用
			          3*gl_divi_st + X_Range_Data[label][v]*1/100*gl_divi_st,
					  3*gl_divi_st + Y_Range_Data[label][v]*1/100*gl_divi_st );

	  }//end if 
     }//end for 
  
  glEnd();

 

  


  //フォントを描画
  //①座標軸名前の描画
  //Y
  glColor3d(0,0,0);
  glPushMatrix();
  glTranslated(6*gl_divi_st+1.0 , 10.0, 1*gl_divi_r+8.0); 
  glRotated(-90.0, 0.0, 1.0, 0.0);
  glRotated(180.0, 1.0, 0.0, 0.0);
  glRotated(50.0, 1.0, 0.0, 0.0);
  //glScaled(0.012, 0.012, 0.012);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("Y [mm]",font,3);
  glPopMatrix();

  //X
  glPushMatrix();
  glTranslated(6*gl_divi_st+ 6.0, 2.5*gl_divi_st, 0.0);
  glRotated(90.0, 0.0, 0.0, 1.0);
  glRotated(50.0, 1.0, 0.0, 0.0);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("X [mm]",font,3);
  glPopMatrix();

  //Z
  glPushMatrix();
  glTranslated(4*gl_divi_st - 2.0, 6*gl_divi_st+ 6.0, -2.0);
  glRotated(180.0, 0.0, 0.0, 1.0);
  glRotated(30.0, 1.0, 0.0, 0.0);
  //glRotated(30.0, 0.0, 1.0, 0.0);
  glScaled(0.01, 0.01, 0.01);
  DrawString3D("Z [mm]",font,3);
  glPopMatrix();

  //②座標軸数値の描画
  glColor3d(0,0,0);
  //X軸
  //DrawString("s", font2,6*gl_divi_st + 4.0, 3*gl_divi_st, 0.0);
  DrawString("-75", font1,6*gl_divi_st + 3,  1.0, 0.0);
  DrawString("-50",font1,6*gl_divi_st + 3, 1*gl_divi_st, 0.0);
  DrawString("-25",font1,6*gl_divi_st + 3, 2*gl_divi_st, 0.0);
  DrawString("0",font1,6*gl_divi_st + 2.5, 3*gl_divi_st, 0.0);
  DrawString("25",font1,6*gl_divi_st + 2.5, 4*gl_divi_st, 0.0);
  DrawString("50",font1,6*gl_divi_st + 2.5, 5*gl_divi_st, 0.0);
  DrawString("75",font1,6*gl_divi_st + 2.5, 6*gl_divi_st, 0.0);


  //Z軸　0～600
  DrawString("600", font1, 0.0, 6*gl_divi_st + 1.0, -1.0);
  DrawString("500",font1,1*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);
  DrawString("400",font1,2*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);
  DrawString("300",font1,3*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);
  DrawString("200",font1,4*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);
  DrawString("100",font1,5*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);
  DrawString("0",font1,6*gl_divi_st, 6*gl_divi_st + 1.0, -1.0);

  // Y軸
  DrawString("-75", font1,6*gl_divi_st + 2, 3.0, 0*gl_divi_r);
  DrawString("-50", font1,6*gl_divi_st + 2, 3.0, 1*gl_divi_r);
  DrawString("-25", font1,6*gl_divi_st + 2, 3.0, 2*gl_divi_r);
  DrawString("0", font1,6*gl_divi_st + 2, -1.0, 3*gl_divi_r);
  DrawString("25", font1,6*gl_divi_st + 2, -1.0, 4*gl_divi_r);
  DrawString("50", font1,6*gl_divi_st + 2, -1.0, 5*gl_divi_r);
  DrawString("75", font1,6*gl_divi_st + 2, -1.0, 6*gl_divi_r);
  glutSwapBuffers();

}







//フォントの描画
void DrawString(const char *str,void *font,float x,float y,float z)
{
	glRasterPos3f(x,y,z);
	while(*str){
		glutBitmapCharacter(font, *str);
		++str;
	}	
}

// ウインドウリサイズのコールバック
void resize(int w, int h)
{
  glViewport(0, 0, w, h);
  //透視変換行列の設定       
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  ////投影変換
  //gluPerspective(35.0, (double)w / (double)h, 1.0, 1000.0);

    //投影変換
  gluPerspective(35.0, (double)w / (double)h, 1.0, 1000.0);
  //glOrtho(1000,1000,1000,1000,1,1000);


  //モデルビュー変換行列の設定       
  glMatrixMode(GL_MODELVIEW);

  /* スクリーン上の表示領域をビューポートの大きさに比例させる */
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);

}

// マウス移動（左ドラッグ）のコールバック
void left_motionFunc(int x, int y) 
{        
	lx = (1.0 - ((double)x*2 / window_width)) * ROTATE_STEP;    
	ly = (1.0 - ((double)y*2 / window_height)) * ROTATE_STEP;  
	//(1-(x*2/window_width)) = (window_width/2 - x) / (window_width/2)
	//printf("%f %f\n",lx, ly);
}

// マウス移動（右ドラッグ）のコールバック
void right_motionFunc(int x, int y) 
{        
	//右ドラッグにはズームを割り当てる     
	int dy = y - oy;  
	lz += (double)dy*ZOOM_RATE/window_width;
	//printf("aaaaaaaaaaaaaaaaaaaaaa\n");
}

// クリック時のコールバック
void mouseFunc(int button, int state, int x, int y) 
{        
	if (button == GLUT_LEFT_BUTTON) 
	{                                         
			glutMotionFunc(left_motionFunc);     
	}
	if (button == GLUT_RIGHT_BUTTON) 
	{                
		exit(0);
	}
}


void ColoredRange(float Z)
{
#define MAX_DISTANCE 800
#define MIN_DISTANCE 50

	double distance = 0.0;

	distance = (double)(((double)Z - MIN_DISTANCE)/(MAX_DISTANCE - MIN_DISTANCE));

	R = G = B = 1.0;

	if(distance >= 0.0 && distance < 0.25){
		B = 0.0;
		G = 4.0*distance;
	}
	else if (distance >= 0.25 && distance < 0.5){
		B = 0.0;
		R = 1.0 + 4.0*(0.25 - distance);
	}
	else if(distance >= 0.5 && distance < 0.75){
		B = 4.0*(distance - 0.5);
		R = 0.0;
	}
	else if(distance >= 0.75 && distance < 1.0){
		G = 1.0 + 4.0*(0.75 - distance);
		R = 0.0;
	}
	

}



//-------------------------------------------------------------------------
// キーボードに対応する関数
//-------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)

{

	switch (key) {

	case '\033':	// '\033' はESCのASCIIコード(Linuxでは"\"になる)
		exit(0);
		break;

	case 'q':	// '\033' はESCのASCIIコード(Linuxでは"\"になる)
		exit(0);
		break;

	default:
		break;
	}

}