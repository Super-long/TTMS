/*
 * Common_Persist.c
 *
 *  Created on: 2015年5月4日
 *      Author: Administrator
 */
#include "EntityKey_Persist.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

//定义存储所有实体主键的文件名为EntityKey.dat
static const char ENTITY_KEY_FILE[] = "EntityKey.dat";

typedef struct {
	char entyName[41];
	long key;
} entity_key_t;


/*根据传入的实体名entName及实体个数count，为这个count个新实体分配一个长度为count的主键值区间，
 * 使得每个新实体在该区间内都可以分配到 唯一的 主键。返回值为该主键区间的最小值*/
long EntKey_Perst_GetNewKeys(const char entName[], int count) {
	entity_key_t ent;
	FILE *fp;
	int found = 0;
	long newEntKey = 1;

	if (count < 1) {
		printf("Entity count must be bigger than 0!\n");
		return 0;
	}

	//判断文件是否存在
	if (access(ENTITY_KEY_FILE, 0)) {
		//新建文件
		fp = fopen(ENTITY_KEY_FILE, "wb+");
		if (NULL == fp) {
			return 0;
		}
	} else {
		//以更新模式打开
		fp = fopen(ENTITY_KEY_FILE, "rb+");
		if (NULL == fp) {
			return 0;
		}
	}

	while (!feof(fp)) {
		if (fread(&ent, sizeof(entity_key_t), 1, fp)) {
			if (0 == strcmp(ent.entyName, entName)) {	//找到主键记录
				fseek(fp, -((int)sizeof(entity_key_t)), SEEK_CUR);
				newEntKey = ent.key + 1;
				ent.key += count;
				fwrite(&ent, sizeof(entity_key_t), 1, fp);
				found = 1;
				break;
			}
		}
	}

	//未找到实体的主键记录，新加主键记录到文件末尾，
	if (!found) {
		strcpy(ent.entyName, entName);
		newEntKey = 1;
		ent.key = count;
		fwrite(&ent, sizeof(entity_key_t), 1, fp);
	}

	fclose(fp);

	return newEntKey;
}

