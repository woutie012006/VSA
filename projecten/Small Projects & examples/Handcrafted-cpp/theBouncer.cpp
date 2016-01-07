#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;


int main (){
    std::string name = "";
    std::vector<std::string>  people(1) ;
    people.push_back("wouter");

    cout<<"what\'s your name?"<<endl;
    cin>>name;
    
    if(std::find(std::begin(people), std::end(people), name) != std::end(people))
    {
    cout<<"welcome "<<name<<endl;
    }else{
    cout<<"you should not have entered here "<<name<<endl;        
    }
    return 0;
}