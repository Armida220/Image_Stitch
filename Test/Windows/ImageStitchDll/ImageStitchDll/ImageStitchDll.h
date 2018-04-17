#define IMAGESTITCHDLL_API __declspec(dllexport)

//��ʼ��·��
IMAGESTITCHDLL_API int __stdcall DLL_IS_initPath(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath);

//ͼ��Ԥ����,��ȡ��ͼ�����Ŀ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_imagePretreatment();
//����ͼ���������ʼ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_computeImageFeaturesInit();
//����ͼ��������
IMAGESTITCHDLL_API int __stdcall DLL_IS_computeImageFeatures();
//����ͼƬ�������ƥ����
IMAGESTITCHDLL_API int __stdcall DLL_IS_Matching();
//����H����
IMAGESTITCHDLL_API int __stdcall DLL_IS_ComputeHMatrix();

//�ֶ�ƴ�Ӽ���H����
IMAGESTITCHDLL_API int __stdcall DLL_IS_HandComputeHMatrix(const char* image1_name, const char* image2_name, int* twoImagePoint);

//��ȫH����
IMAGESTITCHDLL_API int __stdcall DLL_IS_ComplementH();
//������תͼ��
IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageRotate();

//���ͼ��ƴ��
//IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageConformity(std::vector<std::string>& okImages, std::vector<std::string>& nOkImages, std::string& outImageName, std::string& baseImageName);
IMAGESTITCHDLL_API int __stdcall DLL_IS_ImageConformity(std::vector<std::string>** ppvFileName, int** ppnOK, char* outImageName, const char* baseImageName);
//�ͷ���Դ
IMAGESTITCHDLL_API int __stdcall DLL_IS_Unit();
