//完全二叉树存在顺序表中的顺序是层次遍历的顺序
//题目要求将存于顺序表中的完全二叉树转化为二叉链表
//顺序表sa，sa.elem[1,2,...,sa.last]共sa.last个元素
/*核心思想：对于完全二叉树，第n个结点的左孩子是第2n个，右孩子是第2n+1个*/
#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int TElemType;
typedef int ElemType;
typedef int Staus;

//顺序表存储结构
typedef struct{
    ElemType *elem;
    int length; //顺序表长度
}SqList;

//二叉链表存储结构(二叉树)
typedef struct BiNode{
    TElemType data;
    BiNode *lchild,*rchild;
}BiNode,*BiTree;

//顺序表初始化
Staus InitList(SqList &L){
    L.elem=new ElemType[MAXSIZE]; 
    if(!L.elem){
        cout<<"内存分配失败"<<endl;
    }
    L.length=0;
    return OK;
}

//创建结点函数
BiTree newNode(TElemType e){
    BiTree p=new BiNode;
    p->data=e;
    p->lchild=p->rchild=NULL;
    return p;
}

//转化函数
/*思路：第一步先将所有需要创建的节点创建出来并保存在指针数组中
        第二步根据下标建立左右孩子关系*/
Staus ArrayToBiTree(BiTree &T,SqList L){
    if(L.length<=1)return ERROR;
    //第一步
    BiTree nodes[MAXSIZE];  //指针数组(每一个元素是一个指向二叉树结点的指针)
    for(int i=1;i<L.length;++i){
        nodes[i]=newNode(L.elem[i]);
    }
    //第二步
    for(int i=1;i<L.length;++i){
        int left=i*2;
        int right=i*2+1;
        //左孩
        if(left<L.length){
            nodes[i]->lchild=nodes[left];
        }else{
            nodes[i]->lchild=NULL;}
        //右孩
        if(right<L.length){
            nodes[i]->rchild=nodes[right];
        }else{
            nodes[i]->rchild=NULL;
        }
    }
    //上面已经把nodes[1]~nodes[length-1]构建为二叉链表
    //现在需要把nodes[1]作为根节点给T
    T=nodes[1];
    return OK;
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

//主函数测试
int main(){
    SqList sa;
    BiTree T;
    InitList(sa);
    sa.length=8;
    cout<<"请输入深度为3的满二叉树的7个元素:"<<endl;
    for(int i=1;i<sa.length;++i){
        cin>>sa.elem[i];
    }
    ArrayToBiTree(T,sa);
    cout<<"创建的二叉链表先序遍历结果为："<<endl;
    PreOrderTraverse(T);
}