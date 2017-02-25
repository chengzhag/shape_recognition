#include "shape_recognition.h"
#include "ui_mainwindow.h"

//�����������
const int vectorLength = 20; //������������
//const String rootDir("E:\\��Ŀ\\2016 P2P\\���ڻ���ѧϰ�Ļ���ͼ��ʶ��\\opencv\\shape_recognition\\shape_revognition_class\\shape_recognition");
const String rootDir(".");
const String classifierFolder("classifier");//�������ļ���
const String classifierFile("ann.xml");
const String classifierDir = fullfile(fullfile(rootDir, classifierFolder), classifierFile);
const String tffFile("simhei.ttf");
const String tffDir = fullfile(rootDir, tffFile);
const string windowName("���ӱ�ǩ������");

//ѵ����������
const String sampleFolder("sample"); //ͼ�����������ļ���
const String vectorFolder("vector"); //������������ļ���
const String vectorFile("sample.xml");
//const String sampleDir = fullfile("E:\\��Ŀ\\2016 P2P\\���ڻ���ѧϰ�Ļ���ͼ��ʶ��\\ \
//	opencv\\shape_recognition\\shape_revognition_class\\shape_recognition", sampleFolder);
const String sampleDir = fullfile(rootDir, sampleFolder);
const String vectorDir = fullfile(fullfile(rootDir, vectorFolder), vectorFile);
//������Ԥ�����
const char *errorNoImage = "\nͼƬ�����ڣ�\n";
const char *hintCorrectClass = "\n����ѡ����������Ծ���\n";
const char *errorNoXML = "xml�ļ������ڣ�����Ŀ¼�������������������\n";





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
    //���ж�ֵ�����߽���ȡ����
    Mat imGray;
    if (src.channels() == 3) {
        cvtColor(src, imGray, CV_RGB2GRAY);
    }
    else {
        imGray = src;
    }
    switch (preProcessingMethod) {
    case PRE_PROCESSING_OTSU: {
        //OTSU�㷨
        threshold(imGray, dst, 0, 255, CV_THRESH_OTSU);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        morphologyEx(dst, dst, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        break;
    }
    case PRE_PROCESSING_ADAPTIED_THRESHOLD: {
        //������Ӧ�ֲ���ֵ��
        //blur(imGray, imGray, Size(3, 3));
        adaptiveThreshold(imGray, dst, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 5, 10);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
        morphologyEx(dst, dst, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
        break;
    }
    case PRE_PROCESSING_CANNY: {
        //���Ե���
        Canny(imGray, dst, 50, 100, 3);
        threshold(dst, dst, 128, 255, CV_THRESH_BINARY_INV);
        morphologyEx(dst, dst, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(13, 13)));
        morphologyEx(dst, dst, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
        morphologyEx(dst, dst, MORPH_ERODE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
        break;
    }
    default: {
        cout << QString::fromLocal8Bit("�޴�Ԥ��������\n");
		logFlush();
        break;
    }
    }
}


void ShapeRecognition::shapeRecognitionFlow(Mat &im, bool doStatistics) {
    //Ԥ����
    Mat imBin;
    preProcess(im, imBin);

    //��ȡ����
    findContours(imBin, currentContours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    //ɾ����Χ���С������
    deleteSmallContour(currentContours, im.rows*im.cols*smallShapeThreshold);

    //��������
    drawContour(im, currentContours);

    //�Ա߽���ȡ����Ҷ������
    Mat inputs;
    fourierDescriptor(currentContours, vectorLength, inputs);

    //�������������
    Mat outputs;
    net.predict(inputs, outputs);

    //ת��������±�
	currentCategoryIndex = vec2ind(outputs);

    //����labels
    vector<Point> centroids = contourCentroid(currentContours);
    //putLabel(im, centroids, net.categories, index);
    putChineseLabel(im, centroids, net.categories, currentCategoryIndex, chinese);

    //ͳ����Ŀ
    if (doStatistics) {
        shapeStatic();
    }
}

void ShapeRecognition::afterShapeClicked() {
	categoryIndexClicked = categoryIndexHighlighted;
	counterClicked = counterHighlighted;
	cout << QString::fromLocal8Bit("\n�����þ������\n");
	logFlush();

	setComboBoxClassify();
	ui->comboBoxCategory->setCurrentIndex(categoryIndexClicked);
}

void ShapeRecognition::setComboBoxClassify(){
	//���������˵�
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

    cout << QString::fromLocal8Bit("������״ʶ�𡪡��³� 2015010912010\n");
	logFlush();

	//���������ļ���ȡ��Ϣ
	setComboBoxClassify();
	ui->spinBoxNumLayers->setValue(net.numLayers);
	ui->spinBoxHiddenLayerSize->setValue(net.hiddenLayerSize);

    //��״ʶ��
    QObject::connect(ui->pushButtonImSelect, SIGNAL(clicked()), this, SLOT(selectIm()));
    QObject::connect(ui->pushButtonCameraIn, SIGNAL(clicked()), this, SLOT(openCamera()));
    QObject::connect(ui->spinBoxCameraID, SIGNAL(valueChanged(int)), this, SLOT(setCameraID(int)));
    QObject::connect(ui->horizontalSliderAreaThreshold, SIGNAL(sliderMoved(int)), this, 
		SLOT(setSmallShapeThreshold(int)));
    QObject::connect(ui->comboBoxPreProcessingMethod, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setPreProcessingMethod(int)));
    //���������������
    QObject::connect(ui->spinBoxNumLayers, SIGNAL(valueChanged(int)), this, SLOT(setNumLayers(int)));
    QObject::connect(ui->spinBoxHiddenLayerSize, SIGNAL(valueChanged(int)), this, SLOT(setHiddenLayerSize(int)));
    QObject::connect(ui->pushButtonResetSampleNet, SIGNAL(clicked()), this, SLOT(trainFromIm()));
    //���ͼ�ξ���
	QObject::connect(ui->pushButtonAddClassify, SIGNAL(clicked()), this, SLOT(addCategory()));
	QObject::connect(ui->pushButtonStartFineTuning, SIGNAL(clicked()), this, SLOT(fineTuneNet2GroundTruth()));
	//��������������������
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
        tr("ѡ��ͼ��"),
        "",
        tr("Images (*.png *.bmp *.jpg *.tif *.GIF)")); //ѡ��·��
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
	cout << QString::fromLocal8Bit("\n������������Ѹ��ģ���ѡ�񱣴������\n");
	logFlush();
}

void ShapeRecognition::shapeStatic() {
	unsigned int categoriesNum = net.categories.size();

	cout << QString::fromLocal8Bit("\nͳ�ƽ����\n");
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
    im = imread(imageNam); //Ĭ��ת��ΪRGB��ɫͼ

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
        //��ⰴ��������esc����
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
        //��ⰴ��������esc����
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
	//����������
    //net=MyANN_MLP(net.numLayers,net.hiddenLayerSize);
    //cout << "������ṹ��" << net.net->getLayerSizes().t() << endl;

    //׼������
    cout << QString::fromLocal8Bit("\n��ȡͼƬ...") << endl;
	logFlush();
    tic();
    net.prepare(sampleDir, vectorLength);
    cout << QString::fromLocal8Bit("...��ʱ��") << toc() << "s" << endl;
	logFlush();

    //ѵ��������
    net.train();

    //��֤������
    cout << QString::fromLocal8Bit("׼ȷ�ʣ�") << net.validate() * 100 << "%\n";
	logFlush();

	//��ʾ����
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
			cout << QString::fromLocal8Bit("����")
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
	//չʾǰweight<10������
	showContour(im, contours, windowName,10);

	Mat input;
	fourierDescriptor(contours, vectorLength, input);
	net.addSample(input, categoryIndex);
	//��֤������
	cout << QString::fromLocal8Bit("ѵ��֮ǰ׼ȷ�ʣ�") << net.validate() * 100 << "%\n";
	logFlush();

	net.train();

	cout << QString::fromLocal8Bit("ѵ��֮��׼ȷ�ʣ�") << net.validate() * 100 << "%\n";
	logFlush();
}

void ShapeRecognition::fineTuneNet2GroundTruth() {
	int categoryIndex = ui->comboBoxCategory->currentIndex();
	int i = 0;
	while (1) {
		i++;
		cout << QString::fromLocal8Bit("\n��") << i << QString::fromLocal8Bit("�ε�����\n ");
		logFlush();
		fineTuneNet();

		//������״����ʾ����
		//�Ա߽���ȡ����Ҷ������
		Mat inputs;
		vector<vector<Point>> counters;
		counters.push_back(counterClicked);
		fourierDescriptor(counters, vectorLength, inputs);

		//�������������
		Mat outputs;
		net.predict(inputs, outputs);

		//ת��������±�
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
	cout << QString::fromLocal8Bit("...�ѱ���\n");
	logFlush();
	setComboBoxClassify();
}

void ShapeRecognition::loadNetAndSample() {
	net.loadNet(classifierDir);
	net.loadSample(vectorDir);
	setComboBoxClassify();
	cout << QString::fromLocal8Bit("...������\n");
	logFlush();
	setComboBoxClassify();
}




