#include "Ticket_UI.h"

#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int Ticket_UI_MgtEntry(int schedule_id)
 {	
	 schedule_t rec;;
	 if (! Schedule_Srv_FetchByID(schedule_id,&rec)) {
		printf("该演出计划不存在!\n按 [Enter] 返回上层!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	play_t rec2;
	if (!Play_Srv_FetchByID(rec.play_id, &rec2)) {
		printf("该剧目不存在!\n按 [Enter] 返回上层!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	
	
		printf(
				"\n==================================================================\n");
		printf(
				"*************************** 演出计划信息 ***************************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		

			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n",rec.id ,
					rec.play_id, rec.studio_id, rec.date.year,
					rec.date.month,rec.date.day,rec.time.hour,
					rec.time.minute,rec.time.second,rec.seat_count);
        printf(
				"******************************************************************\n");
				printf(
				"\n==================================================================\n");
		printf(
				"********************** 剧目信息 **********************\n");
		printf("%5s %15s   %9s  %5s  %20s  %13s\n", "ID", "剧目名字", "出品地区",
				"时长", "开始->结束","票价");
		printf(
				"------------------------------------------------------------------\n");
			printf("%5d %10s  %8s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", rec2.id,rec2.name,rec2.area,
			rec2.duration,rec2.start_date.year,rec2.start_date.month,rec2.start_date.day,rec2.end_date.year,
			rec2.end_date.month,rec2.end_date.day,rec2.price);
        printf(
				"******************************************************************\n");
		printf(
				"[1]生成演出票　　|　　[2]重新生成票 　　|　　 [0]返回上层\n");
		printf(
				"==================================================================\n");
		int choice;
		printf("请输入您要进行的操作:");
			setbuf(stdin,NULL);
			scanf("%d", &choice);
			switch(choice)
			{
				case 1:
					Ticket_Srv_GenBatch(schedule_id,rec.studio_id);
					break;
				case 2:
					printf("重新");
					Ticket_Srv_DeleteBatch(schedule_id);
					Ticket_Srv_GenBatch(schedule_id,rec.studio_id);
					break;
				case 0:
					break;
				default:
					printf("输入有误!\n");
					break;
			}
		printf("按[ENTER]返回上层");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
		return 0;
}

void Ticket_UI_Query(void) {
	ticket_list_t ticket_list;
	List_Init(ticket_list,ticket_node_t);
	Ticket_Srv_FetchAll(ticket_list);//获取所有票
	ticket_list_t pos=(ticket_list_t)malloc(sizeof(ticket_node_t));
	int choice,id;

	do
	{
	system("clear");
	printf("====================================================\n");
	printf("[1]显示所有演出票   |   [2]查询演出票   |   [0]返回");
	printf("\n====================================================\n");

	printf("\n\n\n");

	
	fflush(stdin);
	printf("请输入：");
	fflush(stdin);
	scanf("%d", &choice);
	fflush(stdin);
	

	switch(choice)
	{
		case 1:system("clear");
			Ticket_UI_ShowTicket(ticket_list);
			break;
		case 2:
			system("clear");
			printf("输入你想查找的票的id");
			scanf("%d",&id);
			pos=Ticket_Srv_FetchByID(id,ticket_list);
			printf(
				"\n=======================================================\n");
			printf(
				"*********************** 票的信息 **********************\n");
			printf("%5s  %5s  %5s %5s %5s","票id","演出计划id","座位id","价格","状态");
			printf(
				"\n-------------------------------------------------------\n");
			printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);
			printf("\n\n\n\n提示：输入任意键返回。");
			setbuf(stdin,NULL);
			getchar();
			break;
		}
	}while(choice != 0);

}

int Ticket_UI_ShowTicket(ticket_list_t list) 
{
	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;
	Paging_Locate_FirstPage(list,paging);
	
	
	ticket_list_t p;
	ticket_list_t pos;
	int count;
	List_ForEach(list,p)
	{
		count++;
	}
	paging.totalRecords=count;

	do {
		
		printf(
				"\n==============================================================\n");
		printf(
				"*********************** 票的信息 *****************************\n");
		printf("%5s  %5s  %5s %5s %5s","票id","演出计划id","座位id","价格","状态");
		printf(
				"\n--------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(list, paging, ticket_node_t, pos, i){
				printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);			
		}
	

		printf(
				"------- 共:%2d条 ---------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"**************************************************************\n");
		printf("[0]返回   |   [1]上一页   |   [2]下一页");
		printf("\n==============================================================\n");


		printf("\n\n\n\n");

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, ticket_node_t);
			}
			break;
			case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	system("clear");
}
