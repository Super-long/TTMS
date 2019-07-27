/*/*
 * Account_UI.c
 *
 *  Created on: 2015��4��24��
 *      Author: Administrator
 */
#include "../View/Account_UI.h"

#include "../Common/List.h"
#include "../Service/Account.h"
#include <stdio.h>
#include <stdlib.h>

static const char ACCOUNT_KEY_NAME[]="Account";

//#include "curses.h"
//#include <conio.h>
#define SIZE 5
#define len 100

extern account_t gl_CurUser;


#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include <stdio.h>
const int key = 0x86;

int change(char *p)
{
    char tmp = *p;
    if((tmp >= '0' && tmp <= '9' ))
    {
        int t = (int)tmp + 15;
        tmp = (char)t;
        *p = tmp;
        return 0;
    }
    else
    {
        int t = (int)tmp^key;
        tmp = (char)t;
        *p = tmp;
    }
    return 0;
}
int encryption(char *str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        change(&str[i]);    
        i++;
    }
    return 0;
}
int reverse(char *p)
{
    char tmp = *p;
    if((tmp >= 48+15 && tmp <= 48+15+9 ))
    {
        int t = (int)tmp - 15;
        tmp = (char)t;
        *p = tmp;
        return 0;
    }
    else
    {
        int t = (int)tmp^key;
        tmp = (char)t;
        *p = tmp;
    }
    return 0;


}
int deciphering(char *str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        reverse(&str[i]);
        i++;
    }
    return 0;
}

int getch()
{
 int c=0;
 struct termios org_opts, new_opts;
    int res=0;
    //-----  store old settings -----------
     res=tcgetattr(STDIN_FILENO, &org_opts);
     assert(res==0);
   //---- set new terminal parms --------
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
  c=getchar();
   //------  restore old settings ---------
  res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  assert(res==0);
  return c;
}









int SysLogin(){

	Account_Srv_InitSys();//0

	gl_CurUser.type=99999999;
	char name[30],passwd[30];
	account_t test;
	int t,count=0;
	long long tele;
	int flag;
	char *p;
	char ch;
	printf("请输入用户名：");
	scanf("%s",name);

	int cnt = 0;

	while(1)
    {
    	printf("\n请输入密码:");
    	for(int i=  0;i<len;i++)
		{
			setbuf(stdin,NULL);
			passwd[i] = getch();
			if(passwd[i] == '\n')
			{
				passwd[i] = '\0';
				break;
			}
			if((int)passwd[i] == 127)
			{
				printf("\b \b");
				i = i-2;
			}
			else
			{
				printf("*");
			}
			if(i < 0) passwd[0] = '\0';
		}
	
		encryption(passwd);
		t=Account_Srv_Vertify1(name,passwd);
		Account_Perst_SelByName(name,&test);

	// printf("%d\n",test.telephone);
	// setbuf(stdin,NULL);
	// getchar();
		if(t==1)
		{
			printf("\n登陆成功！");
			return 1;
		}	
		else
		{
			printf("\n输入错误，请重新输入！");
			cnt++;
		}
		if(cnt==3)
		{
			do{
			printf("\n\n\n三次输入错误，是否找回密码（[0]否退出 | [1]找回密码）:");
			scanf("%d",&flag);
			switch(flag)
			{
				case 1:
							printf("\n输入你的密保号码：");
							scanf("%lld",&tele);
							if(tele==test.telephone)
							{
								printf("\n输入新的密码：");
								for(int i=  0;i<len;i++)
								{
									setbuf(stdin,NULL);
									passwd[i] = getch();
									if(passwd[i] == '\n')
									{
										passwd[i] = '\0';
										break;
									}
									if((int)passwd[i] == 127)
									{
										printf("\b \b");
										i = i-2;
									}
									else
									{
										printf("*");
									}
									if(i < 0) passwd[0] = '\0';
								}
								encryption(test.password);
								Account_Srv_Modify(&test);
								gl_CurUser=test;
	// 								printf("%d\n",gl_CurUser.telephone);
	// setbuf(stdin,NULL);
	// getchar();

								printf("按[enter]自动登录。");
								setbuf(stdin,NULL);
								getchar();
								return;
							}
							else
							{
								printf("密保号码错误，重新输入！");
							}
							
				}
			}while(flag != 0);
			if(flag==0)
			{
				break;
			}
		}
	}
	// printf("%d\n",gl_CurUser.telephone);
	// setbuf(stdin,NULL);
	// getchar();

	return 0;
}



//ϵͳ�û���������
void Account_UI_MgtEntry(){
	account_list_t head;
	account_node_t *pos;
	head=(account_list_t)malloc(sizeof(account_node_t));
	pos=(account_node_t *)malloc(sizeof(account_node_t));
	int i;
	char name[100];
	

	Pagination_t paging;

	List_Init(head, account_node_t);
	paging.offset = 0;
	paging.pageSize = SIZE;
	int choice;

	
	paging.totalRecords = Account_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	system("clear");


	do {
		
		printf("\n===============================================================\n");
		printf("********************** 系统用户信息 ***************************\n");
		printf("%5s  %8s  %10s  %10s  %9s\n", "ID", "类型", "用户名","密码","密保号码");
		printf("---------------------------------------------------------------\n");
		
		
		Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i){
			deciphering(pos->data.password);
			printf("%5d  %5d  %7s  %7s  %9lld\n", pos->data.id,
					pos->data.type, pos->data.username, pos->data.password,pos->data.telephone);
		}

		printf("-------------总计:%2d ----------- Page %2d/%2d -------------------\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("***************************************************************\n");
		printf("[1]上一页            |  [2]下一页                       |\n[3]添加系统用户      |  [4]修改系统用户密码/密保手机号  |\n[5]删除系统用户      |  [6]查询系统用户\n[0]返回              |");
		printf("\n===============================================================\n");
		
		fflush(stdin);
		printf("Your Choice：");
		fflush(stdin);
		scanf("%d", &choice);
	
		fflush(stdin);
		

		switch (choice) {
		case 3:system("clear");
			if (Account_UI_Add(head)) //�����ӳɹ����������һҳ��ʾ
			{
				paging.totalRecords = Account_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, account_node_t);
			}
			break;
		case 4:system("clear");
			printf("输入你要修改的用户名:");
			scanf("%s", name);
			if (Account_UI_Modify(head,name)) {	//������������
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}
			break;
		case 5:system("clear");
			printf("请输入要删除的用户名：");
			scanf("%s", name);
			if (Account_UI_Delete(head,name)) {	//������������
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}
			break;
		case 6:system("clear");
			printf("请输入要查询的用户名：");
			scanf("%s",name);
			if(Account_UI_Query(head,name))
			paging.totalRecords = Account_Srv_FetchAll(head);
			List_Paging(head, paging, account_node_t)
			;
			break;
		case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
			}
			break;
		case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
			}
			break;
		}
	} while (choice != 0);
	//�ͷ������ռ�
	List_Destroy(head, account_node_t);

}

//������ϵͳ�û�����
int  Account_UI_Add(account_list_t list){
	char name1[100];
	printf("请输入要添加的用户名称：");
	scanf("%s",name1);


	

	account_node_t *buf;
	buf=(account_list_t)malloc(sizeof(account_node_t));

	account_list_t flag;
	flag=(account_list_t)malloc(sizeof(account_node_t));
	flag=Account_Srv_FindByUsrName(list,name1);


	
	char passwd[len];
    char passwd2[len];
	if(flag==NULL)
	{

	while(1)
    {
    	printf("\n请输入密码:");
    	for(int i=  0;i<len;i++)
		{
			setbuf(stdin,NULL);
			passwd[i] = getch();
			if(passwd[i] == '\n')
			{
				passwd[i] = '\0';
				break;
			}
			if((int)passwd[i] == 127)
			{
				printf("\b \b");
				i = i-2;
			}
			else
			{
				printf("*");
			}
			if(i < 0) passwd[0] = '\0';
		}
		printf("\n请再次输入密码:");
		for(int i=  0;i<len;i++)
		{
			setbuf(stdin,NULL);
			passwd2[i] = getch();
			if(passwd2[i] == '\n')
			{
				passwd2[i] = '\0';
				break;
			}
			if((int)passwd2[i] == 127)
			{
				printf("\b \b");
				i = i-2;
			}
			else
			{
				printf("*");
			}
			if(i < 0) passwd2[0] = '\0';
		}
		if(strcmp(passwd,passwd2) == 0)
		{
			
			break;
		}
		else
		{
		printf("\n两次输入不一致!"); 
		}
    
    }

	
		encryption(passwd);
		strcpy(buf->data.password,passwd);
		
		long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //获取主键
		if(key<=0)			
			return 0;
		buf->data.id = key;


		printf("\n输入用户类型（1,2,9）：");
		scanf("%d",&buf->data.type);

		printf("请输入密保手机号：");
		scanf("%lld",&buf->data.telephone);


		strcpy(buf->data.username,name1);
	
		
	
		Account_Srv_Add(&buf->data);
	
		
		List_AddTail(list,buf);
		
		
		return 1;
	}
	
	else
	{
		printf("出错！用户已存在！");
	
		return 0;
	}

}


int Account_UI_Modify(account_list_t list,char usrName[]){
	account_node_t *flag;
	flag=(account_list_t)malloc(sizeof(account_node_t));
	flag=Account_Srv_FindByUsrName(list,usrName);	
	

	char passwd[len];
    char passwd2[len];
	if(flag==NULL)
	{
		printf("该用户不存在！");
		
		return;
	}
	else
	{
		while(1)
   		{
		char passwd[len];
    	char passwd2[len];
    	printf("\n请输入密码:");
    	for(int i=  0;i<len;i++)
		{
			setbuf(stdin,NULL);
			passwd[i] = getch();
			if(passwd[i] == '\n')
			{
				passwd[i] = '\0';
				break;
			}
			if((int)passwd[i] == 127)
			{
				printf("\b \b");
				i = i-2;
			}
			else
			{
				printf("*");
			}
			if(i < 0) passwd[0] = '\0';
		}
		printf("\n请再次输入密码:");
		for(int i=  0;i<len;i++)
		{
			setbuf(stdin,NULL);
			passwd2[i] = getch();
			if(passwd2[i] == '\n')
			{
				passwd2[i] = '\0';
				break;
			}
			if((int)passwd2[i] == 127)
			{
				printf("\b \b");
				i = i-2;
			}
			else
			{
				printf("*");
			}
			if(i < 0) passwd2[0] = '\0';
		}
		if(strcmp(passwd,passwd2) == 0)
		{
		
			break;
		}
		else
		{
		printf("\n两次输入不一致!"); 
		}
		
	}

		encryption(passwd);
		strcpy(flag->data.password,passwd);
		
		long long tele;
		int  t;
		while(t!=1)
		{
			printf("\n是否修改位密保号码（[0]不修改 | [1]修改）：");
			scanf("%lld",&t);
			if(t==1)
			{
				printf("输入新的密保号码：");
				scanf("%lld",&tele);
				flag->data.telephone=tele;
			}
			else if(t==0)
			{
				break;
			}
		
			else
			{
				printf("输入错误，重新输入！");
			}
		}
			Account_Srv_Modify(flag);
		
	}


	return 1;

}

//ɾ��ϵͳ�û�����
int Account_UI_Delete(account_list_t list,char usrName[]){
	account_node_t *flag;
	flag=(account_list_t)malloc(sizeof(account_node_t));
	flag=Account_Srv_FindByUsrName(list,usrName);	

	if(flag==NULL)
	{
		printf("该用户不存在！");
	
		return;
	}
	else
	{
	
		Account_Srv_DeleteByID(flag->data.id);

 }
	


	return 1;

}

//��ѯϵͳ�û�����
int Account_UI_Query(account_list_t list,char usrName[]){
	account_node_t *flag;
	flag=(account_list_t)malloc(sizeof(account_node_t));
	flag=Account_Srv_FindByUsrName(list,usrName);	
	deciphering(flag->data.password);
	if(flag==NULL)
	{
		printf("该用户不存在！");
		return 0;
	}
	else
	{
		printf("=============================\n");
		printf("id-------------%d\n",flag->data.id);
		printf("用户名----------%s\n",flag->data.username);
		printf("密码------------%s\n",flag->data.password);
		printf("用户类型---------%d\n",flag->data.type);
		printf("\n\n\n\n\n\n\n\n\n");
	
	}
	return 1;

}


