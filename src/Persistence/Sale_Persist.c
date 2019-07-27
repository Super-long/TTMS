#include "Sale_Persist.h"
#include "../Common/List.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <string.h>
#include "EntityKey_Persist.h"


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";
static const char TICKET_KEY_NAME[]="Ticket";

//�洢�¶���
int Sale_Perst_Insert (sale_t *data){

	FILE *fp;
	fp=fopen("Sale.dat","ab+");
	if(fp==NULL)
	{
		printf("打开文件失败!");
		return 0;
	}
	
	if(fwrite(data,sizeof(sale_t),1,fp))
	{
		printf("写入文件成功！");
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}


//����Ʊ״̬
int Ticket_Perst_Update (const ticket_t *data){
	assert(NULL!=data);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	ticket_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(ticket_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(ticket_t)), SEEK_CUR);
				fwrite(data, sizeof(ticket_t), 1, fp);
				// printf("status = %d\n",data->status);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}



//�����ݳ��ƻ�ID����Ʊ������
int Ticket_Srv_SelBySchID(int id, ticket_list_t list){
	return 0;
}


//����ID�������ۼ�¼
int Sale_Perst_SelByID (sale_list_t list, int usrID){
	sale_node_t *newNode;
	sale_t data;
	int recCount = 0;

	assert(NULL!=list);

	FILE *fp = fopen("Sale.dat", "rb+");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			newNode = (sale_node_t*) malloc(sizeof(sale_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			if(data.user_id==usrID)
			{
				newNode->data = data;
				List_AddTail(list, newNode);
				recCount++;
			}
		}
	}
	fclose(fp);
	return recCount;

}


int Sale_Perst_SelectAll(sale_list_t list) {
	
	sale_node_t *newNode;
	sale_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, sale_node_t);

	FILE *fp = fopen("Account.dat", "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			newNode = (sale_node_t*) malloc(sizeof(sale_node_t));
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

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale)
{
	assert(NULL != sale);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	sale_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			if (ticket_id == data.ticket_id) {
				*sale =  data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}