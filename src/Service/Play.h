#ifndef PLAY_H_
#define PLAY_H_

#include "../Common/common.h"
#include  "Schedule.h"

typedef enum {
	PLAY_TYPE_FILE=1,
	PLAY_TYPE_OPEAR=2,
	PLAY_TYPE_CONCERT=3
} play_type_t;

typedef enum {
	PLAY_RATE_CHILD = 1,
	PLAY_RATE_TEENAGE = 2,
	PLAY_RATE_ADULT = 3
} play_rating_t;

typedef struct {
	int id;
	char name[31];
	play_type_t type;
	char area[9];
	play_rating_t rating;
	int duration; //�Է���Ϊ��λ
	ttms_date_t start_date;
	ttms_date_t end_date;
	int price;
} play_t;

//˫������
typedef struct play_node {
	play_t data;
	struct play_node *next, *prev;
} play_node_t, *play_list_t;

 int Play_Srv_Add( play_t *data);

 int Play_Srv_Modify( play_t *data);

 int Play_Srv_DeleteByID(int ID);

 int Play_Srv_FetchByID(int ID, play_t *buf);

 int Play_Srv_FetchAll(play_list_t list);

//���ݾ�Ŀ���������Ŀ����������ľ�Ŀ����
 int Play_Srv_FetchByName(play_list_t list, char condt[]);

//���ݾ�Ŀ���ƹ��˴�filter��list���й��ˣ����ع��˺�ʣ��ľ�Ŀ����
int Play_Srv_FilterByName(play_list_t list, char filter[]);

#endif //PLAY_H_
