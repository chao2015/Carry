 ///
 /// @file    heapsort.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-01 10:34:26
 ///
 
#include <iostream>
#include <algorithm>
#include <vector>
using std::swap;
using std::vector;
using std::endl;
using std::cout;

template <typename T>
void mySwap(T& elem1,T& elem2){
	T temp=elem1;
	elem1=elem2;
	elem2=temp;
	//elem1=elem1^elem2;
	//elem2=elem1^elem2;
	//elem1=elem1^elem2;
}
//大根堆
template <typename T>
void maxHeapify(T& elem,int size,int parent){
	int lchild=parent*2+1;
	int rchild=lchild+1;
	while(rchild<size){
		if(elem[parent]>=elem[lchild] && elem[parent]>=elem[rchild]){
			return;
		}
		if(elem[lchild]<=elem[rchild]){
			//swap(elem[parent],elem[rchild]);//parent和最大的交换
			mySwap(elem[parent],elem[rchild]);
			parent=rchild;
		}else{
			//swap(elem[parent],elem[lchild]);
			mySwap(elem[parent],elem[lchild]);
			parent=lchild;
		}
		lchild=parent*2+1;
		rchild=lchild+1;
	}
	if(lchild<size && elem[parent]<elem[lchild])
		//swap(elem[parent],elem[lchild]);
		mySwap(elem[parent],elem[lchild]);


}

//整理节点,小根堆
template <typename T>
void minHeapify(T& elem ,int size,int parent){
	int lchild=elem*2+1;
	int rchild=lchild+1;
	while(rchild<size){//子树均在范围内
		if(elem[parent]<=elem[lchild] && elem[parent]<=elem[rchild]){//如果比左右子树都小，完成整理
			return;
		}
		if(elem[lchild]<=elem[rchild]){//如果左子树最小，左子树与父亲交换
			swap(elem[parent],elem[lchild]);
			parent=lchild;
		}else{//如果右字数最小，右子树与父亲交换
			swap(elem[parent],elem[rchild]);
			parent=rchild;
		}
		lchild=elem*2+1;//重新计算子树的位置
		rchild=lchild+1;
	}
	if(lchild<size && elem[lchild]<elem[parent]){//只有左子树且小于父亲时
		swap(elem[lchild],elem[parent]);
	}
}

template <typename T>
void heapSort(T& elem,int size){
	int i;
	for(i=size-1;i>=0;i--){//从子树开始整理，得到的结果是:根为最小值
		//minHeapify(elem,size,i);
		maxHeapify(elem,size,i);
	}
	while(size>0){//拆除树
		//swap(elem[size-1],elem[0]);//将根与数组最末交换，最小值放到数组最末
		mySwap(elem[size-1],elem[0]);
		size--;//剔除排列好的最小值
		//minHeapify(elem,size,0);//针对剩下的元素来整理树，每次都排序一个最小值出来，最后得到的数组从大到小排列
		maxHeapify(elem,size,0);
	}
}

int main(){
	int num[10]={5,4,3,2,1,6,7,8,9,0};
	vector<int> vec(num,num+10);
	heapSort(vec,10);
	vector<int>::iterator it;
	for(it=vec.begin();it!=vec.end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;

	vector<std::string> strVec={"Hello","World","Chen","Chao","!"};
	heapSort(strVec,strVec.size());
	for(auto & elem:strVec){
		cout<<elem<<" ";
	}
	cout<<endl;

}
