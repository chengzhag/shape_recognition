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
功能：判断某文件是否存在
参数：dir：路径
*/
bool exist(string dir);

/*
功能：显示进度
参数：i：当前循环
total：总共循环次数
times：显示次数
*/
void showProgress(long i, long total, int times = 100);

/*
功能：显示菜单
参数：menu：菜单
*/
void showMenu(vector<string> menu, bool showHint=false);

/*
功能：从命令行输入一个数字
参数：
*/
template<typename T>
void cinNum(T &num) {
	char temp[128];
	cin >> temp;
	num = (T)atof(temp);
}

/*
功能：细化
参数：src：源图像
dst：目标图像，可以与源图像相同
iterations：迭代次数，默认一次
*/
void thin(const Mat &src, Mat &dst, const int iterations = 1);

/*
功能：计算轮廓包围图形的质心
参数：contours：轮廓
*/
vector<Point> contourCentroid(vector<vector<Point>> contours);
Point contourCentroid(vector<Point> contour);

/*
功能：删除包围面积小的轮廓
参数：contours：轮廓
*/
void deleteSmallContour(vector<vector<Point>> &contours,unsigned long smallArea);

/*
功能：绘制轮廓
参数：im：图像
contours：轮廓
color：颜色
*/
void drawContour(Mat &im, vector<vector<Point>> contours, Scalar color = Scalar(0, 0, 255));
void drawContour(Mat &im, vector<Point> contours, Scalar color = Scalar(0, 0, 255));

/*
功能：展示轮廓
参数：im：图像
contours：轮廓
color：颜色
windowName:窗口名称
num:展示个数
*/
void showContour(Mat im, vector<vector<Point>> contours, string windowName, unsigned int num = 100, Scalar color = Scalar(0, 0, 255));

/*
功能：判断点击的轮廓
参数：contours：轮廓
mouse：点坐标
*/
int findCounterHighlighted(Point mousePos, vector<vector<Point>> contours);

/*
功能：居中叠加标签
参数：centroids：中点
categories：标签名称列表
index：标签下标
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
功能：形状识别分类器
构造函数初始化所有成员变量为默认值
//样本分割函数将样本分为三类： Training, Validation, Testing
预测函数输入inputs和targets，输出原始输出
验证函数输入inputs和targets，输出准确率
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
