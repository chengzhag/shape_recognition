#include "matlab_fcn.h"

String fullfile(String a, String b) {
	String c(a + "\\" + b);
	return c;
}

clock_t  ticTime;
void tic() {
	ticTime = clock();
}
float toc() {
	clock_t tocTime = clock();
	return (float)(tocTime - ticTime) / CLOCKS_PER_SEC;
}


//ֻ��ȡĳ����·���µĵ�ǰ�ļ�����
void getJustCurrentDir(string path, vector<string>& files)
{
	//�ļ���� 
	long long  hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(fileinfo.name);
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
				}

			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//ֻ��ȡĳ����·���µĵ�ǰ�ļ�����
void getJustCurrentFile(string path, vector<string>& files)
{
	//�ļ���� 
	long long  hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				;
			}
			else
			{
				files.push_back(fileinfo.name);
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//ֻ��ȡĳ����·���µ������ļ���(��������ǰĿ¼����Ŀ¼���ļ�)��
void getFilesAll(string path, vector<string>& files)
{
	//�ļ���� 
	long long  hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//��ȡĳ����·���������ļ������ļ����ƣ���������·��
void getAllFiles(string path, vector<string>& files)
{
	//�ļ���� 
	long long  hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

ImageDataStore::ImageDataStore(String location) {
	getJustCurrentDir(location, categories);
	const unsigned int categoriesNum = categories.size();
	for (unsigned int i = 0; i < categoriesNum; i++) {
		string folderDir = fullfile(location, categories[i]);
		vector<string> imDir;
		getAllFiles(folderDir, imDir);
		//ƴ��files������imDir����
		files.insert(files.end(), imDir.begin(), imDir.end());
		//��labels��ӱ�ǩ
		labels.reserve(labels.size() + imDir.size());
		const unsigned long imDirNum = imDir.size();
		for (unsigned long j = 0; j < imDirNum; j++) {
			labels.push_back(i);
		}
	}
}
Mat ImageDataStore::readImage(unsigned long i, int flags) {
	Mat im = imread(files[i], flags);
	return im;
}

vector<unsigned int> vec2ind(Mat x) {
	vector<unsigned int> index;
	index.reserve(x.rows);
	const unsigned long rowNum = x.rows;
	for (unsigned long i = 0; i < rowNum; i++) {
		unsigned int indexMax=0;
		float max = x.at<float>(i, 0);
		for (unsigned int j = 1; j < x.cols; j++) {
			if (x.at<float>(i, j) > max) {
				max = x.at<float>(i, j);
				indexMax = j;
			}
		}
		index.push_back(indexMax);
	}

	return index;
}



