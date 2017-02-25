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
功能：计算轮廓的傅里叶描述子
参数：contours：轮廓坐标
vectorLength：描述子长度
*/
vector<float> fourierDescriptor(vector<Point> contour, int vectorLength);
void fourierDescriptor(vector<vector<Point>> contours, int vectorLength, Mat &inputs);

/*
功能：向轮廓添加噪声
参数：contours：轮廓坐标
noiseStrength：噪音强度
*/
void addNoiseToContour(vector<Point> &contour, unsigned int noiseStrength, unsigned int seed = clock());
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseStrength);
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseMin, unsigned int noiseMax);
