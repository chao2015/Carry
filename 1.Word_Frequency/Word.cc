#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iterator>
#include <map>
#include <stdlib.h>
using namespace std;

class Word{
	vector<string> vec;
	map<string,int> words;
public:
	void read_file(const string filename);
	void write_file(const string filename);
	void show();//标准流输出单词的词频
};

void Word::show(){
	map<string,int>::iterator mapit=words.begin();
	for(mapit;mapit!=words.end();++mapit){
		cout<<mapit->first<<" "<<mapit->second<<endl;
	}
}

void Word::write_file(const string filename){
	const char *pfilename=filename.c_str();
	ofstream ofs(pfilename,std::ios::out);
	if(!ofs.good()){
		cout<<"write file failed, program exited!"<<endl;
		exit(-1);
	}

	map<string,int>::iterator mapit=words.begin();
	for(mapit;mapit!=words.end();++mapit){
		ofs<<mapit->first<<" "<<mapit->second<<endl;
	}
}

void Word::read_file(const string filename){
	const char* pfilename=filename.c_str();//str.c_str()可以转化成const char*类型
	ifstream ifs(pfilename,std::ios::in);
	if(!ifs.good()){
		cout<<"read file failed, program exited!"<<endl;
		exit(-1);
	}
	string str;
	while(!ifs.eof()){
		ifs>>str;	//以空格、换行符和tab为截断标志，该方法好！
		if(!isdigit(str[0])){
			vec.push_back(str);
		}
	}
	//for(int i=0;i<vec.size();++i){
	//	cout<<vec[i]<<endl;
	//}
	//copy(vec.begin(),vec.end(),ostream_iterator<string>(cout," "));
	
	//word sort:	
	vector<string>::iterator it=vec.begin();
	for(it;it!=vec.end();++it){
		//用find函数定位数据出现的位置，返回一个迭代器。如果map中没有要查找的数据，返回：end函数返回的迭代器。
		if(words.find(*it)!=words.end()){
			int i=words[*it];	//找到单词对应的int型，赋值给i
			++i;	//i计数+1；
			words[*it]=i;	//再把i值赋给该单词对应的int型
		}
		else{//如果map里没找到*it指向的单词，则插入，对应的int型初始化为1
			words.insert(map<string,int>::value_type(*it,1));//insert:*it存在的话插入无效
		}
	}
}

int main(int argc, char** argv){
	//start for example:./a.out the_holy_bible.txt test.txt
	Word mywords;
	mywords.read_file(argv[1]);
	mywords.write_file(argv[2]);
	mywords.show();
	return 0;
}
