#include<iostream>
using namespace std;

//整个树这一章几乎全是递归
#define MAXSIZE 100
#define OK 1
#define ERROR 0 
typedef int TElemType;
typedef int Status; //自定义返回类型

//二叉树的顺序存储表示(适用于存满二叉树和完全二叉树)
//需要用时直接SqBiTree bt即可生成二叉树bt(本质上是拿数组存储二叉树)
//按满二叉树给树节点编号，空的位置就填值为0
typedef TElemType SqBiTree[MAXSIZE] ;

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

//顺序栈类型定义 
typedef struct{
	BiNode **top;
	BiNode **base;
	int stacksize;
}SqStack;

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

//初始化栈(构造一个空栈) 
Status InitStack(SqStack &S){
	S.base=new BiNode*[MAXSIZE];
	if(!S.base){
		cout<<"空间分配失败"<<endl;
		exit(1);
	} 
	S.top=S.base;
	S.stacksize=MAXSIZE;
	cout<<"内存分配成功"<<endl;
	return OK; 
}

//判断栈是否为空
bool StackEmpty(SqStack &S){
    return S.top==S.base;
}

//入栈
Status Push(SqStack &S, BiNode *p){    
    if(S.top-S.base==S.stacksize) return ERROR;
    *S.top++=p;
    return OK;
}

//出栈
Status Pop(SqStack &S, BiNode* &p){
    if(S.top==S.base) return ERROR;
    p=*--S.top;
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


//访问结点的辅助函数
void visit(BiTree T){
    cout<<T->data<<" ";
}

//操作1：构造空二叉树T(二叉树初始化)
Status InitBiTree(BiTree &T){
    T=NULL;
    return OK;
}

//操作2：销毁二叉树
void DestroyBiTree(BiTree &T){
    if(T==NULL)return;
    //递归调用
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;   //先删除（第一个被删除是最左端的叶子结点，因为其无左右孩，左右递归都会直接return）
    T=NULL; //再将指针置空
}

//操作3：按定义构造二叉树T
// CreateBiTree(&T,definition)

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


//操作4：判断二叉树是否为空
bool BiTreeEmpty(BiTree T){
    return T==NULL;
}

//操作5：求二叉树深度
//如果是空树，则深度为0；否则，递归计算左子树深度m，右子树深度n，二叉树深度为max{m,n}+1
Status BiTreeDepth(BiTree T){
    if(T==NULL)return 0;
    else{
        int m=BiTreeDepth(T->lchild);
        int n=BiTreeDepth(T->rchild);
        if(m>n)return (m+1);
        else return (n+1);
    }
}

//操作6：返回e的双亲(若e是根节点，返回空)
//双亲其实指的是一个节点
BiTree Parent(BiTree T,TElemType e){
    if(T==NULL)return NULL;
    //左右孩子存在并且值为e就是e的双亲
    if(T->lchild&&T->lchild->data==e)return T;
    if(T->rchild&&T->rchild->data==e)return T;
    //递归在左子树中找
    BiTree p=Parent(T->lchild,e);
    if(p)   return p;
    //递归在右子树中找
    return Parent(T->rchild,e);
}

//操作7：返回e的左孩(不存在就返回空)
BiTree LeftChild(BiTree T,TElemType e){
    if(T==NULL) return NULL;
    if(T->data==e) return T->lchild;
    //递归左子树
    BiTree p=LeftChild(T->lchild,e);
    if(p) return p;
    //递归右子树
    return LeftChild(T->rchild,e);
}

//操作8：返回e的右孩(不存在就返回空)
BiTree RightChild(BiTree T,TElemType e){
    if(T==NULL) return NULL;
    if(T->data==e) return T->rchild;
    //递归左子树
    BiTree p=RightChild(T->lchild,e);
    if(p) return p;
    //递归右子树
    return RightChild(T->rchild,e);
}

//操作9：返回e的左兄弟(不存在就返回空)
/*核心逻辑：找到e的父亲 P
如果P->lchild==e → e是左孩子 → e没左兄弟 → 返回NULL
如果P->rchild==e → e是右孩子 → 左兄弟=P->lchild（可能为 NULL）*/
BiTree LeftSibling(BiTree T,TElemType e){
    BiTree p=Parent(T,e);   //找到e的双亲
    if(!p) return NULL; //e为根节点
    if(p->rchild&&p->rchild->data==e) return p->lchild;
    return NULL;
}

//操作10：返回e的右兄弟(不存在就返回空)
BiTree RightSibling(BiTree T,TElemType e){
    BiTree p=Parent(T,e);   //还是找e的双亲
    if(!p) return NULL;
    if(p->lchild&&p->lchild->data==e) return p->rchild;
    return NULL;
}

//操作11：二叉树子树插入操作
/*把一棵子树C插入到二叉树T中结点p的左或右子树位置上
先把p原来左（或右）子树挂接到C的最右子节点的右子树上(教材规定，不管是插入左子树还是右子树)
然后再把新得到的C挂到p的左（或右）子树上(p所指结点原有的左子树或右子树均成为C的右子树)
LR=0和LR=1分别对应插在p所指结点的左子树或右子树，C是一棵待插入的二叉树(也就是根节点指针)*/

//辅助函数：寻找指定值为e的结点(完完全全自己写的！)
BiTree FindNode(BiTree T,TElemType e){
    BiTree p;
    p=T;
    if(p==NULL) return NULL;
    if(p->data==e){
        return p;
    }else{
        p=FindNode(p->lchild,e);  //递归寻找左子树
        if(p) return p;
        return FindNode(p->rchild,e);   //递归右子树
    }
}

Status InsertChild(BiTree T,BiNode *p,int LR,BiTree C){
    if(T==NULL||p==NULL||C==NULL)return ERROR;
    BiTree temp=C;
    //找到C的最右子节点，如果C没有右子树，那temp就是C
    while(temp->rchild) temp=temp->rchild;  //擂台思想
    if(LR==0){  //在p所指结点的左子树插入C
        temp->rchild=p->lchild; //把p原来的左子树挂到C的最右子节点
        p->lchild=C;    //再把C挂到p的左子树
    }else{  //否则在p所指结点的右子树插入C
        temp->rchild=p->rchild;
        p->rchild=C;
    } 
    return OK;
}

//操作12：二叉树子树删除操作
//删除二叉树T中结点p的左（LR=0）或右（LR=1）子树，并释放这棵子树所有结点。

//辅助函数：释放子树
void FreeSubTree(BiTree &T){
    if(T==NULL) return;
    //利用递归，按先序遍历释放
    FreeSubTree(T->lchild);
    FreeSubTree(T->rchild);
    delete T;
    T=NULL;
}

Status DeleteChild(BiTree T,BiNode *p,int LR){
    if(T==NULL||p==NULL)return ERROR;
    if(LR==0){
        FreeSubTree(p->lchild);
        p->lchild=NULL;     //防御性代码(可选)
    }else{
        FreeSubTree(p->rchild);
        p->rchild=NULL; //防御性代码(可选)
    }
    return OK;
}

//操作13：遍历二叉树递归算法(分3类)(时间、空间复杂度都是O(n))
//前(先)序遍历二叉树
Status PreOrderTraverse(BiTree T){
    if(T==NULL)return ERROR;   //空二叉树直接返回
    else{
        visit(T);   //访问根节点
        //递归
        PreOrderTraverse(T->lchild); //递归遍历左子树
        PreOrderTraverse(T->rchild); //递归遍历右子树
    }
}

//中序遍历二叉树
Status InOrderTraverse(BiTree T){
    if(T==NULL)return ERROR;   //空二叉树直接返回
    else{
        //递归
        InOrderTraverse(T->lchild); //递归遍历左子树
        visit(T);   //访问根节点
        InOrderTraverse(T->rchild); //递归遍历右子树
    }
}
//后序遍历二叉树
Status PostOrderTraverse(BiTree T){
    if(T==NULL)return ERROR;   //空二叉树直接返回
    else{
        //递归
        PostOrderTraverse(T->lchild); //递归遍历左子树
        PostOrderTraverse(T->rchild); //递归遍历右子树
        visit(T);   //访问根节点
    }
}

//二叉树层次遍历
/*利用队列实现实现，让根节点入队，从现在开始，只要队列不为空，
就出队一个元素同时让出队元素的左右孩子入队直至队列为空为止，出队元素得到的序列便是层次遍历序列*/
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

//操作14：遍历二叉树的非递归算法

//中序遍历(利用栈实现)
//基本思想：建立一个栈,根节点进栈,遍历左子树,左子树为空则根节点出栈,输出根节点,遍历根节点的右子树
Status Stack_InOrderTraverse(BiTree T){
    BiTree p,q;
    SqStack S;
    InitStack(S);   //空栈
    p=T;    //指针变量p(初始指向整个二叉树的根节点)
    while(p||!StackEmpty(S)){   //只写栈不为空的条件会导致循环根本进不来，加个或p存在能进入循环且不影响!StackEmpty控制循环
        //因为最后循环结束条件是p为空且栈为空，也就是p存在或者栈不为空都不行
        if(p){  //只要节点还有左孩子，就会一直p=p->lchild;
            Push(S,p);
            p=p->lchild;
        }else{ //直到p没有左孩子
            Pop(S,q);   //将栈顶元素弹出,q指向出栈的元素
            cout<<q->data<<" "; //输出data域
            p=q->rchild;     //p指向出栈元素的右孩
        }
    }
    return OK;
}

//算法1：先序遍历复制二叉树
/*还是用递归：
    如果是空树，递归结束；
否则，申请新结点空间，复制根节点
    递归复制左子树
    递归复制右子树
*/
Status Copy(BiTree T,BiTree &NewT){    //将二叉树T复制到新二叉树NewT中
    //想不通可以自己画二叉树模拟一遍算法执行过程
    if(T==NULL){
        NewT=NULL;
        return 0;
    }else{
        /*递归终于想通了，就是一直先弄左子树，左子树没了就右子树，如果右子树也没，那这一层递归就结束了，
        但是这一层的看左和看右都还只是上一层的左！！！，这一层左右子树不存在递归结束也就是上一层递归的左结束，
        该到上一层的右递归了，依此类推*/
        NewT=new BiNode;    //创建节点
        NewT->data=T->data; //当前节点复制完成
        Copy(T->lchild,NewT->lchild);
        Copy(T->rchild,NewT->rchild);
    }
}

//算法2：计算二叉树结点总个数(递归)(这个一遍就想通了！天才)
//如果是空树，则节点个数为0；否则，结点个数为左子树的节点个数+右子树的节点个数再加+1(根节点)
Status NodeCount(BiTree T){
    if(T==NULL){
        return 0;
    }else{
        return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
    }
}

//算法3：计算二叉树叶子结点个数(这个也一遍就想通了)
//如果是空树，则叶子结点个数为0；否则，为左子树的叶子结点个数+右子树叶子结点个数
Status LeafCount(BiTree T){
    if(T==NULL) return 0;
    if(T->lchild==NULL&&T->rchild==NULL) return 1;  //关键步骤：左右孩都为空就是叶子结点，返回1
    else
        return LeafCount(T->lchild)+LeafCount(T->rchild);
}


//主函数测试
int main(){
    BiTree T;
    BiTree C;   //子树C
    InitBiTree(T);
    InitBiTree(C);
    string definitionT="1246###5##3##";   //定义：先序遍历序列
    string definitionC="78##9##";
    i=0;
    CreateBiTree(T,definitionT); //按照定义构造二叉树
    i=0;    //重置i
    CreateBiTree(C,definitionC); 

    int k=BiTreeDepth(T);
    cout<<"二叉树的深度为："<<k<<endl;
    BiTree p=Parent(T,4);
    cout<<"4的双亲为:"<<p->data<<endl;
    p=LeftChild(T,2);
    cout<<"2的左孩为:"<<p->data<<endl;
    p=RightChild(T,2);
    cout<<"2的右孩为:"<<p->data<<endl;
    p=LeftSibling(T,3);
    cout<<"3的左兄弟为:"<<p->data<<endl;
    int r=NodeCount(T);
    cout<<"二叉树结点总个数为："<<r<<endl;
    //先序遍历
    cout<<"先序遍历结果为："<<" ";
    PreOrderTraverse(T);
    cout<<endl;
    //中序遍历
    cout<<"中序遍历结果为："<<" ";
    InOrderTraverse(T);
    cout<<endl;
    //后序遍历
    cout<<"后序遍历结果为："<<" ";
    PostOrderTraverse(T);
    cout<<endl;

    //在T中结点2插入右子树C
    p=FindNode(T,2);
    InsertChild(T,p,1,C);
    //中序遍历
    cout<<"插入子树C后,中序遍历结果为："<<" ";
    Stack_InOrderTraverse(T);
    cout<<endl;
    int j=LeafCount(T);
    cout<<"叶子结点总个数为:"<<j<<endl;
    //删除T中2结点的左子树
    cout<<"删除T中2结点的左子树"<<endl;
    p=FindNode(T,2);
    DeleteChild(T,p,0);
    BiTree newT;
    Copy(T,newT);
    //中序遍历
    cout<<"对复制得到的二叉树中序遍历结果为："<<" ";
    InOrderTraverse(newT);
    cout<<endl;
    //对newT层次遍历
    cout<<"对复制得到的二叉树层次遍历结果为："<<" ";
    LevelOrder(newT);


    return 0;
}

