 ///
 /// @file    quick.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-02 18:43:43
 ///
 ///快速排序：挖坑填数，分治法 
#include <iostream>
using std::endl;
using std::cout;

void qSort(int* elem,int low,int high){
	if(low>=high)
		return;
	//1.挖坑填数
	int first=low;
	int last=high;
	int key=elem[first];//用第一个数作为中轴，挖一个坑
	while(first<last){
		while(first<last && elem[last]>=key)
			--last;
		elem[first]=elem[last];//从高端开始向前，将比中轴小的数移动到之前的坑（低端）
		while(first<last && elem[first]<=key)
			++first;
		elem[last]=elem[first];//从低端开始向后，将比中轴大的数移动到上一个坑（高端）
	}
	elem[first]=key;//中轴数记录到遗留下来的坑
	//2.分治法
	qSort(elem,low,first-1);
	qSort(elem,first+1,high);
}

int main(){
	int elem[]={5,4,3,2,1,6,7,8,9,0};
	qSort(elem,0,sizeof(elem)/sizeof(elem[0])-1);
	for(int i=0;i!=sizeof(elem)/sizeof(elem[0]);++i){
		cout<<elem[i]<<" ";
	}
	cout<<endl;
}
