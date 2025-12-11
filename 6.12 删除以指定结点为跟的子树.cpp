//删除二叉树中以元素值为x的节点为根的子树并释放相应空间
#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int TElemType;
typedef int Staus;

//二叉链表存储结构(二叉树)
typedef struct BiNode{
    TElemType data;
    BiNode *lchild,*rchild;
}BiNode,*BiTree;

//创建结点函数,结点元素值为e
BiTree NewNode(TElemType e){
    BiTree p=new BiNode;    //创建结点
    p->data=e;
    p->lchild=p->rchild=NULL;
    return p;
}

//辅助函数：在二叉树T中递归查找值为x的节点并返回
BiTree FindNode(BiTree T,TElemType x){
    if(T==NULL)return NULL;
    if(T->data==x) return T;
    else{
        //递归
        BiTree p=FindNode(T->lchild,x);
        if(p) return p; //判断一下，如果找到了就不用继续递归右子树了，直接返回
        return FindNode(T->rchild,x);
    }
}

//辅助函数：删除以指定节点为根的子树
void FreeTree(BiTree p){
    if(p==NULL) return;
    else{
        //先递归删左，再递归删右，最后删自己
        FreeTree(p->lchild);
        FreeTree(p->rchild);
        delete p;
    }
}

//辅助函数：找到指定节点的双亲并返回
BiTree Parent(BiTree T,BiTree p){
    if(T==NULL) return NULL;
    if(T->lchild==p||T->rchild==p) return T;
    else{
        BiTree t=Parent(T->lchild,p);
        if(t) return t;
        return Parent(T->rchild,p);
    }
}


//删去以值为x的节点为根的子树并释放相应空间(不用递归)
void DeleteTree(BiTree T,BiTree p){
    if(T==NULL||p==NULL) return;
    /*得找到子树根节点的双亲并在删去子树后把它置空，不然删去子树后，双亲指向子树根节点的指针
    就变成了野指针，后续遍历会乱码*/
    else{
        BiTree r=Parent(T,p);
        if(r->lchild==p){
            r->lchild=NULL;
        }else{
            r->rchild=NULL;
        }
        FreeTree(p);
    }
}

//辅助函数：访问节点
void visit(BiTree p){
    cout<<p->data<<" ";
}

//先序遍历
Staus PreOrderTraverse(BiTree T){
    if(T==NULL) return ERROR;
    else{
        visit(T);
        //递归
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return OK;
} 

//主函数验证
int main(){
    //创建二叉树(先序遍历序列：1245367)
    BiTree T=NewNode(1);
    T->lchild=NewNode(2);
    T->rchild=NewNode(3);
    T->lchild->lchild=NewNode(4);
    T->lchild->rchild=NewNode(5);
    T->rchild->lchild=NewNode(6);
    T->rchild->rchild=NewNode(7);
    PreOrderTraverse(T);    //原先序序列
    cout<<endl;

    //删除以3为根节点的子树
    BiTree p=FindNode(T,3);
    DeleteTree(T,p);
    PreOrderTraverse(T);    //查看结果

    return 0;
}