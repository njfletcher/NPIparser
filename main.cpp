#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

bool codes[10][10][10][10][10] = {};

int initializeLookup(){

    ifstream zipCodeFile ("zipcodes.csv");
    string line;

    if(!zipCodeFile.is_open()){
        cout << "failed to open zipcode file" << endl;
        return 2;
    }

    if(zipCodeFile){
        getline(zipCodeFile,line);
    }
    while(zipCodeFile) {

        char post[6] = {'0','0','0','0','0',0};
        getline(zipCodeFile,line);
        int lineSize = line.size();
        for(int i =0; i<lineSize; i++){
            if(line[i] == ','){

                int length = 0;
                for(int j = 0; (j<5) && (line[1+i+j]!= ','); j++){
                    length++;
                }
                for(int j = 5-length; j<5;j++){
                    post[j] = line[1+j+i];
                }
                break;
            }

        }
        if(strcmp(post,"00000") == 0) continue;
        int val1 = post[0]-'0';
        int val2 = post[1]-'0';
        int val3 = post[2]-'0';
        int val4 = post[3]-'0';
        int val5 = post[4]-'0';

        if(val1<0 || val1>9)continue;
        if(val2<0 || val2>9)continue;
        if(val3<0 || val3>9)continue;
        if(val4<0 || val4>9)continue;
        if(val5<0 || val5>9)continue;


        codes[val1][val2][val3][val4][val5]=true;

    }
    zipCodeFile.close();
    return 0;


}

int main(int argc, char** argv) {

    if(argc <2){
        cout << "Provide a file" <<endl;
        return 1;
    }

    int val = initializeLookup();
    if(val!=0) return val;

    string fileName(argv[1]);
    ofstream outputFile;
    string outputFileName = "output" + fileName;
    outputFile.open(outputFileName);

    if(!outputFile.is_open()){
        cout <<outputFileName << endl;
        cout << "failed to open output file" << endl;
        return 3;
    }

    ifstream file (fileName);
    string currentLine;

    if(!file.is_open()){
        cout << "failed to open input file" << endl;
        return 4;
    }

    const int postalColumn = 33;

    //load the header row separately
    if(file){
        getline(file,currentLine);
        outputFile << "\"ZIPCODE\","<< currentLine << "\n";
    }

    while(file){

        getline(file,currentLine);
        char postalCode[6] = {'0','0','0','0','0',0};
        int quotePairs = 0;
        bool quoteClosed = true;
        int size = currentLine.size();
        for(int i =0; i<size; i++){

            if(currentLine[i] == '"'){
                if(quoteClosed){
                    quotePairs++;
                    quoteClosed = false;
                    if(quotePairs == postalColumn){

                        int postLength = 0;
                        for(int j =1; (currentLine[i+j] != '"') && (j <6);j++){
                            postLength++;
                        }
                        for(int j = 5-postLength;j<5;j++){
                            postalCode[j] = currentLine[i+j+1];
                        }
                        break;

                    }
                }
                else{
                    quoteClosed = true;
                }
            }

        }

        char dummy[1] = {0};
        if(strcmp(postalCode,dummy)==0){
            continue;
        }
        int val1 = postalCode[0]-'0';
        int val2 = postalCode[1]-'0';
        int val3 = postalCode[2]-'0';
        int val4 = postalCode[3]-'0';
        int val5 = postalCode[4]-'0';

        if(val1<0 || val1>9)continue;
        if(val2<0 || val2>9)continue;
        if(val3<0 || val3>9)continue;
        if(val4<0 || val4>9)continue;
        if(val5<0 || val5>9)continue;

        if(codes[val1][val2][val3][val4][val5]){
            outputFile << "\"" << postalCode << "\"," << currentLine << "\n";
        }


    }
    outputFile.close();
    file.close();


    return 0;
}
