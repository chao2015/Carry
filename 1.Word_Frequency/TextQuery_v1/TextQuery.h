 ///
 /// @file    search.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-01 23:29:54
 ///
#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using std::string;
using std::vector;
using std::map;
using std::set;
using std::ostream;
using std::ifstream;

class TextQuery{
public:
	typedef vector<string>::size_type lineNo;//line number,int型的描述性表达

	void read_file(ifstream& is){
		store_file(is);
		build_map();
	}
	set<lineNo> run_query(const string&) const;//返回行号
	string text_line(lineNo)const;//根据行号返回文本内容
	lineNo size()const{
		return _linesOfText.size();//获取文本总行数
	}
private:
	void store_file(ifstream&);
	void build_map();
private:
	vector<string> _linesOfText;//存储处理之前的原始文本行
	map<string,set<lineNo> > _wordMap;//像multimap一样在输出时做判
};
 
class QueryBase{
	friend class Query;//给Query句柄类授予友元关系，该类的成员将调用Query_base中的虚函数
protected:
	typedef TextQuery::lineNo lineNo;

	virtual ~QueryBase(){}
private:
	virtual set<lineNo> eval(const TextQuery&)const=0;//返回行数
	virtual ostream& display(ostream&)const=0;//输出结果
};

class Query{//句柄类，保存Query_base指针和使用计数指针
	friend Query operator~(const Query&);
	friend Query operator|(const Query&,const Query&);
	friend Query operator&(const Query&,const Query&);
public:
	Query(const string&);//builds a new WordQuery
	Query(const Query& c):_pQ(c._pQ),_pUse(c._pUse){
		++*_pUse;
	}
	~Query(){
		decr_use();
	}
	
	Query& operator=(const Query&);
	set<TextQuery::lineNo> eval(const TextQuery& t)const{
		return _pQ->eval(t);
	}
	ostream& display(ostream& os)const{
		return _pQ->display(os);
	}
private:
	Query(QueryBase* query):_pQ(query),_pUse(new std::size_t(1)){}

	QueryBase* _pQ;
	std::size_t* _pUse;//使用计数
	void decr_use(){
		if(--*_pUse==0){
			delete _pQ;
			delete _pUse;
		}
	}
};

inline Query& Query::operator=(const Query &rhs){
	++*rhs._pUse;
	decr_use();
	_pQ=rhs._pQ;
	_pUse=rhs._pUse;
	return *this;
}

inline ostream& operator<<(ostream& os,const Query &q){
	return q.display(os);
}

class WordQuery:public QueryBase{
	friend class Query;//Query uses the WordQuery constructor
	WordQuery(const string& s):_queryWord(s){}
	set<lineNo> eval(const TextQuery& t)const{
		return t.run_query(_queryWord);
	}
	ostream& display(ostream& os)const{
		return os<<_queryWord;
	}

	string _queryWord;
};

class NotQuery:public QueryBase{
	friend Query operator~(const Query&);
	NotQuery(Query q):_query(q){}
	set<lineNo> eval(const TextQuery&)const;
	ostream& display(ostream& os)const{
		return os<<"~("<<_query<<")";
	}
	const Query _query;
};

inline Query::Query(const string& s):
_pQ(new WordQuery(s)),_pUse(new std::size_t(1)){}

class BinaryQuery:public QueryBase{//抽象类
protected:
	BinaryQuery(Query left,Query right,string op)
	:_lhs(left),_rhs(right),_oper(op){}
	ostream& display(ostream& os)const{
		return os<<"("<<_lhs<<" "<<_oper<<" "<<_rhs<<")";
	}

	const Query _lhs,_rhs;
	const string _oper;
};

class AndQuery:public BinaryQuery{
	friend Query operator&(const Query&,const Query&);
	AndQuery(Query left,Query right):BinaryQuery(left,right,"&"){}
	set<lineNo> eval(const TextQuery&)const;
};

class OrQuery:public BinaryQuery{
	friend Query operator|(const Query&,const Query&);
	OrQuery(Query left,Query right):BinaryQuery(left,right,"|"){}
	set<lineNo> eval(const TextQuery&)const;
};

inline Query operator&(const Query& lhs,const Query& rhs){
	return new AndQuery(lhs,rhs);
}
inline Query operator|(const Query& lhs,const Query& rhs){
	return new OrQuery(lhs,rhs);
}
inline Query operator~(const Query& oper){
	return new NotQuery(oper);
}

//void print_results(const set<TextQuery::lineNo>&,const string&,const TextQuery&);
void print_results(const set<TextQuery::lineNo>&,const TextQuery&);
ifstream& open_file(ifstream&,const string&);

#endif
