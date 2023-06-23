#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct jointUser{

	char password[10];
	int account_no;
	float balance;
	char status[20];

	int userID;
	char name1[30];
	char name2[30];
}jointUser;

typedef struct normalUser{

	int account_no;
	float balance;
	char status[20];

	int userID;
	char name[30];
	char password[10];
}normalUser;


typedef struct admin{

	int userID;
	char username[30];
	char password[10];
}admin;

void addAccount(int sockd);
void deleteAccount(int sockd);
void modifyAccount(int sockd);
void findAccount(int sockd);
void showMenu(int sockd);
void deposit(int sockd);
void withdraw(int sockd);
void checkBalance(int sockd);
void changePassword(int sockd);
void displayDetails(int sockd);
void NormalUserLogin(int sockd);
void JointUserLogin(int sockd);
void AdminLogin(int sockd);
void selectOption(int sockd);
int option,currUserID;

void selectOption(int sockd){
	while(1){
		write(1,"1 : Normal-User Login\n",sizeof("1 : Normal-User Login\n"));
		write(1,"2 : Joint Account-User Login\n",sizeof("2 : Joint Account-User Login\n"));
		write(1,"3 : Admin Login\n",sizeof("3 : Admin Login\n"));
		
		write(1,"select an option : ",sizeof("select an option : "));
		scanf("%d",&option);
		printf("Option : %d\n",option);
		//option=option-2608;

		if(option == 1){
			NormalUserLogin(sockd); 
			break;
		}
		else if(option == 2){
			JointUserLogin(sockd);
			break;
		}
		else if(option == 3){
			AdminLogin(sockd);
			break;
		}
		else write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
	}
	return;
}

void showMenu(int sockd){
	int select;
	if(option==1 || option==2){
		write(1,"1 : deposit\n",sizeof("1 : deposit\n"));
		write(1,"2 : withdraw\n",sizeof("2 : withdraw\n"));
		write(1,"3 : Balance Enquiry\n",sizeof("3 : Balance Enquiry\n"));
		write(1,"4 : Password Change\n",sizeof("4 : Password Change\n"));
		write(1,"5 : View Details\n",sizeof("5 : View Details\n"));
		write(1,"6 : Exit\n",sizeof("6 : Exit\n"));
	
		write(1,"select an option : ",sizeof("select an option : "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select){
		case 1 :
			deposit(sockd);
			break;
		case 2 :
			withdraw(sockd);
			break;
		case 3 :
			checkBalance(sockd);
			break;
		case 4 :
			changePassword(sockd);
			break;
		case 5 :
			displayDetails(sockd);
			break;
		case 6 :
			write(sockd,&select,sizeof(int));
			write(1,"Thank you\n",sizeof("Thank you\n"));
			exit(0);
		default :
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			showMenu(sockd);
			break;
		}
	}
	else if(option==3){
		write(1,"1 : Add Account\n",sizeof("1 : Add Account\n"));
		write(1,"2 : Delete Account\n",sizeof("2 : Delete Account\n"));
		write(1,"3 : Modify Account\n",sizeof("3 : Modify Account\n"));
		write(1,"4 : Search Account\n",sizeof("4 : Search Account\n"));
		write(1,"5 : Exit\n",sizeof("6 : Exit\n"));

		write(1,"select an option : ",sizeof("select an option : "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select){
		case 1 :
			addAccount(sockd);
			break;
		case 2 :
			deleteAccount(sockd);
			break;
		case 3 :
			modifyAccount(sockd);
			break;
		case 4 :
			findAccount(sockd);
			break;
		case 5 :
			write(sockd,&select,sizeof(int));
			write(1,"Thank you\n",sizeof("Thank you\n"));
			exit(0);
		default :
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			showMenu(sockd);
			break;
		}
	}
}

void NormalUserLogin(int sockd){
	bool result;
	normalUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	//to the server
	write(sockd,&option,sizeof(int));
	write(sockd,&currUser,sizeof(normalUser));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		selectOption(sockd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void JointUserLogin(int sockd){
	bool result;
	jointUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	//to the server
	write(sockd,&option,sizeof(int));
	write(sockd,&currUser,sizeof(jointUser));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		selectOption(sockd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void AdminLogin(int sockd){
	bool result;
	admin currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	//to the server
	write(sockd,&option,sizeof(int));
	write(sockd,&currUser,sizeof(admin));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		selectOption(sockd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void deposit(int sockd){
	float amt;
	int select=1;
	bool result;

	write(1,"Amount to deposit : Rs.",sizeof("Amount to deposit : Rs."));
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to deposit : Rs.",sizeof("Amount to deposit : Rs."));
		scanf("%f",&amt);
	}

	//to the server
	write(sockd,&select,sizeof(int));
	write(sockd,&amt,sizeof(float));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error depositing your money!!\n\n",sizeof("Error depositing your money!!\n\n"));
	}
	else{
		write(1,"Succesfully deposited!!\n\n",sizeof("Succesfully deposited!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void withdraw(int sockd){
	float amt;
	int select=2;
	bool result;

	write(1,"Amount to withdraw : Rs.",sizeof("Amount to withdraw : Rs."));
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to withdraw : Rs.",sizeof("Amount to withdraw : Rs."));
		scanf("%f",&amt);
	}

	//to the server
	write(sockd,&select,sizeof(int));
	write(sockd,&amt,sizeof(float));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error withdrawing your money, please check your balance!!\n\n",sizeof("Error depositing your money, please check your balance!!\n\n"));
	}
	else{
		write(1,"Succesfully withdrew!!\n\n",sizeof("Succesfully withdrew!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void checkBalance(int sockd){
	float amt;
	int select=3;
	int len;

	//to the server
	write(sockd,&select,sizeof(int));
	
	len=read(sockd,&amt,sizeof(float));	//from server

	write(1,"Balance :: Rs.",sizeof("Balance :: Rs."));
	printf("%0.2f\n\n",amt);

	showMenu(sockd);
	return;
}

void changePassword(int sockd){
	int select=4;
	char nPassword[10];
	bool result;

	write(1,"Enter the new password(max 10 characters) : ",sizeof("Enter the new password(max 10 characters) : "));
	scanf("%s",nPassword);

	//to the server
	write(sockd,&select,sizeof(int));
	write(sockd,nPassword,sizeof(nPassword));

	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error changing your password!!\n\n",sizeof("Error changing your password!!\n\n"));
	}
	else{
		write(1,"Succesfully changed your password!!\n\n",sizeof("Succesfully changed your password!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void displayDetails(int sockd){
	int select=5;

	//to the server
	write(sockd,&select,sizeof(int));

	if(option==1){
		normalUser currUser1;
		read(sockd,&currUser1,sizeof(normalUser));
		
		printf("User ID : %d\n",currUser1.userID);
		printf("Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
		printf("Status : %s\n\n",currUser1.status);
	}
	else if(option==2){
		jointUser currUser2;
		read(sockd,&currUser2,sizeof(jointUser));
		
		printf("User ID : %d\n",currUser2.userID);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
		printf("Status : %s\n\n",currUser2.status);
	}
	showMenu(sockd);
	return;
}

void addAccount(int sockd){
	int select=1;
	int type;
	bool result;

	write(sockd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sockd,&type,sizeof(int));

	if(type==1){
		normalUser addUser1;
		write(1,"Name of the account holder : ",sizeof("Name of the account holder : "));
		scanf(" %[^\n]",addUser1.name);
		write(1,"Password(max 10 characters) : ",sizeof("Password(max 10 characters) : "));
		scanf("%s",addUser1.password);
		write(1,"Initial deposit : Rs.",sizeof("Initial deposit : Rs."));
		scanf("%f",&addUser1.balance);
		write(sockd,&addUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser addUser2;
		write(1,"Name of the primary account holder : ",sizeof("Name of the primary account holder : "));
		scanf(" %[^\n]",addUser2.name1);
		write(1,"Name of the other account holder : ",sizeof("Name of the other account holder : "));
		scanf(" %[^\n]",addUser2.name2);
		write(1,"Password(max 10 characters) : ",sizeof("Password(max 10 characters) : "));
		scanf("%s",addUser2.password);
		write(1,"Initial deposit : Rs.",sizeof("Initial deposit : Rs."));
		scanf("%f",&addUser2.balance);
		write(sockd,&addUser2,sizeof(jointUser));
	}
	
	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error adding the account!!\n\n",sizeof("Error adding the account!!\n\n"));
	}
	else{
		write(1,"Succesfully added the account!!\n\n",sizeof("Succesfully added the account!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void deleteAccount(int sockd){
	int select=2;
	int type,userID;
	bool result;

	write(sockd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);
	
	write(sockd,&type,sizeof(int));

	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&userID);
	write(sockd,&userID,sizeof(int));
	
	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error deleting the account ,please re-check the User ID!!\n\n",sizeof("Error deleting the account ,please re-check the User ID!!\n\n"));
	}
	else{
		write(1,"Succesfully deleted the account!!\n\n",sizeof("Succesfully deleted the account!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void modifyAccount(int sockd){
	int select=3;
	int type;
	bool result;

	write(sockd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sockd,&type,sizeof(int));

	if(type==1){
		normalUser modUser1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser1.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser1.account_no);
		write(1,"New Name of the account holder : ",sizeof("New Name of the account holder : "));
		scanf(" %[^\n]",modUser1.name);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser1.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser1.balance);
		write(sockd,&modUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser modUser2;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser2.userID);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser2.account_no);
		write(1,"New Name of the primary account holder : ",sizeof("New Name of the primary account holder : "));
		scanf(" %[^\n]",modUser2.name1);
		write(1,"New Name of the other account holder : ",sizeof("New Name of the other account holder : "));
		scanf(" %[^\n]",modUser2.name2);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser2.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.balance);
		write(sockd,&modUser2,sizeof(jointUser));
	}
	
	read(sockd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error modifying the account ,please re-check the User ID and Account No!!\n\n",sizeof("Error modifying the account ,please re-check the User ID and Account No!!\n\n"));
	}
	else{
		write(1,"Succesfully modified the account!!\n\n",sizeof("Succesfully modified the account!!\n\n"));
	}
	showMenu(sockd);
	return;
}

void findAccount(int sockd){
	int select=4;
	int type,len;
	bool result;

	write(sockd,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sockd,&type,sizeof(int));

	if(type==1){
		normalUser searchUser1;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sockd,&userID,sizeof(int));
		
		len=read(sockd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.status);
		}
	}

	if(type==2){
		jointUser searchUser2;
		int userID1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID1);
		write(sockd,&userID1,sizeof(int));
		
		len=read(sockd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"The User ID is incorrect!!\n\n",sizeof("The User ID is incorrect!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser2.userID);
			printf("Name of main account holder: %s\n",searchUser2.name1);
			printf("Name of other account holder : %s\n",searchUser2.name2);
			printf("AC Number : %d\n",searchUser2.account_no);
			printf("Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.status);
		}
	}
	showMenu(sockd);
	return;
}

int main(){
	struct sockaddr_in server;
	int sockd,msgLength;
	char buff[50];
	char result;

	sockd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_port=htons(5555);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	
	connect(sockd,(struct sockaddr *)&server,sizeof(server));

	selectOption(sockd);
	showMenu(sockd);	

	close(sockd);

	return 0;
}
