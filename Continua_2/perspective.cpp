#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

/// Global variables
int threshold_value = 0;
int const max_value = 255;
int const max_BINARY_value = 255;
Mat src, dst, src_copy, finalOutput, map_x, map_y;
int n_sq=2,max_n=20;

vector<vector<Point> > contours;
vector<Point> outerMostContour, lineArriba, lineAbajo;
vector<Point> cortarTL, cortarTR, cortarBL, cortarBR;
vector<Vec4i> hierarchy;

double topLength, bottomLength;
int lineArribaCentral=0,lineAbajoMiddle=0;
Point table[2][151][151];
vector<int> compresionParametros;

int outputSizeW,outputSizeH,fullSizeH,fullSizeW;

void TransforamcionPerspectiva(int pos)
{
  Mat input = src.clone();
	for(int j=1;j<=n_sq;j++){
		for(int i=1;i<=n_sq;i++){
			//coordenadas
			Point2f inputQuad[4];
			//coordenadas output
			Point2f outputQuad[4];
			// Mat
			Mat lambda( 2, 4, CV_32FC1 );
			lambda = Mat::zeros(outputSizeH , outputSizeW, input.type() );
			//Imagen resultante
			Mat output;

			printf("Progreso: %.1f % \n",((float)(j-1)/n_sq*50+(float)(i-1)/n_sq/n_sq*50)+50*pos);
			// 4 puntos que fueron seleccionados de un cuadrilatero del input
			// Los puntos son los datos de una caja usada como input
			inputQuad[0] = Point2f( table[pos][j-1][i-1].x	,	table[pos][j-1][i-1].y );
			inputQuad[1] = Point2f( table[pos][j-1][i].x	,	table[pos][j-1][i].y );
			inputQuad[2] = Point2f( table[pos][j][i].x		,	table[pos][j][i].y );
			inputQuad[3] = Point2f( table[pos][j][i-1].x	,	table[pos][j][i-1].y );

			//Los puntos donde el mapping es hecho
			outputQuad[0] = Point2f( 0,0 );
			outputQuad[1] = Point2f( outputSizeW-1,0);
			outputQuad[2] = Point2f( outputSizeW-1,outputSizeH-1);
			outputQuad[3] = Point2f( 0,outputSizeH-1  );

			//La transformacion de perspectiva
			lambda = getPerspectiveTransform( inputQuad, outputQuad );
			Mat inv_lambda(lambda.inv());

			double array_lamb[3][3];
			for(int y=0;y<3;y++){
				for(int x=0;x<3;x++){
					array_lamb[y][x]=inv_lambda.at<double>(y,x);
				}
			}

			for(int y=0;y<outputSizeH;y++){
				for(int x=0;x<outputSizeW;x++){
					float v_x=(float)( x*array_lamb[0][0]	+	y*array_lamb[0][1]	+	array_lamb[0][2]);
					float v_y=(float)( x*array_lamb[1][0]	+	y*array_lamb[1][1]	+	array_lamb[1][2]);
					float v_z=(float)( x*array_lamb[2][0]	+	y*array_lamb[2][1]	+	array_lamb[2][2]);
					map_x.at<float>(outputSizeH*(j-1)+y	,	outputSizeW*(i-1)+outputSizeW*(pos*(n_sq))+x)	= v_x/v_z;
					map_y.at<float>(outputSizeH*(j-1)+y	,	outputSizeW*(i-1)+outputSizeW*(pos*(n_sq))+x)	= v_y/v_z;
				}
			}
		}
	}
	if(pos==1)
	printf("Fin\n");
}

int main()
{
	src = imread("dog.jpg", 1 );

	namedWindow( "Dog", WINDOW_NORMAL );
	imshow("Dog", src );
	//destroyAllWindows();
	// Set the output image size
	outputSizeW = topLength/n_sq/2;
	outputSizeH = topLength/n_sq/2*1.5;
	fullSizeH=outputSizeH*(n_sq);
	fullSizeW=outputSizeW*(n_sq);
	finalOutput = Mat::zeros(fullSizeH , fullSizeW*2, src.type() );
	map_x = Mat::zeros(fullSizeH , fullSizeW*2, CV_32FC1 );
	map_y = Mat::zeros(fullSizeH , fullSizeW*2, CV_32FC1 );
	TransforamcionPerspectiva(0);
	TransforamcionPerspectiva(1);
	remap(src, finalOutput, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0));

	namedWindow( "Perspectiva", WINDOW_NORMAL);
	imshow("Perspectiva", finalOutput );
	resizeWindow("Perspectiva", fullSizeW, fullSizeH/2);
}
