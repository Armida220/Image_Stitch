#ifndef _Algorithm_h_
#define _Algorithm_h_
#include <vector>
#include <string>
//��ʼ��·��
int IS_initPath(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath);
//ͼ��Ԥ����,��ȡ��ͼ�����Ŀ��
int IS_imagePretreatment();
//����ͼ���������ʼ��
int IS_computeImageFeaturesInit();
//����ͼ��������
int IS_computeImageFeatures();
//����ͼƬ�������ƥ����
int IS_Matching();
//����H����
int IS_ComputeHMatrix();

//�ֶ�ƴ�Ӽ���H����
int IS_HandComputeHMatrix(const char* image1_name, const char* image2_name, int* twoImagePoint);

//��ȫH����
int IS_ComplementH();
//������תͼ��
int IS_ImageRotate();

//���ͼ��ƴ��
//int IS_ImageConformity(std::vector<std::string>& okImages, std::vector<std::string>& nOkImages, std::string& outImageName, std::string& baseImageName);
int IS_ImageConformity(std::vector<std::string>** ppvFileName, int** ppnOK, char* outImageName, const char* baseImageName);
//�ͷ���Դ
int IS_Unit();
#endif