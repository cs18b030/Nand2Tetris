#include<bits/stdc++.h>
using namespace std;
//// APT COMENTS WRITTEN IN FUNCTIONS
fstream fin, fout, ferr; 
/// fin for input, fout for outpit and ferr for error file
string tok,error_file;
/// tok has the current token and error_file=file_name.err
int spaces=0;  ///used in printSpaces();
int token_check=0; /// used in some functions as some checks where input was already taken
void compileClass();
void compileClassVarDec();
void compileSubroutineDec();
void compileParameterList();
void compileSubroutineBody();
void compileVarDec();
void compileStatements();
void compileStatement();
void compileIfStatements();
void compileWhileStatements();
void compileDoStatements();
void compileLetStatements();
void compileReturnStatements();
void compileExpression();
void compileTerm();
void compileExpressionList();
void compileSubroutineCall();

void printspaces(){
    //prints number of spaces ='spaces'(global variable)
    for(int i=0; i<spaces; i++){
        fout<<" ";
    }
    return;
}
string eraseToken(string s){
    /// removes <..> and </..> from string (eg. <keyword> let </keyword> becomes "let")
    int i=s.find(">");
    s.erase(s.begin(),s.begin()+i+2);
    s.erase(s.end()-i-3,s.end());
    return s;
}
void getToken(){
    ///takes the next line as input(eg. tok="<keyword> let </keyword>")
    getline(fin, tok);
    return;
}
void print(){
    //print appropriate spaces(indentation)
    //and prints the input line
    printspaces();
    fout<<tok<<endl;
    return;
}
bool checkKeyword(string s){
    //checks if string s is a keyword
    if(s.substr(1,7)=="keyword")return true;
    else return false;
}
bool checkIdentifier(string s){
    //checks if string s is a identifier
    if(s.substr(1,10)=="identifier")return true;
    else return false;
}
bool checkSymbol(string s){
    //checks if string s is a symbol
    if(s.substr(1,6)=="symbol")return true;
    else return false;
}
bool checkType(string s){
    //return true if type is  int|char|boolean|classname(identifier)
    //else returns false
    if(s=="<keyword> int </keyword>")return true;
    if(s=="<keyword> char </keyword>") return true;
    if(s=="<keyword> boolean </keyword>")return true;
    if(checkIdentifier(tok)==true)return true;
    return false;
}
bool checkOperator(string s){
    if(s=="<symbol> + </symbol>") return true;
    if(s=="<symbol> - </symbol>") return true;
    if(s=="<symbol> * </symbol>") return true;
    if(s=="<symbol> / </symbol>") return true;
    if(s=="<symbol> &lt; </symbol>") return true;
    if(s=="<symbol> &gt; </symbol>") return true;
    if(s=="<symbol> = </symbol>") return true;
    if(s=="<symbol> &amp; </symbol>") return true;
    if(s=="<symbol> | </symbol>") return true;
    return false;
}
bool checkUnaryOp(string s){
    if(s=="<symbol> - </symbol>") return true;
    if(s=="<symbol> ~ </symbol>") return true;
    return false;
}
bool checkKeywordConstant(string s){
    if(s=="<keyword> true </keyword>") return true;
    if(s=="<keyword> false </keyword>") return true;
    if(s=="<keyword> null </keyword>") return true;
    if(s=="<keyword> this </keyword>") return true;
    return false;
}
bool checkIntegerConstant(string s){
    //checks if string s is a identifier
    if(s.substr(1,3)=="int")return true;
    else return false;
}
bool checkStringConstant(string s){
    //checks if string s is a identifier
    if(s.substr(1,3)=="str")return true;
    else return false;
}

void error(string correct_type,string correct_token){
    ////checks for correct type and token, if not prints error in error file and exits
    string current_type;
    string current_token=tok;
    current_token=eraseToken(current_token);
    if(checkIdentifier(tok)==true)current_type="identifier";
    else if(checkKeyword(tok)==true)current_type="keyword";
    else if(checkIntegerConstant(tok)==true)current_type="integerConstant";
    else if(checkStringConstant(tok)==true)current_type="stringConstant";
    else if(checkSymbol(tok)==true)current_type="symbol";
    if(correct_type==current_type){
        ///type matches
        if(correct_token!=current_token){
            ///but token does not matches
            ferr.open(error_file,ios::out);
            ferr<<"ERROR: "<<current_token<<endl;
            exit(-1);
        }
    }
    else{
        ///type mismatch
        ferr.open(error_file,ios::out);
        ferr<<"ERROR: Expecting <"<<correct_type<<"> but "<<current_token<<endl;
        exit(-1);
    }
    return;
}

/// getToken() takes in next token as input
// error(string ,string) checks for correct strings, i.e if incorrect, it generates an error file
// of the same file name and exits
// print() prints the current string with correct indentation using printSpaces();

void compileExpressionList(){
    printspaces();
    fout<<"<expressionList>"<<endl;
    spaces+=2;
    getToken();
    if(tok!="<symbol> ) </symbol>"){
        token_check=1;
        compileExpression();
        while(tok=="<symbol> , </symbol>"){
            print();
            compileExpression();
        }
        error("symbol",")");
    }
    spaces-=2;
    printspaces();
    fout<<"</expressionList>"<<endl;
    print();
    return;
}
void compileSubroutineCall(char c){
    if(c=='.'){
        getToken();
        string s=eraseToken(tok);
        error("identifier",s);
        print(); 
        getToken();
        error("symbol","(");
        print();
    }
    compileExpressionList();
    return;
}
void compileTerm(){
    printspaces();
    fout<<"<term>"<<endl;
    spaces+=2;
    int check=0;
    if(token_check==1){
        token_check=0;
    }
    else if(token_check==0){
        getToken();
    }

    if(checkIntegerConstant(tok)==true || checkStringConstant(tok)==true || checkKeywordConstant(tok)==true){
        print();
        getToken();
        check=1;
    }
    else if(checkIdentifier(tok)==true){
        check=1;
        print();
        getToken();
        if(tok=="<symbol> [ </symbol>"){
            print();
            compileExpression();
            error("symbol","]");
            print();
            getToken();
        }
        else if(tok=="<symbol> . </symbol>"){
            print();
            compileSubroutineCall('.');
            getToken();
        }
        else if(tok=="<symbol> ( </symbol>"){
            print();
            compileSubroutineCall('(');
            getToken();
        }

    }
    else if(tok=="<symbol> ( </symbol>"){
        check=1;
        print();
        compileExpression();
        error("symbol",")");
        print();
        getToken();
    }
    else if(checkUnaryOp(tok)==true){
        check=1;
        print();
        compileTerm();
    }
    if(check==0){
        ferr.open(error_file,ios::out);
        ferr<<"Syntax error: <Term> expected"<<endl;
        exit(-1);
    }
    spaces-=2;
    printspaces();
    fout<<"</term>"<<endl;
    return;
}


void compileExpression(){/// input already taken when function ends
    printspaces();
    fout<<"<expression>"<<endl;
    spaces+=2;
    compileTerm();
    if(checkOperator(tok)==true){
        print();
        compileTerm();
    }
    spaces-=2;
    printspaces();
    fout<<"</expression>"<<endl;
    return;
}

void compileDoStatement(){
    printspaces();
    fout<<"<doStatement>"<<endl;
    spaces+=2;
    print(); /// do
    getToken();
    string s=eraseToken(tok);
    error("identifier",s);
    print();  ///identifier
    getToken();
    if(tok=="<symbol> . </symbol>"){
        print();
        compileSubroutineCall('.');
    }
    else if(tok=="<symbol> ( </symbol>"){
        print();
        compileSubroutineCall('(');
    }
    else{
        ferr.open(error_file,ios::out);
        ferr<<"ERROR: <symbol> expected"<<endl;
        exit(-1);
    }
    getToken();
    error("symbol",";");
    print();
    getToken();
    spaces-=2;
    printspaces();
    fout<<"</doStatement>"<<endl;
    return;
}
void compileReturnStatement(){
    printspaces();
    fout<<"<returnStatement>"<<endl;
    spaces+=2;
    print(); /// return;
    getToken();
    if(tok!="<symbol> ; </symbol>"){
        token_check=1;
        compileExpression();
        error("symbol",";");
        print(); // ;
    }
    else{
        print(); // ;
    }
    getToken();
    spaces-=2;
    printspaces();
    fout<<"</returnStatement>"<<endl;
    return;
}

void compileIfStatement(){///CHECKED!!!
    printspaces();
    fout<<"<ifStatement>"<<endl;
    spaces+=2;
    print();  // if
    getToken();
    error("symbol","(");
    print(); /// (
    compileExpression();
    error("symbol",")");
    print();//// )
    getToken();
    error("symbol","{");
    print(); /// {
    getToken();
    compileStatements();
    error("symbol","}");
    print(); /// }
    getToken();
    if(tok=="<keyword> else </keyword>"){
        print();
        getToken();
        error("symbol","{");
        print(); /// {
        getToken();
        compileStatements();
        error("symbol","}");
        print(); /// }
        getToken();
    }
    spaces-=2;
    printspaces();
    fout<<"</ifStatement>"<<endl;
    return;
}
void compileWhileStatement(){////CHECKED!!
    printspaces();
    fout<<"<whileStatement>"<<endl;
    spaces+=2;
    print();  ////while
    getToken();
    error("symbol","(");
    print(); /// (
    compileExpression();
    error("symbol",")");
    print();//// )
    getToken();
    error("symbol","{");
    print(); /// {
    getToken();
    compileStatements();
    error("symbol","}");
    print(); /// }
    getToken();
    spaces-=2;
    printspaces();
    fout<<"</whileStatement>"<<endl;
    return;
}

void compileLetStatement(){ ////CHECKED!!!
    printspaces();
    fout<<"<letStatement>"<<endl;
    spaces+=2;
    print(); //let
    getToken();
    string s=eraseToken(tok);
    error("identifier",s);
    print();///identifier
    getToken();
    if(tok=="<symbol> [ </symbol>"){
        print();  // [
        compileExpression();
        error("symbol","]");
        print();  /// ]
        getToken();
    }
    error("symbol","=");
    print(); //// =
    compileExpression(); ///  expression
    error("symbol",";");
    print();  /// ;
    spaces-=2;
    printspaces();
    fout<<"</letStatement>"<<endl;
    getToken();
    return;
}

void compileStatement(){
    if(tok=="<keyword> let </keyword>")
        compileLetStatement();
    else if(tok=="<keyword> if </keyword>")
        compileIfStatement();
    else if(tok=="<keyword> while </keyword>")
        compileWhileStatement();
    else if(tok=="<keyword> do </keyword>")
        compileDoStatement();
    else if(tok=="<keyword> return </keyword>")
        compileReturnStatement();
    else {return;}
    // input already taken in the all the five above functions
    compileStatement();
}

void compileStatements(){
    printspaces();
    fout<<"<statements>"<<endl;
    spaces+=2;
    compileStatement();
    spaces-=2;
    printspaces();
    fout<<"</statements>"<<endl;
    return;
}

void compileVarDec(){
    getToken();
    if(tok=="<keyword> var </keyword>"){
        printspaces();
        fout<<"<varDec>"<<endl;
        spaces+=2;
        print();
        getToken();
        if(checkType(tok)==false){
            ferr.open(error_file,ios::out);
            ferr<<"Syntax error: <Type> expected"<<endl;
            exit(-1);
        }
        print();
        getToken();
        string s=eraseToken(tok);
        error("identifier",s);
        print();
        getToken();
        while(tok=="<symbol> , </symbol>"){
            print();
            getToken();
            string s=eraseToken(tok);
            error("identifier",s);
            print();
            getToken();
        }
        error("symbol",";");
        print();
        spaces-=2;
        printspaces();
        fout<<"</varDec>"<<endl;
        compileVarDec();
    }
    else return;
}

void compileSubroutineBody(){
    printspaces();
    fout<<"<subroutineBody>"<<endl;
    spaces+=2;
    getToken();
    error("symbol","{");
    print();
    compileVarDec();
    ///input alreadt taken
    compileStatements();
    //input already taken
    error("symbol","}");
    print();
    spaces-=2;
    printspaces();
    fout<<"</subroutineBody>"<<endl;
    return;
}
void compileParameterList(){
    getToken();
    error("symbol","(");
    print();
    printspaces();
    fout<<"<parameterList>"<<endl;
    spaces+=2;
    getToken();
    if(tok!="<symbol> ) </symbol>"){
        if(checkType(tok)==false){
            ferr<<"Syntax error: <Type> expected"<<endl;
            exit(-1);
        }
        print();
        getToken();
        string s=eraseToken(tok);
        error("identifier",s);
        print();
        getToken();
        while(tok=="<symbol> , </symbol>"){
            print();
            getToken();
            if(checkType(tok)==false){
                ferr<<"Syntax error: <Type> expected"<<endl;
                exit(-1);
            }
            print();
            getToken();
            string s=eraseToken(tok);
            error("identifier",s);
            print();
            getToken();
        }
        error("symbol",")");
    }spaces-=2;
    printspaces();
    fout<<"</parameterList>"<<endl;
    print();
    return;
}
void compileSubroutineDec(){
    printspaces();
    fout<<"<subroutineDec>"<<endl;
    spaces+=2;
    print();
    getToken();
    if(tok!="<keyword> void </keyword>" && checkType(tok)==false){
        ferr.open(error_file,ios::out);
        ferr<<"ERROR: <void> or <type> expected"<<endl;
        exit(-1);
    }
    print();
    getToken();
    string s=eraseToken(tok);
    error("identifier",s);
    print();  ///print identifier

    compileParameterList();
    compileSubroutineBody();

    spaces-=2;
    printspaces();
    fout<<"</subroutineDec>"<<endl;
    getToken();
    if(checkKeyword(tok)==true && (tok.find("constructor")!=string::npos || tok.find("method")!=string::npos || tok.find("function")!=string::npos)){
        compileSubroutineDec();
    }
    else return;
}

void compileClassVarDec(){
    printspaces();
    fout<<"<classVarDec>"<<endl;
    spaces+=2;
    print();
    getToken();
    if(checkType(tok)==false){
        ferr.open(error_file,ios::out);
        ferr<<"ERROR: <Type> expected"<<endl;
        exit(-1);
    }
    print();
    getToken();
    string s=eraseToken(tok);
    error("identifier",s);
    print();
    getToken();
    while(tok=="<symbol> , </symbol>"){
        print();
        getToken();
        string s=eraseToken(tok);
        error("identifier",s);
        print();
        getToken();
    }
    error("symbol",";");
    print();
    spaces-=2;
    printspaces();
    fout<<"</classVarDec>"<<endl;
    getToken();
    if(checkKeyword(tok)==true && (tok.find("static")!=string::npos || tok.find("field")!=string::npos)){
       compileClassVarDec();
    }
    else return;
}

void compileClass(){
    printspaces();
    fout<<"<class>"<<endl;
    spaces+=2;
    getToken();
    error("keyword","class");
    print();
    getToken();
    string s=eraseToken(tok);
    error("identifier",s);
    print();
    getToken();
    error("symbol","{");
    print();
    getToken();
    if(checkKeyword(tok)==true && (tok.find("static")!=string::npos || tok.find("field")!=string::npos)){
        compileClassVarDec();
    }
    if(checkKeyword(tok)==true && (tok.find("constructor")!=string::npos || tok.find("method")!=string::npos || tok.find("function")!=string::npos)){
        compileSubroutineDec();
    }
    error("symbol","}");
    print();
    spaces-=2;
    fout<<"</class>"<<endl;
    return;
}

int main(int argc, char* argv[]){
    for(int ii=2; ii<argc; ii++){
        string s=argv[ii];
        int f=s.find(".");
        s.erase(f);
        string s1, s2;
        s1=s+"T.xml";
        s2=s+".xml";
        error_file=s+".err";
        fin.open(s1);
        fout.open(s2,ios::out);
        getToken();
        if(tok!="<tokens>"){
            ferr<<"Syntax error: <tokens> expected"<<endl;
            exit(-1);
        }
        else {
            compileClass();
        }
        getToken();
        if(tok!="</tokens>"){
            ferr<<"Syntax error: </tokens> expected"<<endl;
            exit(-1);
        }
        fin.close();
        fout.close();
        ferr.close();
    }
    return 0;
}