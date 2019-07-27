/*
 * studio.h
 *
 *  Created on: 2015��4��21��
 *      Author: Administrator
 */
#ifndef STUDIO_H_
#define STUDIO_H_

typedef struct {
	int id;			//��ӳ��ID
	char name[30];	//��ӳ������
	int rowsCount;	//��λ����
	int colsCount;	//��λ����
	int seatsCount;
} studio_t;

//˫������
typedef struct studio_node {
	studio_t data;				//ʵ������
	struct studio_node *next;	//����ָ��
	struct studio_node *prev;	//ǰ��ָ��
} studio_node_t, *studio_list_t;

int Studio_Srv_Add(studio_t *data);

int Studio_Srv_Modify(const studio_t *data);

int Studio_Srv_DeleteByID(int ID);

int Studio_Srv_FetchByID(int ID, studio_t *buf);

int Studio_Srv_FetchAll(studio_list_t list);

//ͨ��ID��list�в��Ҷ�Ӧ��ӳ�����
studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID);

#endif //STUDIO_H_
