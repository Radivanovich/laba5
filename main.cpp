#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

class Contact
{
    string nickname;
public:
    Contact(string word)
    {
        nickname = word;
    }
    Contact():nickname("temp") {}
    string getContact()
    {
        return nickname;
    }
};

class incorrectChoose:public exception
{};
class notFinded:public exception
{};

template <class Templ>
class SharedPtr
{
private:
    Templ* ptr;
    int* count;
    void deleteData()
    {
        if (--*count == 0)
        {
            delete count;
            delete ptr;
        }
    }
public:
    SharedPtr():ptr(0), count(new int(0)){}
    explicit SharedPtr(Templ* p=0): ptr(p), count(new int(1)) {}
    SharedPtr(const SharedPtr<Templ>& p) throw(): ptr(p.ptr), count(p.count){++*count;}
    ~SharedPtr()
    {
        deleteData();
    }
    SharedPtr<Templ>& operator= (const SharedPtr<Templ>& p) throw()
    {
        if(this!=&p)
        {
            deleteData();
            ptr=p.ptr;
            count=p.count;
            ++*count;
        }
        return *this;
    }
    Templ& operator*(){return *ptr;}
    Templ* operator->(){return ptr;}
};

int main()
{
    SharedPtr<Contact> ob1 (new Contact ("Jack"));
    SharedPtr<Contact> ob2 (new Contact ("Nick"));
    SharedPtr<Contact> ob3 (new Contact ("Mike"));
    SharedPtr<Contact> ob4 (new Contact ("Liz"));
    SharedPtr<Contact> ob5 (new Contact ("Kate"));
    SharedPtr<Contact> ob6 (new Contact ("Bob"));
    map <string,Contact> Online;
    Online["bob"]=(*ob6);
    map <string,Contact> Offline;
    Offline["liz"]=(*ob4);
    Offline["kate"]=(*ob5);
    map <string,Contact> Banned;
    Banned["jack"]=(*ob1);
    Banned["nick"]=(*ob2);
    Banned["mike"]=(*ob3);
    map<string,Contact>::iterator cur;
    int ch;
    string str;
    do
    {
        cout<<"What do you want to see now?"<<endl;
        cout<<" 1 - All contacts"<<endl;
        cout<<" 2 - Online"<<endl;
        cout<<" 3 - Offline"<<endl;
        cout<<" 4 - Banned"<<endl;
        cout<<" 5 - Ban user"<<endl;
        cout<<" 6 - Unban user"<<endl;
        cout<<" 7 - Exit"<<endl;
        cin>>ch;
        if(ch>7||ch<1)
            throw incorrectChoose();
        switch(ch)
        {
        case 1:
        {
            cout<<"Your contact-list:"<<endl;
            cout<<"Online:"<<endl;
            for (cur=Online.begin(); cur!=Online.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            cout<<"Offline:"<<endl;
            for (cur=Offline.begin(); cur!=Offline.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            cout<<"Banned:"<<endl;
            for (cur=Banned.begin(); cur!=Banned.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            system("pause");
            system("cls");
        }
        break;
        case 2:
        {
            cout<<"Online:"<<endl;
            for (cur=Online.begin(); cur!=Online.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            cout<<"Offline:"<<endl;
            for (cur=Offline.begin(); cur!=Offline.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            cout<<"Banned:"<<endl;
            for (cur=Banned.begin(); cur!=Banned.end(); cur++)
                cout<<"-"<<cur->second.getContact()<<endl;
            system("pause");
            system("cls");
            break;
        }
        case 5:
        {
             cout<<"Enter nickname pls:"<<endl;
            cin>>str;
            for (cur=Online.begin(); cur!=Online.end(); cur++)
                if(cur->first==str)
                {
                    Banned[str]=Online[str];
                    Online.erase(cur);
                    break;
                }
            for (cur=Offline.begin(); cur!=Offline.end(); cur++)
                if(cur->first==str)
                {
                    Banned[str]=Offline[str];
                    Offline.erase(cur);
                    break;
                }
            break;
            throw notFinded();
            break;
        }
        case 6:
            cout<<"Enter nickname pls:"<<endl;
            cin>>str;
            for (cur=Banned.begin(); cur!=Banned.end(); cur++)
                if(cur->first==str)
                {
                    Offline[str]=Banned[str];
                    Banned.erase(cur);
                    break;
                }
            break;
            throw notFinded();
            break;
        case 7:
            break;
        }
    }
    while (ch!=7);
}
