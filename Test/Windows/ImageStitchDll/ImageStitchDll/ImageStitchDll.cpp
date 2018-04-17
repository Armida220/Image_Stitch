// ImageStitchDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include<string>
#include <vector>
#include "ImageStitchDll.h"
#include "Algorithm.h"
using namespace std;
//��ʼ��·��
IMAGESTITCHDLL_API int __stdcall DLL_IS_initPath(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath)
{
	IS_initPath(srcImagePath, dstImagePath, matchingPath, featurePath, imageRotationPath, imageISPath);
	return 0;
}

//ͼ��Ԥ����,��ȡ��ͼ�����Ŀ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_imagePretreatment()
{
	IS_imagePretreatment();
	return 0;
}
//����ͼ���������ʼ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_computeImageFeaturesInit()
{
	//����ͼ���������ʼ��
	IS_computeImageFeaturesInit();
	return 0;
}
//����ͼ��������
IMAGESTITCHDLL_API int __stdcall DLL_IS_computeImageFeatures()
{
	//����ͼ��������
	IS_computeImageFeatures();
	return 0;
}
//����ͼƬ�������ƥ����
IMAGESTITCHDLL_API int __stdcall DLL_IS_Matching()
{
	//����ͼƬ�������ƥ����
	IS_Matching();
	return 0;
}
//����H����
IMAGESTITCHDLL_API int __stdcall DLL_IS_ComputeHMatrix()
{
	//����H����
	IS_ComputeHMatrix();
	return 0;
}

//�ֶ�ƴ�Ӽ���H����
IMAGESTITCHDLL_API int __stdcall DLL_IS_HandComputeHMatrix(const char* image1_name, const char* image2_name, int* twoImagePoint)
{
	if (image1_name == NULL || image2_name == NULL || *image1_name == '\0' || *image2_name == '\0')
	{
		return -1;
	}
	//�ֶ�ƴ�Ӽ���H����
	IS_HandComputeHMatrix(image1_name, image2_name, twoImagePoint);
	return 0;
}

//��ȫH����
IMAGESTITCHDLL_API int __stdcall DLL_IS_ComplementH()
{
	//��ȫH����
	IS_ComplementH();
	return 0;
}
//������תͼ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageRotate()
{
	//������תͼ��
	IS_ImageRotate();

	return 0;
}

//���ͼ��ƴ��
// IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageConformity(vector<string>& okImages, vector<string>& nOkImages, string& outImageName, string& baseImageName)
// {
// 	//���ͼ��ƴ��
// 	IS_ImageConformity(okImages, nOkImages, outImageName, baseImageName);
// 	return 0;
// }

IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageConformity(std::vector<std::string>** ppvFileName, int** ppnOK, char* outImageName, const char* baseImageName)
{
	IS_ImageConformity(ppvFileName, ppnOK, outImageName, baseImageName);
	return 0;
}

//�ͷ���Դ
IMAGESTITCHDLL_API int __stdcall DLL_IS_Unit()
{
	//�ͷ���Դ
	IS_Unit();
	return 0;
}

