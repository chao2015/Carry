 ///
 /// @file    qsort.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-05 00:49:53
 ///
 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

//在模板函数中如果出现:T key=elem[first];类似的赋值语句时，会暴露出容器和数组类型不兼容的问题.
//因为参数是容器时必须传递引用，此时T代表容器的对象类型或者是*elem.
//解决方案1:多定义一个模板参数S，S的作用是引进一个类型来兼容数组指针的问题(但是为此多加一个形参的方式略显鸡肋)；
//解决方案2:写两个特化的函数模板，分别针对数组和容器.
/* argv[1]=数组地址或者容器名;
 * argv[2]=0(首数据的下标);
 * argv[3]=size-1(尾数据的下标);
 * argv[4]=elem[0](第一个数据对象); */
template <typename T,typename S>
void qSort(T& elem,int low,int high,S s){
	if(low>=high)
		return;
	int first=low;//保留low数据
	int last=high;//保留high数据，为了后续递归时使用
	S key=elem[first];//挖第一个坑
	while(first<last){
		while(first<last && elem[last]>=key)
			--last;
		elem[first]=elem[last];//填上一个坑,留下一个新坑
		while(first<last && elem[first]<=key)
			++first;
		elem[last]=elem[first];//填坑留坑
	}
	elem[first]=key;//填最后一坑

	qSort(elem,low,first-1,s);
	qSort(elem,first+1,high,s);
}

int main(){
	int elem[]={5,6,7,8,9,0,1,2,3,4};
	qSort(elem,0,9,elem[0]);
	for(int i=0;i<10;++i){
		cout<<elem[i]<<" ";
	}
	cout<<endl;
	
	vector<int> elem1={5,6,7,8,9,0,1,2,3,4};
	qSort(elem1,0,elem1.size()-1,elem1[0]);
	vector<int>::iterator it1;
	for(it1=elem1.begin();it1!=elem1.end();++it1){
		cout<<*it1<<" ";
	}
	cout<<endl;
	
	vector<string> elem2={"hello","world","chen","chao","nihao","!"};
	qSort(elem2,0,elem2.size()-1,elem2[0]);
	vector<string>::iterator it2;
	for(it2=elem2.begin();it2!=elem2.end();++it2){
		cout<<*it2<<" ";
	}
	cout<<endl;
}
