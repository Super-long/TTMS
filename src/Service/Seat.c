/*
 *  Seat.c
 *
 *  Created on: 2015��6��12��
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"
#include <stdio.h>

inline int Seat_Srv_Add(seat_t *data)
 {

	return Seat_Perst_Insert(data);
}

inline int Seat_Srv_AddBatch(seat_list_t list) //书上还没找到
{
	return 0;
}

inline int Seat_Srv_Modify(const seat_t *data)
 {
	return Seat_Perst_Update(data);
}

inline int Seat_Srv_DeleteByID(int ID)
 {
	return Seat_Perst_DeleteByID(ID);
}

inline int Seat_Srv_FetchByID(int ID, seat_t *buf) //Seat_Perst_FetchByID书上的
{
	return Seat_Perst_SelectByID(ID,buf);
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID)
 {
	return Seat_Perst_DeleteAllByRoomID(roomID);
}

//�����ݳ���ID������λ
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID) 
{
	int seatCount = 0;
	seatCount = Seat_Perst_SelectByRoomID(list,roomID);
	//Seat_Srv_SortSeatList(list);//干什么用的
	return seatCount;
	

}

/*���ݷ�ӳ��ID��ȡ��Ч����λ*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)//
 {
	 seat_node_t *p;
	 int seatcount = Seat_Perst_SelectByRoomID(list,roomID);
	 List_ForEach(list,p)
	 {
		 	if(p->data.status != 1)
			 {
				 	List_DelNode(p);
					 seatcount--;
			 } 
	 }
	//排序?
	return seatcount;

}

//�����С�������ʼ���ݳ�������λ
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) 
{
	seat_list_t p ;   
	for(int i = 1;i<=rowsCount;i++)
	{
		for(int j = 1;j<=colsCount;j++)
		{
			    p = (seat_list_t)malloc(sizeof(seat_node_t));
				p->data.roomID = roomID;
				p->data.row = i;
				p->data.column = j;
				p->data.status = 1;
				List_AddTail(list,p);
		}
	}
	
	
	return Seat_Perst_InsertBatch(list);

}

//����λ����list���а���λ�кź��к�����
void Seat_Srv_SortSeatList(seat_list_t list) 
{
		seat_list_t listLeft,p;
       if(list == NULL) return ;
       list->prev->next = NULL;//断开循环链表
       listLeft = list->next;
       list->next = list->prev = list;
       if(listLeft == NULL) return ;
       else
       {
              p = listLeft;
              listLeft = listLeft->next;
              Seat_Srv_AddToSoftedList(list,p);
       }
       return ;
}

//�����node���뵽����������list��
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node)
 {
	 seat_list_t p  = list->next;//可能有问题
       if(list == NULL) 
       {
              List_AddTail(list,node);
       }
       else
       {
              while(p!= list && (p->data.row < node->data.row || (p->data.row == node->data.row && p->data.column < node->data.column)))
              {
                     p = p->next;
              }
              List_AddHead(p,node);
       }
       return ;
}

seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row,int column)
 {
	 seat_list_t p;
	 List_ForEach(list,p)
	 {
		 if(p->data.row == row && p->data.column == column)
		 {
			 return p;
		 }
	 }
	//  printf("aaa");
	// setbuf(stdin,NULL);
	// getchar();
	return NULL;
}

inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) //书上还没找到
{

	return NULL;
}
