#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <io.h>
#include <fstream>

#include "foutier_descriptor.h"
#include "matlab_fcn.h"
#include "CvxText.h"  

using namespace std;
using namespace cv;
using namespace ml;

/*
���ܣ��ж�ĳ�ļ��Ƿ����
������dir��·��
*/
bool exist(string dir);

/*
���ܣ���ʾ����
������i����ǰѭ��
total���ܹ�ѭ������
times����ʾ����
*/
void showProgress(long i, long total, int times = 100);

/*
���ܣ���ʾ�˵�
������menu���˵�
*/
void showMenu(vector<string> menu, bool showHint=false);

/*
���ܣ�������������һ������
������
*/
template<typename T>
void cinNum(T &num) {
	char temp[128];
	cin >> temp;
	num = (T)atof(temp);
}

/*
���ܣ�ϸ��
������src��Դͼ��
dst��Ŀ��ͼ�񣬿�����Դͼ����ͬ
iterations������������Ĭ��һ��
*/
void thin(const Mat &src, Mat &dst, const int iterations = 1);

/*
���ܣ�����������Χͼ�ε�����
������contours������
*/
vector<Point> contourCentroid(vector<vector<Point>> contours);
Point contourCentroid(vector<Point> contour);

/*
���ܣ�ɾ����Χ���С������
������contours������
*/
void deleteSmallContour(vector<vector<Point>> &contours,unsigned long smallArea);

/*
���ܣ���������
������im��ͼ��
contours������
color����ɫ
*/
void drawContour(Mat &im, vector<vector<Point>> contours, Scalar color = Scalar(0, 0, 255));
void drawContour(Mat &im, vector<Point> contours, Scalar color = Scalar(0, 0, 255));

/*
���ܣ�չʾ����
������im��ͼ��
contours������
color����ɫ
windowName:��������
num:չʾ����
*/
void showContour(Mat im, vector<vector<Point>> contours, string windowName, unsigned int num = 100, Scalar color = Scalar(0, 0, 255));

/*
���ܣ��жϵ��������
������contours������
mouse��������
*/
int findCounterHighlighted(Point mousePos, vector<vector<Point>> contours);

/*
���ܣ����е��ӱ�ǩ
������centroids���е�
categories����ǩ�����б�
index����ǩ�±�
*/
void putLabel(Mat &im, vector<Point> centroids, vector<string> categories, vector<unsigned int> index, Scalar color = Scalar(0, 0, 0),\
	double fontScale = 0.5, int thickness = 1, int fontFace = FONT_HERSHEY_SIMPLEX);
void putLabel(Mat &im, Point centroids, vector<string> categories, unsigned int index, Scalar color = Scalar(0, 0, 0), \
	double fontScale = 0.5, int thickness = 1, int fontFace = FONT_HERSHEY_SIMPLEX);
void putChineseLabel(Mat &im, Point centroids, vector<string> categories, unsigned int index, CvxText &fft, \
	double fontScale = 15, Scalar color = Scalar(0, 0, 0));
void putChineseLabel(Mat &im, vector<Point> centroids, vector<string> categories, vector<unsigned int> index, CvxText &fft, \
	double fontScale = 15, Scalar color = Scalar(0, 0, 0));



/*
���ܣ���״ʶ�������
���캯����ʼ�����г�Ա����ΪĬ��ֵ
//�����ָ����������Ϊ���ࣺ Training, Validation, Testing
Ԥ�⺯������inputs��targets�����ԭʼ���
��֤��������inputs��targets�����׼ȷ��
*/
enum {
	DO_SAVE_SAMPLE = 0,
	DO_SAVE_NET = 1,
	DO_SAVE_SAMPLE_AND_NET = 2,
	DO_SAVE_ALL_TOGETHER = 3
};
class MyANN_MLP {
public:
	Ptr<ANN_MLP> net;
	unsigned int numLayers;
	unsigned int numInputs;
	unsigned int numOutputs;
	unsigned int hiddenLayerSize;
	vector<string> categories;
	Mat trainInputs;
	Mat trainTargets;
	//struct DivideParam {
	//	float trainRatio;
	//	//float valRatio;
	//	float testRatio;
	//}divideParam;
	struct Inputs {
		Mat trainInputs;
		//Mat valInputs;
		//Mat testInputs;
	}inputs;
	struct Targets {
		Mat trainTargets;
		//Mat valInputs;
		//Mat testInputs;
	}targets;
	struct Trainparam {
		unsigned int epochs;
		float goal;
		//unsigned int show;
	}trainparam;

	MyANN_MLP(int hiddenLayerNum, int hiddenLayerNodeNum);
	MyANN_MLP() :MyANN_MLP(1, 9) {};
	MyANN_MLP(string dir);

	void prepare(String sampleDir, Mat &inputsReturn, Mat &targetsReturn, unsigned int vectorLength);
	void prepare(String sampleDir, unsigned int vectorLength);

	void train(Mat inputs, Mat targets);
	void train();
	void train(string dir);

	void predict(InputArray inputs, OutputArray outputs);

	float validate(Mat inputs, Mat targets);
	float validate();

	void saveNet(string dir);
	void saveSample(string dir);
	void askIfSaveChange(string classifierDir, string vectorDir, int flag = DO_SAVE_ALL_TOGETHER);

	void loadNet(string dir);
	void loadSample(string dir);

	void addSample(vector<float> input, unsigned int label, unsigned long weight=1);
	void addSample(Mat input, unsigned int label);
	void addCategory(vector<float> input, string category, unsigned long weight=1);
	void addCategory(Mat input, string category);
	bool askAddAndTrain(Mat im, vector<Point> counterSelected, int vectorLength, const string windowName);
};
