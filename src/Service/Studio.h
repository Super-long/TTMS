/*
 * studio.h
 *
 *  Created on: 2015年4月21日
 *      Author: Administrator
 */
#ifndef STUDIO_H_
#define STUDIO_H_

typedef struct {
	int id;			//放映厅ID
	char name[30];	//放映厅名称
	int rowsCount;	//座位行数
	int colsCount;	//座位列数
	int seatsCount;
} studio_t;

//双向链表
typedef struct studio_node {
	studio_t data;				//实体数据
	struct studio_node *next;	//后向指针
	struct studio_node *prev;	//前向指针
} studio_node_t, *studio_list_t;

int Studio_Srv_Add(studio_t *data);

int Studio_Srv_Modify(const studio_t *data);

int Studio_Srv_DeleteByID(int ID);

int Studio_Srv_FetchByID(int ID, studio_t *buf);

int Studio_Srv_FetchAll(studio_list_t list);

//通过ID在list中查找对应放映厅结点
studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID);

#endif //STUDIO_H_
