#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ASiftParameter.h"
#include "ComputeHMatrix.h"
#include "Flow.h"
#include "ISLog.h"
static void Copy_H(float* srcH, float* destH, int number)
{
    int i = 0;
    for(i = 0; i < number; i ++)
    {
        destH[i] = srcH[i];
    }
}


static int countImageUsedNumber(int* imageUsedFlag, int number)
{
    int i = 0;
    int sum = 0;
    for(i = 0; i < number; i ++)
    {
        sum += imageUsedFlag[i];
    }
    return sum;
}
// number:ͼ�������
// baseIndex:��׼ͼ
// mHMatrixInfo:H������Ϣ
// outHMatrixList:��׼ͼ��H����ȫ
//����˵��: ��ȫһ��ͼƬ������ͼƬ��H����
static int StitchingFlow(int number, int baseIndex, HMatrixInfo* mHMatrixInfo, HMatrixList* outHMatrixList)
{
    int i = 0, j = 0;
    int* everyImagePairCount = NULL;
    int** everyImagePairIndex = NULL;
    int* imageUsedFlag = NULL;

    int sum = 0;
    int preSum = 0;

    NodeHead * nodeHead1 = NULL;
    NodeHead * nodeHead2 = NULL;
    NodeHead * nodeHeadTemp = NULL;

    nodeHead1 = (NodeHead *)calloc(1, sizeof(NodeHead));
	CHECK_ALLOC_P(nodeHead1);
    nodeHead2 = (NodeHead *)calloc(1, sizeof(NodeHead));
	CHECK_ALLOC_P(nodeHead2);

    initListHead(nodeHead1);
    initListHead(nodeHead2);

    //���ͼƬ�Ƿ�ʹ��
    imageUsedFlag = (int*)calloc(1, sizeof(int) * number);
	CHECK_ALLOC_P(imageUsedFlag);
    //ÿ��ͼƬ�ĺϸ�H��������
    everyImagePairCount = (int*)calloc(1, sizeof(int) * number);
	CHECK_ALLOC_P(everyImagePairCount);
    //ÿ��ͼƬ��ƥ��ͼ��  H����ϸ� ��index
    everyImagePairIndex = (int**)calloc(1, sizeof(int*) * number);
	CHECK_ALLOC_P(everyImagePairIndex);
    for(i = 0; i < number; i ++)
    {
        everyImagePairCount[i] = mHMatrixInfo->hMatrixList[i].pairCount;
        everyImagePairIndex[i] = (int*)calloc(1, sizeof(int) * everyImagePairCount[i]);
		CHECK_ALLOC_P(everyImagePairIndex[i]);
    }

    //ͳ��ĳһ��ͼƬ��������ͼƬ��H�����Ƿ�ϸ�
    for(i = 0; i < number; i ++)
    {
        int count = 0;
        for(j = 0; j < number; j ++)
        {
            if(mHMatrixInfo->hMatrixList[i].hMatrix[j].flag == 1)
            {
                everyImagePairIndex[i][count] = j;
                //printf("%d  ", j);
                count ++;
            }
        }
        //printf("      i = %d  count = %d\n", i, count);
    }

    //baseImage ��1
    imageUsedFlag[baseIndex] = 1;
    //everyImagePairCount[baseIndex] baseImage  H���������
    for(i = 0; i < everyImagePairCount[baseIndex]; i ++)
    {
        node* newNode = instancePariImage();
        //mHMatrixInfo->hMatrixList[baseIndex].hMatrix[everyImagePairIndex[baseIndex][i]].H   H����ϸ�
        Copy_H(mHMatrixInfo->hMatrixList[baseIndex].hMatrix[everyImagePairIndex[baseIndex][i]].H, newNode->m->H, 9);
        newNode->m->imageIndex = everyImagePairIndex[baseIndex][i];

        Copy_H(mHMatrixInfo->hMatrixList[baseIndex].hMatrix[everyImagePairIndex[baseIndex][i]].H, outHMatrixList->hMatrix[everyImagePairIndex[baseIndex][i]].H, 9);

        outHMatrixList->hMatrix[everyImagePairIndex[baseIndex][i]].flag = 1;
        outHMatrixList->pairCount ++;
        headInsert(nodeHead1, newNode);

        imageUsedFlag[everyImagePairIndex[baseIndex][i]] = 1;
    }
    //����ΪֹnodeHead1�д洢����  baseImage������ͼƬH����ϸ��H����


    do 
    {
        preSum = sum;

        for(i = 0; i < nodeHead1->count; i ++)
        {
            node* nodeTemp = getNode(nodeHead1, i);
            for(j = 0; j < everyImagePairCount[nodeTemp->m->imageIndex]; j ++)
            {
                if(imageUsedFlag[everyImagePairIndex[nodeTemp->m->imageIndex][j]] == 0)
                {
                    node* newNode = instancePariImage();
                    Alva_HMixH(nodeTemp->m->H, mHMatrixInfo->hMatrixList[nodeTemp->m->imageIndex].hMatrix[everyImagePairIndex[nodeTemp->m->imageIndex][j]].H, newNode->m->H);

                    Copy_H(newNode->m->H, outHMatrixList->hMatrix[everyImagePairIndex[nodeTemp->m->imageIndex][j]].H, 9);
                    
                    outHMatrixList->hMatrix[everyImagePairIndex[nodeTemp->m->imageIndex][j]].flag = 1;
                    outHMatrixList->pairCount ++;

                    newNode->m->imageIndex = everyImagePairIndex[nodeTemp->m->imageIndex][j];

                    headInsert(nodeHead2, newNode);

                    imageUsedFlag[newNode->m->imageIndex] = 1;
                }
            }
        }

        nodeHeadTemp = nodeHead1;
        nodeHead1 = nodeHead2;
        nodeHead2 = nodeHeadTemp;


        destroyList(nodeHead2);

        sum = countImageUsedNumber(imageUsedFlag, number);
    } while (sum != preSum);

    destroyList(nodeHead1);
    free(nodeHead1);
    free(nodeHead2);

    for(i = 0; i < number; i ++)
    {     
        free(everyImagePairIndex[i]);
    }
    free(everyImagePairIndex);
    free(everyImagePairCount);

    return 0;
}


int ISComplementH(int number, HMatrixInfo* mHMatrixInfo, HMatrixInfo* mOutHMatrixInfo)
{
    int i = 0;
    for(i = 0; i < number; i ++)
    {
        StitchingFlow(number, i, mHMatrixInfo, &(mOutHMatrixInfo->hMatrixList[i]));
        //printf("i = %d  pairCount = %d\n", i, mOutHMatrixInfo->hMatrixList[i].pairCount);
    }
    return 0;
}


node* instancePariImage()
{
    node* newNode = NULL;
    newNode = (node*)calloc(1, sizeof(node));
	CHECK_IS_NULL(newNode);
    newNode->m = (pairImage*)calloc(1, sizeof(pairImage));
	CHECK_IS_NULL((newNode->m));
    newNode->m->imageIndex = 0;
    newNode->m->H = (float*)calloc(1, sizeof(float) * 9);
	CHECK_IS_NULL((newNode->m->H));
    return newNode;
}
void initListHead(NodeHead* listHead)
{
    listHead->count = 0;
    listHead->next = NULL;
}
void headInsert(NodeHead* listHead, node* newNode)
{
    newNode->next = listHead->next;
    listHead->next = newNode;
    listHead->count ++;
}
void destroyList(NodeHead* listHead)
{
    node* temp = NULL;
    listHead->count = 0;
    while(listHead->next != NULL)
    {
        temp = listHead->next;
        listHead->next = temp->next;
        free(temp->m->H);
        free(temp);
    }
}
node* getNode(NodeHead* listHead, int nodeIndex)
{
    int i = 0;
    node* temp = NULL;
    temp = listHead->next;
    for(i = 0; i < nodeIndex; i ++)
    {
        temp = temp->next;
    }
    return temp;
}