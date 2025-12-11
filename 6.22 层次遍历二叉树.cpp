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

//队列类型定义(元素为指针，因为二叉树链式结构是对地址进行操作，栈同理)
typedef struct{
    BiNode **base;  //能存放一个元素全为指针的数组(树需要)
    int front,rear;
}SqQueue;

//初始化队列
Status InitQueue(SqQueue &Q){
    Q.base=new BiNode*[MAXSIZE];
    if(!Q.base){
        cout<<"队列内存分配失败"<<endl;
        return ERROR;
    }
    Q.front=Q.rear=0;
    return OK;
}

//判断队列是否为空
bool QueueEmpty(SqQueue &Q){
    return Q.front == Q.rear;
}

//循环队列的入队
Status EnQueue(SqQueue &Q,BiNode *p){   //p是指针，类型为BiTree;*p为一个节点BiNode
	if((Q.rear+1)%MAXSIZE==Q.front){	//判断队列是否已满 
		return ERROR;
	}
	Q.base[Q.rear]=p;
	Q.rear=(Q.rear+1)%MAXSIZE;		//队尾指针rear指向下一个位置
	return OK; 
} 

//循环队列的出队
Status DeQueue(SqQueue &Q,BiNode* &p){  //队列里全是BiNode*型的元素，传给p要加引用，不然只是复制
	//先判断队列是否为空
	if(Q.front==Q.rear) {
		return ERROR;
	}
	p=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;	//队头指针+1 
	return OK;
}

//构造空二叉树T(二叉树初始化)
Status InitBiTree(BiTree &T){
    T=NULL;
    return OK;
}

//访问结点的辅助函数
void visit(BiTree T){
    cout<<T->data<<" ";
}

//按先序遍历序列建立二叉树的二叉链表
int i=0;
Status CreateBiTree(BiTree &T,const string &definition){
    char ch=definition[i++];
    if(ch=='#'){
        T=NULL;
    }else{
        T=new BiNode;
        T->data=ch-'0'; //将单个字符数字转化为整数数字，即'1'->1
        CreateBiTree(T->lchild,definition);
        CreateBiTree(T->rchild,definition);
    }

    return OK;
}

//利用队列实现层次遍历
void LevelOrder(BiNode *b){
    if(!b) return;  //空树直接返回
    BiNode *p;
    SqQueue qu;
    InitQueue(qu);
    EnQueue(qu,b);
    while(!QueueEmpty(qu)){
        DeQueue(qu,p);
        cout<<p->data<<" ";
        if(p->lchild!=NULL)EnQueue(qu,p->lchild);
        if(p->rchild!=NULL)EnQueue(qu,p->rchild);
    }
    cout<<endl;
}


//主函数测试
int main(){
    BiTree T;
    InitBiTree(T);
    string definition="1246###5##3##";   //定义：先序遍历序列
    i=0;
    CreateBiTree(T,definition); //按照定义构造二叉树
    LevelOrder(T);

    return 0;
}