/*
 *salesanalysis.h
 *
 *  Created on: 2015��5��8��
 *      Author: Administrator
 */
#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_

#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"

typedef struct {
	int play_id; 	//��Ŀ���
	char name[31]; 	//��Ŀ����
	char area[9]; 	//��Ŀ����
	int duration; 	//�Է���Ϊ��λ
	long totaltickets; //��ĿƱ��������
	long sales; 	//��ӰƱ��
	int price; 		//��ĿƱ��
	ttms_date_t start_date; 	//��Ŀ��ӳ����
	ttms_date_t end_date; 	//��Ŀ��ӳ����
} salesanalysis_t;

//˫������
typedef struct salesanalysis_node {
	salesanalysis_t data;
	struct salesanalysis_node *next, *prev;
} salesanalysis_node_t, *salesanalysis_list_t;

//��ȡ��ĿƱ��
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list);

//��ĿƱ������
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list);

//���ݾ�ĿID��ȡƱ��
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);
//�����ݳ��ƻ�ID��ȡƱ��
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount);

//�����ݳ��ƻ�ID��ȡƱ������
//int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);

//����ƱID��ȡ���ۼ�¼
int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale);

#endif 
