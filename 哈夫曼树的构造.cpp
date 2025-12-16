//贪心算法之构造哈夫曼树:构造哈夫曼树时首先选择权值小的叶子结点

/*算法思路:n个权值,那就构造大小为2n的结构数组(0号位置不存元素),用来存最后哈夫曼树的2n-1个结点，
结构数组每个节点包含信息有(权值、双亲、左孩、右孩),其中下标1~n的位置存这初始n个带权值的节点,
然后从第n+1个结点开始,每次从当前结点的前面所有双亲为0(代表没有双亲)的结点中选取两个权值最小
结点构成一个新节点,新节点权值为二者权值之和,双亲为0,左孩和右孩分别是二者的下标
而被选取的两个节点的双亲变为新节点的下标,然后重复,从当前结点前面所有双亲为0的节点中选取两个权值最小的节点...
直至最后数组刚好被占满(1~2n-1都存了结点)且只有一个节点的双亲为0(即根节点),哈夫曼树构造完成
*/
/*合并步骤:需要依次合并HT[i],i=n+1,n+2,...,2n-1共n-1个结点
每次合并:a.对HT[i],在HT[1]~HT[i-1]中选取两个双亲为0且权值最小的节点HT[s1]和HT[s2]
b.HT[s1].parent=HT[s2].parent=i;即两个节点的双亲更改为当前新产生结点的下标
c.修改新产生结点和信息:
    HT[i].weight=HT[s1].weight+HT[s2].weight;
    HT[i].lch=s1;
    HT[i].rch=s2;
*/

#include<iostream>
using namespace std;

//一维结构数组的节点存储结构
typedef struct{
    int weight; //结点权值
    int parent,lch,rch;  //结点双亲、左孩、右孩下标
}HTNode,*HuffmanTree;

//辅助函数:从HT[1~n]中选出两个双亲为0且权值最小的节点
void Select(HuffmanTree HT,int n,int &a,int &b){
    //先随便找一个parent=0的作为最小
    a=0;
    for(int i=1;i<=n;++i){
        if(HT[i].parent==0){
            a=i;
            break;
        }
    }
    for(int i=1;i<=n;++i){
        if(HT[i].parent==0&&HT[i].weight<HT[a].weight){
            a=i;
        }
    }
    b=0;
    for(int i=1;i<=n;++i){
        if(HT[i].parent==0&&i!=a){  //i!=a是后加的而且是必须的(避免第一个parent为0的节点权值是最小的导致a和b都不更新最后a==b的情况)
            b=i;
            break;
        }
    }
    for(int i=1;i<=n;++i){
        if(HT[i].parent==0&&HT[i].weight<HT[b].weight&&i!=a){
            b=i;
        }
    }
}

//构造哈夫曼树
//三步:初始化、输入n个叶子结点的权值、进行n-1次合并(依次产生HT[i],i=n+1,n+2,...,2n-1共n-1个结点)
void CreateHuffmanTree(HuffmanTree &HT,int n){
    if(n<=1) return;
    int m=2*n-1;
    HT=new HTNode[m+1];//创建大小为2n的结构数组,由HT指向其基地址
    for(int i=1;i<=m;++i){  //将2n-1个元素初始化
        HT[i].lch=0;
        HT[i].rch=0;
        HT[i].parent=0;
    }
    for(int i=1;i<=n;++i){
        cin>>HT[i].weight;  //输入前n个元素的权值(已知)
    }
    //进行n-1次合并
    for(int i=n+1;i<=m;++i){
        int s1,s2;
        //Select函数,从HT的HT[1]~HT[i-1]中选出两个双亲为0且权值最小的节点,将下标分别以s1和s2返回
        Select(HT,i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        //修改新节点的信息
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight; 
    }
}

//主函数测试:
int main(){
    HuffmanTree HT;
    int n=5;
    CreateHuffmanTree(HT,5);
    for(int i=1;i<=2*n-1;++i){
        cout<<i<<" weight:"<<HT[i].weight<<" parent:"<<HT[i].parent<<" lch:"
        <<HT[i].lch<<" rch:"<<HT[i].rch<<endl;
    }

    return 0;
}