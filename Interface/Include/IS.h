#ifndef _IS_h_
#define _IS_h_
//��ʼ��
int ISInit(int& width, int& height);
//�ͷ���Դ
int ISUnit();

//����ͼ��������
int ISFeature(vector<string>& imagesPath, vector<string>& featurePath);

//��������ͼ���ƥ���
int ISMatching(vector<string>& featuresPath, vector<vector<string>>& matchings);


#endif