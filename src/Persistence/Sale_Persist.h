#ifndef SLAEINGPERSIST_H
#define SALEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"

//�洢�¶���
int Sale_Perst_Insert (sale_t *data);
//����Ʊ״̬
int Ticket_Perst_Update (const ticket_t *data);

//�����ݳ��ƻ�ID����Ʊ������
int Ticket_Srv_SelBySchID(int id, ticket_list_t list);

//����ƱID�������ۼ�¼
int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale);

//����ID�������ۼ�¼
int Sale_Perst_SelByID (sale_list_t list, int usrID);

int Sale_Perst_SelectAll(sale_list_t list);
int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale);
#endif
