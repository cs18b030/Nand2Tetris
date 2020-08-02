#include<bits/stdc++.h>
using namespace std;

 int x=0;
int check=0;
string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
    return str; 
} 
 string removecommentstar(string str){
     size_t flag0=str.find("/*");
     size_t flag1=str.find("*/");
    //  if(flag1==::string::npos && flag0==::string::npos && x==1){
    //       return NULL;
    //  }
     if(flag0!=::string::npos && flag1!=::string::npos){
        str.erase(str.begin()+flag0,str.begin()+flag1+2);
        return str;
     }
     if(flag0!=::string::npos){
        str.erase(flag0);
        x=1;
        return str;
     }
     if(flag1!=::string::npos){
        str.erase(str.begin(),str.begin()+flag1+2);
        x=2;
        return str;
     }
     return str;
 }

 string removecomment2(string str){
     size_t flag=str.find("//");
     if(flag!=::string::npos)
        str.erase(flag);
    return str;
 }

 bool isnumber(string str){
     for(int i=0; i<str.length(); i++){
         if(isdigit(str[i])==false)
            return false;
    }
    return true;
 }
 int decimalToBinary(int N){
    int B_Number = 0; 
    int cnt = 0; 
    while (N != 0) { 
        int rem = N % 2; 
        int c = pow(10, cnt); 
        B_Number += rem * c; 
        N /= 2; 
        cnt++; 
    } 
    return B_Number; 
} 


int main(int argc, char *argv[]){
    fstream fin, fout;
    string line; 

     fin.open(argv[1]); 
     fout.open("inter.txt",ios::out);
     int check=0;
     while (fin){ 
        if(fin.good()!=true) break;
        getline(fin, line); 
        if(line!=""){
            line = removeSpaces(line);  ///all the spaces and tabs are removed
            //also all the blank lines ared also removed
            //
            /*dsffsd
            dsfsf
            dsf*/
           line=removecommentstar(line);
           if(x==1 && check==0 ){
               check=1;
               if(line!="")
               fout<<line<<endl;
           }
           else if(x==1 && check==1){
               continue;
           }
           else if(x==2 && line!=""){
               fout<<line<<endl;
               x=0;
               check=0;
           }

           else if(x==0){
               line=removecomment2(line);
               if(line!="")
               fout<<line<<endl;
               
           }

        // Print line in Console     
        }
        
     } 
        fout.close();
        fin.close();
        fin.open("inter.txt"); 
        fout.open("pass1.txt",ios::out);
        while(fin){
            // if(fin.good()!=true) break;
            getline(fin, line);
            if(line[0]!='('){
                fout<< line<<endl;
            }
            else{
                string s=line;
                size_t flag=s.find(")");
                if(flag!=::string::npos){
                    line.erase(flag+1);
                    fout<<line<<endl;
                    s.erase(s.begin(),s.begin()+flag+1);
                    if(s!=""){
                        fout<<s<<endl;
                    }
                }
            }
        }

    fin.close();
    fout.close();



    fin.open("pass1.txt");
    map <string, int> sym;
    sym.insert(pair<string, int>("SP", 0));
    sym.insert(pair<string, int>("LCL", 1));
    sym.insert(pair<string, int>("ARG", 2));
    sym.insert(pair<string, int>("THIS", 3));
    sym.insert(pair<string, int>("THAT", 4));
    sym.insert(pair<string, int>("R0", 0));
    sym.insert(pair<string, int>("R1", 1));
    sym.insert(pair<string, int>("R2", 2));
    sym.insert(pair<string, int>("R3", 3));
    sym.insert(pair<string, int>("R4", 4));
    sym.insert(pair<string, int>("R5", 5));
    sym.insert(pair<string, int>("R6", 6));
    sym.insert(pair<string, int>("R7", 7));
    sym.insert(pair<string, int>("R8", 8));
    sym.insert(pair<string, int>("R9", 9));
    sym.insert(pair<string, int>("R10", 10));
    sym.insert(pair<string, int>("R11", 11));
    sym.insert(pair<string, int>("R12", 12));
    sym.insert(pair<string, int>("R13", 13));
    sym.insert(pair<string, int>("R14", 14));
    sym.insert(pair<string, int>("R15", 15));
    sym.insert(pair<string, int>("KBD", 24576));
    sym.insert(pair<string, int>("SCREEN", 16384));

    ////label assigning to map
    int count=0;
    while(fin){
        // if(fin.good()!=true) break;
        getline(fin, line);
        if(line[0]!='('){
            count++;
            continue;
        }
        else{
            line.erase(line.begin(),line.begin()+1);
            size_t flag=line.find(")");
            line.erase(flag);
            // count++;
            sym[line]=count;
        }
    }
    fin.close();
    fin.open("pass1.txt");
    count=16;
    ///this to store the @symbols
    while(fin){ 
        // if(fin.good()!=true) break;
        getline(fin,line);
        if(line[0]!='@'){
            continue;
        }
        else{
            line.erase(line.begin(),line.begin()+1);
            if(isnumber(line)==true)
                continue;
            else{
                auto itr=sym.find(line);
                if(itr==sym.end()){
                    sym[line]=count;
                    count++;
                }
            }
        }
    }
    fin.close();

    // for(auto it = sym.begin(); it != sym.end(); ++it){
    //     cout<< it->first<<"\t"<<it->second<<endl;

    // }
    ////check for map values.

    ///////pass 1 COMPLETED!!!!!!!!!!!!!
    map <string, string> dict;
    ////dictionary for A and D
    dict.insert(pair<string, string>("0","0101010"));
    dict.insert(pair<string, string>("1","0111111"));
    dict.insert(pair<string, string>("-1","0111010"));
    dict.insert(pair<string, string>("D","0001100"));
    dict.insert(pair<string, string>("A","0110000"));
    dict.insert(pair<string, string>("!D","0001101"));
    dict.insert(pair<string, string>("!A","0110001"));
    dict.insert(pair<string, string>("-D","0001111"));
    dict.insert(pair<string, string>("-A","0110011"));
    dict.insert(pair<string, string>("D+1","0011111"));
    dict.insert(pair<string, string>("1+D","0011111"));
    dict.insert(pair<string, string>("A+1","0110111"));
    dict.insert(pair<string, string>("1+A","0110111"));
    dict.insert(pair<string, string>("D-1","0001110"));
    dict.insert(pair<string, string>("-1+D","0001110"));
    dict.insert(pair<string, string>("A-1","0110010"));
    dict.insert(pair<string, string>("-1+A","0110010"));
    dict.insert(pair<string, string>("D+A","0000010"));
    dict.insert(pair<string, string>("A+D","0000010"));
    dict.insert(pair<string, string>("D-A","0010011"));
    dict.insert(pair<string, string>("-A+D","0010011"));
    dict.insert(pair<string, string>("A-D","0000111"));
    dict.insert(pair<string, string>("-D+A","0000111"));
    dict.insert(pair<string, string>("D&A","0000000"));
    dict.insert(pair<string, string>("A&D","0000000"));
    dict.insert(pair<string, string>("D|A","0010101"));
    dict.insert(pair<string, string>("A|D","0010101"));
    /////dictionary for M
    dict.insert(pair<string, string>("M","1110000"));
    dict.insert(pair<string, string>("!M","1110001"));
    dict.insert(pair<string, string>("-M","1110011"));
    dict.insert(pair<string, string>("M+1","1110111"));
    dict.insert(pair<string, string>("1+M","1110111"));
    dict.insert(pair<string, string>("M-1","1110010"));
    dict.insert(pair<string, string>("-1+M","1110010"));
    dict.insert(pair<string, string>("D+M","1000010"));
    dict.insert(pair<string, string>("M+D","1000010"));
    dict.insert(pair<string, string>("D-M","1010011"));
    dict.insert(pair<string, string>("-M+D","1010011"));
    dict.insert(pair<string, string>("M-D","1000111"));
    dict.insert(pair<string, string>("-D+M","1000111"));
    dict.insert(pair<string, string>("D&M","1000000"));
    dict.insert(pair<string, string>("M&D","1000000"));
    dict.insert(pair<string, string>("D|M","1010101"));
    dict.insert(pair<string, string>("M|D","1010101"));
    /////dictionary for jump
    map<string, string> jump;
    jump.insert(pair<string, string>("null","000"));
    jump.insert(pair<string, string>("JGT","001"));
    jump.insert(pair<string, string>("JEQ","010"));
    jump.insert(pair<string, string>("JGE","011"));
    jump.insert(pair<string, string>("JLT","100"));
    jump.insert(pair<string, string>("JNE","101"));
    jump.insert(pair<string, string>("JLE","110"));
    jump.insert(pair<string, string>("JMP","111"));
    ////dictionary for destination
    map<string,string> dest;
    dest.insert(pair<string, string>("M","001"));
    dest.insert(pair<string, string>("D","010"));
    dest.insert(pair<string, string>("MD","011"));
    dest.insert(pair<string, string>("DM","011"));
    dest.insert(pair<string, string>("A","100"));
    dest.insert(pair<string, string>("AM","101"));
    dest.insert(pair<string, string>("MA","101"));
    dest.insert(pair<string, string>("AD","110"));
    dest.insert(pair<string, string>("DA","110"));
    dest.insert(pair<string, string>("AMD","111"));
    dest.insert(pair<string, string>("ADM","111"));
    dest.insert(pair<string, string>("MDA","111"));
    dest.insert(pair<string, string>("MAD","111"));
    dest.insert(pair<string, string>("DMA","111"));
    dest.insert(pair<string, string>("DAM","111"));

    fin.open("pass1.txt");
    fout.open(argv[2],ios::out);    
    while(fin){
        // if(fin.good()!=true) break;
        getline(fin, line);
        if(line[0]=='('){
            continue;
        }
        else if(line[0]=='@'){
            fout<<"0";
            line.erase(line.begin(),line.begin()+1);
            int y=0;
            if(isnumber(line)==true){
                stringstream convert(line); 
                convert >> y;
            }
            else{
                y=sym[line];
            }
            for(int i=14; i>= 0; i--){ 
                int k=y >> i; 
                if(k & 1) 
                    fout << "1"; 
                else
                    fout << "0"; 
            }
            fout<<endl;
        }
        else{
            size_t flag=line.find("=");
            if(flag!=::string::npos){
                fout<<"111";
                string s1=line;
                string s2=line;
                s1.erase(flag);     /////s1 is before =
                s2.erase(s2.begin(),s2.begin()+flag+1);     ////s2 is after =
                fout<<dict[s2];
                fout<<dest[s1];
                fout<<"000"<<endl;
            }
            else{
                size_t flag=line.find(";");
                if(flag!=::string::npos){
                    fout<<"111";
                    string s1=line;
                    string s2=line;
                    s1.erase(flag);
                    s2.erase(s2.begin(),s2.begin()+flag+1);
                    fout<<dict[s1];
                    fout<<"000";
                    fout<<jump[s2]<<endl;
                }

            }
        }
    }

    fin.close();
    fout.close();

    
     return 0;
}


///////labels ka binary gadbad h