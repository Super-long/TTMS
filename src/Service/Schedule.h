#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "../Common/common.h"
typedef struct 
{
	int hour;
	int minute;
	int second;
}ttms_time_t;

typedef struct 
{
	int year;
	int month;
	int day;
}ttms_date_t;

typedef struct {
	int id;
	int play_id;
	int studio_id;
	ttms_date_t date;
	ttms_time_t time;
	int seat_count;
}schedule_t;

//˫������
typedef struct schedule_node {
	schedule_t data;
	struct schedule_node *next, *prev;
} schedule_node_t, *schedule_list_t;

 int Schedule_Srv_Add(schedule_t *data);

 int Schedule_Srv_Modify( schedule_t *data);

 int Schedule_Srv_DeleteByID(int ID);

 int Schedule_Srv_FetchByID(int ID, schedule_t *buf);

 int Schedule_Srv_FetchAll(schedule_list_t list);

 int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id);
 
//���ݾ�ĿID��ȡƱ��
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);

//�����ݳ�ID��ͳ�������ʼ�Ʊ��������Ʊ��������
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount, int *totalCount);


#endif //SCHEDULE_H_
