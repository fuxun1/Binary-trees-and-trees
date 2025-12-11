//递归算法，将二叉树中所有节点的左右子树交换
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

//所有结点左右子树交换(自己独立写出来的)
void Mirror(BiTree T){
    if(T==NULL) return;
    if(T->lchild==NULL&&T->rchild==NULL) return;
    else{
        BiTree temp;
        temp=T->lchild;
        T->lchild=T->rchild;
        T->rchild=temp;
        //递归
        Mirror(T->lchild);
        Mirror(T->rchild);
    }
}

//主函数测试
int main(){
    BiTree T=newNode(1);
    T->lchild=newNode(2);
    T->rchild=newNode(3);
    T->lchild->lchild=newNode(4);
    T->lchild->rchild=newNode(5);
    Mirror(T);
    cout<<"交换后的层次遍历结果为："<<" ";
    cout<<T->data<<T->lchild->data<<T->rchild->data<<
    T->rchild->lchild->data<<T->rchild->rchild->data<<endl;

}