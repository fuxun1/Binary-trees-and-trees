#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0
typedef char TElemType;
typedef int Status;

//结点结构
typedef struct BSTNode{
    TElemType data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

//插入操作
//还是用递归
void InsertKey(BSTree &T,TElemType enterkey){
    //如果树为空
    if(T==NULL){
        BSTNode* p=new BSTNode;
        p->lchild=NULL;
        p->rchild=NULL;
        p->data=enterkey;
        T=p;    //将新节点的地址值写入插入位置的指针域
    }else if(T->data>enterkey){
        InsertKey(T->lchild,enterkey);
    }else{
        InsertKey(T->rchild,enterkey);
    }

}

//访问结点的辅助函数
void visit(BSTree T){
    cout<<T->data<<" ";
}

//中序遍历二叉树
Status InOrderTraverse(BSTree T){
    if(T==NULL)return ERROR;   //空二叉树直接返回
    else{
        //递归
        InOrderTraverse(T->lchild); //递归遍历左子树
        visit(T);   //访问根节点
        InOrderTraverse(T->rchild); //递归遍历右子树
    }
}

//主函数测试
int main(){
    BSTree T=NULL;
    InsertKey(T,'A');
    InsertKey(T,'C');
    InsertKey(T,'F');
    InsertKey(T,'E');
    InsertKey(T,'B');
    
    InOrderTraverse(T);

    return 0;
}