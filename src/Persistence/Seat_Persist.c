/*
 *  Seat_Persist.c
 *
 *  Created on: 2015��5��23��
 *  Author: lc
 */

#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "EntityKey_Persist.h"
#include "../Common/List.h"
#include "../Service/Ticket.h"//?
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";

//���Ӷ���������ʶ����
static const char SEAT_KEY_NAME[] = "Seat";
static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";
static const char TICKET_KEY_NAME[]="Ticket";

int Seat_Perst_Insert(seat_t *data) 
{   
	assert(NULL!=data);
	long key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME, 1); //Ϊ���ݳ��������ȡ
	if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
		return 0;
	data->id = key;		//�����¶�����ص�UI��


	FILE *fp = fopen(SEAT_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) 
	{
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(seat_t), 1, fp);

	fclose(fp);
	return rtn;
}

int Seat_Perst_InsertBatch(seat_list_t list) 
{
	int rtn = 0;
	seat_node_t *p;
	assert(NULL!=list);

	int len = 0;
	List_ForEach(list,p)
	{
		len++;
	}
	int key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME,len);
	if(key <= 0) 
	{
		printf("分配主键失败!\n");
		return 0;
	}
	else
	{
		FILE *fp = fopen(SEAT_DATA_FILE,"ab");
		if(fp == NULL) 
		{
			printf("打开文件失败%s",SEAT_DATA_FILE);
			return 0;
		}
		else
		{
			List_ForEach(list,p)
			{
				p->data.id = key++;
				fwrite(&p->data,sizeof(seat_t),1,fp);
				rtn++;
			}
		}
		fclose(fp);
		
		
	}
	
	return rtn;
}

int Seat_Perst_Update(seat_t *seatdata)
 {
	assert(NULL!=seatdata);
	FILE *fp = fopen(SEAT_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	seat_t buf;
	int found = 0;
	seatdata->id  = (int)EntKey_Perst_GetNewKeys(SEAT_KEY_NAME, 1);
	while (!feof(fp)) {
		if (fread(&buf, sizeof(seat_t), 1, fp)) {
			if (buf.row == seatdata->row && buf.column == seatdata->column)
			 {
				fseek(fp, -((int)sizeof(seat_t)), SEEK_CUR);
				fwrite(seatdata, sizeof(seat_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);
	// printf("found = %d",found);
	return found;
}

int Seat_Perst_DeleteByID(int ID)
 {
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}


	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(SEAT_DATA_TEMP_FILE);
}


int Seat_Perst_DeleteAllByRoomID(int roomID)//书上叫remove all
 {
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}


	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (roomID == buf.roomID) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(SEAT_DATA_TEMP_FILE);
	return found;
}

int Seat_Perst_SelectByID(int ID, seat_t *buf) 
{
	assert(NULL!=buf);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	seat_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}

int Seat_Perst_SelectAll(seat_list_t list) //没用过
{
	seat_node_t *newNode;
	seat_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			newNode = (seat_node_t*) malloc(sizeof(seat_node_t));
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

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID) 
{
	int recCount = 0;
	if(access(SEAT_DATA_FILE,F_OK) == -1)//文件不存在
	{
		printf("SEAT_DATA_FILE文件不存在\n");
		return 0;
	}
	else
	{
		seat_node_t *p ;
		p = (seat_list_t)malloc(sizeof(seat_node_t));
		FILE *fp = fopen(SEAT_DATA_FILE,"rb");
		seat_t q;
		while(1)
		{
				
				if(fread(&q,sizeof(seat_t),1,fp) < 1) break;
				if(q.roomID == roomID)
				{
					p->data = q;
					List_AddTail(list,p);
					recCount++;
				}
				else
				{
					free(p);
				}
				//优化不用全部遍历其实
				p = (seat_list_t)malloc(sizeof(seat_node_t));
		}



		fclose(fp);

		
	}
	return recCount;
}

int  Seat_Perst_Showticket(ticket_list_t list,int schedule_id)
{
	ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, ticket_node_t);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp))
	 {
		if (fread(&data, sizeof(ticket_t), 1, fp))
		 {
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode)
			 {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			if(data.schedule_id == schedule_id)
			{
				newNode->data = data;
				List_AddTail(list,newNode);
				recCount++;
			}
			
		}
	}
	fclose(fp);
	return recCount;
}
