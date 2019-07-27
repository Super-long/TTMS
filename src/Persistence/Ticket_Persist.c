#include "Ticket_Persist.h"
#include "Schedule_Persist.h"
#include "EntityKey_Persist.h"	
#include "Play_Persist.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";
static const char TICKET_KEY_NAME[]="Ticket";

int Ticket_Perst_Insert(int schedule_id,seat_list_t list)
{
	int cnt = 0;
	FILE *fp = fopen(TICKET_DATA_FILE,"ab");
	if(!fp) printf("打开失败%s",TICKET_DATA_FILE);

	schedule_t buf;
	Schedule_Perst_SelectByID(schedule_id,&buf);
	play_t buf2;
	Play_Perst_SelectByID(buf.play_id,&buf2);

	int len = 0;
	seat_node_t *p;
	ticket_t data;
	List_ForEach(list,p)
	{
		data.id = EntKey_Perst_GetNewKeys(TICKET_KEY_NAME,1);
		data.price = buf2.price;
		data.schedule_id = schedule_id;
		data.seat_id = p->data.id;
		data.status = 0;
		fwrite(&data,sizeof(ticket_t),1,fp);
		cnt++;
	}
	fclose(fp);
	

	return cnt;
}

int Ticket_Perst_Rem(int schedule_id)
{
	if(rename(TICKET_DATA_FILE, TICKET_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(TICKET_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(TICKET_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", TICKET_DATA_TEMP_FILE);
		return 0;
	}


	ticket_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(ticket_t), 1, fpSour)) {
			if (schedule_id == buf.schedule_id) {
				found++;
				continue;
			}
			fwrite(&buf, sizeof(ticket_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(TICKET_DATA_TEMP_FILE);
	return found;
}

//����ID�����ݳ�Ʊ
int Ticket_Perst_SelByID(int id, ticket_t *buf)
{//座位id
	assert(NULL!=buf);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	ticket_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			if (id == data.seat_id)
			 {
				*buf = data;
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
	
}

int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id)
{
	assert(NULL!= list);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	ticket_t data;
	int found = 0;
	ticket_list_t p;
	while (!feof(fp))
	 {
		 p = (ticket_list_t)malloc(sizeof(ticket_node_t));
		if (fread(&data, sizeof(ticket_t), 1, fp)) 
		{
			if (schedule_id == data.schedule_id) {
				p->data = data;
				found++;
				List_AddTail(list,p);
			}
			else
			{
				free(p);
			}
			

		}
	}
	fclose(fp);

	return found;
}

int Ticket_Perst_Make(ticket_list_t list)
{

	assert(NULL != list);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	ticket_t data;
	int found = 0;
	ticket_list_t p;
	while (!feof(fp)) {
		p = (ticket_list_t)malloc(sizeof(ticket_node_t));
		if (fread(&data, sizeof(ticket_t), 1, fp))
		 {
				List_AddTail(list,p);
				found++;
			}
			else
			{
				free(p);
			}
			

		}
	fclose(fp);

	return found;
}



int Ticket_Perst_SelectAll(ticket_list_t ticket_list)
{
	ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=ticket_list);

	List_Free(ticket_list, ticket_node_t);

	FILE *fp = fopen("Ticket.dat", "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(ticket_list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;


}