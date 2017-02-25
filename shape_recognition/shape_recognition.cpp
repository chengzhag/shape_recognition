#include "shape_recognition.h"
#include "ui_mainwindow.h"

//分类参数定义
const int vectorLength = 20; //特征向量长度
//const String rootDir("E:\\项目\\2016 P2P\\基于机器学习的基本图形识别\\opencv\\shape_recognition\\shape_revognition_class\\shape_recognition");
const String rootDir(".");
const String classifierFolder("classifier");//分类器文件夹
const String classifierFile("ann.xml");
const String classifierDir = fullfile(fullfile(rootDir, classifierFolder), classifierFile);
const String tffFile("simhei.ttf");
const String tffDir = fullfile(rootDir, tffFile);
const string windowName("叠加标签和轮廓");

//训练参数定义
const String sampleFolder("sample"); //图像样本输入文件夹
const String vectorFolder("vector"); //特征向量输出文件夹
const String vectorFile("sample.xml");
//const String sampleDir = fullfile("E:\\项目\\2016 P2P\\基于机器学习的基本图形识别\\ \
//	opencv\\shape_recognition\\shape_revognition_class\\shape_recognition", sampleFolder);
const String sampleDir = fullfile(rootDir, sampleFolder);
const String vectorDir = fullfile(fullfile(rootDir, vectorFolder), vectorFile);
//命令行预定输出
const char *errorNoImage = "\n图片不存在！\n";
const char *hintCorrectClass = "\n单击选择高亮轮廓以纠错！\n";
const char *errorNoXML = "xml文件不存在，请检查目录或重置神经网络和样本！\n";





void onMouse(int event, int x, int y, int flags, void *param) {
    OnMouseParams *onMouseParams = (OnMouseParams*)param;
    if (event == CV_EVENT_MOUSEMOVE) {
        onMouseParams->mousePos.x = x;
        onMouseParams->mousePos.y = y;
    }
    else if (event == CV_EVENT_LBUTTONDOWN) {
        onMouseParams->lButtonDown = true;
    }
}


void ShapeRecognition::highLightShape(Mat &im) {
    int counterClickedindex = findCounterHighlighted(onMouseParams.mousePos, currentContours);
    if (counterClickedindex >= 0) {
		categoryIndexHighlighted = currentCategoryIndex[counterClickedindex];
		counterHighlighted = currentContours[counterClickedindex];
        drawContour(im, counterHighlighted, Scalar(0, 255, 255));
        Point centroid = contourCentroid(counterHighlighted);
        //putLabel(im, centroid, net.categories, categoryIndex[counterClickedindex], Scalar(255, 0, 0), 0.8, 2);
        putChineseLabel(im, centroid, net.categories, currentCategoryIndex[counterClickedindex], chinese,25, Scalar(255, 0, 0));
	}
}


void ShapeRecognition::preProcess(Mat src, Mat &dst) {
    //进行二值化、边界提取操作
    Mat imGray;
    if (src.channels() == 3) {
        cvtColor(src, imGray, CV_RGB2GRAY);
    }
    else {
        imGray = src;
    }
    switch (preProcessingMethod) {
    case PRE_PROCESSING_OTSU: {
        //OTSU算法
        threshold(imGray, dst, 0, 255, CV_THRESH_OTSU);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        morphologyEx(dst, dst, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        break;
    }
    case PRE_PROCESSING_ADAPTIED_THRESHOLD: {
        //或自适应局部二值化
        //blur(imGray, imGray, Size(3, 3));
        adaptiveThreshold(imGray, dst, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 5, 10);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
        morphologyEx(dst, dst, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
        break;
    }
    case PRE_PROCESSING_CANNY: {
        //或边缘检测
        Canny(imGray, dst, 50, 100, 3);
        threshold(dst, dst, 128, 255, CV_THRESH_BINARY_INV);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(13, 13)));
        morphologyEx(dst, dst, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        morphologyEx(dst, dst, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
        break;
    }
    default: {
        cout << QString::fromLocal8Bit("无此预处理方法！\n");
		logFlush();
        break;
    }
    }
}


void ShapeRecognition::shapeRecognitionFlow(Mat &im, bool doStatistics) {
    //预处理
    Mat imBin;
    preProcess(im, imBin);

    //获取轮廓
    findContours(imBin, currentContours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    //删除包围面积小的轮廓
    deleteSmallContour(currentContours, im.rows*im.cols*smallShapeThreshold);

    //绘制轮廓
    drawContour(im, currentContours);

    //对边界提取傅里叶描述子
    Mat inputs;
    fourierDescriptor(currentContours, vectorLength, inputs);

    //送入分类器分类
    Mat outputs;
    net.predict(inputs, outputs);

    //转换输出得下标
	currentCategoryIndex = vec2ind(outputs);

    //叠加labels
    vector<Point> centroids = contourCentroid(currentContours);
    //putLabel(im, centroids, net.categories, index);
    putChineseLabel(im, centroids, net.categories, currentCategoryIndex, chinese);

    //统计数目
    if (doStatistics) {
        shapeStatic();
    }
}

void ShapeRecognition::afterShapeClicked() {
	categoryIndexClicked = categoryIndexHighlighted;
	counterClicked = counterHighlighted;
	cout << QString::fromLocal8Bit("\n请设置纠错参数\n");
	logFlush();

	setComboBoxClassify();
	ui->comboBoxCategory->setCurrentIndex(categoryIndexClicked);
}

void ShapeRecognition::setComboBoxClassify(){
	//设置下拉菜单
	int numComboBoxCategory = ui->comboBoxCategory->count();
	for (int i = 0; i < numComboBoxCategory; i++) {
		ui->comboBoxCategory->removeItem(0);
	}
	vector<string> categories = net.categories;
	unsigned int numCategories = categories.size();
	for (unsigned int i = 0; i < numCategories; i++) {
		ui->comboBoxCategory->addItem(QString::fromLocal8Bit(categories[i].c_str()));
	}
	ui->comboBoxCategory->setCurrentIndex(numCategories-1);
}

//public
ShapeRecognition::ShapeRecognition(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),
	cameraID(0), preProcessingMethod(0), smallShapeThreshold(0.005), 
	chinese(tffDir), cout(&LogTemp, QIODevice::WriteOnly){

    ui->setupUi(this);


    if (exist(classifierDir) && exist(vectorDir)) {
        net.loadNet(classifierDir);
        net.loadSample(vectorDir);
    }
    else {
        cout << QString::fromLocal8Bit(errorNoXML);
		logFlush();
    }

    cout << QString::fromLocal8Bit("基本形状识别——章程 2015010912010\n");
	logFlush();

	//从神经网络文件读取信息
	setComboBoxClassify();
	ui->spinBoxNumLayers->setValue(net.numLayers);
	ui->spinBoxHiddenLayerSize->setValue(net.hiddenLayerSize);

    //形状识别
    QObject::connect(ui->pushButtonImSelect, SIGNAL(clicked()), this, SLOT(selectIm()));
    QObject::connect(ui->pushButtonCameraIn, SIGNAL(clicked()), this, SLOT(openCamera()));
    QObject::connect(ui->spinBoxCameraID, SIGNAL(valueChanged(int)), this, SLOT(setCameraID(int)));
    QObject::connect(ui->horizontalSliderAreaThreshold, SIGNAL(sliderMoved(int)), this, 
		SLOT(setSmallShapeThreshold(int)));
    QObject::connect(ui->comboBoxPreProcessingMethod, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setPreProcessingMethod(int)));
    //重置神经网络和样本
    QObject::connect(ui->spinBoxNumLayers, SIGNAL(valueChanged(int)), this, SLOT(setNumLayers(int)));
    QObject::connect(ui->spinBoxHiddenLayerSize, SIGNAL(valueChanged(int)), this, SLOT(setHiddenLayerSize(int)));
    QObject::connect(ui->pushButtonResetSampleNet, SIGNAL(clicked()), this, SLOT(trainFromIm()));
    //点击图形纠错
	QObject::connect(ui->pushButtonAddClassify, SIGNAL(clicked()), this, SLOT(addCategory()));
	QObject::connect(ui->pushButtonStartFineTuning, SIGNAL(clicked()), this, SLOT(fineTuneNet2GroundTruth()));
	//保存或重载神经网络和样本
	QObject::connect(ui->pushButtonSaveNetAndSample, SIGNAL(clicked()), this, SLOT(saveNetAndSample()));
	QObject::connect(ui->pushButtonLoadNetAndSample, SIGNAL(clicked()), this, SLOT(loadNetAndSample()));
};


ShapeRecognition::~ShapeRecognition()
{
    delete ui;
	destroyAllWindows();
}

void ShapeRecognition::selectIm(){
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
        tr("选择图像"),
        "",
        tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        openIm(filename.toLocal8Bit().toStdString());
    }
}

void ShapeRecognition::hintSaveOrReload(){
	setComboBoxClassify();
	cout << QString::fromLocal8Bit("\n神经网络和样本已更改，可选择保存或重置\n");
	logFlush();
}

void ShapeRecognition::shapeStatic() {
	unsigned int categoriesNum = net.categories.size();

	cout << QString::fromLocal8Bit("\n统计结果：\n");
	unsigned int *shapeStatistics = new unsigned int[categoriesNum];
	memset(shapeStatistics, 0, categoriesNum * sizeof(unsigned int));
	for (unsigned int i = 0; i < currentCategoryIndex.size(); i++) {
		shapeStatistics[currentCategoryIndex[i]]++;
	}
	for (unsigned int i = 0; i < categoriesNum; i++) {
		if (shapeStatistics[i]) {
			cout << QString::fromLocal8Bit(net.categories[i].c_str()) << ": " << shapeStatistics[i] << endl;
		}
	}
	logFlush();
}

void ShapeRecognition::logFlush() {
	ui->textBrowserLog->setText(LogTemp);
	ui->textBrowserLog->moveCursor(QTextCursor::End);
}

void ShapeRecognition::openIm(string imageNam) {
	ui->groupBoxResetSampleNet->setEnabled(false);
    im = imread(imageNam); //默认转换为RGB彩色图

    if (im.empty()) {
        cout << QString::fromLocal8Bit(errorNoImage);
		logFlush();
        return;
    }
    net.loadNet(classifierDir);
    im.copyTo(imTemp);
    shapeRecognitionFlow(imTemp,true);
    imshow(windowName, imTemp);
    void *param = (void*)&onMouseParams;
    setMouseCallback(windowName, onMouse, param);
    cout << QString::fromLocal8Bit(hintCorrectClass);
	logFlush();
    while (1) {
        im.copyTo(imTemp);
        shapeRecognitionFlow(imTemp, false);
        highLightShape(imTemp);
        imshow(windowName, imTemp);
        if (onMouseParams.lButtonDown) {
            if (counterHighlighted.size() > vectorLength) {
                vector<float> input = fourierDescriptor(counterHighlighted, vectorLength);
				afterShapeClicked();
            }
            onMouseParams.lButtonDown = false;
        }
        keyPressed = waitKey(30);
        //检测按键，按下esc结束
        if (keyPressed == 27) {
            destroyAllWindows();
            break;
        }
    }
	ui->groupBoxResetSampleNet->setEnabled(true);
}
void ShapeRecognition::openCamera() {
	ui->groupBoxResetSampleNet->setEnabled(false);
    net.loadNet(classifierDir);
    VideoCapture capture(cameraID);
    namedWindow(windowName);
    void *param = (void*)&onMouseParams;
    setMouseCallback(windowName, onMouse, param);
    cout << QString::fromLocal8Bit(hintCorrectClass);
	logFlush();
    while (1) {
        capture >> im;
        im.copyTo(imTemp);
        shapeRecognitionFlow(imTemp, false);
        highLightShape(imTemp);
        imshow(windowName, imTemp);
        if (onMouseParams.lButtonDown) {
            if (counterHighlighted.size() > vectorLength) {
				afterShapeClicked();
            }
            onMouseParams.lButtonDown = false;
        }
        keyPressed = waitKey(30);
        //检测按键，按下esc结束
        if (keyPressed == 27) {
            destroyAllWindows();
            break;
        }
    }
	ui->groupBoxResetSampleNet->setEnabled(true);
}
void ShapeRecognition::setPreProcessingMethod(int index) {
    if (index < 0 || index>2) {
        preProcessingMethod = 0;
    }
    else {
        preProcessingMethod = index;
    }
}
void ShapeRecognition::setCameraID(int id) {
    cameraID = id;
}
void ShapeRecognition::setSmallShapeThreshold(int num) {
    smallShapeThreshold = (float)num/1000;
}
void ShapeRecognition::setNumLayers(int num){
    net.numLayers=num;
}
void ShapeRecognition::setHiddenLayerSize(int num){
    net.hiddenLayerSize=num;
}
void ShapeRecognition::trainFromIm() {
	//重置神经网络
    //net=MyANN_MLP(net.numLayers,net.hiddenLayerSize);
    //cout << "神经网络结构：" << net.net->getLayerSizes().t() << endl;

    //准备样本
    cout << QString::fromLocal8Bit("\n读取图片...") << endl;
	logFlush();
    tic();
    net.prepare(sampleDir, vectorLength);
    cout << QString::fromLocal8Bit("...用时：") << toc() << "s" << endl;
	logFlush();

    //训练神经网络
    net.train();

    //验证神经网络
    cout << QString::fromLocal8Bit("准确率：") << net.validate() * 100 << "%\n";
	logFlush();

	//提示保存
	hintSaveOrReload();
}

void ShapeRecognition::addCategory() {
	string category =ui->lineEditAddCategory->text().toLocal8Bit().toStdString();
	if (category.size() == 0) {
		return;
	}
	for (int i = 0; i < net.categories.size(); i++) {
		if (net.categories[i].compare(category)==0) {
			ui->comboBoxCategory->setCurrentIndex(i);
			cout << QString::fromLocal8Bit("已有")
				<< QString::fromLocal8Bit(category.c_str()) << "\n";
			logFlush();
			return;
		}
	}
	copyMakeBorder(net.targets.trainTargets, net.targets.trainTargets, 0, 0, 0, 1, BORDER_CONSTANT, 0);
	net.categories.push_back(category);
	setComboBoxClassify();
}

void ShapeRecognition::fineTuneNet() {
	int categoryIndex = ui->comboBoxCategory->currentIndex();
	unsigned long weight = ui->spinBoxWeight->value();
	unsigned int noiseStrength = ui->spinBoxNoiseStrength->value();

	vector<vector<Point>> contours;
	contours.reserve(weight);
	for (unsigned long i = 0; i < weight; i++) {
		contours.push_back(counterClicked);
	}
	if (noiseStrength != 0) {
		addNoiseToContour(contours, 0, noiseStrength);
	}
	//展示前weight<10个轮廓
	showContour(im, contours, windowName,10);

	Mat input;
	fourierDescriptor(contours, vectorLength, input);
	net.addSample(input, categoryIndex);
	//验证神经网络
	cout << QString::fromLocal8Bit("训练之前准确率：") << net.validate() * 100 << "%\n";
	logFlush();

	net.train();

	cout << QString::fromLocal8Bit("训练之后准确率：") << net.validate() * 100 << "%\n";
	logFlush();
}

void ShapeRecognition::fineTuneNet2GroundTruth() {
	int categoryIndex = ui->comboBoxCategory->currentIndex();
	int i = 0;
	while (1) {
		i++;
		cout << QString::fromLocal8Bit("\n第") << i << QString::fromLocal8Bit("次迭代：\n ");
		logFlush();
		fineTuneNet();

		//测试形状并显示出来
		//对边界提取傅里叶描述子
		Mat inputs;
		vector<vector<Point>> counters;
		counters.push_back(counterClicked);
		fourierDescriptor(counters, vectorLength, inputs);

		//送入分类器分类
		Mat outputs;
		net.predict(inputs, outputs);

		//转换输出得下标
		vector<unsigned int> index = vec2ind(outputs);

		if (index[0] == categoryIndex) {
			break;
		}
	}
	hintSaveOrReload();
	ui->comboBoxCategory->setCurrentIndex(categoryIndex);
}

void ShapeRecognition::saveNetAndSample() {
	net.saveNet(classifierDir);
	net.saveSample(vectorDir);
	cout << QString::fromLocal8Bit("...已保存\n");
	logFlush();
	setComboBoxClassify();
}

void ShapeRecognition::loadNetAndSample() {
	net.loadNet(classifierDir);
	net.loadSample(vectorDir);
	setComboBoxClassify();
	cout << QString::fromLocal8Bit("...已重载\n");
	logFlush();
	setComboBoxClassify();
}




