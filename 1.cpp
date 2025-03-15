/* To write a C program to simulate the create, delete
, copy, move file operation functions of an OS */ 

#include<iostream>  // for input output
#include<fstream> // for create file
#include<cstring> // for using strcmp()
#include<cstdio> // for remove() function 
#include <windows.h>  // Required for CopyFile()

using namespace std;

// Function Prototypes
void create(const char *);
void deleteFile(const char* );
void copyFile(const char*, const char*);
void moveFile(const char*, const char*);
void renameFile(const char*, const char*);


int main(int argc, char* argv[]) {

    if(argc < 2) {
        cout << "No argument is passed." << endl;
        return 0;
    }

    if(strcmp(argv[1], "create") == 0) {
        create(argv[2]);
        return 0;
    }

    else if(strcmp(argv[1], "delete") == 0){
        deleteFile(argv[2]);
        return 0;
    }

    else if(strcmp(argv[1], "copy") == 0) {
        if(argc < 4) { // Ensure a destination file is provided
            cout << "Error: Missing destination filename for copy operation." << endl;
            return 0;
        }
        copyFile(argv[2], argv[3]);

    } 
    
    else if(strcmp(argv[1], "move") == 0) {
        if(argc < 4) { // Ensure a destination file is provided
            cout << "Error: Missing destination filename for move operation." << endl;
            return 0;
        }
        moveFile(argv[2], argv[3]);
    } 

    else if(strcmp(argv[1], "rename") == 0){
        if(argc < 4) { // Ensure a destination file is provided
            cout << "Error: Missing destination filename for move operation." << endl;
            return 0;
        }

        renameFile(argv[2], argv[3]);
    }

    else {
        cout << "Invalid command." << endl;
    }


    return 0;
}

// for create file
void create(const char* str) {
    ofstream MyFile(str);

    if(!MyFile){

        cout << "Error creating file : " << str << "(-_-)"<< endl;
    }
    else {
        cout << "File created Successfully. (._.)";
    }

    MyFile.close();
}

// Delete file
void deleteFile(const char* str){
    if(remove(str) == 0){
        cout << "File " <<str << " deleted Successfully. (._.)";
    }
    else {
        cout << "Error deleting file : " << str << "(-_-)"<< endl;

    }
}


// Copy File 
void copyFile(const char* str1, const char* str2){

    if(CopyFile(str1, str2, false)){
        cout << "File Copied Successfully (._.)" << endl;
    }
    else{
        cout << "Failed to copy File. Error Code:" << GetLastError() << endl;
    }
}

// Move File
void moveFile(const char* str1, const char* str2){

    if(CopyFile(str1, str2, false)){
        remove(str1);
        cout << "File moved Successfully (._.)" << endl;
    }
    else{
        cout << "Failed to move File. Error Code:" << GetLastError() << endl;
    }
}

//rename file
void renameFile(const char* str1, const char* str2)
{
    if (rename(str1, str2) == 0)
    {
        cout << "File renamed successfully." << endl;
    }
    else
        perror("Error");
}


