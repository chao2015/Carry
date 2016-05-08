 ///
 /// @file    search.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-01 13:08:28
 ///

#include "TextQuery.h"
#include <iostream>
#include <fstream>
#include <algorithm>//set_intersection
using std::cerr;
using std::cout;
using std::endl;
using std::cin;
using std::istringstream;
using std::string;

set<TextQuery::lineNo> OrQuery::eval(const TextQuery& file)const{
	set<lineNo> right=_rhs.eval(file);
	set<lineNo> ret_lines=_lhs.eval(file);
	ret_lines.insert(right.begin(),right.end());
	return ret_lines;
}

set<TextQuery::lineNo> AndQuery::eval(const TextQuery& file)const{
	set<lineNo> left=_lhs.eval(file);
	set<lineNo> right=_rhs.eval(file);
	set<lineNo> ret_lines;
	set_intersection(left.begin(),left.end(),right.begin(),right.end(),
			inserter(ret_lines,ret_lines.begin()));
	return ret_lines;
}

set<TextQuery::lineNo> NotQuery::eval(const TextQuery& file)const{
	set<TextQuery::lineNo> has_val=_query.eval(file);
	set<lineNo> ret_lines;
	for(TextQuery::lineNo n=0;n!=file.size();++n)
		if(has_val.find(n)==has_val.end())
			ret_lines.insert(n);
	return ret_lines;
}

string TextQuery::text_line(lineNo line)const{
	if(line<_linesOfText.size())
		return _linesOfText[line];
	throw std::out_of_range("line number out of range");
}

set<TextQuery::lineNo> TextQuery::run_query(const string& queryWord)const{
	map<string,set<lineNo> >::const_iterator loc=_wordMap.find(queryWord);
	if(loc==_wordMap.end())
		return set<lineNo>();//not found,return empty set
	else
		return loc->second;
}

void TextQuery::build_map(){
	for(lineNo line_num=0;line_num!=_linesOfText.size();++line_num){
		istringstream line(_linesOfText[line_num]);
		string word;
		while(line>>word)
			_wordMap[word].insert(line_num);
	}
}

void TextQuery::store_file(ifstream& is){
	string line;
	while(getline(is,line))
		_linesOfText.push_back(line);
}

ifstream& open_file(ifstream& in,const string &file){
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}
//判断并返回一个单词的单/复数版本
string make_plural(size_t ctr,const string& word,const string& ending){
	return (ctr==1) ? word : word+ending;
}

void print_results(const set<TextQuery::lineNo>& locates,const TextQuery& file){
	typedef set<TextQuery::lineNo> lineNums;
	lineNums::size_type size=locates.size();
	if(locates.empty()){
		cout<<"\nSorry.There are no entries for your query.\nTry again."<<endl;
		return;
	}
	cout<<"---------------------------------\n"
		<<"match occurs "
		<<size<<" "
		<<make_plural(size,"time","s")<<endl;
	lineNums::const_iterator it=locates.begin();
	for(;it!=locates.end();++it){
		cout<<"\t(line "
			<<(*it)+1<<") "
			<<file.text_line(*it)<<endl;
	}
}


