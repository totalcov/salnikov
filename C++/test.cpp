#include <iostream>
#include <string>

using namespace std;


struct Tree{
    string name;
    int age;
};

void print(string word){
    cout << word << endl;
}

void print(int word){
    cout << word << endl;
}

int main(){
    Tree dub;
    dub.age = 24;
    dub.name = "МАКСИМ";

    print(dub.age);
    print(dub.name);

    return 0;

}

