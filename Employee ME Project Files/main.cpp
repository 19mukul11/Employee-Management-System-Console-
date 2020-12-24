 #include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
using namespace std;


class Random            // class Random
{
public:
    int id[10];
};


int i,j,frequency=0;                            // formal declarations of global variables
char searchVar[20],searchName[20],tempUid[8];
Random tempID,searchID;
char *dirname="D:\\EmployeeDatabase";

FILE *fp;
void gotoxy(int,int);           // formal declarations of functions used
void header();
void AdminMode();
void EmployeeLogin();
void feedToDatabase();
 int compareID(Random,Random);
void searchEmployee();
void EmpIDmaker();
Random random();
void printR();
class Employee;
int main();
int compareUid();




class Employee                  // Global Defination of Class Employee
{
private:
    char uid[8],pwd[8];

public:
    char name[20],designation[25],phoneNo[11],emailId[30],address[50],salary[20];
    int age,joiningYear;
    Random employeeID;



    void getData()              //input of employee data
    {
       gotoxy(1,30); cout<<"*** New Employee Registeration ***";
        cout<<"\n\nCreate UserName (Exactly 6 characters) : ";    fflush(stdin);  gets(tempUid);
         if(compareUid()==0)
         {
             strcpy(uid,tempUid);
         }
        cout<<"\nCreate Password (Exactly 6 Characters) : ";    fflush(stdin);  gets(pwd);

        cout<<"\nEnter Employee Name : "; fflush(stdin); gets(name);
        cout<<"\nAge : ";   fflush(stdin);  scanf("%d",&age);
        cout<<"\nDesignation : ";     fflush(stdin);    gets(designation);
        cout<<"\nResidential Address : ";     fflush(stdin);    gets(address);
        cout<<"\nPhone number : ";    fflush(stdin);    gets(phoneNo);
        cout<<"\nEmail ID : ";    fflush(stdin);    gets(emailId);
        cout<<"\nJoining Year : ";    fflush(stdin);    scanf("%d",&joiningYear);
        cout<<"\nSalary Structure (INR) : ";    fflush(stdin);  gets(salary);
        employeeID=tempID;
    }

    void printR()
    {
        for(i=0;i<=9;i++)
            cout<<employeeID.id[i];
    }

    int matchUidPwd(char checkuid[8],char checkpwd[8])         //matchIDPwd Function
    {                                                               // returns 1, if strings are same
        if(strcmp(uid,checkuid)==0&&strcmp(pwd,checkpwd)==0)            // returns 0, if strings are different
            return(1);

        else
            return(0);

    }

    int compareUid2()
    {
         if(strcmp(uid,tempUid)==0)
                {
                    frequency=frequency+10;
                    return(1);
                }
          else
            return(0);
    }
};

Employee E1;            // Global object of employee classs

void EmpIDmaker()       // Unique EmployeeID maker function defination
{
    tempID=random();
        gotoxy(1,10); cout<<"System is generating new Employee ID, please wait.......";
        _sleep(4500);

        fp=fopen("D:\\EmployeeDatabase\\Database.dat","rb");
        while(fread(&E1,sizeof(E1),1,fp)!=NULL)
        {
            if(compareID(tempID,E1.employeeID)==0)
            {
               gotoxy(2,25); cout<<"Unique Employee-ID generation problem. ";
                gotoxy(1,25);   cout<<"Failed to generate Unique ID. Please press Enter and Restart Application";
                getch();
                exit(1);
            }
            else if(compareID(tempID,E1.employeeID)==1)
            {       //vacant block intentionally
            }
        }
            //fclose(fp);

       // E1.employeeID=tempID;
        //cout<<"\nEmployee ID : ";
       // E1.printR();
            cout<<"\n Press Enter to Continue.....";
             getch();
}

int compareUid()
{
     fseek(fp,0,SEEK_SET);
            while(fread(&E1,sizeof(E1),1,fp)!=NULL)
            {
               if(E1.compareUid2()==1)
               {
                  gotoxy(2,40); cout<<"This UserName is not available. TRY AGAIN !!!";
                  frequency=0;
                  cout<<"\nCreate UserName (Exactly 8 characters) : ";    fflush(stdin);  gets(tempUid);
                  compareUid();
                }
            }

            fclose(fp);
            if(frequency==0)
            {
                return(0);
            }

}

void displayData()          // function to display Employee Data
{
     gotoxy(2,30); cout<<"*** Employee details ***";
                      gotoxy(2,20); cout<<"*************************************************";
                       gotoxy(2,25);  cout<<"Employee ID : ";   E1.printR();
                       gotoxy(1,25);    cout<<"Name : "; puts(E1.name);
                       gotoxy(0,25);    cout<<"Designation : "; puts(E1.designation);
                       gotoxy(0,25);    cout<<"Joining Year : ";  cout<<E1.joiningYear;
                        gotoxy(1,25);    cout<<"Phone : "; puts(E1.phoneNo);
                         gotoxy(0,25);  cout<<"Email : "; puts(E1.emailId);
                         gotoxy(0,25);    cout<<"Residential Address : "; puts(E1.address);
                       gotoxy(0,25);    cout<<"Age : "; cout<<E1.age;
                          gotoxy(2,20); cout<<"*************************************************";


}

void AdminMode()                // AdminMode function defination
{
   admin:
    header();
    gotoxy(2,35);
    cout<<"*** Welcome to Administration mode ***\n";
    gotoxy(1,30);cout<<"1. Register new Employee ";
    gotoxy(1,30);cout<<"2. Search Employee ";
    gotoxy(1,30);cout<<"3. Log Out ";
    gotoxy(2,25); cout<<"Enter your preference : ";
    cin>>i;

    if(i==1)
    {
          // New Registeration process
        header();
        EmpIDmaker();           // procedure of New ID generation
        E1.getData();           // User input of data
        feedToDatabase();       // Feed data to Database
    }
    else if(i==2)
    {
        header();
        searchEmployee();
    }
    else if(i==3)
    {
        main();
    }

    else
    {
        gotoxy(2,20); cout<<"Invalid Request. Please enter correct preference !!!";
        _sleep(800);
        goto admin;

    }

}

void searchEmployee()               //searching employee function
{

    gotoxy(2,30);   cout<<"Search employee by :--";
    gotoxy(2,25);   cout<<"1. Employee ID";
    gotoxy(1,25);   cout<<"2. Employee Name";
    gotoxy(1,25);   cout<<"3. Admin Home";
    gotoxy(2,35); cout<<"Enter your preference : ";
                    cin>>i;

    fp=fopen("D:\\EmployeeDatabase\\Database.dat","rb");

    switch(i)
    {
    case 1:
        {
            gotoxy(1,20);   cout<<"Enter Employee ID of 10 digits (Press ENTER after every digit) : \n";
            for(i=0;i<10;i++)
                cin>>searchID.id[i];

            while(fread(&E1,sizeof(E1),1,fp)!=NULL)
            {
                 if(compareID(E1.employeeID,searchID)==0)
                    {
                       frequency=frequency+10;
                       header();
                      displayData();
                       searchAgainid:
                       gotoxy(2,30); cout<<"1. Admin Home page";
                       gotoxy(1,30);    cout<<"2. Search another employee";
                       gotoxy(2,25);    cout<<"Enter your preference : ";
                            cin>>i;

                       switch(i)
                       {
                       case 1:
                        {
                           system("cls");
                           AdminMode();
                            break;
                        }
                       case 2:
                        {
                            system("cls");
                            searchEmployee();
                            break;
                        }
                        default:
                        {
                            gotoxy(2,25);
                            cout<<"Invalid request, Please  enter correct preference !!!";
                            _sleep(400);
                            goto searchAgainid;
                        }
                       }

                    }

                  if(frequency==0)
                  {
                    gotoxy(2,35);    cout<<"Sorry!!! , No record match your search";
                    _sleep(500);
                    system("cls");
                   searchEmployee();
                  }
            }
               fclose(fp);
                            break;
        }
    case 2:
        {
            gotoxy(1,20);   cout<<"Enter Employee Name : ";
                            fflush(stdin);   gets(searchName);

                while(fread(&E1,sizeof(E1),1,fp)!=NULL)
                {
                    if(strcmp(E1.name,searchName)==0)
                    {
                       frequency=frequency+1;
                       displayData();

                      fclose(fp);
                      searchAgain:
                       gotoxy(2,30); cout<<"1. Admin Home page";
                       gotoxy(1,30);    cout<<"2. Search another employee";
                       gotoxy(2,25);    cout<<"Enter your preference : ";
                            cin>>i;

                       switch(i)
                       {
                       case 1:
                        {
                           system("cls");
                           AdminMode();
                            break;
                        }
                       case 2:
                        {
                            system("cls");
                            searchEmployee();
                            break;
                        }
                        default:
                        {
                            gotoxy(2,25);
                            cout<<"Invalid request, Please  enter correct preference !!!";
                            _sleep(400);
                            goto searchAgain;
                        }
                       }
                    }

                }

                if(frequency==0)
                 {
                   gotoxy(1,35);    cout<<"Sorry!!! , No record match your search";
                    _sleep(800);
                    system("cls");
                   searchEmployee();
                }
            break;
        }

    case 3:
    {
       system("cls");
       AdminMode();
    }
    default:
        {
            gotoxy(2,30);   cout<<"Invalid request. Please enter correct preference!!!";
            _sleep(500);
            system("cls");
            searchEmployee();

        }
    }

}

void EmployeeLogin()                // EmployeeLogin Function defination
{
    char loginid[8],loginpwd[8];
    login:
    header();
    gotoxy(2,30);
    fp=fopen("D:\\EmployeeDatabase\\Database.dat","rb");
    cout<<"*** Welcome to Employee login page ***\n";
    gotoxy(2,35);   cout<<"Enter following Credentials to Login ";
    gotoxy(3,40);   cout<<"UserName : ";   fflush(stdin); gets(loginid);
    gotoxy(1,40);   cout<<"Password : ";   fflush(stdin);    gets(loginpwd);
    frequency=0;
    while(fread(&E1,sizeof(E1),1,fp)!=NULL)
        {
            if(E1.matchUidPwd(loginid,loginpwd)==1)
            {
                frequency=frequency+20;
               header();
               gotoxy(2,35);    cout<<"*** Welcome "<<E1.name<<" ***";
                displayData();
                fclose(fp);
              gotoxy(2,40);     cout<<"1. Log Out ";
              cout<<"\nEnter your prference : ";  cin>>i;

              switch(i)
              {
              case 1:
                {
                    main();
                    break;
                }
              default:
                {
                    main();
                }
              }

            }

        }

    if(frequency==0)
    {
        gotoxy(2,35);   cout<<"Login Failed !!!! ";
        gotoxy(1,35);   cout<<"Invalid Username or Password";
        _sleep(600);
        preference:
        system("cls");
        gotoxy(2,35);   cout<<"1. Try Again";
        gotoxy(2,35);   cout<<"2. Return to Home";
        cout<<"\nEnter your preference : "; cin>>i;
        switch(i)
        {
        case 1:
            {
                goto login;
            }
        case 2:
            {
                main();
                break;
            }
        default:
            {
                cout<<"Please Enter valid request !";
                _sleep(500);
                goto preference;
            }
        }
    }
}

void feedToDatabase()                   // writing to database
{
    header();
    gotoxy(2,20);   cout<<"Please press Enter to confirm registeration";
    getch();
    fp=fopen("D:\\EmployeeDatabase\\Database.dat","ab");
    fwrite(&E1,sizeof(E1),1,fp);
    fclose(fp);
    gotoxy(2,20);  cout<<"Registeration complete!!!";
       cout<<"\n\n Unique Employee ID  : ";  E1.printR();   cout<<"\nPlease note it down for future reference";
         gotoxy(2,20);  cout<<"Press Enter to return to Home page";
    getch();
    AdminMode();
}

int main()                      // main function
{
    header();
    mkdir(dirname);
     gotoxy(2,40); cout<<"1. Admin mode";
      gotoxy(1,40); cout<<"2. Employee login";
      gotoxy(1,40); cout<<"3. Exit Application";
    gotoxy(2,40);    cout<<"Enter your preference : ";
    cin>>i;

    switch(i)
    {
    case 1:
        {
            char adminID[8],adminPwd[8];
            admin:
            header();
          gotoxy(2,20);   cout<<"*** Enter following credentials to login ***";
            gotoxy(2,30);   cout<<"User Name : ";   cin>>adminID;
            gotoxy(1,30);   cout<<"Password : ";    cin>>adminPwd;
            if(strcmp(adminID,"2000")==0&&strcmp(adminPwd,"2001")==0)
            {
                AdminMode();
               break;
            }
            else
            {
                gotoxy(2,20);   cout<<"Incorrect Username or Password. Please try again!!!";
                _sleep(600);
                goto admin;
            }

        }
    case 2:
        {  EmployeeLogin();
            break;
        }
    case 3:
        {
            exit(1);
        }
    default:
        {
            gotoxy(2,20); cout<<"Invalid Request. Please enter correct preference !!!";
            _sleep(800);
            main();
        }
    }
    getch();
}



void gotoxy(int a,int b)     // gotoxy function defination
{
    for(i=1;i<=a;i++)
    {
        cout<<"\n";
    }
    for(i=1;i<=b;i++)
        cout<<" ";

}

void header()                   // header function defination
{
    system("cls");
    for(i=1;i<=120;i++)
        printf("%c",254);
        cout<<endl;
        for(i=1;i<=120;i++)
            printf("%c",254);
    gotoxy(2,32);
    cout<<"*** Employee Management System ***\n";
    cout<<endl;
    for(i=1;i<=120;i++)
            printf("%c",254);
        cout<<endl;
        for(i=1;i<=120;i++)
            printf("%c",254);

}

Random random()                 // Random ID generator
{
   Random rnd;
    srand(time(0));
	for( i=0;i<=9;i++)
		{rnd.id[i]=rand()%10;}
		return(rnd);
}


int compareID(Random x,Random y)            // function to compare Two RANDOM type of objects
    {
        // returns 1, if ID's are unique
        // returns 0, if ID's are same

       for(i=0;i<10;i++)
       {
           if(x.id[i]!=y.id[i])
           {
               return(1);
           }

       }
       return(0);
    }

