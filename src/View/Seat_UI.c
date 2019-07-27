/*
 *  Seat_UI.c
 *
 *  Created on: 2015��5��23��
 *  Author: lc
 */
#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>

//����״̬���ض�Ӧ��ʾ״̬����
inline char Seat_UI_Status2Char(seat_status_t status) 
{//' ' # * 0 1 9
	if(status == 0) return ' ';
	else if(status == 1) return '#';
	return '*';
}

//����״̬���ŷ�����λ״̬
inline seat_status_t Seat_UI_Char2Status(char statusChar) 
{
	if(statusChar == ' ') return 0;
	else if(statusChar == '#') return 1;
	return 9;
}

void Seat_UI_MgtEntry(int roomID)
 {
	 	studio_t buf;
	if(Studio_Srv_FetchByID(roomID,&buf))
	{//演出厅存在
		seat_list_t list;
		List_Init(list,seat_node_t);
		if(!Seat_Srv_FetchByRoomID(list,roomID))//判断座位是否存在
		{//不存在座位
			
			buf.seatsCount = Seat_Srv_RoomInit(list,roomID,buf.rowsCount,buf.colsCount);
			Studio_Srv_Modify(&buf);
			printf("座位初始化完成!\n");
			printf("按[ENTER]继续\n");
			setbuf(stdin,NULL);
			getchar();
		}
		else
		{
				seat_node_t *p;
				int flag = 0;
				for(int i = 1;i<=buf.rowsCount;i++)
				{
					printf("第%2d行   ",i);
					for(int j = 1;j<=buf.colsCount;j++)
					{
						flag = 0;
						List_ForEach(list,p)
						{
								if(p->data.row == i && p->data.column == j) 
								{
									printf("%c ",Seat_UI_Status2Char(p->data.status));
									flag = 1;
									break;
								}
						}
						if(flag == 0) printf("  ");
						}
					printf("\n");
				}

						int choice ;             
						do
						{
							printf(
									"******************************************************************\n");
							printf(
									"[1]添加座位 | [2]删除座位 |  [3]修改座位 | [0]返回上层");
							printf(
									"\n\n\n\n==================================================================\n");
							printf("请输入您要进行的操作:");
							setbuf(stdin,NULL);
							scanf("%d",&choice);


							switch (choice)
							{
										case 1:
										{
												int row,col;
												printf("请输入要添加的座位坐标:\n");
												do
												{
													if(row > buf.rowsCount || col > buf.colsCount)
														printf("输入不合法!\n");
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
												}while(row > buf.rowsCount || col > buf.colsCount);

												Seat_UI_Add(list,roomID,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
												// char map[buf.rowsCount+5][buf.colsCount+5];
												// Seat_Srv_map(list,(char*)map,buf.colsCount);
												// //printf("输出座位!\n");
												// for(int  i =1;i<=buf.rowsCount;i++)
												// {
												// 	printf("第%d行 ",i);
												// 	for(int j = 1;j<=buf.colsCount;j++)
												// 	{
												// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
												// 	}
												// 	printf("\n");
												// }
												//system("clear");
												break;
										}


									case 2:
								
										{
											int row,col;
											printf("请输入要删除的座位坐标:\n");
											do
												{
													if(row > buf.rowsCount || col > buf.colsCount)
														printf("输入不合法!\n");
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Delete(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("输出座位!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("第%d行 ",i);
											// 	for(int j = 1;j<=buf.colsCount;j++)
											// 	{
											// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
											// 	}
											// 	printf("\n");
											// }
											// //system("clear");
											break;
										}
										


									case 3:
										{
											int row,col;
											printf("请输入要管理的座位坐标:\n");
											do
												{
													if(row > buf.rowsCount || col > buf.colsCount)
														printf("输入不合法!\n");
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Modify(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("输出座位!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("第%d行 ",i);
											// 	for(int j = 1;j<=buf.colsCount;j++)
											// 	{
											// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
											// 	}
											// 	printf("\n");
											// }
											// //system("clear");
											break;
										}
										



									default:
										printf("输入有误，请重新输入!\n");
										break;
							}
									
						}while(choice != 0);
						system("clear");

					
		}
		
		
	}
	else
	{
		printf("演出厅不存在!\n");
		printf("按[ENTER]返回上层");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
		return ;
	}
	return ;
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) 
{  
	int choice;
	do 
	{
		seat_list_t p = Seat_Srv_FindByRowCol(list,row,column);
		if(p != NULL)
		{
			printf("座位已经存在!\n");
			printf("按下[ENTRE]返回上层!\n");
			setbuf(stdin,NULL);
			getchar();
			return 0;
		}
		else
		{//座位不存在可以添加
			seat_t data;
			data.roomID = roomID;
			data.row = row; 
			data.column = column;
			printf("请输入座位状态([0]过道 | [1] 好 | [9] 损坏):");
			scanf("%d",&data.status);
			if(Seat_Srv_Add(&data))
			{
				printf("添加成功!\n");
			}
			else printf("添加失败!\n");
			// printf("按下[ENTRE]返回上层!\n");
			// setbuf(stdin,NULL);
			// getchar();
			
			printf("[1] 继续添加 | [0]返回上层");
			scanf("%d",&choice);
			
		}
			
	}while(choice != 0);
	return 	1;
	
}

int Seat_UI_Modify(seat_list_t list, int row, int column)
 {
	 int flag = 0;
	seat_list_t p = Seat_Srv_FindByRowCol(list, row, column);
	if( p == NULL)
	{
		printf("该座位不存在!\n");
	}
	else
	{
				seat_t rec;
				printf("请输入要修改的座位状态([0]过道 | [1] 好 | [9] 损坏):");
				setbuf(stdout,NULL);
				setbuf(stdin,NULL);
				scanf("%d",&rec.status);
				rec.column = p->data.column;
				rec.roomID = p->data.roomID;
				rec.row = p->data.row;
				// printf("status = %d\n",rec.status);
				Seat_Srv_Modify(&rec);
	}
	
	return 0;
}

int Seat_UI_Delete(seat_list_t list, int row, int column)
 {
	 int rtn = 0;
	seat_list_t p = Seat_Srv_FindByRowCol(list,row,column);
	if (p != NULL)
	 {
		
		Seat_Srv_DeleteByID(p->data.id);
		printf(
				"成功删除座位!\n按下 [Enter]返回上层!\n");
		rtn = 1;
	} 
	else 
	{
		printf("座位不存在!\n按下[Enter]返回上层!\n");
	}

	setbuf(stdin,NULL);
	getchar();
	return rtn;
	return 0;

}
int Seat_UI_ShowTicket(ticket_list_t list,int schedule_id)
{
	return Seat_Perst_Showticket(list,schedule_id);
}
