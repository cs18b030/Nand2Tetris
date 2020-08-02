#include<bits/stdc++.h>
using namespace std;

int x=0;
int check=0;

 string removecommentstar(string str){ ///removes coments of type /*..*/
     size_t flag0=str.find("/*");
     size_t flag1=str.find("*/");
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

 string removecomment2(string str){ ////removes coments of type "//"
     size_t flag=str.find("//");
     if(flag!=::string::npos)
        str.erase(flag);
    return str;
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
        }
        
     } 
        fout.close();
        fin.close();

    fin.open("inter.txt");
    FILE *fptr = fopen(argv[2], "w");
    int i=0;
    while(fin>>line){
        if(line=="add")
            fprintf(fptr,"@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n");
        else if(line=="sub")
            fprintf(fptr,"@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n");
        else if(line=="and")   
            fprintf(fptr,"@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D\n");
        else if(line=="or")   
            fprintf(fptr,"@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D\n");
        else if(line=="not")
            fprintf(fptr,"@SP\nA=M-1\nM=!M\n");
        else if(line=="neg")
            fprintf(fptr,"@SP\nA=M-1\nM=-M\n");
        else if(line=="eq"){
            fprintf(fptr, "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@TRUE%d\nD;JEQ\n@SP\nA=M-1\nM=0\n(TRUE%d)\n",i,i);
            i++;
        }
        else if(line=="gt"){
            fprintf(fptr, "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@TRUE%d\nD;JGT\n@SP\nA=M-1\nM=0\n(TRUE%d)\n",i,i);
            i++;
        }
        else if(line=="lt"){
            fprintf(fptr, "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\nM=-1\n@TRUE%d\nD;JLT\n@SP\nA=M-1\nM=0\n(TRUE%d)\n",i,i);
            i++;
        }
            //////Arithematic and logical commands DONE!!!!
        else if(line=="push"){
            string segment;
            int index;
            fin>>segment>>index;
            if(segment=="constant"){
                fprintf(fptr,"@%d\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n",index);
            }
            else if(segment=="argument"){
                fprintf(fptr,"@ARG\nD=M\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="local"){
                fprintf(fptr,"@LCL\nD=M\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="this"){
                fprintf(fptr,"@THIS\nD=M\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="that"){
                fprintf(fptr,"@THAT\nD=M\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="pointer"){
                fprintf(fptr,"@3\nD=A\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="temp"){
                fprintf(fptr,"@5\nD=A\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",index);
            }
            else if(segment=="static"){
                fprintf(fptr,"@%s%d\nD=A\n@%d\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n",argv[2],index,index);
            }
            else{
                cerr<<"Error in input 'segment', segment not found"<<endl;
                break;
            }
        }
        else if(line=="pop"){
            string segment;
            int index;
            fin>>segment>>index;
            if(segment=="constant"){
                cerr<<"ERROR: cannot POP into a constant segment"<<endl;
                exit(-1);
            }
            else if(segment=="local")
                fprintf(fptr,"@LCL\nD=M\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="argument")
                fprintf(fptr,"@ARG\nD=M\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="this")
                fprintf(fptr,"@THIS\nD=M\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="that")
                fprintf(fptr,"@THAT\nD=M\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="temp")
                fprintf(fptr,"@5\nD=A\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="pointer")
                fprintf(fptr,"@3\nD=A\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",index);
            else if(segment=="static")
                fprintf(fptr,"@%s%d\nD=A\n@%d\nD=A+D\n@R13\nM=D\n@SP\nA=M\nA=A-1\nD=M\n@R13\nA=M\nM=D\n@SP\nM=M-1\n",argv[2],index,index);
            else{
                cerr<<"Error in input 'segment', segment not found"<<endl;
                break;
            }
        }
        //////push pop done!!!!
        else if(line=="label"){
            string s;
            fin>> s;
            // cout<<s;
            fprintf(fptr, "(%s_%s)\n", argv[2], s);
        }
        else if(line=="goto"){
            string s;
            fin>>s;
            fprintf(fptr,"@%s_%s\n0;JMP\n", argv[2], s);
        }
        else if(line=="if-goto"){
            string s;
            fin>>s;
            fprintf(fptr,"@SP\nMA=M-1\nD=M\n@%s_%s\nD;JNE\n",argv[2], s);
        }
        else{
            cerr<<"Invalid input"<<endl;
            break;
        }
    }
    fin.close();
    fclose(fptr);
    return 0;
}