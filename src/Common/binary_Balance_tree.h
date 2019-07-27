#ifndef binary_Balance_tree_H_
#define binary_Balance_tree_H_


#include"../Service/SalesAnalysis.h"

//extern salesanalysis_t;

int taller;

typedef struct BiNode
{
    int bf;
    salesanalysis_t data;
    struct BiNode *lchild,*rchild;
}BiNode,*BiTree;

int SearchBST(BiTree T, int key ,BiTree f,BiTree *p);
int InserBST(BiTree *T,int key);
int Delete(BiTree *p);
int DeleteBST(BiTree *T,int key);
void PreOrderTraverse(BiTree T,salesanalysis_list_t list);
//void PreOrderTraverse(BiTree T);
void Tree_free(BiTree T);
void R_Rotate(BiTree *p);  //右旋转
void L_Rotate(BiTree *p);  //左旋转
void LeftBalance(BiTree *T);  //左平衡 左子树高于右子树
void RightBalance(BiTree *T);  //右平衡 右子树高于左子树
int InsertAVL(BiTree *T,salesanalysis_t e ,int *taller);//插入树中


#endif binary_Balance_tree_H_