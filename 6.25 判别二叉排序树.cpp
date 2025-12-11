#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct BiNode {
    string data;
    BiNode *lchild, *rchild;
} BiNode, *BiTree;

// 中序遍历存入数组
void InorderTraverse(BiTree T, vector<string> &arr) {
    if (!T) return;
    InorderTraverse(T->lchild, arr);
    arr.push_back(T->data);
    InorderTraverse(T->rchild, arr);
}

// 判断是否为二叉排序树
//二叉排序树中序遍历得到的序列一定是非递减的
bool isBST(BiTree T) {
    vector<string>arr;
    InorderTraverse(T, arr);

    // 判断是否非递减序列
    for(int i=1;i<arr.size();i++) {
        if (arr[i]<arr[i-1])     
            return false;
    }
    return true;
}

// 创建节点
BiTree newNode(string e) {
    BiTree p=new BiNode;
    p->data=e;
    p->lchild=p->rchild=NULL;
    return p;
}

int main() {
    //构造一个二叉排序树
    BiTree p=newNode("mc");
    p->lchild=newNode("m");
    p->rchild=newNode("t");
    p->lchild->lchild=newNode("a");
    p->lchild->rchild=newNode("ma");

    if (isBST(p))
        cout<<"是二叉排序树"<<endl;
    else
        cout<<"不是二叉排序树"<<endl;

    return 0;
}
