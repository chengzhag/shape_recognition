#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <windows.h>

#include "foutier_descriptor.h"
#include "matlab_fcn.h"
#include "my_fcn.h"
#include "CvxText.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>

using namespace std;
using namespace cv;
using namespace ml;
namespace Ui {
class MainWindow;
}

class OnMouseParams {
public:
	Point mousePos;
	bool lButtonDown;
	OnMouseParams() :mousePos(-1, -1), lButtonDown(false) {};
};
void onMouse(int event, int x, int y, int flags, void *param);


enum {
	PRE_PROCESSING_OTSU = 0,
	PRE_PROCESSING_ADAPTIED_THRESHOLD = 1,
	PRE_PROCESSING_CANNY = 2
};


class ShapeRecognition:public QMainWindow {
    Q_OBJECT

private:
    //变量
    CvxText chinese;
	MyANN_MLP net;
	Mat im, imTemp;
	vector<vector<Point>> currentContours;
	vector<Point> counterHighlighted;
	vector<Point> counterClicked;
	unsigned int categoryIndexHighlighted;
	unsigned int categoryIndexClicked;
	vector<unsigned int> currentCategoryIndex;
	int cameraID;
	int preProcessingMethod;
	char keyPressed;
	float smallShapeThreshold;
	OnMouseParams onMouseParams;
	QTextStream cout;
	

    //函数
	void hintSaveOrReload();

	void shapeStatic();

    void openIm(string imageNam);

	void highLightShape(Mat & im);

	void preProcess(Mat src, Mat & dst);

	void shapeRecognitionFlow(Mat & im, bool doStatistics);

	void afterShapeClicked();

	void setComboBoxClassify();

public:
	QString LogTemp;

	Ui::MainWindow *ui;

	void logFlush();

    explicit ShapeRecognition(QWidget *parent = 0);

    ~ShapeRecognition();

public slots:
    void selectIm();

	void openCamera();

	void setPreProcessingMethod(int index);

	void setCameraID(int id);

    void setSmallShapeThreshold(int num);

    void setNumLayers(int num);

    void setHiddenLayerSize(int num);

    void trainFromIm();

	void addCategory();

	void fineTuneNet();

	void fineTuneNet2GroundTruth();

	void saveNetAndSample();

	void loadNetAndSample();
};

