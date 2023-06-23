#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

typedef struct admin{
	int uid;
	char username[30];
	char password[10];
}admin;

typedef struct normalUser{
	int uid;
	char name[30];
	char password[10];
	int ACno;
	float balance;
	char status[20];
}normalUser;

typedef struct jointuser{
	int uid;
	char name1[30];
	char name2[30];
	char password[10];
	int ACno;
	float balance;
	char status[20];
}jointuser;

normalUser getNormalUser(int ID);
jointuser getjointuser(int ID);
admin getAdmin(int ID);
bool checkNormalUser(normalUser currUser);
bool checkjointuser(jointuser currUser);
bool checkAdmin(admin currUser);
bool depositMoney(int ACtype,int ID,float amount);
bool withdrawMoney(int ACtype,int ID,float amount);
float showBalance(int ACtype,int ID);
bool alterPassword(int ACtype,int ID,char newPwd[10]);
bool addNormalUser(normalUser record);
bool addjointuser(jointuser record);
bool deleteNormalUser(int ID);
bool deletejointuser(int ID);
bool changenormaluser(normalUser modUser);
void serverTask(int nSocketd);
bool changejointuser(jointuser modUser);
void *connection_handler(void *nSocketd);


normalUser getNormalUser(int ID){
	int i=ID-1000;
	normalUser currUser;
	int fd=open("NUfile",O_RDONLY,0744);
	
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

jointuser getjointuser(int ID){
	int i=ID-1000;
	jointuser currUser;
	int fd=open("JUfile",O_RDONLY,0744);
	
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointuser);    	     //nth record
	lock.l_len=sizeof(jointuser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointuser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

admin getAdmin(int ID){
	int i=ID-1000;
	admin currUser;
	int fd=open("ADfile",O_RDONLY,0744);
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     //nth record
	lock.l_len=sizeof(admin);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

bool checkNormalUser(normalUser currUser){
	int i=currUser.uid-1000;
	int fd=open("NUfile",O_RDONLY,0744);
	bool result;
	normalUser temp;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(normalUser));
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkjointuser(jointuser currUser){
	int i=currUser.uid-1000;
	int fd=open("JUfile",O_RDONLY,0744);
	bool result;
	jointuser temp;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointuser);    	     //nth record
	lock.l_len=sizeof(jointuser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(jointuser));
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAdmin(admin currUser){
	int i=currUser.uid-1000;
	int fd=open("ADfile",O_RDONLY,0744);
	bool result;
	admin temp;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     //nth record
	lock.l_len=sizeof(admin);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(admin));
	if(!strcmp(temp.password,currUser.password))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool depositMoney(int ACtype,int ID,float amount){
	int i=ID-1000;
	if(ACtype==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amount;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;		
	}
	else if(ACtype==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointuser);    //nth record
		lock.l_len=sizeof(jointuser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointuser currUser;
		lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointuser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amount;
			lseek(fd,sizeof(jointuser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointuser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	return false;
}

bool withdrawMoney(int ACtype,int ID,float amount){
	int i=ID-1000;
	if(ACtype==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amount){
			currUser.balance-=amount;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	else if(ACtype==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointuser);    //nth record
		lock.l_len=sizeof(jointuser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointuser currUser;
		lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointuser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amount){
			currUser.balance-=amount;
			lseek(fd,sizeof(jointuser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointuser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float showBalance(int ACtype,int ID){
	int i=ID-1000;
	float result;
	if(ACtype==1){
		int i=ID-1000;
		int fd=open("NUfile",O_RDONLY,0744);
		normalUser temp;
	
		int flock1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    	     //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(normalUser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(ACtype==2){
		int i=ID-1000;
		int fd=open("JUfile",O_RDONLY,0744);
		jointuser temp;
	
		int flock1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointuser);    	     //nth record
		lock.l_len=sizeof(jointuser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(jointuser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool alterPassword(int ACtype,int ID,char newPwd[10]){
	int i=ID-1000;
	if(ACtype==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(ACtype==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int flock1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointuser);    //nth record
		lock.l_len=sizeof(jointuser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointuser currUser;
		lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointuser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(jointuser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointuser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool addNormalUser(normalUser record){
	int fd=open("NUfile",O_RDWR,0744);
	bool result;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser endUser;
	lseek(fd,(-1)*sizeof(normalUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(normalUser));
		
	record.uid=endUser.uid+1;
	record.ACno=endUser.ACno+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(normalUser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool addjointuser(jointuser record){
	int fd=open("JUfile",O_RDWR,0744);
	bool result;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointuser);    //nth record
	lock.l_len=sizeof(jointuser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointuser endUser;
	lseek(fd,(-1)*sizeof(jointuser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(jointuser));
		
	record.uid=endUser.uid+1;
	record.ACno=endUser.ACno+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(jointuser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deleteNormalUser(int ID){
	int i=ID-1000;
	int fd=open("NUfile",O_RDWR,0744);
	bool result;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));
	
	if(!strcmp(currUser.status,"ACTIVE")){	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deletejointuser(int ID){
	int i=ID-1000;
	int fd=open("JUfile",O_RDWR,0744);
	bool result;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointuser);    //nth record
	lock.l_len=sizeof(jointuser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointuser currUser;
	lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointuser));
	
	if(!strcmp(currUser.status,"ACTIVE")){	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(jointuser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(jointuser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}


bool changejointuser(jointuser modUser){
	int i=modUser.uid-1000;
	int fd=open("JUfile",O_RDWR,0744);
	bool result=false;
	
	int flock1;
	struct flock lock;
	lock.l_start=(i)*sizeof(jointuser);   
	lock.l_len=sizeof(jointuser);	
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
    
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointuser currUser;
	lseek(fd,(i)*sizeof(jointuser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointuser));
	
	if(strcmp(currUser.status,"ACTIVE") == false && (modUser.ACno==currUser.ACno) == true){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(jointuser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(jointuser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool changenormaluser(normalUser modUser){
	int i=modUser.uid-1000;
	int fd=open("NUfile",O_RDWR,0744);
	bool result=false;
	
	int flock1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	flock1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));
	
	if(!strcmp(currUser.status,"ACTIVE") && (modUser.ACno==currUser.ACno)){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

void serverTask(int nSocketd){
	int msgLength,select,type,option,ACtype,curruid;
	bool result;
	while(true){
		read(nSocketd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			normalUser currUser1;
			ACtype=1;
			msgLength=read(nSocketd,&currUser1,sizeof(normalUser));
			printf("Username : %d\n",currUser1.uid);
			printf("Password : %s\n",currUser1.password);
			curruid=currUser1.uid;
			result=checkNormalUser(currUser1);
			write(nSocketd,&result,sizeof(result));
		}
		else if(option==2){
			jointuser currUser2;
			ACtype=2;
			msgLength=read(nSocketd,&currUser2,sizeof(jointuser));
			curruid=currUser2.uid;
			printf("Username : %d\n",currUser2.uid);
			printf("Password : %s\n",currUser2.password);
			result=checkjointuser(currUser2);
			write(nSocketd,&result,sizeof(result));
		}
		else if(option==3){
			admin currUser3;
			ACtype=3;
			msgLength=read(nSocketd,&currUser3,sizeof(admin));
			curruid=currUser3.uid;
			printf("Username : %d\n",currUser3.uid);
			printf("Password : %s\n",currUser3.password);
			result=checkAdmin(currUser3);
			write(nSocketd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nSocketd,&result,sizeof(result));
		}
		if(result)	break;		
	}
 
	while(true){
		read(nSocketd,&select,sizeof(int));
		if(option==1 || option==2){
			switch(select){
				case 1: {
				float amount;
				read(nSocketd,&amount,sizeof(float));
				result=depositMoney(ACtype,curruid,amount);
				write(nSocketd,&result,sizeof(result));
				break;
				}
				case 2: {
				float amount;
				read(nSocketd,&amount,sizeof(float));
				result=withdrawMoney(ACtype,curruid,amount);
				write(nSocketd,&result,sizeof(result));
				break;
				}
				case 3: {
				float amount;
				amount=showBalance(ACtype,curruid);
				write(nSocketd,&amount,sizeof(float));
				break;
				}
				case 4: {
				char pwd[10];
				read(nSocketd,pwd,sizeof(pwd));
				result=alterPassword(ACtype,curruid,pwd);
				write(nSocketd,&result,sizeof(result));
				break;
				}
				case 5: {
				if(option==1){
					normalUser user1=getNormalUser(curruid);
					write(nSocketd,&user1,sizeof(normalUser));
				}
				else if(option==2){
					jointuser user2=getjointuser(curruid);
					write(nSocketd,&user2,sizeof(jointuser));
				}
				break;
				}
				default: break;
			}
			
		}
		else if(option==3){
			read(nSocketd,&type,sizeof(int));
			if(select==1){
				if(type==1){
					normalUser newUser1;
					read(nSocketd,&newUser1,sizeof(normalUser));
					result=addNormalUser(newUser1);
					write(nSocketd,&result,sizeof(result));
				}
				else if(type==2){
					jointuser newUser2;
					read(nSocketd,&newUser2,sizeof(jointuser));
					result=addjointuser(newUser2);
					write(nSocketd,&result,sizeof(result));
				}
			}
			else if(select==2){
				if(type==1){
					int deluid1;
					read(nSocketd,&deluid1,sizeof(int));
					result=deleteNormalUser(deluid1);
					write(nSocketd,&result,sizeof(result));
				}
				else if(type==2){
					int deluid2;
					read(nSocketd,&deluid2,sizeof(int));
					result=deletejointuser(deluid2);
					write(nSocketd,&result,sizeof(result));
				}
			}
			else if(select==3){
				if(type==1){
					normalUser modUser1;
					read(nSocketd,&modUser1,sizeof(normalUser));
					result=changenormaluser(modUser1);
					write(nSocketd,&result,sizeof(result));
				}
				else if(type==2){
					jointuser modUser2;
					read(nSocketd,&modUser2,sizeof(jointuser));
					result=changejointuser(modUser2);
					write(nSocketd,&result,sizeof(result));
				}
			}
			else if(select==4){
				if(type==1){
					normalUser searchUser1;
					int uid1;
					read(nSocketd,&uid1,sizeof(int));
					searchUser1=getNormalUser(uid1);
					write(nSocketd,&searchUser1,sizeof(normalUser));
				}
				else if(type==2){
					jointuser searchUser2;
					int uid2;
					read(nSocketd,&uid2,sizeof(int));
					searchUser2=getjointuser(uid2);
					write(nSocketd,&searchUser2,sizeof(jointuser));
				}
			}
			else if(select==5)	break;
		}
	}
	close(nSocketd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}




void *connection_handler(void *nSocketd) {
	int nsfd = *(int*)nSocketd;
	serverTask(nsfd);
}


int main(){
	struct sockaddr_in server,client;
	int sd,nSocketd,clientLen;
	pthread_t threads;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);	
	
	write(1,"Waiting for the client...\n",sizeof("Waiting for the client...\n"));
	while(true){
		clientLen=sizeof(client);
		nSocketd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Connected to the client...\n",sizeof("Connected to the client...\n"));
		if(pthread_create(&threads,NULL,connection_handler,(void*) &nSocketd)<0){
			perror("could not create thread");
			return 1;
		}		
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}
