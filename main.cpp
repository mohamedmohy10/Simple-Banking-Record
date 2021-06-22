#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;
//Function Declaration
void writeAccount();
void dispFile();
void dispAll();
void deleteAcc();
void modif();
//class
class account{
private:
  int account_number;
  char FirstName [15],LastName[15];
  double TotalBalance;
public:
    void add()
    {
    cout<<"Enter Account number: ";
    cin>>account_number;
    cout<<"\nEnter First name: ";
    cin>>FirstName;
    cout<<"\nEnter Last name: ";
    cin>>LastName;
    cout<<"\nEnter Total balance: ";
    cin>>TotalBalance;
    cout<<endl;
    }

    void display()
    {
    cout<<"\nAccount number: ";
    cout<<account_number;
    cout<<"\nFirst name: ";
    cout<<FirstName;
    cout<<"\nLast name: ";
    cout<<LastName;
    cout<<"\nTotal balance: ";
    cout<<fixed<<setprecision(2)<<TotalBalance;
    cout<<endl;
    }

    int ReturnNumber() //for using the account number in processes
    {
        int x=account_number;
    return x;
    }
    void modify()
    {
    display();
    cout<<"\nEnter new First name: ";
    cin>>FirstName;
    cout<<"\nEnter new Last name: ";
    cin>>LastName;
    cout<<"\nEnter new Total balance: ";
    cin>>TotalBalance;
    cout<<endl;
    }
};
// ----------Main Function-------------
int main()
{   int x;
    cout<<"\t\t*** Mini Banking System project***\n\n";
    while(true)
    { cout<<"\n*************************************************\n\nPress the number related to your desired operation:\n";
      cout<<"\t1->Insert a new account\n\t2->search for and display an account\n\t3->Modify an account\n\t4->Display all accounts\n\t5->Delete an account\n\t6->exit\n";
      cin>>x;
      switch(x)
    {
    case 1: writeAccount();  break;
    case 2: dispFile();      break;
    case 3: modif();         break;
    case 4: dispAll();       break;
    case 5: deleteAcc();     break;
    case 6: exit(0);          break;
    default: cout<<"\aEnter a valid operation number\n";
    }
    }
    getch();
    return 0;
}
//--------------Functions---------------

void writeAccount() //creates new account
{
account c;
ofstream myfile("bank.txt",ios::app);
c.add();
myfile.write(reinterpret_cast<char*>(&c),sizeof(account));
//myfile.write((char*)&c,sizeof(account));
cout<<"\n----Account has been added successfully!!----\n";
}

void dispFile() //searches for and displays account by account number
{
 account c;
 int n;
 cout<<"Enter the account number:";
 cin>>n;
 ifstream myfile("bank.txt",ios::binary);
 while(myfile.read(reinterpret_cast<char*>(&c),sizeof(account)))
 {
     if(n==c.ReturnNumber())
        {
        c.display();
        return;
        }
 }
 cout<<"Account not found\n";
}

void dispAll() //shows all saved accounts
{
 account c;
 ifstream myfile("bank.txt",ios::binary);
 cout<<"----------- All registered accounts list ---------- \n";
 while(myfile.read(reinterpret_cast<char*>(&c),sizeof(account)))
    {
    c.display();
    cout<<endl<<"---------------------\n";
    }
}

void deleteAcc()   //For deleting an account
{
    account c;
    int n;
    cout<<"Enter the number of the account you want to delete:";
    cin>>n;
    ifstream myfile("bank.txt",ios::binary);
    ofstream myfile2("temp.txt",ios::app);
    if(!myfile) //test in case the program crashed during opening the file or something
	{
		cout<<"File could not be open..";
		return;
	}
    while(myfile.read(reinterpret_cast<char*>(&c),sizeof(account)))
    {
        if(c.ReturnNumber()!=n)
            myfile2.write(reinterpret_cast<char*>(&c),sizeof(account));
    }
    myfile.close();
    myfile2.close();
    remove("bank.txt");
    rename("temp.txt","bank.txt");
    cout<<"\n----Account deleted successfully----\n";
}
void modif()  //Modify an Account
{
    account c;
    int n;
    fstream myfile("bank.txt",ios::binary|ios::in|ios::out);
    cout<<"\nEnter the account number you want to modify: ";
    cin>>n;
    while(myfile.read(reinterpret_cast<char*>(&c),sizeof(account)))
    {

      if(c.ReturnNumber()==n)
    {
        c.modify();
        int position=-int(sizeof(account));
        myfile.seekp(position,ios::cur);
        myfile.write(reinterpret_cast<char*>(&c),sizeof(account));
        cout<<"\n----Account has been modified successfully !! ----\n";
        return;
    }
    }
    cout<<"\nAccount not found";
}
