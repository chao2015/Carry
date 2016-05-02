 ///
 /// @file    search.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-01 23:29:54
 ///
#ifndef __MYFILE_H__
#define __MYFILE_H__

#include <iostream>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;
using std::multimap;

struct word_st{
	string word;//单词
	int atLine;//所在行
};

class MyFile{
public:
	MyFile();
	~MyFile();
	void file_read(const string&);//文本读取，将数据存进容器里
	void file_search(const string&);//文本查询，打印输出
	void file_write(string&);//输出词典到文件(单词-词频)
private:
	void line_handle(string&);//文本处理，非字母的字符全部替换为空格，可改进
private:
	struct word_st _Word;
	vector<string> _lineVec;//存储处理之前的原始文本行
	map<string,int> _freqMap;//存储单词-词频
	multimap<string,int> _lineMmap;//存储单词-所在行(为了保证行号的唯一性，注意在输出时做判断)
	//map<string,set<int> > _map;//方法2：可以用set<int>存储行号，自动去重，但是注意输出的词频set.size()也计少了
};

#endif
