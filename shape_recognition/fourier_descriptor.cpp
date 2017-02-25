#include "foutier_descriptor.h"


vector<float> fourierDescriptor(vector<Point> contour, int vectorLength) {

	//把边界坐标转换为复数
	vector<Complex<float>> vectorComplex;
	int contourLength = contour.size();
	vectorComplex.reserve(contourLength);
	for (int i = 0; i < contourLength; i++) {
		Complex<float> pointComplex(contour[i].x, contour[i].y);
		vectorComplex.push_back(pointComplex);
	}

	//vector<Complex<float>> 作 dft 运算
	dft(vectorComplex, vectorComplex);

	//合并正负频率低频幅度谱为一个特征向量,去除直流分量,去除归一化参考量
	float halfLength = (float)vectorLength / 2;
	vector<float> featureVector;
	featureVector.reserve(vectorLength);

	//计算幅度谱,进行归一化
	float norm1 = abs(vectorComplex[contourLength - 1]);
	float norm2 = abs(vectorComplex[1]);
	if (norm2 > norm1) {
		norm1 = norm2;
		reverse(vectorComplex.begin()+1, vectorComplex.end());
	}
	for (int i = contourLength - floor(halfLength) - 1; i < contourLength - 1; i++) {
		featureVector.push_back(abs(vectorComplex[i]) / norm1);
	}
	for (int i = 1; i < ceil(halfLength) + 1; i++) {
		featureVector.push_back(abs(vectorComplex[i]) / norm1);
	}

	return featureVector;
}
void fourierDescriptor(vector<vector<Point>> contours, int vectorLength,Mat &inputs) {
	unsigned long shapeAllNum = contours.size();
	inputs=Mat(shapeAllNum, vectorLength, CV_32FC1);
	for (unsigned int i = 0; i < shapeAllNum; i++) {
		//cout  << contours[i].size() << ": \t" << endl;
		vector<float> input;
		input = fourierDescriptor(contours[i], vectorLength);
		for (int j = 0; j < vectorLength; j++) {
			inputs.at<float>(i, j) = input[j];
			//cout << setprecision(4) << fixed << input[j] << " ";
		}
		//cout << endl;
	}
}

void addNoiseToContour(vector<Point> &contour, unsigned int noiseStrength,unsigned int seed) {
	srand(seed);
	for (unsigned int i = 0; i < contour.size(); i++) {
		contour[i].x = contour[i].x + (rand()/ double(RAND_MAX)-0.5)*2*noiseStrength;
		contour[i].y = contour[i].y + (rand()/ double(RAND_MAX)-0.5)*2*noiseStrength;
	}
}
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseStrength) {
	srand(clock());
	for (unsigned int i = 0; i < contours.size(); i++) {
		addNoiseToContour(contours[i], noiseStrength,rand());
	}
}
void addNoiseToContour(vector<vector<Point>> &contours, unsigned int noiseMin, unsigned int noiseMax) {
	srand(clock());
	unsigned int noiseStrength;
	for (unsigned int i = 0; i < contours.size(); i++) {
		noiseStrength = rand() / double(RAND_MAX)*(noiseMax - noiseMin) + noiseMin;
		addNoiseToContour(contours[i], noiseStrength,rand());
	}
}