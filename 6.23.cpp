#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode,*BiTree;

//创建节点
BiTree createNode(ElemType data){
    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    node->data=data;
    node->lchild=node->rchild=NULL;
    return node;
}

//缩进打印函数
void PrintTree(BiTree T,int level,int spacecount){
    if(T==NULL)return;
    PrintTree(T->rchild,level+1,spacecount);
    for(int i=0;i<level*spacecount;i++)cout<<" ";
    cout<<T->data<<endl;

    //再到左子树
    PrintTree(T->lchild,level+1,spacecount);

}
//中序遍历
void InorderTraver(BiTree T){
    if(T==NULL)return;
    InorderTraver(T->lchild);
    cout<<T->data;
    InorderTraver(T->rchild);

}

int main(){
    BiTree A=createNode('A');
    BiTree B=createNode('B');
    BiTree C=createNode('C');
    BiTree D=createNode('D');
    BiTree E=createNode('E');
    BiTree F=createNode('F');

    A->lchild=B;
    A->rchild=C;
    B->rchild=D;
    C->lchild=E;
    E->rchild=F;

    PrintTree(A,0,4);
    cout<<"中序遍历的结果为：";
    InorderTraver(A);

    return 0;

}