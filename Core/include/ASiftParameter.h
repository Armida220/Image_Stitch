#ifndef _A_Sift_Parameter_h_
#define _A_Sift_Parameter_h_

#define OCTAVES 5
#define INTERVALS 4
#define INIT_SAMPLE 2
#define THRES 0.0004f


typedef struct _Image_Size_
{
    int width;
    int height;
}Size;

typedef struct _ResponseLayer_
{
    Size size;
    int step;
    int filter;
}ResLayer;


typedef struct _Surf_Parameter_
{
    Size srcSize;
    int octaves;                //����
    int intervals;              //ÿ��Ĳ���
    int initSampStep;           //����������
    float thres;                //��ֵ
    int descroptNumber;         
    int pyramids;
    ResLayer responseFilter[OCTAVES * 2 + 2];
    int filter_map[OCTAVES][INTERVALS];
}SurfParameter;




#ifdef __cplusplus
extern "C"
{
#endif

    SurfParameter* getSurfarameter();

    int initSurfParameter(int SrcWidth, int SrcHeight);

    int unitSurfParameter();


#ifdef __cplusplus
};
#endif

#endif