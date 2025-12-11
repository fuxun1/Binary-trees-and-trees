//求二叉树中以元素值为x的节点为根的子树深度
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

//寻找值为x的节点(自己独立写出)
//递归
BiTree FindNode(BiTree T,TElemType x){
    if(T==NULL)return NULL;
    if(T->data==x)return T;
    else{
        BiTree p=FindNode(T->lchild,x);
        if(p)return p;
        return FindNode(T->rchild,x);
    }
} 

//求指定根节点的二叉树深度(递归)
Status BiTreeDepth(BiTree T){
    if(T==NULL)return 0;
    else{
        //递归
        int m=BiTreeDepth(T->lchild);
        int n=BiTreeDepth(T->rchild);
        if(m>n){
            return (m+1);
        }else{
            return (n+1);
        }
    }
}


//主函数测试
int main(){
    BiTree T=newNode(1);
    T->lchild=newNode(2);
    T->rchild=newNode(3);
    T->lchild->lchild=newNode(4);
    T->lchild->rchild=newNode(5);
    //求以2为根节点的子树深度
    BiTree p=FindNode(T,2);
    int k=BiTreeDepth(p);
    cout<<"以"<<2<<"为根结点的子树深度为："<<k<<endl;

    return 0;
}