/*普通树：一个节点的孩子分两类，最左边的孩子，其余的右边的孩子全部称为最左边那个孩子的兄弟，
兄弟不由双亲指示，而是由最左边的那个孩子指示*/

#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int TElemType;
typedef int Staus;

typedef struct CSNode{
    int data;
    CSNode *firstchild; //最左边的那个孩子
    CSNode *nextsibling;    //其余的右边的孩子全称为兄弟
}CSNode,*CSTree;

//创建节点函数
CSTree newNode(TElemType e){
    CSTree p=new CSNode;
    p->data=e;
    p->firstchild=p->nextsibling=NULL;
    return p;
}

//为结点node添加孩子child
void addChild(CSTree node,CSTree child){
    if(node->firstchild==NULL){
        node->firstchild=child;
    }else{
        CSTree p;
        p=node->firstchild;
        //一直寻找直到找到最右边的兄弟
        while(p->nextsibling){
        p=p->nextsibling;
        }
        p->nextsibling=child;
    }
}


//求深度(递归)
int TreeDepth(CSTree T){
    if(T==NULL)return ERROR;
    int childDepth=TreeDepth(T->firstchild);    //子树深度
    int siblingDepth=TreeDepth(T->nextsibling);     //兄弟深度

    return max(1+childDepth,siblingDepth);
}

//求叶子节点数
int LeafCount(CSTree T){
    if(T == NULL) return 0;

    if(T->firstchild == NULL) 
        return 1;   // 没有孩子就是叶子

    // 递归求所有孩子的叶子数
    int count = 0;
    for(CSTree child = T->firstchild; child; child = child->nextsibling){
        count += LeafCount(child);
    }
    return count;
}


//主函数测试
int main(){
    //构建树
    CSTree T;
    T=newNode(1);

    //1的四个孩子: 2 3 4 5
    addChild(T,newNode(2));
    addChild(T,newNode(3));
    addChild(T,newNode(4));
    addChild(T,newNode(5));
    
    //让4有3个孩子: 6 7 8
    CSTree D = T->firstchild->nextsibling->nextsibling;
    addChild(D,newNode(6));
    addChild(D,newNode(7));
    addChild(D,newNode(8));

    int k=TreeDepth(T);
    cout<<"树的深度为："<<k<<endl;
    int t=LeafCount(T);
    cout<<"叶子结点数目为:"<<t<<endl;

    return 0;
}