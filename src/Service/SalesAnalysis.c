/*
 * salesanalysis.c
 *
 *  Created on: 2015��6��12��
 *      Author: Administrator
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"

#include "../Common/binary_Balance_tree.h"

//��ȡ��ĿƱ��
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
	int cnt = 0;
	assert(NULL!=list);
	play_list_t playlist;
	play_node_t *pos;
	int sold;//存储已售有效票数
	salesanalysis_list_t p;
	List_Free(list,salesanalysis_node_t);
	List_Init(playlist,play_node_t);
	Play_Srv_FetchAll(playlist);

	BiTree T=NULL;
	int tall=0;

	List_ForEach(playlist,pos)
	{
		p  =   (salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
		strcpy(p->data.area,pos->data.area);
		p->data.duration = pos->data.duration;
		p->data.end_date = pos->data.end_date;
		strcpy(p->data.name,pos->data.name);
		p->data.play_id = pos->data.id;
		p->data.price = pos->data.price;
		p->data.start_date = pos->data.start_date;
		
		p->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold);//票房
		p->data.totaltickets = sold;//上座

		InsertAVL(&T,p->data,&tall);

		//List_AddTail(list,p);
		// printf("剧目id :%d\n",pos->data.id);
		cnt++;
	}

	PreOrderTraverse(T,list);
	return cnt;

}

// //��ĿƱ������
// void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){

// }

//�����ݳ��ƻ�ID��ȡƱ��
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount){
	return 0;

}


//����ƱID��ȡ���ۼ�¼
int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale){
	return 0;

}
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
 { 
	salesanalysis_node_t *p;    
  	if(list == NULL) return ;   
    list->prev->next = NULL;//将循环断开     
	salesanalysis_list_t listleft =  list->next;//listleft指向第一个数据节点 
	list->next = list->prev = list;//将ｌｉｓｔ链表置为空  
	while(listleft != NULL)    
	{   
		       p = listleft;     
			    listleft = listleft->next;       
    SalesAnalysis_Srv_addnode(list,p);//+    
	}     
	return ; 
} 
void SalesAnalysis_Srv_addnode(salesanalysis_list_t list,salesanalysis_node_t *p)
{ 	salesanalysis_node_t *cur;   
   if(list == NULL)  
    {         List_AddTail(list,p);     }     
	  
   else   
  	{        
	   cur = list->next;       
	     while(cur != list)      
		    {            
				 if(p->data.sales > cur->data.sales) break;  
				            cur = cur->next;      
		   }      
		      List_InsertBefore(cur,p);    
	}   
	  return ;
 }
