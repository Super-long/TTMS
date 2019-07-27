#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Common/List.h"
//�����¶�����Ϣ
int Sale_Srv_Add(sale_t *data){
	return Sale_Perst_Insert(data);

}

//�޸�Ʊ״̬
int Ticket_Srv_Modify (const ticket_t *data){

	return Ticket_Perst_Update(data);
}


//�����ݳ��ƻ�ID��ȡƱ������
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
	return Ticket_Perst_SelectBySchID(list,schedule_id);

}


//����ID��ȡƱ
ticket_node_t * Ticket_Srv_FetchBySeatID (ticket_list_t list, int seat_id)
{
	ticket_node_t* p;
	List_ForEach(list,p)
	{
			if(p->data.seat_id == seat_id) return p;
	}
	return NULL;
}

int Sale_Srv_FetchAll(sale_list_t list){
	int i;
	i=Sale_Perst_SelectAll(list);
	return i;
}

int Sale_Srv_FetchByticket(int ticket_id,sale_t *sale)//+
{
	// return 0;
	return Sale_Perst_SelByTicketID(ticket_id,sale);
}

int Ticket_Srv_FetchBySchID2(ticket_list_t  list,int schedule_id)
{
	int  count  = 0;
	List_Free(list,ticket_node_t);
	count = Ticket_Perst_SelectBySchID(list,schedule_id);
	return count;
}