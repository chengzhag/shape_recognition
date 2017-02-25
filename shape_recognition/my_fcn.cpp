#include "my_fcn.h"

bool exist(string dir) {
    fstream _file;
    _file.open(dir, ios::in);
    if (!_file)
    {
        return false;
    }
    return true;
}

void showProgress(long i, long total, int times) {
    if (times > total)times = total;
    if ((i + 1) % (total / times) == 0) {
        cout << "\r" << (float)(i + 1) * 100 / total << "%";
    }
}
void showMenu(vector<string> menu, bool showHint) {
    unsigned int i = 0;
    cout << endl;
    for (; i < menu.size(); i++) {
        cout << i + 1 << "-" << menu[i] << endl;
    }
    if (showHint) {
        cout << "�����Ų��س�ѡȡ��";
    }
}


void thin(const Mat &src, Mat &dst, const int iterations)
{
    const int height = src.rows - 1;
    const int width = src.cols - 1;

    //����һ���������һ������
    if (src.data != dst.data)
    {
        src.copyTo(dst);
    }


    int n = 0, i = 0, j = 0;
    Mat tmpImg;
    uchar *pU, *pC, *pD;
    bool isFinished = false;

    for (n = 0; n < iterations; n++)
    {
        dst.copyTo(tmpImg);
        isFinished = false;   //һ�� ���к���ɨ�� ��ʼ
                              //ɨ�����һ ��ʼ
        for (i = 1; i < height; i++)
        {
            pU = tmpImg.ptr<uchar>(i - 1);
            pC = tmpImg.ptr<uchar>(i);
            pD = tmpImg.ptr<uchar>(i + 1);
            for (int j = 1; j < width; j++)
            {
                if (pC[j] > 0)
                {
                    int ap = 0;
                    int p2 = (pU[j] > 0);
                    int p3 = (pU[j + 1] > 0);
                    if (p2 == 0 && p3 == 1)
                    {
                        ap++;
                    }
                    int p4 = (pC[j + 1] > 0);
                    if (p3 == 0 && p4 == 1)
                    {
                        ap++;
                    }
                    int p5 = (pD[j + 1] > 0);
                    if (p4 == 0 && p5 == 1)
                    {
                        ap++;
                    }
                    int p6 = (pD[j] > 0);
                    if (p5 == 0 && p6 == 1)
                    {
                        ap++;
                    }
                    int p7 = (pD[j - 1] > 0);
                    if (p6 == 0 && p7 == 1)
                    {
                        ap++;
                    }
                    int p8 = (pC[j - 1] > 0);
                    if (p7 == 0 && p8 == 1)
                    {
                        ap++;
                    }
                    int p9 = (pU[j - 1] > 0);
                    if (p8 == 0 && p9 == 1)
                    {
                        ap++;
                    }
                    if (p9 == 0 && p2 == 1)
                    {
                        ap++;
                    }
                    if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7)
                    {
                        if (ap == 1)
                        {
                            if ((p2*p4*p6 == 0) && (p4*p6*p8 == 0))
                            {
                                dst.ptr<uchar>(i)[j] = 0;
                                isFinished = true;
                            }

                            //   if((p2*p4*p8==0)&&(p2*p6*p8==0))
                            //    {
                            //         dst.ptr<uchar>(i)[j]=0;
                            //         isFinished =TRUE;
                            //    }

                        }
                    }
                }

            } //ɨ�����һ ����


            dst.copyTo(tmpImg);
            //ɨ����̶� ��ʼ
            for (i = 1; i < height; i++)  //һ�� ���к���ɨ�� ��ʼ
            {
                pU = tmpImg.ptr<uchar>(i - 1);
                pC = tmpImg.ptr<uchar>(i);
                pD = tmpImg.ptr<uchar>(i + 1);
                for (int j = 1; j < width; j++)
                {
                    if (pC[j] > 0)
                    {
                        int ap = 0;
                        int p2 = (pU[j] > 0);
                        int p3 = (pU[j + 1] > 0);
                        if (p2 == 0 && p3 == 1)
                        {
                            ap++;
                        }
                        int p4 = (pC[j + 1] > 0);
                        if (p3 == 0 && p4 == 1)
                        {
                            ap++;
                        }
                        int p5 = (pD[j + 1] > 0);
                        if (p4 == 0 && p5 == 1)
                        {
                            ap++;
                        }
                        int p6 = (pD[j] > 0);
                        if (p5 == 0 && p6 == 1)
                        {
                            ap++;
                        }
                        int p7 = (pD[j - 1] > 0);
                        if (p6 == 0 && p7 == 1)
                        {
                            ap++;
                        }
                        int p8 = (pC[j - 1] > 0);
                        if (p7 == 0 && p8 == 1)
                        {
                            ap++;
                        }
                        int p9 = (pU[j - 1] > 0);
                        if (p8 == 0 && p9 == 1)
                        {
                            ap++;
                        }
                        if (p9 == 0 && p2 == 1)
                        {
                            ap++;
                        }
                        if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7)
                        {
                            if (ap == 1)
                            {
                                //   if((p2*p4*p6==0)&&(p4*p6*p8==0))
                                //   {
                                //         dst.ptr<uchar>(i)[j]=0;
                                //         isFinished =TRUE;
                                //    }

                                if ((p2*p4*p8 == 0) && (p2*p6*p8 == 0))
                                {
                                    dst.ptr<uchar>(i)[j] = 0;
                                    isFinished = true;
                                }

                            }
                        }
                    }

                }

            } //һ�� ���к���ɨ�����
              //�����ɨ�������û��ɾ���㣬����ǰ�˳�
            if (isFinished == false)
            {
                break;
            }
        }

    }
}

vector<Point> contourCentroid(vector<vector<Point>> contours) {
    vector<Point> centroids;
    centroids.reserve(contours.size());
    vector<vector<Point>>::iterator it = contours.begin();
    while (it != contours.end())
    {
        Point centroid= contourCentroid(*it++);
        centroids.push_back(centroid);
    }
    return centroids;
}
Point contourCentroid(vector<Point> contour) {
    //�����
    Moments mom = moments(contour);
    //��������
    Point centroid(mom.m10 / mom.m00, mom.m01 / mom.m00);

    return centroid;
}
void deleteSmallContour(vector<vector<Point>> &contours, unsigned long smallArea) {
    vector<vector<Point>>::iterator contoursIt = contours.begin();
    while (contoursIt != contours.end()) {
        //cout << contourArea(*contoursIt) << endl;
        if (contourArea(*contoursIt) < smallArea) {
            contoursIt = contours.erase(contoursIt);
        }
        else {
            contoursIt++;
        }
    }
}
void drawContour(Mat &im, vector<vector<Point>> contours, Scalar color) {
    drawContours(im, contours, -1, Scalar(255, 255, 255), 5);
    drawContours(im, contours, -1, color, 2);
}
void drawContour(Mat &im, vector<Point> contour, Scalar color) {
    vector<vector<Point>> tempContours;
    tempContours.push_back(contour);
    drawContour(im, tempContours, color);
}

void showContour(Mat im, vector<vector<Point>> contours, string windowName, unsigned int num, Scalar color) {
    Mat imTemp;
    for (int i = 0; i < (contours.size() < num ? contours.size() : num); i++) {
        im.copyTo(imTemp);
        drawContour(imTemp, contours[i], color);
        imshow(windowName, imTemp);
        waitKey(30);
    }
}

int findCounterHighlighted(Point mousePos, vector<vector<Point>> contours) {
    int index = -1;
    unsigned long minArea = -1;
    unsigned long tempArea;
    for (int i = 0; i < contours.size(); i++) {
        if (pointPolygonTest(contours[i], mousePos, false) > 0) {
            tempArea = contourArea(contours[i]);
            if (tempArea < minArea) {
                minArea = tempArea;
                index = i;
            }
        }
    }
    return index;
}

void putLabel(Mat &im, vector<Point> centroids, vector<string> categories, vector<unsigned int> index, Scalar color, double fontScale, int thickness, int fontFace) {
    vector<Point>::iterator centroidsIt = centroids.begin();
    int i = 0;
    int baseline = 0;
    while (centroidsIt != centroids.end()) {
        putLabel(im, (*centroidsIt), categories, index[i], color, fontScale, thickness, fontFace);
        centroidsIt++;
        i++;
    }
}
void putLabel(Mat &im, Point centroids, vector<string> categories, unsigned int index, Scalar color, double fontScale, int thickness, int fontFace) {
    int baseline = 0;
    String text(categories[index]);
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    Point textOrg((centroids.x - textSize.width / 2), (centroids.y + textSize.height / 2));
    putText(im, text, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness*4-1);
    putText(im, text, textOrg, fontFace, fontScale, color, thickness);
}
void putChineseLabel(Mat &im, vector<Point> centroids, vector<string> categories, vector<unsigned int> index, CvxText &fft, double fontScale, Scalar color) {
    vector<Point>::iterator centroidsIt = centroids.begin();
    int i = 0;
    while (centroidsIt != centroids.end()) {
        putChineseLabel(im, (*centroidsIt), categories, index[i], fft, fontScale, color);
        centroidsIt++;
        i++;
    }
}
void putChineseLabel(Mat &im, Point centroids, vector<string> categories, unsigned int index, CvxText &fft, double fontScale, Scalar color) {
    string text(categories[index]);
    Point textOrg(centroids.x - text.size()*fontScale*0.9 / 4, centroids.y + fontScale*0.9/ 2);
    CvScalar m_fontSize(fontScale, 0.5, 0.1, 0);
    fft.setFont(NULL, &m_fontSize, NULL, NULL);
    rectangle(im, Rect(centroids.x - text.size()*fontScale*1.1 / 4, centroids.y - fontScale*1.1 / 2, text.size()*fontScale*1.1 / 2, fontScale*1.1), Scalar(255, 255, 255),-1);
    fft.putText(im, text.c_str(), textOrg, color);
}


MyANN_MLP::MyANN_MLP(int hiddenLayerNum, int hiddenLayerNodeNum) {
    ////������������������ Training, Validation, Testing
    //divideParam.trainRatio = 1;
    //divideParam.testRatio = 0;
    //����ѵ������
    trainparam.epochs = 300;
    trainparam.goal = FLT_EPSILON;
    //����������ṹ
    numLayers = hiddenLayerNum;
    hiddenLayerSize = hiddenLayerNodeNum;
    //��ʼ��������
    net = ANN_MLP::create();
}
MyANN_MLP::MyANN_MLP(string dir) {
    loadNet(dir);
}

void MyANN_MLP::prepare(String sampleDir, Mat &inputsReturn, Mat &targetsReturn, unsigned int vectorLength) {
    //ͼƬ��ȡ
    ImageDataStore imds(sampleDir);
    categories = imds.categories;
    if (imds.categories.size() == 0) {
        cout << "\nImageDataStore�����·�������ڣ�\n";
        return;
    }
    cout << "��" << imds.categories.size() << "�࣬" << imds.labels.size() << "������" << "��" ;
    showMenu(categories);

    //������ȡ
    cout <<endl<< "������ȡ..." << endl;
    const unsigned long sampleAllNum = imds.labels.size();
    //��������������Mat
    Mat inputs(sampleAllNum, vectorLength, CV_32FC1);
    for (unsigned long i = 0; i < sampleAllNum; i++) {
        //��ȡͼƬ����ֵ��
        Mat image = imds.readImage(i, IMREAD_GRAYSCALE);
        Mat imageBin;
        threshold(image, imageBin, 0, 255, CV_THRESH_OTSU);
        //imshow("", imageBin);
        waitKey(1);
        //��ȡ����
        vector<vector<Point>> contours;
        findContours(imageBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        //cout << imds.labels[i] << " �����ĳ���: " << contours[0].size() << std::endl; //��ʾ�����ĳ���
        //ѡȡ��Χ�����������
        unsigned long maxArea = 0;
        unsigned int maxIndex = 0;
        for (unsigned int i = 0; i < contours.size(); i++) {
            if (unsigned long tempArea = contourArea(contours[i]) > maxArea) {
                maxArea = tempArea;
                maxIndex = i;
            }
        }
        //��ȡ��������
        vector<float> input;
        input = fourierDescriptor(contours[maxIndex], vectorLength);
        for (int j = 0; j < vectorLength; j++) {
            inputs.at<float>(i, j) = input[j];
        }
        //��ʾ����
        //showProgress(i, sampleAllNum);
    }
    //cout << "    ������������" << endl << inputs << endl; //��ʾ������������

    //����������ѵ���ñ�ǩ����
    const unsigned int categoriesNum = imds.categories.size();
    //����Ŀ�굽Mat
    Mat targets = Mat::zeros(sampleAllNum, categoriesNum, CV_32FC1);
    for (unsigned long i = 0; i < sampleAllNum; i++) {
        targets.at<float>(i, imds.labels[i]) = 1;
    }
    //cout << "    ��ǩ����" << endl << targets << endl; //��ʾ��ǩ����
    inputsReturn = inputs;
    targetsReturn = targets;
}
void MyANN_MLP::prepare(String sampleDir, unsigned int vectorLength) {
    prepare(sampleDir, inputs.trainInputs, targets.trainTargets, vectorLength);
}

void MyANN_MLP::train(Mat inputs, Mat targets) {
    cout << "ѵ��������..." << endl;
    tic();
    //����ѵ����������������ṹ
    numInputs = inputs.cols;
    numOutputs = targets.cols;
    //���ò�ṹ
    Mat layerSizes(1, numLayers + 2, CV_32SC1);
    layerSizes.at<int>(0, 0) = numInputs;
    for (int i = 1; i < numLayers + 1; i++) {
        layerSizes.at<int>(0, i) = hiddenLayerSize;
    }
    layerSizes.at<int>(0, numLayers + 1) = numOutputs;
    //cout << "    ������ṹ��" << endl << "    " << layerSizes << endl; //��ʾ��ṹ
    //�������������ԡ�ѵ������
    net->setLayerSizes(layerSizes);
    net->setActivationFunction(ANN_MLP::SIGMOID_SYM, 1, 1);
    net->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, trainparam.epochs, trainparam.goal));
    net->setTrainMethod(ANN_MLP::BACKPROP, 0.1);
    //��ʼѵ��
    Ptr<TrainData> tData = TrainData::create(inputs, ROW_SAMPLE, targets);
    net->train(tData);
    cout << "...��ʱ��" << toc() << "s" << endl;
}
void MyANN_MLP::train() {
    train(inputs.trainInputs, targets.trainTargets);
}
void MyANN_MLP::train(string dir) {
    loadSample(dir);

    //ѵ��������
    train();
}

void MyANN_MLP::predict(InputArray inputs, OutputArray outputs) {
    net->predict(inputs, outputs);
}

float MyANN_MLP::validate(Mat inputs, Mat targets) {
    Mat outputs;
    net->predict(inputs, outputs);
    unsigned long sampleAllNum = inputs.rows;
    vector<unsigned int> outputIndex = vec2ind(outputs);
    vector<unsigned int> targetIndex = vec2ind(targets);
    //cout << "    �����ǩ�±꣺" << Mat(index) << endl;
    unsigned long trueNum = 0;
    for (unsigned long i = 0; i < sampleAllNum; i++) {
        if (targetIndex[i] == outputIndex[i])
            trueNum++;
    }
    return (float)trueNum / sampleAllNum;
}
float MyANN_MLP::validate() {
    return validate(inputs.trainInputs, targets.trainTargets);
}

void MyANN_MLP::saveNet(string dir) {
    net->save(dir);
}
void MyANN_MLP::saveSample(string dir) {
    FileStorage fs(dir, FileStorage::WRITE);
    fs << "trainInputs" << inputs.trainInputs;
    fs << "trainTargets" << targets.trainTargets;
    fs << "categories" << "["; // ע��Ҫ��������
    for (vector<string>::iterator it = categories.begin(); it != categories.end(); it++)
    {
        fs << (*it);
    }
    fs << "]";
}
void MyANN_MLP::askIfSaveChange(string classifierDir, string vectorDir, int flag) {
    if (flag == DO_SAVE_SAMPLE || flag == DO_SAVE_SAMPLE_AND_NET) {
        cout << "\n�Ƿ񱣴���ĺ�ĵ�������\n";
        while (1) {
            cout << "[y/n]: ";
            string stringIn;
            cin >> stringIn;
            if (!stringIn.compare("y") || !stringIn.compare("Y")) {
                cout << "��������...\n";
                tic();
                saveSample(vectorDir);
                cout << "�ѱ���...��ʱ��" << toc() << "s" << endl;
                break;
            }
            else if (!stringIn.compare("n") || !stringIn.compare("N")) {
                cout << "\n��ԭ����..." << endl;
                loadSample(vectorDir);
                cout << "�ѻ�ԭ\n" << endl;
                break;
            }
        }

    }
    if (flag == DO_SAVE_NET || flag == DO_SAVE_SAMPLE_AND_NET) {
        cout << "\n�Ƿ񱣴���ĺ�ĵ������磿\n";
        while (1) {
            cout << "[y/n]: ";
            string stringIn;
            cin >> stringIn;
            if (!stringIn.compare("y") || !stringIn.compare("Y")) {
                cout << "����������...\n";
                tic();
                saveNet(classifierDir);
                cout << "�ѱ���...��ʱ��" << toc() << "s" << endl;
                break;
            }
            else if (!stringIn.compare("n") || !stringIn.compare("N")) {
                cout << "\n��ԭ������..." << endl;
                loadNet(classifierDir);
                cout << "�ѻ�ԭ\n" << endl;
                break;
            }
        }
    }
    if (flag == DO_SAVE_ALL_TOGETHER) {
        cout << "\n�Ƿ񱣴���ĺ�ĵ��������������\n";
        while (1) {
            cout << "[y/n]: ";
            string stringIn;
            cin >> stringIn;
            if (!stringIn.compare("y") || !stringIn.compare("Y")) {
                cout << "����������...\n";
                tic();
                saveNet(classifierDir);
                cout << "�ѱ���...��ʱ��" << toc() << "s" << endl;
                cout << "��������...\n";
                tic();
                saveSample(vectorDir);
                cout << "�ѱ���...��ʱ��" << toc() << "s" << endl;
                break;
            }
            else if (!stringIn.compare("n") || !stringIn.compare("N")) {
                cout << "\n��ԭ������..." << endl;
                loadNet(classifierDir);
                cout << "�ѻ�ԭ" << endl;
                cout << "\n��ԭ����..." << endl;
                loadSample(vectorDir);
                cout << "�ѻ�ԭ\n" << endl;
                break;
            }
        }
    }
}

void MyANN_MLP::loadNet(string dir) {
    net = Algorithm::load<ANN_MLP>(dir);
    Mat layerSizes = net->getLayerSizes();
    numInputs = layerSizes.at<int>(0, 0);
    numLayers = layerSizes.rows - 2;
    numOutputs = layerSizes.at<int>(numLayers + 1, 0);
    hiddenLayerSize = layerSizes.at<int>(1, 0);
    trainparam.epochs = net->getTermCriteria().MAX_ITER;
    trainparam.goal = net->getTermCriteria().EPS;
}
void MyANN_MLP::loadSample(string dir) {
    FileStorage fs(dir, FileStorage::READ);
    fs["trainInputs"] >> inputs.trainInputs;
    fs["trainTargets"] >> targets.trainTargets;
    FileNode n = fs["categories"];
    categories.clear();
    if (n.type() != FileNode::SEQ)
    {
        cout << "����categories����һ������" << endl;
    }
    for (FileNodeIterator it = n.begin(); it != n.end(); it++)
    {
        categories.push_back((string)*it);
    }
    cout << "���У�" << inputs.trainInputs.rows << "������\n";
}


void MyANN_MLP::addSample(vector<float> input, unsigned int label, unsigned long weight) {
    copyMakeBorder(inputs.trainInputs, inputs.trainInputs, 0, weight, 0, 0, BORDER_CONSTANT, 0);
    copyMakeBorder(targets.trainTargets, targets.trainTargets, 0, weight, 0, 0, BORDER_CONSTANT, 0);
    for (unsigned long j = 0; j < weight; j++) {
        for (unsigned int i = 0; i < input.size(); i++) {
            inputs.trainInputs.at<float>(inputs.trainInputs.rows + j - weight, i) = input[i];
        }
        targets.trainTargets.at<float>(targets.trainTargets.rows + j - weight, label) = 1;
    }
}
void MyANN_MLP::addSample(Mat input, unsigned int label) {
    copyMakeBorder(inputs.trainInputs, inputs.trainInputs, 0, input.rows, 0, 0, BORDER_CONSTANT, 0);
    copyMakeBorder(targets.trainTargets, targets.trainTargets, 0, input.rows, 0, 0, BORDER_CONSTANT, 0);
    for (unsigned long j = 0; j < input.rows; j++) {
        for (unsigned int i = 0; i < input.cols; i++) {
            inputs.trainInputs.at<float>(inputs.trainInputs.rows + j - input.rows, i) = input.at<float>(j,i);
        }
        targets.trainTargets.at<float>(targets.trainTargets.rows + j - input.rows, label) = 1;
    }
}
void MyANN_MLP::addCategory(vector<float> input, string category, unsigned long weight) {
    copyMakeBorder(inputs.trainInputs, inputs.trainInputs, 0, weight, 0, 0, BORDER_CONSTANT, 0);
    copyMakeBorder(targets.trainTargets, targets.trainTargets, 0, weight, 0, 1, BORDER_CONSTANT, 0);
    for (unsigned long j = 0; j < weight; j++) {
        for (unsigned int i = 0; i < input.size(); i++) {
            inputs.trainInputs.at<float>(inputs.trainInputs.rows + j - weight, i) = input[i];
        }
        targets.trainTargets.at<float>(targets.trainTargets.rows + j - weight, targets.trainTargets.cols - 1) = 1;
    }
    categories.push_back(category);
}
void MyANN_MLP::addCategory(Mat input, string category) {
    copyMakeBorder(inputs.trainInputs, inputs.trainInputs, 0, input.rows, 0, 0, BORDER_CONSTANT, 0);
    copyMakeBorder(targets.trainTargets, targets.trainTargets, 0, input.rows, 0, 1, BORDER_CONSTANT, 0);
    for (unsigned long j = 0; j < input.rows; j++) {
        for (unsigned int i = 0; i < input.cols; i++) {
            inputs.trainInputs.at<float>(inputs.trainInputs.rows + j - input.rows, i) = input.at<float>(j, i);
        }
        targets.trainTargets.at<float>(targets.trainTargets.rows + j - input.rows, targets.trainTargets.cols - 1) = 1;
    }
    categories.push_back(category);
}
bool MyANN_MLP::askAddAndTrain(Mat im, vector<Point> counterSelected, int vectorLength,const string windowName) {
    cout << "\n������ѡ����\n";
    vector<string> menu = categories;
    menu.push_back("����µ����");
    showMenu(menu);
    cout << "ѡ����״����𣬻�����0ȡ����";
    unsigned int label;
    cinNum(label);
    if (label == 0) {}
    else if (label > menu.size()) {
        cout << "�����ڴ����\n";
    }
    else if (label == menu.size()) {
        cout << "���������������ƣ����ģ���";
        string category;
        cin >> category;
        cout << "����������Ȩ�أ���������������0ȡ����";
        unsigned long weight;
        cinNum(weight);
        if (weight != 0) {
            cout << "������������ӵ�����ǿ�ȣ���������λ���أ���0���������,10���½ϼѣ�";
            unsigned int noiseStrength;
            cinNum(noiseStrength);
            vector<vector<Point>> contours;
            contours.reserve(weight);
            for (unsigned long i = 0; i < weight; i++) {
                contours.push_back(counterSelected);
            }
            if (noiseStrength != 0) {
                addNoiseToContour(contours, 0, noiseStrength);
            }
            //չʾǰweight<100������
            showContour(im, contours, windowName);

            Mat input;
            fourierDescriptor(contours, vectorLength, input);
            addCategory(input, category);
            //��֤������
            cout << "ѵ��֮ǰ׼ȷ�ʣ�" << validate() * 100 << "%\n";
            train();
            cout << "ѵ��֮��׼ȷ�ʣ�ʵ��Ч���뿴ͼ����" << validate() * 100 << "%\n";
            return true;
        }
    }
    else {
        cout << "ѡ��������Ȩ�أ���������������0ȡ����";
        unsigned long weight;
        cinNum(weight);
        if (weight != 0) {
            cout << "������������ӵ�����ǿ�ȣ���������λ���أ���0���������,10���½ϼѣ�";
            unsigned int noiseStrength;
            cinNum(noiseStrength);
            vector<vector<Point>> contours;
            contours.reserve(weight);
            for (unsigned long i = 0; i < weight; i++) {
                contours.push_back(counterSelected);
            }
            if (noiseStrength != 0) {
                addNoiseToContour(contours, 0, noiseStrength);
            }
            //չʾǰweight<100������
            showContour(im, contours, windowName);

            Mat input;
            fourierDescriptor(contours, vectorLength, input);
            addSample(input, label - 1);
            //��֤������
            cout << "ѵ��֮ǰ׼ȷ�ʣ�" << validate() * 100 << "%\n";
            train();
            cout << "ѵ��֮��׼ȷ�ʣ�ʵ��Ч���뿴ͼ����" << validate() * 100 << "%\n";
            return true;
        }
    }
    return false;
}

