#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <io.h>
#include <fstream>
#include <time.h>

using namespace std;
using namespace cv;

/*
功能：合并路径与文件名
参数：a：文件夹路径
b：文件名
*/
String fullfile(String a, String b);

/*
功能：计时
*/
extern clock_t  ticTime;
void tic();
float toc();

/*
功能：储存主文件夹中所有子文件夹的图片路径，并以子文件夹名作为标签名称
参数：location：主文件夹路径
*/
class ImageDataStore {
public:
	ImageDataStore(String location);
	Mat readImage(unsigned long i, int flags = IMREAD_COLOR);
	vector<string> categories;
	vector<unsigned int> labels;
	vector<string> files;
};

/*
功能：将神经网络输出的向量转换为下标
参数：x：神经网络输出的向量或Mat矩阵，每行一组输出
*/
vector<unsigned int> vec2ind(Mat x);







