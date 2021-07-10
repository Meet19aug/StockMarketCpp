#include<iostream>
#include<fstream>
#include<cstring>
#include <stdlib.h>
using namespace std;
typedef struct
{
    char *name;
    double price;
    int qua;
} stock;
void stocklist()//TO RETRIVE THE LIST OF THE STOCKS FROM THE FILE
{
    fstream file;
    file.open("stocklistv.txt",ios::in);
    char c[250];
    while(!file.eof())
    {
        file.getline(c,250);
        cout<<c<<endl;
    }
}
void menu()//TO DISPLAY THE LIST OF OPERATION FOR MENU
{
    cout<<"                                                                     ";
    cout<<"Choose the below listed operations to be performed with our trading company"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
    cout<<"                                                                               ";
    cout<<"1. Display the list of the shares listed at the Stock Exchange"<<endl;
    cout<<"                                                                               ";
    cout<<"2. To buy shares listed"<<endl;
    cout<<"                                                                               ";
    cout<<"3. To sell the shares bought"<<endl;
    cout<<"                                                                               ";
    cout<<"4. To display account info"<<endl;
    cout<<"                                                                               ";
    cout<<"5. To add balance to account"<<endl;
    cout<<"                                                                               ";
    cout<<"6. To see your Portfolio:"<<endl;
    cout<<"                                                                               ";
    cout<<"7. To exit"<<endl;
}
class Account//TEMPARORY CLASS FOR LOGIN
{
protected:
    char name[30];
    char phone[11];
    //static long long int cont;
    static long long int accno;
    double balance;
    char pan[11];
    char filename[16];
public:
    int filelen;
    Account()
    {
        cout<<"\n";
        cout<<"                                                                              ";
        cout<<"WELCOME TO LOGIN PAGE...FILL UP YOUR DETAILS HERE:                                                                              "<<endl;
        //cout<<"                                                                               ";
        cout<<"\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
        cout<<"\n";
        cout<<"                                                                                    ";
        cout<<"ENTER THE NAME OF THE CLIENT:-> ";
        cin>>name;
        cout<<"\n";
        cout<<"                                                                                ";
        cout<<"ENTER YOUR 10 DIGIT UNIQUE PAN NUMBER:-> ";
        cin>>pan;
        while(strlen(pan)!=10)
        {
            cout<<"                                                                                ";
            cout<<"PlEASE ENTER A 10 DIGIT PAN NUMBER:-> ";
            cin>>pan;
        }
        cout<<"\n";
        strcpy(filename,pan);
        strcat(filename,".txt");
        if(checkfile(name,strlen(name),pan))
        {
            cout<<"                                                ";
            cout<<"YOU HAVE ALREADY REGISTERED WITH OUR PLATFORM WE FETCHED YOUR DATA FROM OUR DATABASE YOU ARE READY TO GO....\n"<<endl;
            cout<<"                                                                                    CONTINUE TRADING....GOOD LUCK FOR YOUR TRADING"<<endl;
            cout<<"\n";
            cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
        }
        else
        {
            cout<<"                                                                               ";
            cout<<"...GET REGISTERED HERE FIRST YOU ARE A NEW USER..."<<endl;
            get_more_data();
            insertacc();
        }

    }
    int checkfile(char *n,int l,char *p)
    {
    fstream afile;
    afile.open("account.txt",ios::in);
    if(!afile)
    {
        afile.open("account.txt",ios::out);
        afile<<0<<endl;
        afile.close();
        afile.open("account.txt",ios::in);
    }
    int line;
    afile>>line;
    filelen=line;
    //accinfo *acc=new accinfo;
    for(int i=0;i<line;i++)
    {
        int namelen;
        afile>>namelen;
        char *na=new char[namelen+1];
        na[namelen]='\0';
        char *pa=new char[11];
        char *ph=new char[11];
        long long int ac;
        double ba;
        afile>>na>>pa>>ph>>ac>>ba;
        if(strcmp(pa,p)==0)
        {
            if(strcmp(na,n)==0)
            {
                strcpy(name,na);
                strcpy(pan,pa);
                strcpy(phone,ph);
                accno=ac;
                balance=ba;
                return 1;
            }
            else
            {
                cout<<"                                                                     ";
                cout<<"These pan number is already exist in our database with different name:\n"<<endl;
                cout<<"                                                                                       ";
                cout<<"YOUR NAME WILL BE CONSIDER AS PER OUR RECORD:\n"<<endl;
                cout<<"                                                                                          ";
                cout<<"YOUR NAME AS PER OUR DATABASE IS :->"<<na<<"\n"<<endl;
                strcpy(phone,ph);
                accno=ac;
                balance=ba;
                return 1;
            }
        }
    }
    return 0;
    }
    void get_more_data()
    {
        cout<<"\n";
        cout<<"                                                                                  ";
        cout<<"ENTER THE RECOVERY PHONE NUMBER:-> ";
        cin>>phone;
        cout<<"\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
        accno+=filelen;
        balance=0;
        cout<<"\n";
        cout<<"                                                                          ";
        cout<<"YOUR UNIQUE ACCOUNT NUMBER FOR YOUR DEMATE ACCOUNT IS CREATED:"<<endl;
        cout<<"\n";
        cout<<"                                                                                                    ";
        cout<<accno<<endl;
        cout<<"\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
    }
    void insertacc()
    {
        fstream acc;
        acc.open("account.txt",ios::in);
        int number_of_line;
        acc>>number_of_line;
        number_of_line++;
        acc.close();
        acc.open("account.txt",ios::app);
        acc<<"\n"<<strlen(name)<<" "<<name<<" "<<pan<<" "<<phone<<" "<<accno<<" "<<balance;
        acc.close();
        acc.open("account.txt",ios::in|ios::out);
        acc.seekg(0);
        acc.seekp(0,ios::beg);
        acc<<number_of_line;
        acc.close();
    }
    void balancetofile()//TO UPDATE THE BALANCE OF TRANSACTION BEFORE ENDING PROGRAM
    {
        fstream afile,tfile;
        afile.open("account.txt",ios::in);
        tfile.open("temp.txt",ios::out);
        int line;
        afile>>line;
        tfile<<line<<endl;
        for(int i=0;i<line;i++)
        {
            int namelen;
            afile>>namelen;
            char *na=new char[namelen+1];
            na[namelen]='\0';
            char *pa=new char[11];
            char *ph=new char[11];
            long long int ac;
            double ba;
            afile>>na>>pa>>ph>>ac>>ba;
            if(strcmp(pa,pan)==0)
            {
                ba=balance;
                tfile<<strlen(na)<<" "<<na<<" "<<pa<<" "<<ph<<" "<<ac<<" "<<ba<<endl;
            }
            else
            {
                tfile<<strlen(na)<<" "<<na<<" "<<pa<<" "<<ph<<" "<<ac<<" "<<ba<<endl;
            }
        }
        afile.close();
        tfile.close();
        remove("account.txt");
        rename("temp.txt","account.txt");
    }
    void display_account()
    {
        cout<<"\n";
        cout<<"                                                                                          ";
        cout<<"NAME OF THE CLIENT: "<<name<<endl;
        cout<<"\n";
        cout<<"                                                                                          ";
        cout<<"PAN NUMBER: "<<pan<<endl;
        cout<<"\n";
        cout<<"                                                                                          ";
        cout<<"YOUR LINKED PHONE NUMBER: "<<phone<<endl;
        cout<<"\n";
        cout<<"                                                                                          ";
        cout<<"DEMATE ACCOUNT NUMBER: "<<accno<<endl;
        cout<<"\n";
        cout<<"                                                                                          ";
        cout<<"ACCOUNT BALANCE: "<<balance<<endl;
        cout<<"\n";
    }
    void acc_balance()
    {
        double x;
        cout<<"\n";
        cout<<"                                                                           ";
        cout<<"ENTER THE AMOUNT OF THE BALANCE TO BE ADDED TO YOUR ACCOUNT:-> ";
        cin>>x;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout<<"                                                                                   ";
            cout<<"DO NOT ENTER ALPHABETS.PLEASE ENTER DIGITS:";
            cin>>x;
        }
        balance+=x;
        if(balance>0)
        {cout<<"\n\n                                                                                             ";
         cout<<"LALA, RISK HAI TO ISHQ HAI\n\n";}
    }
    double balanceret(){return balance;}
    char* retpan()//-------------------------------------------------------------------------------
    {
        return filename;
    }
    void mystocklist()
    {
        fstream sfile;
        sfile.open(filename,ios::in);
        int line;
        if(!sfile)
        {
            sfile.open(filename,ios::out);
            sfile<<0<<endl;
            sfile.close();
            sfile.open(filename,ios::in);
        }
        sfile>>line;
        stock *stk=new stock;
        double total=0;
        cout<<"\t\t\t\t\t\t\t\tName\t\t\tPrice\t\t\tQuantity\t\tShareInvestment"<<endl;
        cout<<"\t\t\t\t\t\t\t\t----------------------------------------------------------------------------------------"<<endl;
        for(int i=0;i<line;i++)
        {
            int namelen;
            sfile>>namelen;
            char *name=new char[namelen+1];
            name[namelen]='\0';
            double price;
            int qua;
            float net;
            sfile>>name>>price>>qua;
            net=price*qua;
            total+=net;
            cout<<"\t\t\t\t\t\t\t\t"<<name<<"\t\t\t"<<price<<"\t\t\t"<<qua<<"\t\t\t"<<net<<endl;
        }
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tTotal Investment="<<total<<endl;
        sfile.close();
    }
};
long long int Account::accno=800000000001;
class Buy_sell:public Account//FOR BUYING SELLING FUNCTIONALITY
{
private:
    double profit;
public:
    void buys()
    {
    typedef struct
    {
    char *name;
    double price;
    int qua;
    } stock;
    fstream org,temp;
    org.open(filename,ios::in);
    if(!org)
    {
        org.open(filename,ios::out);
        org<<0<<endl;
        org.close();
        org.open(filename,ios::in);

    }
    temp.open("buytemp.txt",ios::out);
    int stockcount;
    org>>stockcount;
    stock *buy=new stock[stockcount+1];

    int buycount=0;
    char s[20];
    cout<<"\n";
    cout<<"                                                                                                ";
    cout<<"ACCOUNT BALANCE: "<<balance<<endl;
    cout<<"\n";
    cout<<"                                                                                    ";
    cout<<"ENTER THE NAME OF THE STOCK YOU WANT TO BUY:-> ";
    cin>>s;
    int buynamelen=strlen(s);
    s[buynamelen]='\0';
    int flag=0;
    for(int i=0;i< stockcount;i++)
    {
        int namelen;
        org>>namelen;
        char *name=new char[namelen+1];
        name[namelen]='\0';
        double price;
        int qua;
        org>>name>>price>>qua;
        int k=3;
        for(int j=0;j<namelen;j++)
        {
            if(name[j]!=s[j])
            {
                k=5;
                break;
            }
        }
        if(k==3)
        {
            double p;
            cout<<"\n";
            cout<<"                                                                               ";
            cout<<"ENTER THE PRICE AT WHICH YOU WANT TO BUY THE STOCK:-> ";
            cin>>p;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout<<"                                                                                   ";
                cout<<"DO NOT ENTER ALPHABETS.PLEASE ENTER DIGITS:";
                cin>>p;
            }
            int q;
            cout<<"\n";
            cout<<"                                                                                       ";
            cout<<"ENTER THE NET QUANTITY OF THE STOCK:-> ";
            cin>>q;
            if(q>0&&p>0)
            {
                buy[buycount].name=name;
                buy[buycount].price=((price*qua)+(p*q))/(qua+q);
                buy[buycount].qua=qua+q;
                balance=balance-(q*p);
                buycount++;
                flag=10;
            }
        }
        else
        {
            buy[buycount].name=name;
            buy[buycount].price=price;
            buy[buycount].qua=qua;
            buycount++;
        }
    }
    if(flag!=10)
    {
        double p;
        int q;
        cout<<"\n";
        cout<<"                                                                               ";
        cout<<"ENTER THE PRICE AT WHICH YOU WANT TO BUY THE STOCK:-> ";
        cin>>p;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout<<"                                                                                   ";
            cout<<"DO NOT ENTER ALPHABETS.PLEASE ENTER DIGITS:";
            cin>>p;
        }
        cout<<"\n";
        cout<<"                                                                                       ";
        cout<<"ENTER THE NET QUANTITY OF THE STOCK:-> ";
        cin>>q;
        buy[buycount].name=s;
        buy[buycount].price=p;
        buy[buycount].qua=q;
        balance=balance-(q*p);
        buycount++;


    }
    temp<<buycount<<endl;
    for(int i=0;i<buycount;i++)
    {
        temp<<strlen(buy[i].name)<<" "<<buy[i].name<<" "<<buy[i].price<<" "<<buy[i].qua<<endl;
    }
    org.close();
    temp.close();
    remove(filename);
    rename("buytemp.txt",filename);
    cout<<"\n";
    cout<<"                                                                                      ";
    cout<<"SUCCESSFULLY PERFORMED THE OPERATION!!!!:"<<endl;
    cout<<"\n";
    }
    void sells()
    {
    typedef struct
    {
    char *name;
    double price;
    int qua;
    } stock;
    fstream org,temp;
    org.open(filename,ios::in);
    temp.open("temp.txt",ios::out);
    if(!org)
    {
        org.open(filename,ios::out);
        org<<0<<endl;
        org.close();
        org.open(filename,ios::in);
    }
    int stockcount;
    org>>stockcount;
    stock *sell=new stock[stockcount];
    int sellcount=0;
    char s[30];
    cout<<"\n";
    cout<<"                                                                               ";
    cout<<"ENTER THE NAME OF THE STOCK YOU WANT TO SELL:-> ";
    cin>>s;
    s[strlen(s)]='\0';
    int flag=0;
    for(int i=0;i<stockcount;i++)
    {
        int namelen;
        org>>namelen;
        char *name=new char[namelen+1];
        name[namelen]='\0';
        double price;
        int qua;
        org>>name>>price>>qua;
        int k=3;
        for(int j=0;j<namelen;j++)
        {
            if(name[j]!=s[j])
            {
                k=5;
                break;
            }
        }
        if(qua>0&&(k==3))
        {
            double p;
            cout<<"\n";
            cout<<"                                                                            ";
            cout<<"ENTER THE PRICE AT WHICH YOU WANT TO SELL THE STOCK:-> ";
            cin>>p;
            int q;
            cout<<"\n";
            cout<<"                                                                            ";
            cout<<"ENTER THE NET QUANTITY OF THE STOCK TO BE SOLD:-> ";
            cin>>q;
            if(qua-q>=0)
            {
                profit=((q*p)-(q*price));
                cout<<"\n";
                cout<<"                                                                                      ";
                cout<<"NET PROFIT FROM THE TRANSACTION IS:"<<profit<<endl;
                if(qua-q>0)
                {   sell[sellcount].name=name;
                    sell[sellcount].price=price;
                    sell[sellcount].qua=qua-q;
                    sellcount++;
                }
                balance+=(q*p);
                cout<<"\n";
                cout<<"                                                                                                ";
                cout<<"ACCOUNT BALANCE: "<<balance<<endl;
                flag=10;
                if(profit>50)
                {
                    cout<<"\n\n                                                                            ***** ";
                    cout<<"PROFIT DIKHTA HAI TO HAR KOI JUKTA HAI ****\n\n";
                }
                else
                {
                    cout<<"\n\n                                                                            ***** ";
                    cout<<"SUCCESS KYA HAI? FAILURE KE BAAD KA NAYA CHAPTER ****"<<endl;
                }
            }
        }
        else
        {
            sell[sellcount].name=name;
            sell[sellcount].price=price;
            sell[sellcount].qua=qua;
            sellcount++;
        }
    }
    temp<<sellcount<<endl;
    for(int i=0;i<sellcount;i++)
    {
        temp<<strlen(sell[i].name)<<" "<<sell[i].name<<" "<<sell[i].price<<" "<<sell[i].qua<<endl;
    }
    org.close();
    temp.close();
    remove(filename);
    rename("temp.txt",filename);
    cout<<"\n";
    cout<<"                                                                                ";
    if(flag==10)
    {cout<<"SUCCESSFULLY PERFORMED THE OPERATION!!!!:"<<endl;}
    else
    {
        cout<<"\n                                                                           ";
        cout<<"-------------------------------------------------------------";
        cout<<"\n                                                                                ";
        cout<<"WE ARE NOT ABLE TO FIND STOCK WHICH YOU ENTERED!!!!\n\n";
        cout<<"                                                                                ";
        cout<<"PLEASE REFER TO YOUR PORTFOLIO AND TRY AGAIN:\n\n";
    }
    }

};
int main()
{
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
    cout<<"\n";
    cout<<"                                                                                    WELCOME TO GROW MORE TRADING COMPANY                                                                                          "<<endl;
    cout<<"\n";
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
    Buy_sell a;
    int x=0;
    while(x!=7)
    {
        menu();
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
        cout<<"                                                                                   ";
        cout<<"CHOOSE YOUR CHOICE FROM THE ABOVE MENU:-> ";
        cin>>x;
        while(x<1 || x>7 || cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout<<"                                                                                   ";
            cout<<"PLEASE CHOOSE FROM 1 TO 7:->";
            cin>>x;
        }
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->>>"<<endl;
        switch(x)
        {
        case 1:
            system ("CLS");
            stocklist();
            system ("PAUSE");
            system ("CLS");
            break;
        case 2:
            system ("CLS");
            a.buys();
            system ("PAUSE");
            system ("CLS");
            break;
        case 3:
            system ("CLS");
            a.sells();
            system ("PAUSE");
            system ("CLS");
            break;
        case 4:
            system ("CLS");
            a.display_account();
            system ("PAUSE");
            system ("CLS");
            break;
        case 5:
            system ("CLS");
            a.acc_balance();
            system ("PAUSE");
            system ("CLS");
            break;
        case 6:
            system ("CLS");
            a.mystocklist();
            system ("PAUSE");
            system ("CLS");
            break;
        case 7:
            if(a.balanceret()>=0)
            {
                a.balancetofile();
                x=7;
                exit(1);
            }
            else
            {
                cout<<"\n";
                cout<<"                                                                    ";
                cout<<"YOUR BALANCE IS NEGATIVE ADD MINIMUM BALANCE TO KEEP YOUR ACCOUNT ACTIVE!!!"<<endl;
                x=0;
            }
        default:
            cout<<"                                                                                               ";
            cout<<"ENTER VALID CHOICE!!!"<<endl;
            cout<<"\n";
    }
    }
    return 0;
}
