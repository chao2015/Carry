 ///
 /// @file    search.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-01 13:08:28
 ///

#include "MyFile.h"
#include <ctype.h>
#include <stdlib.h> 
#include <iostream>
#include <sstream>
#include <fstream>
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::pair;

MyFile::MyFile(){
	cout<<"快输入要查看的文件名："<<endl;
}

MyFile::~MyFile(){
	cout<<"终于结束了！"<<endl;
}

void MyFile::file_write(string& fileName){
	string appName="(WordFrequency)";
	ofstream ofs((appName+fileName).c_str(),std::ios::out);
	if(!ofs.good()){
		cout<<"write file failed,program exited!"<<endl;
		exit(-1);
	}
	map<string,int>::iterator mit;
	for(mit=_freqMap.begin();mit!=_freqMap.end();++mit){
		ofs<<mit->first<<" "<<mit->second<<endl;
	}
	ofs.close();
}

void MyFile::file_search(const string& wordName){
	multimap<string,int>::iterator mmit=_lineMmap.lower_bound(wordName);
	cout<<wordName<<" occurs "<<_freqMap[wordName]<<" times."<<endl;
	int distinct=mmit->second;//存储上一个输出的行号，通过判断达到给输出的行号去重的目的
	bool flag=false;//控制从第二次进循环开始做上述判断
	for(mmit=_lineMmap.lower_bound(wordName);mmit!=_lineMmap.upper_bound(wordName);++mmit){
		if(flag && distinct==mmit->second)
			continue;
		cout<<"    (line "<<mmit->second<<") ";
		cout<<_lineVec[mmit->second-1]<<endl;
		distinct=mmit->second;
		flag=true;
	}
}

void MyFile::file_read(const string& fileName){
	ifstream ifs(fileName.c_str(),std::ios::in);
	if(!ifs.good()){
		cout<<"read file failed,program exited!"<<endl;
		exit(-1);
	}
	string line;
	int i=0;
	while(getline(ifs,line)){
		++i;
		_lineVec.push_back(line);//要在line_handle()之前
		line_handle(line);
		istringstream iss(line);
		while(iss>>_Word.word){
			_Word.atLine=i;
			_lineMmap.insert(pair<string,int>(_Word.word,_Word.atLine));
		
			if(_freqMap.find(_Word.word)!=_freqMap.end()){
				++_freqMap[_Word.word];
			}else{
				_freqMap.insert(pair<string,int>(_Word.word,1));
			}
		}
	}
	ifs.close();
}

void MyFile::line_handle(string& line){
	for(int i=0;i!=line.size();++i){
		if(!isalpha(line[i]))
			line[i]=' ';
	}
}

int main(){
	MyFile myfile;
	string fileName;
	getline(cin,fileName);
	myfile.file_read(fileName);
	myfile.file_write(fileName);
	bool flag=true;
	while(flag){
		cout<<"快输入要搜索的单词(ctrl+d结束)："<<endl;
		string wordName;
		getline(cin,wordName);
		if(cin.eof())
			flag=false;
		else
			myfile.file_search(wordName);
	}
	return 0;
}
