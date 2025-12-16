//寻找特定遍历序列中二叉树的节点的前驱和后继
/*利用空指针域:已知含有n个结点的二叉链表中，会有2n个指针域，有n-1个孩子(根节点除外)
对应会有n-1个指针域指向这些孩子，那么剩下的n+1个指针域就是空指针域，不指向任何节点，
我们就要利用这n+1个空指针域
具体方法:如果某一个节点没有左孩子，那么就把它的左指针域改为指向其前驱
        如果某一个节点没有右孩子，那么就把它的右指针域改为指向其后继
        这样，这种指向前驱或者后继的指针我们就称为"线索"
        加上了线索的二叉树就叫线索二叉树
        注：线索二叉树的前驱和后继是指的在某一种遍历序列中的前驱和后继而非实际二叉树的父节点和子树
        将二叉链表(表里前驱后继都存在了)转化为线索二叉树就叫线索化
为区分左右指针域到底指的是孩子还是前驱后继，给每个节点增设两个标志域ltag和rtag,值为0代表指的是孩子，
值为1代表指向前驱或者后继(ltag前驱,rtag后继)
可增设头结点(一般只在中序线索二叉树强调)，头结点ltag=0,lchild指向根节点，rtag=1,rchild指向遍历序列最后一个节点
遍历序列第一个节点的lchild和最后一个节点的rchild都指向头结点
作用:提供统一的起点
    提供统一的终点
    统一处理空树情况(即使树空，head->lchild=head->rchild=head,仍然满足循环)。
    让遍历能闭环（避免NULL指针）
*/

#include<iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0 
typedef int TElemType;
typedef int Status; //自定义返回类型

//线索二叉树存储结构(thread:线索)
typedef struct BiThrNode{
    TElemType data;
    int ltag,rtag;
    struct BiThrNode *lchild,*rchild;
}BiThrNode,*BiThrTree;



