#include <vector>
#include <string>
using namespace std;
#include "Algorithm.h"
#include "ImagePathInfo.h"
#include "CutImage.h"
#include "IS.h"
#include "ISStruct.h"
#include "ComputeHMatrix.h"
#include "Flow.h"
#include "ImageIS.h"
static ImagePathInfo gImagePathInfo;
int IS_Image_Width;
int IS_Image_Height;
HMatrixInfo mHMatrixInfo;
HMatrixInfo mComplementHMatrixInfo;
ISImgInfo mISImgInfo;
//·��������ʼ��
int IS_initPath(char* srcImagePath, char* dstImagePath, char* matchingPath, char* featurePath, char* imageRotationPath, char* imageISPath)
{
    gImagePathInfo.clearImagePathInfo();
    gImagePathInfo.init(srcImagePath, dstImagePath, matchingPath, featurePath, imageRotationPath, imageISPath);
    return 0;
}

//ͼ��Ԥ����,��ȡ��ͼ�����Ŀ��
int IS_imagePretreatment()
{
    int ret = 0;
    static vector<int> allImageWidth;
    static vector<int> allImageHeight;
    ret = CutAllImages(gImagePathInfo.outFilePaths, gImagePathInfo.filePaths, IS_Image_Width, IS_Image_Height,allImageWidth,allImageHeight);
    if (ret)
        return ret;
    int count = allImageWidth.size();
    for (int i = 0; i < count; i++)
    {
        if (allImageHeight[i] != IS_Image_Height || allImageWidth[i] != IS_Image_Width)
        {
            return -1;
        }
    }
    initHMatrixInfo(&mHMatrixInfo, gImagePathInfo.names.size());
    initHMatrixInfo(&mComplementHMatrixInfo, gImagePathInfo.names.size());
    ISImgInfoInit(gImagePathInfo.names.size(), &mISImgInfo);
    return ret;
}
//����ͼ���������ʼ��
int IS_computeImageFeaturesInit()
{
    ISInit(IS_Image_Width, IS_Image_Height);
    return 0;
}
//����ͼ��������
int IS_computeImageFeatures()
{
    ISFeature(gImagePathInfo.outFilePaths, gImagePathInfo.featureNames);
    return 0;
}
//����ͼƬ�������ƥ����
int IS_Matching()
{
    ISMatching(gImagePathInfo.featureNames, gImagePathInfo.matchings);
    return 0;
}
//����H����
int IS_ComputeHMatrix()
{
    Alva_HMatrixes(gImagePathInfo.matchings, &mHMatrixInfo);

    return 0;
}

//�ֶ�ƴ�Ӽ���H����
int IS_HandComputeHMatrix(const char* image1_name, const char* image2_name, int* twoImagePoint)
{
    Alva_TwoImage_HMatrixes(image1_name, image2_name, twoImagePoint, &mHMatrixInfo, gImagePathInfo.names);
    return 0;
}

//��ȫH����
int IS_ComplementH()
{
    ISComplementH(gImagePathInfo.names.size(), &mHMatrixInfo, &mComplementHMatrixInfo);
    return 0;
}
//������תͼ��
int IS_ImageRotate()
{    
    ISComputeISImgMulHInfo(gImagePathInfo.outFilePaths, gImagePathInfo.imageRotatesPath, &mISImgInfo, &mComplementHMatrixInfo);
    return 0;
}

//���ͼ��ƴ��
// int IS_ImageConformity(vector<string>& okImages, vector<string>& nOkImages, string& outImageName, string& baseImageName)
// {
//     ImageConformity(gImagePathInfo.imageRotatesPath, gImagePathInfo.outFilePaths, &mISImgInfo, baseImageName, 
//         gImagePathInfo.ISImgs, gImagePathInfo.names, okImages, nOkImages, outImageName);
//     return 0;
// }

int IS_ImageConformity(std::vector<std::string>** ppvFileName, int** ppnOK, char* outImageName, const char* baseImageName)
{
	*ppvFileName = &gImagePathInfo.names;
	*ppnOK = (int*)calloc(gImagePathInfo.names.size(), sizeof(int));
	ImageConformity(gImagePathInfo.imageRotatesPath, gImagePathInfo.outFilePaths, &mISImgInfo, baseImageName, 
	    gImagePathInfo.ISImgs, gImagePathInfo.names, *ppnOK, outImageName);
	return 0;
}

//�ͷ���Դ
int IS_Unit()
{
    ISImgInfoUnit(&mISImgInfo);
    //�ͷ�H���������Դ
    unitHMatrixInfo(&mHMatrixInfo, gImagePathInfo.names.size());
    unitHMatrixInfo(&mComplementHMatrixInfo, gImagePathInfo.names.size());

    //�ͷ�ASift��Դ
    ISUnit();
    return 0;
}