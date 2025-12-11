//默认为大根堆，已知(k1,k2,...kp)是堆，编写将(k1,k2,...kp,kp+1)调整为堆的算法
//新增元素kp+1只有应从叶子向根的方向进行调整
//思路：新元素插入到最后，然后不断与父节点比较，只要它比父节点大，就交换两结点位置，直到不能再上升为止

#include <iostream>
using namespace std;

#define MAXSIZE 100

struct Node {
    int data;
    Node *left;
    Node *right;
    Node *parent;
};

// 创建节点
Node* newNode(int x){
    Node* p=new Node;
    p->data=x;
    p->left=p->right=p->parent=NULL;
    return p;
}

// 上滤（大根堆）
void siftUp(Node* node){
    while(node->parent && node->data > node->parent->data){
        // 交换值即可（不换指针）
        int t=node->data;
        node->data=node->parent->data;
        node->parent->data=t;

        node=node->parent;
    }
}

//插入（按完全二叉树结构）
void insert(Node* &root, int x){
    Node* n=newNode(x);

    if(root==NULL){
        root=n;
        return;
    }

    // 用数组模拟层次遍历队列
    Node* q[MAXSIZE];
    int front=0, rear=0;
    q[rear++]=root;
    while(front<rear){
        Node* cur=q[front++];
        if(cur->left==NULL){
            cur->left=n;
            n->parent=cur;
            break;
        } else {
            q[rear++]=cur->left;
        }
        if(cur->right==NULL){
            cur->right=n;
            n->parent=cur;
            break;
        } else {
            q[rear++]=cur->right;
        }
    }

    // 上滤
    siftUp(n);
}

//层次输出
void levelPrint(Node* root){
    if(!root) return;

    Node* q[MAXSIZE];
    int front=0, rear=0;

    q[rear++]=root;

    while(front<rear){
        Node* cur=q[front++];
        cout<<cur->data<<" ";

        if(cur->left) q[rear++]=cur->left;
        if(cur->right) q[rear++]=cur->right;
    }
    cout<<endl;
}

int main(){
    Node* root=NULL;

    insert(root, 50);
    insert(root, 30);
    insert(root, 40);
    insert(root, 10);
    insert(root, 20);

    cout<<"初始堆层次遍历："<<endl;
    levelPrint(root);

    cout<<"插入45后:"<<endl;
    insert(root,45);
    levelPrint(root);

    return 0;
}
