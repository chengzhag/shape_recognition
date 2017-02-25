#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
using namespace cv;

/*
���ܣ����������ĸ���Ҷ������
������contours����������
vectorLength�������ӳ���
*/
vector<float> fourierDescriptor(vector<Point> contour, int vectorLength);
void fourierDescriptor(vector<vector<Point>> contours, int vectorLength, Mat &inputs);

/*
���ܣ��������������
������contours����������
noiseStrength������ǿ��
*/
void addNoiseToContour(vector<Point> &contour, unsigned int noiseStrength, unsigned int seed = clock());
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseStrength);
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseMin, unsigned int noiseMax);
