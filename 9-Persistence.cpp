Persistence
- Storage of data on to non volatile memory
- Advantage . In future we can retrieve information

Object Persistence 
- Storage of object on to disk

Serialization
- Sending object by value on to streams

Stream
- Acts as a middle buffer between two input and   output devices
Stream operations
1-Write (output)
2-read  (input)

- In order to store object on disk write operation is used
..........................................
C++ Code
ofstream file("c:\\temp\\a.dat",ios:out);
car c("suzuki",10000);
file.write((char*)&c,sizeof(car));
...............................................
Another Method
ifstream file("c:\\temp\\a.dat",ios:out);
car c("suzuki",10000);
file<<c;// i m still in doubt
..............................................

Binary File

- File of formatted data
  e.g File of objects
      file of structures
- Don't try to open binary file in text editors
  text editors  will show garbage
.............................................
Problem : Write Two account objects onto disk
#include <fstream.h>
#include <iostream.h>
#include <string.h>
class Account{
public:
    Account () { }
    Account(int id,char ow[],int bal){
    aid=id;
    strcpy(owner,ow);
    balance=bal;
    }
int getAid(){ return aid;}
char* getOwner(){ return owner;}
int getBalance() { return balance;}
void setAid(int id) { aid=id;}
void setOwner(char ow[]){strcpy(owner,ow);}
void setBalance(int bal) {balance=bal;}
private:
int aid;
char owner[50];
int balance;
};

void main() {
	ofstream file("c:\\temp\\a.dat",ios::out);
//above line will create new file on disk
Account ob1(1,"Shoaib",1000);
Account ob2(2,"Farooq",2000);
file.write((char*)&ob1,sizeof(Account));
file.write((char*)&ob2,sizeof(Account));
file.close();
}
..................................................
Problem : Retrieve (input)Two account objects from disk
#include <fstream.h>
#include <iostream.h>
#include <string.h>
class Account{
public:
    Account () { }
    Account(int id,char ow[],int bal){
    aid=id;
    strcpy(owner,ow);
    balance=bal;
    }
int getAid(){ return aid;}
char* getOwner(){ return owner;}
int getBalance() { return balance;}
void setAid(int id) { aid=id;}
void setOwner(char ow[]){strcpy(owner,ow);}
void setBalance(int bal) {balance=bal;}
private:
int aid;
char owner[50];
int balance;
};

void main() {
ifstream file("c:\\temp\\a.dat",ios::in);
//above line will create new file on disk
Account ob;

file.read((char*)&ob,sizeof(Account));
cout<<ob.getAid()<<" "<<ob.getOwner()<<" "<<ob.getBalance()<<endl;
file.read((char*)&ob,sizeof(Account));
cout<<ob.getAid()<<" "<<ob.getOwner()<<" "<<ob.getBalance()<<endl;
file.close();
}
................................................
Problem : Retrieve (input)all account objects from disk
void main() {
ifstream file("c:\\temp\\a.dat",ios::in);
//above line will create new file on disk
Account ob;

while (file.read((char*)&ob,sizeof(Account)))
cout<<ob.getAid()<<" "<<ob.getOwner()<<" "<<ob.getBalance()<<endl;

file.close();
}
    
..............................................    

Problem :Add more records in accounts File
   (append problem)

void main() {
ofstream file("c:\\temp\\a.dat",ios::app);
//above line will open existing file in append mode
Account ob1(3,"osama",5000);
Account ob2(4,"Sheikh",2000);
file.write((char*)&ob1,sizeof(Account));
file.write((char*)&ob2,sizeof(Account));
file.close();
}
..................................................
       Persistence of Collection

Problem : implement persistence bank

e.g Simulate Bank Problem  (Again)
  Accounts(accno,Title,balance,activeFlag,CloseFlag)
  Bank (collection of accounts)
          Methods
         OpenAccount(account)
         deposit(accno,amount)
         withdraw(accno,amount)
         closeAccount(accno)
         freezeAccount(accno)
         unFreezeAccount(accno)
         openBank()
         closeBank()
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> 
#include <fstream.h>
class Account {
private:
int accno;
char title[30];
int balance;
bool activeFlag;
bool closeFlag;
public:
    Account() { }
    Account(int ano,char t[],int bal){
    accno=ano;
    strcpy(title,t);
    balance=bal;
    activeFlag=true;
    closeFlag=false;    
    }
void setAccno(int ano){accno=ano;}
void setTitle(char t[]){strcpy(title,t);}
void setBalance(int bal){balance=bal;}
void setActiveFlag(bool flag){activeFlag=flag;}
void setCloseFlag(bool flag){closeFlag=flag;}
int getAccno() { return accno;}
char * getTitle() { return title;}
int getBalance() { return balance;}
bool getActiveFlag() { return activeFlag;}
bool getCloseFlag() { return closeFlag;}
};

class Bank {
private :
 Account *a;
 int size;
public :
      Bank() { }
      Bank (int s) { size=s;
           a=new Account[size];
      }
void openAccount(Account form){
 a[form.getAccno()]=form;
}
int getBalance(int ano) {
   return a[ano].getBalance();
}
void withdraw(int ano,int amt  ){
if (a[ano].getActiveFlag()==false){
    cout<<"At present Account is freezed \n"; 
    return;
} 
 int balance=getBalance(ano);
 if (amt<=balance)
    a[ano].setBalance(balance-amt);
 else
     cout<<" Out of balance"<<endl;
}
void deposit(int ano,int amt  ){
 if (a[ano].getActiveFlag()==false){
    cout<<"At present Account is freezed \n"; 
    return;
}
 int balance=getBalance(ano);
  a[ano].setBalance(balance+amt); 
}
void freezAccount(int ano){
 a[ano].setActiveFlag(false);
}
void unFreezAccount(int ano){
 a[ano].setActiveFlag(true);
}
void openBank(){
 delete []a;
 ifstream file2("c:\\temp\\size.dat",ios::in); 
 ifstream file("c:\\temp\\Bank.dat",ios::in);
 file2>>size;
 file2.close();
 Account account;
 a=new Account[size];
 int i=1;
 while (file.read((char*)&account,sizeof(Account))){
     a[i]=account;
     i++;
 }
 file.close();
}
void closeBank(){
	ofstream file("c:\\temp\\Bank.dat",ios::out);
	ofstream file2("c:\\temp\\size.dat",ios::out);
 file2<<size;
 file2.close();
 Account account;
 for(int i=1;i<size;i++){
   account=a[i];
  file.write((char*)&account,sizeof(Account));
 }
 file.close(); 
 }
};
class Menu{
public :
void  menu(){
system("cls");
cout<<" B   A   N   K     M   E   N  U \n\n";
cout<<"1- Open Account  \n ";
cout<<"2- withdraw  \n ";
cout<<"3- deposit  \n ";
cout<<"4- Get Balance  \n ";
cout<<"5- freeze Account  \n ";
cout<<"6- unFreeze Account  \n ";
cout<<"7- Display All Accounts \n ";
cout<<"8- OpenBank  \n ";
cout<<"9- CloseBank \n ";
cout<<"0- exit  \n ";
cout <<"Select Option = ";
}

void displayMenu() {
     Bank bank(5);
     Account form;
     char option; int accno; int amount;
     menu();
	 cout.flush();
while (true){
     option=getche();
switch(option){
case '1': bank.openAccount(fillForm());
          cout<<"Account Successfully Opened\n";
		  cout<<endl;
          break;      
   
case '2': system("cls");
          cout<<"Account No ="; cin>>accno;
          cout<<"Amount ="; cin>>amount;
          bank.withdraw(accno,amount);
		  cout<<endl;
          break;  
case '3': system("cls");
          cout<<"Account No ="; cin>>accno;
          cout<<"Amount ="; cin>>amount;
          bank.deposit(accno,amount);
		  cout<<endl;
          break; 
case  '4': system("cls");
          cout<<"Account No ="; cin>>accno;
          cout<<"Balance =";                       

        cout<<bank.getBalance(accno);
         cout<<endl;
		 cout<<"press any key to go back \n";
          cout.flush();
          getch(); 

          break; 
case  '8': system("cls");
   cout<<"It will Load All Accounts from Disk\n";
   bank.openBank();
   cout<<" Successfully Loaded \n";
   cout<<"press any key to go back \n";
   cout.flush();
   getch();                      
       break; 
case  '9': system("cls");
   cout<<"It will Save All Accounts onto Disk\n";
   bank.closeBank();
   cout<<" Successfully Saved \n";
   cout<<"press any key to go back \n";
   cout.flush();
   getch();                      
       break; 

case '0': bank.closeBank();
	     exit(0);

  }//end switch
  system("cls");
  menu();
  cout.flush();
}//end  of loop
}    

Account fillForm(){
  system("cls");
  cout <<" Account form Data entry \n";
  int accno;
  char title[30];
  int balance;
  cout<<"Account No ="; cin>>accno;
  cout<<"Account Title ="; cin>>title;
  cout<<"Account Balance ="; cin>>balance;
  Account form(accno,title,balance);
  return form;
}
 
};

void main () {
Menu m;
m.displayMenu();

}


