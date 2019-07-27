#ifndef 	SALETICKET_UI_H_
#define 	SALETICKET_UI_H_

#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
#include "../Service/Ticket.h"


//���ݾ�ĿID��ʾ�ݳ��ƻ�
void Sale_UI_ShowScheduler(int playID);

void Sale_UI_ShowScheduler1(int playID);
//��Ʊ����
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList);

//������Ʊ��������
void Sale_UI_MgtEntry(void);

//��Ʊ
void Sale_UI_RetfundTicket();

void Sale_UI_ShowTicket(int schedule_id);

void Sale_UI_ShowTicket1(int schedule_id);

int Sale_UI_SellTicket1(ticket_list_t tickList,seat_list_t seatList);

void Sale_UI_ShowTicketBypic(int schedule_id);
#endif
