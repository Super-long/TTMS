#include<stdio.h>
#include<stdlib.h>
#include"binary_Balance_tree.h"
#define LH +1
#define EH 0
#define RH -1

int SearchBST(BiTree T, int key ,BiTree f,BiTree *p)  //f，p初始值应该都为NULL
{
    if(!T)
    {
        *p = f;
        return 0;
    }else if(T->data.sales == key)
    {
        *p = T;
        return 1;
    }else if(T->data.sales > key)
    {
        return SearchBST(T->lchild,key,T,p);
    }else
    {
        return SearchBST(T->rchild,key,T,p);
    }
}

int InserBST(BiTree *T,int key)
{
    BiTree s,p;
    if(!SearchBST(*T,key,NULL,&p))
    {
        s = (BiTree)malloc(sizeof(BiNode));
        s->data.sales = key;
        s->lchild=s->rchild=NULL;
        if(!p)
        {
            *T=s;        //第一次这里忽略
        }
        else if(key<p->data.sales)
        {
            p->lchild=s;
        }else
        {
            p->rchild=s;
        }
        return 1;
    }else
    {
        printf("节点已存在！\n");
        return 0;
    }
}

int Delete(BiTree *p)  //这个值要被改变
{
    BiTree q,s;
    if((*p)->lchild==NULL)
    {
        q=*p;
        *p=(*p)->rchild;
        free(q);
        return 1;
    }else if((*p)->rchild==NULL)
    {
        q=*p;
        *p=(*p)->lchild;
        free(q);
        return 1;
    }else  //左右子树都不为空
    {
        q=*p;   //q为s的前驱节点
        s=q->lchild;
        while(s->rchild!=NULL)
        {
            q=s;
            s=s->rchild;
        }//循环结束之后s为要删除的节点的前驱节点
        (*p)->data.sales=s->data.sales;
        if(q!=*p)
        {
            q->rchild=s->lchild;
        }else  //要删除的节点无右子树
        {
            q->lchild=s->lchild;
        }
        free(s);
    }
}

int DeleteBST(BiTree *T,int key)  
{
    if(!*T)
    {
        return 0;
    }else
    {
        if(key==(*T)->data.sales)
        {
            return Delete(T);
        }else if(key<(*T)->data.sales)
        {
            DeleteBST(&(*T)->lchild,key);
        }else
        {
            DeleteBST(&(*T)->rchild,key);
        }
    }
    return 0;
}

//中序遍历 递归实现
void PreOrderTraverse(BiTree T,salesanalysis_list_t list)
{
    if(T==NULL)
    return;
    PreOrderTraverse(T->lchild,list);
    salesanalysis_list_t temp=(salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
    temp->data=T->data;  //第一遍错在了这里
    List_AddHead((list),temp);
    PreOrderTraverse(T->rchild,list);
}  

/*  void PreOrderTraverse(BiTree T)
{
    if(T==NULL)
    return;
    PreOrderTraverse(T->lchild);
    salesanalysis_list_t temp=(salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
    temp=T;
    printf("%d\n",T->data.sales);
    PreOrderTraverse(T->rchild);
}  */  

void Tree_free(BiTree T)
{
    BiTree p=T;
    if(T==NULL) return;
    free(T);
    Tree_free(p->lchild);
    Tree_free(p->rchild);
}

void R_Rotate(BiTree *p)  //右旋转
{
    BiTree L;
    L=(*p)->lchild;
    (*p)->lchild=L->rchild;
    L->rchild=(*p);
    *p=L;
}

void L_Rotate(BiTree *p)  //左旋转
{
    BiTree R;
    R=(*p)->rchild;
    (*p)->rchild=R->lchild;
    R->lchild=(*p);
    *p=R;
}

//算法结束时 T指向新结点
void LeftBalance(BiTree *T)  //左平衡 左子树高于右子树
{   
    BiTree L,Lr;
    L=(*T)->lchild;  //左子树根节点
    switch (L->bf)
    {
        case LH :
            (*T)->bf=L->bf=EH;
            R_Rotate(T);
            break;
        case RH :
            Lr = L->rchild;
            switch (Lr->bf)
            {
                case LH :
                    L->bf=EH;
                    (*T)->bf=RH;  
                    break;
                case EH:
                    (*T)->bf=EH;
                case RH:
                    L->bf=LH;
                    (*T)->bf=EH;
                    break;
            }
            Lr->bf=EH;
            L_Rotate((&L));
            R_Rotate(T);
    }
}

void RightBalance(BiTree *T)  //右平衡 右子树高于左子树
{   
    BiTree R,Rr;
    R=(*T)->rchild;  //右子树根节点
    switch (R->bf)
    {
        case LH :
            (*T)->bf=R->bf=EH;
            L_Rotate(T);
            break;
        case RH :
            Rr = R->lchild;
            switch (Rr->bf)
            {
                case LH :
                    R->bf=RH;
                    (*T)->bf=EH;  
                    break;
                case EH:
                    (*T)->bf=EH;
                case RH:
                    R->bf=EH;
                    (*T)->bf=LH;
                    break;
            }
            Rr->bf=EH;
            R_Rotate((&R));
            L_Rotate(T);
    }
}

//布尔变量表示长高与否
int InsertAVL(BiTree *T,salesanalysis_t e ,int *taller)
{
    if(!*T)   //树为空
    {
        *T=(BiTree)malloc(sizeof(BiNode));
        (*T)->data=e;
        //printf("插入中  %s %d %d\n",(*T)->data.name,(*T)->data.sales,(*T)->data.duration);
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=EH;
        *taller=1;
    }else
    {
        if((*T)->data.sales==e.sales)
        {
            *taller=0;
            return 0;
        }
        if(e.sales<(*T)->data.sales)
        {
            if(!InsertAVL(&(*T)->lchild,e,taller))
                return 0;
            if(*taller) //插入成功 树长高 平衡性改变
            {
                switch ((*T)->bf)
                {
                    case LH://原本左子树高于右子树
                        LeftBalance(T);
                        *taller=0;
                        break;
                        //以下两种不会导致不平衡
                    case RH:
                        (*T)->bf=EH;
                        *taller=0;
                        break;
                    case EH:
                        (*T)->bf=RH;
                        *taller=1;
                        break;
                }
            }   
        }else if(e.sales>(*T)->data.sales)
        {
            if(!InsertAVL(&(*T)->rchild,e,taller))
                return 0;
            if(*taller)  //表示成功插入一个新的节点
            {
                switch ((*T)->bf)
                {
                    case RH:
                        RightBalance(T);
                        *taller=0;
                        break;
                    //以下两种不会导致不平衡
                    case EH:
                        (*T)->bf=RH;
                        *taller=1;
                    case LH:
                        (*T)->bf=EH;
                        *taller=0;
                }
            }
        }
    }
    //printf("跳出  %s %d %d\n",(*T)->data.name,(*T)->data.sales,(*T)->data.duration);
    return (*T)->data.sales;
}

/* int main() 
{
    int taller=0;
    int temp=0;
    int b[10]={3,2,1,4,5,6,7,10,9,8};
    salesanalysis_t a[20];
    for(long i=0;i<10;i++)
    a[i].sales=b[i];
    BiTree T=NULL;
    for(int  i = 0; i < 15; i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    PreOrderTraverse(T);
     while(temp)
    {
        printf("输入要删除的元素！");
        scanf("%d",&temp);
        DeleteBST(&T,temp);
        PreOrderTraverse(T);
    } 
    Tree_free(T);
}   */