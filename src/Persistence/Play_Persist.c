#include "Play_Persist.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Persistence/EntityKey_Persist.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";
static const char PLAY_KEY_NAME[]="Play";

int Play_Perst_Insert( play_t *data) 
{
	 assert(NULL!=data);

                
	long key = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1); //获取主键
	if(key<=0)			
		return 0;
	data->id = key;	



	FILE *fp = fopen(PLAY_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(play_t), 1, fp);

	fclose(fp);
	return rtn;
}

int Play_Perst_Update( play_t *data)
 {
	assert(NULL!=data);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	play_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(play_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(play_t)), SEEK_CUR);
				fwrite(data, sizeof(play_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

int Play_Perst_RemByID(int ID) 
{
	if(rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
		}

		FILE *fpSour, *fpTarg;
		fpSour = fopen(PLAY_DATA_TEMP_FILE, "rb");
		if (NULL == fpSour ){
			printf("Cannot open file %s!\n", PLAY_DATA_FILE);
			return 0;
		}

		fpTarg = fopen(PLAY_DATA_FILE, "wb");
		if ( NULL == fpTarg ) {
			printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
			return 0;
		}

		play_t buf;

		int found = 0;
		while (!feof(fpSour)) {
			if (fread(&buf, sizeof(play_t), 1, fpSour)) {
				if (ID == buf.id) {
					found = 1;
					continue;
				}
				fwrite(&buf, sizeof(play_t), 1, fpTarg);
			}
		}

		fclose(fpTarg);
		fclose(fpSour);

		
		remove(PLAY_DATA_TEMP_FILE);
		return found;
}

int Play_Perst_SelectByID(int ID, play_t *buf) 
{
	assert(NULL != buf);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	play_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
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

int Play_Perst_SelectAll(play_list_t list) 
{
	play_node_t *newNode;
	play_t data;
	int recCount = 0;

	assert(NULL!=list);

    List_Free(list,play_node_t);
	//List_Free(list, play_node_t);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			newNode = (play_t*) malloc(sizeof(play_node_t));
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

//未写
int Play_Perst_SelectByName(play_list_t list, char condt[]) 
{
	assert(NULL!=list);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	play_t data;
	int found = 0;
	play_list_t p;
	while (!feof(fp)) 
	{
		p = (play_list_t)malloc(sizeof(play_node_t));
		if (fread(&data, sizeof(play_t), 1, fp)) {
			if (strstr(data.name,condt))
			 {
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

