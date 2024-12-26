#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream inputFile("test.cpp"); // read the file
    ofstream outputFile("output.cpp"); // write the file

    if(!inputFile){
        cout << "Error: file can't open successfully" << endl;
        return 0;
    }
    if(!outputFile){
        cout << "Error :file can't create successfully" <<endl;
        return 0;
    }
    string charact = "'";
 
    string line;
    bool comment = false; // for comment
    bool str = false; //for comment
    int str_num = -1; // check the string start or not
    bool characte = false;
    

    while(getline(inputFile, line)){
        int num = line.size();

        for(int i = 0 ; i < num ; ++i){
            
            if(line[i] == charact[0] && !comment && !str){
                if (characte){
                    characte = false;
                }
                else{
                    characte = true;
                }
            }

            if(line[i] == '"' && !str && !comment && !characte){
                if(!str){  //show string is close
                    str = true;
                    str_num = i;
                }
                

            }
            if(line[i] == '"' && str && i != str_num && !characte ){
                str = false; //show string is close
            }

            if (line[i] == '/' && !str && i +1 < num){
                if (line[i+1] == '/'){ // when single comment start break the line
                    break;
                }

                if(line[i+1]== '*'){ // show double comment is start
                    comment= true;
                }
            }

            if(line[i] == '*' && comment && !str && i +1 < num){ // show comment on or not
                if (line[i+1] == '/'){
                    comment = false;
                    i += 2;
                }
            }

            if (!comment){ // print or not
           outputFile << line[i] ;
            }
        }
        if(!comment){
         outputFile << endl;
        }
    }

    inputFile.close();
    return 0;
}