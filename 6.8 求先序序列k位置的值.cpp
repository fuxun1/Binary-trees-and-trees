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

//自定义访问操作函数
void visit(BiTree T,int arr[],int &i){
    arr[i++]=T->data;
}

//先序遍历
//递归
Status PreOrderTraverse(BiTree T,int arr[],int &i){ //C/C++中数组在函数参数中会退化为指针，不用加"&"
    if(T==NULL) return ERROR;
    else{
        visit(T,arr,i);
        PreOrderTraverse(T->lchild,arr,i);
        PreOrderTraverse(T->rchild,arr,i); 
    }
}

int main(){
    int arr[10];
    BiTree T=newNode(1);
    T->lchild=newNode(2);
    T->rchild=newNode(3);
    T->lchild->lchild=newNode(4);
    T->lchild->rchild=newNode(5);

    int i=0;
    PreOrderTraverse(T,arr,i);
    cout<<"请输入你要查找的先序序列位置k:"<<endl;
    int k;
    cin>>k;
    cout<<"先序序列第"<<k<<"个位置的值为："<<arr[k-1]<<endl;

    return 0;
}