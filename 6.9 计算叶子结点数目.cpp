//递归计算二叉树叶子结点数目
#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0 
typedef int TElemType;
typedef int Status; //自定义返回类型

//二叉树的链式存储结构
typedef struct BiNode{
    TElemType data; //数据域
    struct BiNode *lchild,*rchild;  //左右孩子指针
}BiNode,*BiTree;

// 创建节点
BiTree newNode(TElemType e) {
    BiTree p=new BiNode;
    p->data=e;
    p->lchild=p->rchild=NULL;
    return p;
}

//递归计算叶子结点数目
Status LeafCount(BiTree T){
    if(T==NULL) return 0;
    if(T->lchild==NULL&&T->rchild==NULL) return 1;
    else{
        return LeafCount(T->lchild)+LeafCount(T->rchild);
    }
}

//主函数测试
int main(){
    BiTree T=newNode(1);
    T->lchild=newNode(2);
    T->rchild=newNode(3);
    T->lchild->lchild=newNode(4);
    T->lchild->rchild=newNode(5);
    int k=LeafCount(T);
    cout<<"叶子结点数目为:"<<k<<endl;

    return 0;
}