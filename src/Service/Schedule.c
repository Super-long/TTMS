#include "Schedule.h"
#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "Ticket.h"
#include <stdio.h>
#include "../Service/Sale.h"

int Schedule_Srv_Add(schedule_t *data)
 {
	return Schedule_Perst_Insert(data);
}

int Schedule_Srv_Modify(schedule_t *data)
 {
	return Schedule_Perst_Update(data);
}

 int Schedule_Srv_DeleteByID(int ID)
{
	return Schedule_Perst_RemByID(ID);
}

 int Schedule_Srv_FetchByID(int id,schedule_t *buf)
{
	return Schedule_Perst_SelectByID(id,buf);
}

int Schedule_Srv_FetchAll(schedule_list_t list)
{
        return Schedule_Perst_SelectAll(list);
}

// //
//  int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id) {
// 		return 0;
// }


//有问题　我不知道是要形成一个链表还是直接传回节点
int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id)
{
	return Schedule_Perst_SelectByPlay(list,play_id);

}


//未写
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount)
{
	int value = 0;//存储票房
	int sold = 0; //存储有效售票数量
	schedule_list_t list;
	schedule_node_t *p;
	*soldCount = 0;
	List_Init(list,schedule_node_t);
	Schedule_Perst_SelectByPlay(list,play_id);//构建演出计划链表list
	List_ForEach(list,p)
	{
		value += Ticket_Srv_StatRevSchID(p->data.id,&sold);//+
		*soldCount = *soldCount+sold;
	}
	List_Destroy(list,schedule_node_t);//销毁链表
	return value;
}



//�����ݳ�ID��ͳ�������ʼ�Ʊ��������Ʊ��������
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount, int *totalCount) {
//	return 0;
//}

