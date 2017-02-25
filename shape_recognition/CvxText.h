#pragma once
//====================================================================  
//====================================================================  
//  
// �ļ�: CvxText.h  
//  
// ˵��: OpenCV�������  
//  
// ʱ��:   
//  
// ����: chaishushan#gmail.com  
//  
//====================================================================  
//====================================================================  

#ifndef OPENCV_CVX_TEXT_2007_08_31_H  
#define OPENCV_CVX_TEXT_2007_08_31_H  

/**
* \file CvxText.h
* \brief OpenCV��������ӿ�
*
* ʵ���˺���������ܡ�
*/
#include<opencv2/opencv.hpp>
#include <ft2build.h>  
#include FT_FREETYPE_H  

using namespace std;
using namespace cv;

/**
* \class CvxText
* \brief OpenCV���������
*
* OpenCV��������֡��ֿ���ȡ�����˿�Դ��FreeFype�⡣����FreeFype��
* GPL��Ȩ�����Ŀ⣬��OpenCV��Ȩ����һ�£����Ŀǰ��û�кϲ���OpenCV
* ��չ���С�
*
* ��ʾ���ֵ�ʱ����Ҫһ�������ֿ��ļ����ֿ��ļ�ϵͳһ�㶼�Դ��ˡ�
* ������õ���һ����Դ���ֿ⣺����Ȫ�������塱��
*
* ����"OpenCV��չ��"��ϸ�������
* http://code.google.com/p/opencv-extension-library/
*
* ����FreeType��ϸ�������
* http://www.freetype.org/
*
* ���ӣ�
*
* \code
int main(int argc, char *argv[])
{
// ����CvxApplication����

CvxApplication app(argc, argv);

// ��һ��Ӱ��

IplImage *img = cvLoadImage("test.jpg", 1);

// �������

{
// "wqy-zenhei.ttf"Ϊ��Ȫ��������

CvText text("wqy-zenhei.ttf");

const char *msg = "��OpenCV��������֣�";

float p = 0.5;
text.setFont(NULL, NULL, NULL, &p);   // ͸������

text.putText(img, msg, cvPoint(100, 150), CV_RGB(255,0,0));
}
// ���崰�ڣ�����ʾӰ��

CvxWindow myWin("myWin");
myWin.showImage(img);

// ������Ϣѭ��

return app.exec();
}
* \endcode
*/

class CvxText
{
	// ��ֹcopy  

	CvxText& operator=(const CvxText&);

	//================================================================  
	//================================================================  

public:

	/**
	* װ���ֿ��ļ�
	*/

	CvxText(const char *freeType);
	CvxText(string freeType) :CvxText(freeType.c_str()) {};
	virtual ~CvxText();

	//================================================================  
	//================================================================  

	/**
	* ��ȡ���塣Ŀǰ��Щ�����в�֧�֡�
	*
	* \param font        ��������, Ŀǰ��֧��
	* \param size        �����С/�հױ���/�������/��ת�Ƕ�
	* \param underline   �»���
	* \param diaphaneity ͸����
	*
	* \sa setFont, restoreFont
	*/

	void getFont(int *type,
		CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

	/**
	* �������塣Ŀǰ��Щ�����в�֧�֡�
	*
	* \param font        ��������, Ŀǰ��֧��
	* \param size        �����С/�հױ���/�������/��ת�Ƕ�
	* \param underline   �»���
	* \param diaphaneity ͸����
	*
	* \sa getFont, restoreFont
	*/

	void setFont(int *type,
		CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

	/**
	* �ָ�ԭʼ���������á�
	*
	* \sa getFont, setFont
	*/

	void restoreFont();

	//================================================================  
	//================================================================  

	/**
	* ������֡���������������ַ���ֹͣ��
	*
	* \param img   �����Ӱ��
	* \param text  �ı�����
	* \param pos   �ı�λ��
	* \param color �ı���ɫ
	*
	* \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
	*/

	int putText(Mat &img, const char    *text, CvPoint pos, CvScalar color = CvScalar(0, 0, 0));
	int putText(IplImage *img, const char *text, CvPoint pos, CvScalar color = CvScalar(0, 0, 0));

	/**
	* ������֡���������������ַ���ֹͣ��
	*
	* \param img   �����Ӱ��
	* \param text  �ı�����
	* \param pos   �ı�λ��
	* \param color �ı���ɫ
	*
	* \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
	*/
	int putText(IplImage *img, const wchar_t *text, CvPoint pos, CvScalar color = CvScalar(0, 0, 0));
	

	//================================================================  
	//================================================================  

private:

	// �����ǰ�ַ�, ����m_posλ��  

	void putWChar(IplImage *img, wchar_t wc, CvPoint &pos, CvScalar color);

	//================================================================  
	//================================================================  

public:

	FT_Library   m_library;   // �ֿ�  
	FT_Face      m_face;      // ����  

							  //================================================================  
							  //================================================================  

							  // Ĭ�ϵ������������  

	int         m_fontType;
	CvScalar   m_fontSize;
	bool      m_fontUnderline;
	float      m_fontDiaphaneity;

	//================================================================  
	//================================================================  
};

#endif // OPENCV_CVX_TEXT_2007_08_31_H  
