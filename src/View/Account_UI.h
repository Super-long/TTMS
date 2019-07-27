/*
 * Account_UI.h
 *
 *  Created on: 2015��5��8��
 *      Author: Administrator
 */

#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_

#include "../Common/List.h"
#include "../Service/Account.h"

static const int ACCOUNT_PAGE_SIZE = 3;

int encryption(char *str);
int change(char *p);
//ϵͳ��¼
int SysLogin();
int reverse(char *p);
int deciphering(char *str);
//ϵͳ�û���������
void Account_UI_MgtEntry();

//������ϵͳ�û�����
int  Account_UI_Add(account_list_t list);

//�޸�ϵͳ�û�����
int Account_UI_Modify(account_list_t list,char usrName[]);

//ɾ��ϵͳ�û�����
int Account_UI_Delete(account_list_t list,char usrName[]);

//��ѯϵͳ�û�����
int Account_UI_Query(account_list_t list,char usrName[]);

int getch();


#endif /* ACCOUNT_UI_H_ */

