#include <vector>
#include <string.h>
#include <iostream>
using namespace std;
#include "ImagePathInfo.h"
#include "ReadDir.h"
ImagePathInfo::ImagePathInfo()
{

}
ImagePathInfo::ImagePathInfo(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath)
{    
    this->fileType = "*.bmp";
    this->outFilesType = ".bmp";
    this->matchFileType = ".txt";
    this->featureType = "feat.txt";
    //��ȡ�ļ����µ�ͼƬ
    ReadDir(srcImagePath, this->fileType.c_str(), this->fileNames, this->filePaths);
    //�õ�ͼƬ������
    GetFileNames(this->fileType.c_str(), this->fileNames, this->names);
    //ͼƬ�ñߺ󱣴�
    TidyBmpDir(dstImagePath, this->outFilesType.c_str(), this->names, this->outFilePaths);
    //����ͼƬ������ƥ���ĵ�Դ洢������
    GetMatchingFileNames(matchingPath, this->matchFileType.c_str(), this->names, this->matchings);
    //ÿ��ͼƬ����������ļ���
    GetFeatureFileNames(featurePath, this->featureType.c_str(), this->names, this->featureNames);
    //ÿ��ͼƬ��ת����ļ���
    GetImageRotateFilePathNames(imageRotationPath, this->outFilesType.c_str(), this->names, this->imageRotatesPath);
    //��������ƴ�Ӻõ�ͼ��
    GetISPathNames(imageISPath, this->outFilesType.c_str(), this->names, this->ISImgs);
    
}
void ImagePathInfo::init(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath)
{

    this->fileType = "*.bmp";
    this->outFilesType = ".bmp";
    this->matchFileType = ".txt";
    this->featureType = "feat.txt";
    //��ȡ�ļ����µ�ͼƬ
    ReadDir(srcImagePath, this->fileType.c_str(), this->fileNames, this->filePaths);
    //�õ�ͼƬ������
    GetFileNames(this->fileType.c_str(), this->fileNames, this->names);
    //ͼƬ�ñߺ󱣴�
    TidyBmpDir(dstImagePath, this->outFilesType.c_str(), this->names, this->outFilePaths);
    //����ͼƬ������ƥ���ĵ�Դ洢������
    GetMatchingFileNames(matchingPath, this->matchFileType.c_str(), this->names, this->matchings);
    //ÿ��ͼƬ����������ļ���
    GetFeatureFileNames(featurePath, this->featureType.c_str(), this->names, this->featureNames);
    //ÿ��ͼƬ��ת����ļ���
    GetImageRotateFilePathNames(imageRotationPath, this->outFilesType.c_str(), this->names, this->imageRotatesPath);
    //��������ƴ�Ӻõ�ͼ��
    GetISPathNames(imageISPath, this->outFilesType.c_str(), this->names, this->ISImgs);
}
void ImagePathInfo::clearImagePathInfo()
{
    unsigned int i = 0;
    this->fileNames.clear();
    this->filePaths.clear();
    this->outFilePaths.clear();
    this->names.clear();
    for (i = 0; i < this->matchings.size(); i++)
    {
        this->matchings[i].clear();
    }
    this->matchings.clear();

    this->featureNames.clear();
    for (i = 0; i < this->imageRotatesPath.size(); i++)
    {
        this->imageRotatesPath[i].clear();
    }
    this->imageRotatesPath.clear();
    this->ISImgs.clear();
}
ImagePathInfo::~ImagePathInfo()
{

}