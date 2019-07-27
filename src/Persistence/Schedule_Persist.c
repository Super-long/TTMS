#include "Schedule_Persist.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "EntityKey_Persist.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>


static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat";
static const char SCHEDULE_KEY_NAME[]="Schedule";

int Schedule_Perst_Insert(schedule_t *data)
{
	assert(NULL!=data);

	
	long key = EntKey_Perst_GetNewKeys(SCHEDULE_KEY_NAME, 1); //获取主键
	if(key<=0)	
	{
			printf("Key <= 0\n");
			return 0;
	}	
		
	data->id = key;	



	FILE *fp = fopen(SCHEDULE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(schedule_t), 1, fp);

	fclose(fp);
	return rtn;
}

int Schedule_Perst_Update( schedule_t *data)
{
	assert(NULL!=data);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	schedule_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(schedule_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(schedule_t)), SEEK_CUR);
				fwrite(data, sizeof(schedule_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

int Schedule_Perst_RemByID(int ID)
{
	if(rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n",SCHEDULE_DATA_FILE);
		return 0;
		}

		FILE *fpSour, *fpTarg;
		fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
		if (NULL == fpSour ){
			printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
			return 0;
		}

		fpTarg = fopen(SCHEDULE_DATA_FILE, "wb");
		if ( NULL == fpTarg ) {
			printf("Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
			return 0;
		}

		schedule_t buf;

		int found = 0;
		while (!feof(fpSour)) {
			if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
				if (ID == buf.id) {
					found = 1;
					continue;
				}
				fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
			}
		}

		fclose(fpTarg);
		fclose(fpSour);

		
		remove(SCHEDULE_DATA_TEMP_FILE);
		return found;
}

int Schedule_Perst_SelectByID(int ID, schedule_t *buf)
{
	assert(NULL != buf);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	schedule_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
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

int Schedule_Perst_SelectAll(schedule_list_t list)
{
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, schedule_node_t);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
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

int Schedule_Perst_SelectByPlay(schedule_list_t buf, int play_id)
{//有问题
	assert(NULL != buf);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	schedule_t data;
	int found = 0;
	schedule_list_t p;
	while (!feof(fp)) {
		p = (schedule_list_t)malloc(sizeof(schedule_node_t));
		if (fread(&data, sizeof(schedule_t), 1, fp))
		 {
			if (play_id == data.play_id) {
				

				p->data = data;
				List_AddTail(buf,p);
				found++;
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
