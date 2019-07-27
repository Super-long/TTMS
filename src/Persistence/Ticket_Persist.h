#ifndef TICKETPERSIST_H_
#define TICKETPERSIST_H_

#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "EntityKey_Persist.h"


int Ticket_Perst_Insert(int schedule_id, seat_list_t list);//�����ݳ��ƻ�ʱ����������Ʊ

int Ticket_Perst_Rem(int schedule_id);

int Ticket_Perst_Update(const ticket_t * data);

int Ticket_Perst_SelectByID(int ID, ticket_t *buf) ;

int Ticket_Perst_SelectAll(ticket_list_t list) ;

int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id);

int Ticket_Perst_SelByID(int id, ticket_t *buf);

int Ticket_Perst_Make(ticket_list_t list);

#endif /* TICKETPERSIST_H_ */
