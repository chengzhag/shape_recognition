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
���ܣ��ϲ�·�����ļ���
������a���ļ���·��
b���ļ���
*/
String fullfile(String a, String b);

/*
���ܣ���ʱ
*/
extern clock_t  ticTime;
void tic();
float toc();

/*
���ܣ��������ļ������������ļ��е�ͼƬ·�����������ļ�������Ϊ��ǩ����
������location�����ļ���·��
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
���ܣ������������������ת��Ϊ�±�
������x�������������������Mat����ÿ��һ�����
*/
vector<unsigned int> vec2ind(Mat x);







