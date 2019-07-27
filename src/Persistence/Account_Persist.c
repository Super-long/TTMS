/*
 * Account_Persist.c
 *
 *  Created on: 2015��5��8��
 *      Author: Administrator
 */

#include "Account_Persist.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include "EntityKey_Persist.h"	
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

//�ж��˺��ļ��Ƿ���ڣ�����1���ڣ�����0������
int Account_Perst_CheckAccFile() {

	if(access("Account.dat",F_OK)!=-1)
	{
		return 1;
	}
	return 0;
}

//�����û��������˺�,����ɹ� return 1������ return 0
int Account_Perst_SelByName(char usrName[], account_t *buf) {

	FILE *fp;
	account_t flag;
	fp=fopen("Account.dat","ab+");
	if(fp==NULL)
	{
		printf("打开文件失败！");
		return 0;
	}
	while(fread(&flag,sizeof(account_t),1,fp))
	{
		if(strcmp(flag.username,usrName)==0)
		{
			*buf=flag;
		
			return 1;
		}
	}
	return 0;

}

//���˺�д���˺��ļ��У�����ʵ��д������ݿ���Ŀ
int Account_Perst_Insert(account_t *data) {

	FILE *fp;
	fp=fopen("Account.dat","ab+");
	if(fp==NULL)
	{
		printf("打开文件失败!");
		return 0;
	}
	
	if(fwrite(data,sizeof(account_t),1,fp))
	{
	
		printf("写入文件成功！");
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}

//���˺��ļ��в���������˺�ƥ����˺ţ��ҵ� return 1������ return 0�������и�����д
int Account_Perst_Update(const account_t * data) {

	assert(NULL!=data);

	FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	account_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(account_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(account_t)), SEEK_CUR);
				fwrite(data, sizeof(account_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;

}

//���˺��ļ���ɾ�������idƥ����˺ţ�ɾ���ɹ� return 1������ return 0��
int Account_Perst_DeleteByID(int id) {
	// FILE *fp;
	// FILE *fp1;
	// account_node_t *buf;
	// buf=(account_node_t *)malloc(sizeof(account_node_t));

	// fp=fopen("Account.dat","ab+");
	// if(fp==NULL)
	// {
	// 	printf("打开文件失败！");
	// 	return 0;
	// }
	// fp1=fopen("AccountTmp.dat","ab+");
	// if(fp1==NULL)
	// {
	// 	printf("打开文件失败！");
	// 	return 0;
	// }
	// // printf("啊哈");
	// // 	setbuf(stdin,NULL);
	// // 	getchar();
	// while(1)
	// {
	// 	if(fread(buf,sizeof(account_node_t),1,fp)<1)
	// 		break;
	// 	if(buf->data.id!=id)
	// 		fwrite(buf,sizeof(account_node_t),1,fp1);
	// }
	// // printf("啊哈");
	// // 	setbuf(stdin,NULL);
	// // 	getchar();
	// fclose(fp);
	// fclose(fp1);
	// remove("Account.dat");
	// rename("Account.dat","AccountTmp.dat");
	// return 1;
	if(rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(ACCOUNT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(ACCOUNT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", ACCOUNT_DATA_TEMP_FILE);
		return 0;
	}


	account_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(account_t), 1, fpSour)) {
			if (id == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(account_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(ACCOUNT_DATA_TEMP_FILE);
	return found;
}

//���˺��ļ��в��������idƥ����˺ţ���ͨ��ָ��buf������ƥ��ɹ� return 1������ return 0��
int Account_Perst_SelectByID(int id, account_t *buf) {

	return 1;
}

//������ACCOUNT_DATA_FILE�ļ�����̬�����û��˺�list����,list Ϊ����ͷָ�룬����list����
int Account_Perst_SelectAll(account_list_t list) {
	// int count=0;
	// account_node_t *buf;
	// buf=(account_list_t)malloc(sizeof(account_node_t));

	// FILE *fp;
	// fp=fopen("Account.dat","ab+");
	// if(fp==NULL)
	// {
	// 	printf("打开文件失败！");
	// 	return 0;
	// }
	// while(!feof(fp))
	// {
	// 	fread(buf,sizeof(account_node_t),1,fp);
	// 	printf("%d\n",buf->data.id);
	// 	account_list_t new;
	// 	new=(account_list_t)malloc(sizeof(account_node_t));
	// 	List_AddTail(list,new);
	// 	count++;
		
	// }
	// return count;
	account_node_t *newNode;
	account_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, account_node_t);

	FILE *fp = fopen("Account.dat", "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(account_t), 1, fp)) {
			newNode = (account_node_t*) malloc(sizeof(account_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

