 ///
 /// @file    main1.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-08 21:02:28
 ///
#include "TextQuery.h" 
#include <iostream>
#include <fstream>
using std::ifstream;
using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::string;

int main(int argc,char **argv){
	ifstream infile;
	if(argc<2 || !open_file(infile,argv[1])){
		cerr<<"No input file!"<<endl;
		return EXIT_FAILURE;
	}
	TextQuery tq;
	tq.read_file(infile);
	//Query q=Query("the") & Query("a");
	//cout<<"\nExecuted query:"<<q<<endl;
	//set<TextQuery::lineNo> locates=q.eval(tq);
	//print_results(locates,tq);
#if 1
	while(true){
		cout<<"快点输入要查的单词(支持& | ~查询):"<<endl;
		string s1,s2,s3;
		cin>>s1;
		if(!cin)
			continue;
		if("~"==s1 && cin){
			cin>>s2;
			Query q=~Query(s2);
			cout<<"Executed query:"<<q<<endl;
			set<TextQuery::lineNo> locates=q.eval(tq);
			print_results(locates,tq);
			//Query q=s1;
			//cout<<"Executed query:"<<q<<endl;
			//set<TextQuery::lineNo> locates=q.eval(tq);
			//print_results(locates,tq);
		}else{
			cin>>s2;
			if("&"==s2){
				cin>>s3;
				Query q=Query(s1) & Query(s3);
				cout<<"Executed query:"<<q<<endl;
				set<TextQuery::lineNo> locates=q.eval(tq);
				print_results(locates,tq);
			}else if("|"==s2){
				cin>>s3;
				Query q=Query(s1) | Query(s3);
				cout<<"Executed query:"<<q<<endl;
				set<TextQuery::lineNo> locates=q.eval(tq);
				print_results(locates,tq);
			}else{
				cout<<"你输错了吧！(确认以正确的格式输入,如:a & b, a | b, ~ a)."<<endl;
			}
		}
	}
#endif
	return 0;
}
