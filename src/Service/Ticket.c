#include "Ticket.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include "./Sale.h"
#include <stdio.h>
#include <stdlib.h>

int Ticket_Srv_GenBatch(int schedule_id, int studio_id)
{
	seat_list_t list;
	list = (seat_node_t*)malloc(sizeof(seat_node_t));
	List_Init(list,seat_node_t);
	Seat_Srv_FetchValidByRoomID(list,studio_id);
	  int cnt = Ticket_Perst_Insert(schedule_id,list);
	if(cnt > 0)
	{
		printf("成功生成票!\n");
	}
	else
	{
		printf("生成票失败!\n");
	}
	
	return cnt;
}

int Ticket_Srv_DeleteBatch(int schedule_id) 
{
	return Ticket_Perst_Rem(schedule_id);
}


ticket_list_t Ticket_Srv_FetchByID (int id,ticket_list_t buf)//id 是什么id
{
	ticket_list_t p;
	List_ForEach(buf,p)
	{
		if(p->data.seat_id == id)
		return p;
	}
	return NULL;
	
}

ticket_list_t Ticket_Srv_FetchByTicketID(int x,ticket_list_t list)
{
	ticket_list_t p;
	List_ForEach(list,p)
	{
		if(p->data.id == x)
		return p;
	}
	return NULL;
}



int Ticket_Srv_Make(ticket_list_t list)
{
	return Ticket_Perst_Make(list);
}


int Ticket_Srv_FetchAll(ticket_list_t ticket_list)
{
	return Ticket_Perst_SelectAll(ticket_list);
}
int Ticket_Srv_StatRevSchID(int schedule_id,int *soldCount)
{
	int value = 0;//存放票房
	ticket_list_t list;
	ticket_node_t *p;
	sale_t sale;
	List_Init(list,ticket_node_t);
	*soldCount = 0;//有效售票室数量
	// *soldCount = Ticket_Srv_FetchBySchID(list,schedule_id);//+
	Ticket_Srv_FetchBySchID2(list,schedule_id);
	List_ForEach(list,p)
	{
		Sale_Srv_FetchByticket(p->data.id,&sale);//+
		//sale.type = 1;
		if(sale.type == 1 && p->data.status == 1)//确认为买票状态，再确认为已售
		{
			*soldCount++;
			value +=  p->data.price;
		}
	}

	List_Destroy(list,ticket_node_t);
	return value;
}