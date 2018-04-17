#ifndef _Read_Dir_h_
#define _Read_Dir_h_

#include "ISStruct.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "keyPoint.h"


#ifdef __cplusplus
};
#endif
//��ȡpng�ļ���·��     ��ȡ�ļ�������.png    �ļ�������(������׺��)    ���հ���·���������ļ���
int ReadDir(const char* DirPath,const char* fileType, std::vector<std::string>& fileNames, std::vector<std::string>& filePaths);
//���BMP�ļ���·��     .bmp      �ļ����������ļ�������(���Ӻ�׺��)     �洢���BMP�������ļ���
int TidyBmpDir(const char* DirPath, const char* fileType, std::vector<std::string>& names, std::vector<std::string>& filePaths);
//��ȡ�ļ���(��������׺��)
int GetFileNames(const char* fileType, std::vector<std::string>& fileNames, std::vector<std::string>& names);
//
int GetMatchingFileNames(const char * outPath, const char* outFileType, std::vector<std::string>& names, std::vector<std::vector<std::string>>& matchingName);
int GetFeatureFileNames(const char * featurePath, const char * featureType, std::vector<std::string>& names, std::vector<std::string>& featureNames);

int GetImageRotateFilePathNames(const char * rotatePath, const char * imageType, std::vector<std::string>& names, std::vector<std::vector<std::string>>& imageRotatesPath);
int GetISPathNames(const char* ISPath, const char* imageType, std::vector<std::string>& names, std::vector<std::string>& ISPaths);
void fprintfFeature(char * filename, keyPointInfo * mKeyPointInfo);
void fscanfFeature(char * filename, keyPointInfo * mKeyPointInfo);
void fpritfMatching(char * matchingName, MatchCoorList * matchCoorList);
void fscanfMatching(char* matchingName, MatchCoorList* matchCoorList);
#endif