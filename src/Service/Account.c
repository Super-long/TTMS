/*
 * account.c
 *
 *  Created on: 2015��6��12��
 *      Author: Administrator
 */
#include "Account.h"
#include "../Common/List.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const char ACCOUNT_KEY_NAME[]="Account";

account_t gl_CurUser;

//����ϵͳ��ʼ���˺�admin
void Account_Srv_InitSys(){
	if(Account_Perst_CheckAccFile())//用户文件存在
	{
		return;
	}
	else
	{
		printf("初始化：\n");
		account_t data_admin;
		printf("请输入你的姓名：");
		scanf("%s",data_admin.username);
		// printf("\n请输入你的id：");
		// scanf("%d",&data_admin.id);
		long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //获取主键
		if(key<=0)			
			return 0;
		data_admin.id = key;



		printf("\n请输入你的密码：");
		scanf("%s",data_admin.password);
		encryption(data_admin.password);
		// printf("\n请输入你的类型：");
		data_admin.type=0;

		printf("\n请输入你的密保号码：");

		scanf("%lld",&data_admin.telephone);
	// 										printf("%d\n",data_admin.telephone);
	// setbuf(stdin,NULL);
	// getchar();
		// printf("哈哈");
		// setbuf(stdin,NULL);
		// getchar();
		// fflush(stdin);

		Account_Srv_Add(&data_admin);
	}
	return;

}

//��֤��¼�˺��Ƿ��Ѵ��ڣ����ڣ������¼�û���Ϣ��ȫ�ֱ���gl_CurUser��return 1������return 0
int Account_Srv_Vertify(char usrName[], char pwd[]){
	account_t usr;
	int t;
	t=Account_Perst_SelByName(usrName,&usr);
	if(t==1)
	{
		gl_CurUser=usr;
		// printf(" type = %d\n",gl_CurUser.type);
		return 1;
	}
	// printf(" type = %d\n",gl_CurUser.type);
		
	return 0;
}
int Account_Srv_Vertify1(char usrName[], char pwd[])
{
	account_t usr;
	Account_Perst_SelByName(usrName,&usr);
	if(strcmp(usr.password,pwd)==0)
	{
		gl_CurUser=usr;
		return 1;
	}
	else
	{
		return 0;
	}	
}



//��֤�û����Ƿ���ڣ�����list�������ڣ����ض�Ӧ���ָ�룻���򣬷���null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {

	account_node_t *pos;
	pos=(account_list_t)malloc(sizeof(account_node_t));
	List_ForEach(list,pos)
	{
		if(strcmp(pos->data.username,usrName)==0)
		{
			return pos;
		}
	}

	return NULL ;
}

//����һ���û��˺ţ�ͨ������Account_Perst_Insert(data)����ʵ��
int Account_Srv_Add(const account_t *data){
	int i;

	i=Account_Perst_Insert(data);

	// printf("啊哈");
	// 	setbuf(stdin,NULL);
	// 	getchar();
		
	if(i==1){
		printf("添加成功!\n");
		return 1;
	}
	else
	{
		printf("添加失败！\n");
		return 0;
	}
}

//�޸�һ���û��˺ţ�ͨ������Account_Perst_Update(data)����ʵ��
int Account_Srv_Modify(const account_t *data){
	int i;
	i=Account_Perst_Update(data);

	if(i==0)
	{
		printf("修改密码失败！");
	}
	else
	{
		printf("\n\n\n\n");
	}
}


//ɾ��һ���û��˺ţ�ͨ������Account_Perst_DeleteByID(usrID)����ʵ��
inline int Account_Srv_DeleteByID(int usrID){
	int i;
	i=Account_Perst_DeleteByID(usrID);
	// printf("啊哈");
	// 	setbuf(stdin,NULL);
	// 	getchar();
	if(i==1)
	{
		printf("删除用户成功！");
		return 1;
	}
	else
	{
		printf("删除失败！");
		return 0;
	}
	

}

//��ȡusrID��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelectByID(usrID, buf)����ʵ��
inline int Account_Srv_FetchByID(int usrID, account_t *buf){
	return 1;
}

//��ȡusrName��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelByName(usrName, buf)����ʵ��
int Account_Srv_FetchByName(char usrName[], account_t *buf){
	return Account_Perst_SelByName(usrName,buf);
}

//��ȡ�����û��˺���Ϣ�����浽list�����У�ͨ������Account_Perst_SelectAll(list)����ʵ��
int Account_Srv_FetchAll(account_list_t list){
	int i;
	i=Account_Perst_SelectAll(list);
	return i;
}


