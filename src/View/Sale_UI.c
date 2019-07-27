#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/Sale.h"
#include "../Common/List.h"
#include "./Seat_UI.h"

static const char SALE_KEY_NAME[]="Sale";

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 5

void Sale_UI_ShowScheduler(int playID)
{
	play_t buf;
	int i;
	int choice;
	i=Play_Srv_FetchByID(playID,&buf);
	if(i==0)
	{
		printf("此剧目id不存在！");
		return;
	}

	schedule_list_t flag;
	List_Init(flag, schedule_node_t);
	Schedule_Srv_FetchByPlay(flag,playID); //flag为剧目id所对应的所有演出计划链表
	
	schedule_list_t pos;
	
	Pagination_t paging;
	int len = 0;
	List_ForEach(flag,pos)
	{
		len++;
	}
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	paging.totalRecords = len;
	Paging_Locate_FirstPage(flag, paging);

	
	do {

		printf(
				"\n==================================================================\n");
		printf(
				"************************** 演出计划信息 **************************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);}

		printf(
				"------- 共:%2d页 -------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        printf("\n\n\n\n"); 
        printf(
				"******************************************************************\n");

		printf("==================================================================\n");
		printf("[1]上一页       [2]下一页      [3]列表显示演出票   \n[4]图形显示演出票              [0]返回\n");
		printf("==================================================================\n");
		
		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");
		
		
		int x;
		switch (choice) {
			case 3:
				system("clear");
				printf("请输入演出计划id：");
				scanf("%d",&x);
				Sale_UI_ShowTicket(x);//传入演出计划id，获取票
				break;
			case 4:
				system("clear");
				printf("请输入演出计划id：");
				scanf("%d",&x);
				Sale_UI_ShowTicketBypic(x);//传入演出计划id，获取票
				break;
			case 1:
				system("clear");
				if (!Pageing_IsFirstPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
				}
				break;
			case 2:
				system("clear");
				if (!Pageing_IsLastPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
				}
				break;
		}
	}while(choice!=0);
	List_Destroy(flag, schedule_node_t);
}



int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	int x,y;
	printf("输入你想要买的票的行号：");
	scanf("%d",&x);
	printf("输入列号：");
	scanf("%d",&y);
	printf("\n");
	ticket_list_t q;
	int cnt2 = 1;


	seat_list_t b;
	b=Seat_Srv_FindByRowCol(seatList,x,y);//传入行列，找到座位信息，，buf储存座位信息链表节点

	if(b == NULL) 
	{
		printf("该座位不存在!");
		return;
	}
	ticket_list_t flag;
	int i;
	flag=Ticket_Srv_FetchByID(b->data.id,tickList);//根据座位id，找到票的信息，，flag存储票信息链表节点
	// printf("tticket_id =%d\n",flag->data.id);

	if(flag == NULL){
		printf("该票不存在！\n");
		return;
	}
	else
	{
		printf("找到该票！\n");
	}
	
	
	if(flag->data.status==0)
	{
		printf("该票等待售出！\n");

		flag->data.status=1;
		Ticket_Srv_Modify(&(flag->data));
		
		sale_t buf;//保存这次售票的销售记录

		
		long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); //获取主键
		if(key<=0)			
			return 0;
		buf.id = key;	
		printf("\n");
		printf("输入你的id");
		scanf("%d",&buf.user_id);

		buf.ticket_id=flag->data.id;
		// printf("tticket_id =%d\n",flag->data.id);
		// printf("tticket_id =%d\n",buf.ticket_id);

		buf.value==flag->data.price;

		struct tm *local;
		time_t t;
		t=time(&t);
		local=localtime(&t);  //当前日期
		printf("%d年%d月%d日\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		buf.date.year=local->tm_year+1900;
		buf.date.month=local->tm_mon+1;
		buf.date.day=local->tm_mday;

		printf("%d时%d分%d秒\n",local->tm_hour,local->tm_min,local->tm_sec);
		buf.time.hour=local->tm_hour;
		buf.time.minute=local->tm_min;
		buf.time.second=local->tm_sec;
		buf.type=1;//买票

	// printf("tticket_id =%d\n",buf.ticket_id);
	
		Sale_Srv_Add(&buf);//讲小书记卢写入文件中


		return 1;
	}
	else if(flag->data.status==1)
	{
		printf("该票已售出！");
		return 0;
	}
	else
	{
		printf("该票已被预定，不可购买！");

		return 0;
	}
}




void Sale_UI_MgtEntry(void)
{
	play_list_t head;
	play_list_t pos;
	
	int i;
	

	Pagination_t paging;

	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = SIZE;
	int choice;

	//��������
	paging.totalRecords = Play_Srv_FetchAll(head);//head返回所有剧目链表
	Paging_Locate_FirstPage(head, paging);
	system("clear");
	

	do {
		printf(
				"\n==================================================================\n");
		printf(
				"***************************** 剧目信息 ***************************\n");
		printf("%5s %15s  %9s  %5s  %20s     %10s\n", "ID", "剧目名字", "出品地区",
				"时长", "开始->结束","票价");
		printf(
				"------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
			printf("%5d %8s  %9s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", pos->data.id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
		}
		printf(
				"------- 共:%2d页 --------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
		

		printf("-------------总计:%2d -------------- Page %2d/%2d --------------------\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("*******************************************************************\n");
		printf("[1]上一页  |   [2]下一页    |  [3]根据ID筛选演出计划  | [4]根据名字筛选演出计划  |   [0]返回");
		printf("\n===================================================================\n");

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");
		char name[64];
		switch (choice)
		 {
			int id;
			case 3:system("clear");
			printf("请输入一个剧目id：");
			scanf("%d",&id);
			Sale_UI_ShowScheduler(id); 
			break;
		
			case 4:
			
            system("clear");
			printf("请输入要查询的剧目名字:");
			scanf("%s", name);
			Schedule_UI_Query(name);
			break;

		// case 4:system("clear");
		// 	printf("请输入要删除的用户名：");
		// 	scanf("%s", name);
		// 	if (Account_UI_Delete(head,name)) {	//������������
		// 		paging.totalRecords = Account_Srv_FetchAll(head);
		// 		List_Paging(head, paging, account_node_t);
		// 	}
			// break;
		// case 5:system("clear");
		// 	printf("请输入要查询的用户名：");
		// 	scanf("%s",name);
		// 	if(Account_UI_Query(head,name))
		// 	paging.totalRecords = Account_Srv_FetchAll(head);
		// 	List_Paging(head, paging, account_node_t)
		// 	;
		// 	break;


		case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		 }
	} while (choice != 0);
	//�ͷ������ռ�
	//List_Destroy(head, sale_node_t);

}


//��Ʊ
void Sale_UI_RetfundTicket(){
	play_list_t head;
	play_list_t pos;
	
	int i;
	char name[64];

	Pagination_t paging;

	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = SIZE;
	int choice;

	//��������
	paging.totalRecords = Play_Srv_FetchAll(head);//head返回所有剧目链表
	Paging_Locate_FirstPage(head, paging);
	system("clear");
	

	do {
		printf(
				"\n==================================================================\n");
		printf(
				"***************************** 剧目信息 ***************************\n");
		printf("%5s %15s  %9s  %5s  %20s     %10s\n", "ID", "剧目名字", "出品地区",
				"时长", "开始->结束","票价");
		printf(
				"------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
			printf("%5d %8s  %9s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", pos->data.id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
		}
		printf(
				"------- 共:%2d页 --------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
		

		printf("-------------总计:%2d -------------- Page %2d/%2d --------------------\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("*******************************************************************\n");
		printf("[1]上一页         |   [2]下一页             |   [3]查询演出计划   |   [4]根据名字筛选演出计划   |   [0]返回");
		printf("\n===================================================================\n");

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");

		switch (choice)
		 {
			int id;
			case 3:system("clear");
			printf("请输入一个剧目id：");
			scanf("%d",&id);
			Sale_UI_ShowScheduler1(id); 
			break;
		case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		case 4:
			
            system("clear");
			printf("请输入要查询的剧目名字:");
			scanf("%s", name);
			Schedule_UI_Query(name);
			break;
		 }
	} while (choice != 0);














	
	// int x;
	// fflush(stdin);
	// printf("请输入要退的票id：");
	// fflush(stdin);
	// scanf("%d", &x);
	// fflush(stdin);

	// ticket_list_t list;
	// List_Init(list,ticket_node_t);
	// Ticket_Srv_Make(list);//文件中获得票链表
	
	// ticket_list_t flag;
	// flag=Ticket_Srv_FetchByTicketID(x,list);//在票链表中 据票id找到对应节点
	// if(flag==NULL)
	// {
	// 	printf("该票不存在！");
	// 	return;
	// }
	// if(flag->data.status==1)
	// {
	// 	flag->data.status==0;
	// 	Ticket_Srv_Modify(&(flag->data));//修改票的状态
		
	// 	sale_t buf;
	// 	printf("输入销售记录id：");//添加销售记录
	// 	scanf("%d",&buf.id);
	// 	printf("输入你的id");
	// 	scanf("%d",&buf.user_id);
	// 	buf.ticket_id==flag->data.id;
	// 	buf.value==(flag->data.price)*(-1);
	// 	printf("输入销售记录的日期：");
	// 	scanf("%d/%d/%d",&buf.date.year,&buf.date.month,&buf.date.day);
	// 	printf("输入销售记录的时间：");
	// 	scanf("%d/%d/%d",&buf.time.hour,&buf.time.minute,&buf.time.second);
	// 	buf.type=-1;
	// 	Sale_Srv_Add(&buf);
	// 	printf("退票成功");

	// }



}


void Sale_UI_ShowTicket(int schedule_id)
{
	schedule_t schedule_buf;
	Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//根据演出计划id，找出演出计划的节点信息  演出计划理由剧目id


	ticket_list_t buf;//buf保存着某演出计划的所有票      票理由演出计划id
	List_Init(buf,ticket_node_t);
	ticket_list_t pos;

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;

	seat_list_t flag;//flag保存演出计划的所有座位      座位里由演出计划id
	List_Init(flag,seat_node_t);
	Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//根据剧目id找到座位链表

	
	paging.totalRecords=Ticket_Srv_FetchBySchID(buf,schedule_id);
	Paging_Locate_FirstPage(buf,paging);

	do {
		
		printf(
				"\n=======================================================\n");
		printf(
				"********************** 票的信息 ***********************\n");
		printf("%5s  %5s  %5s %5s %5s","票id","演出计划id","座位id","价格","状态\n");
		printf(
				"-------------------------------------------------------\n");
		Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
				printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);			
		}
	

		printf(
				"------- 共:%2d条 --------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"*******************************************************\n");
		printf("[1]买票|[0]返回|[3]上一页|[4]下一页\n");
		printf("=======================================================\n");
		
		

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:
			system("clear");
			
			Sale_UI_SellTicket(buf,flag);	
			
			break;

			case 3:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
			}
			break;
			case 4:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	List_Destroy(flag, seat_node_t);
	List_Destroy(buf, ticket_node_t);



}


void Sale_UI_ShowScheduler1(int playID)
{
	play_t buf;
	int i;
	int choice;
	i=Play_Srv_FetchByID(playID,&buf);
	if(i==0)
	{
		printf("此剧目id不存在！");
		return;
	}

	schedule_list_t flag;
	List_Init(flag, schedule_node_t);
	Schedule_Srv_FetchByPlay(flag,playID); //flag为剧目id所对应的所有演出计划链表
	
	schedule_list_t pos;
	
	Pagination_t paging;
	int len = 0;
	List_ForEach(flag,pos)
	{
		len++;
	}
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	paging.totalRecords = len;
	Paging_Locate_FirstPage(flag, paging);

	
	do {

		printf(
				"\n==================================================================\n");
		printf(
				"************************** 演出计划信息 **************************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);}

		printf(
				"------- 共:%2d页 -------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        printf("\n\n\n\n"); 
        printf(
				"******************************************************************\n");

		printf("==================================================================\n");
		printf("[1]上一页   |   [2]下一页   |  [3]显示演出票   |   [0]返回\n");
		printf("==================================================================\n");
		
		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");
		
		
		int x;
		switch (choice) {
			case 3:
				system("clear");
				printf("请输入演出计划id：");
				scanf("%d",&x);
				Sale_UI_ShowTicket1(x);//传入演出计划id，获取票
				break;
			case 1:
				system("clear");
				if (!Pageing_IsFirstPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
				}
				break;
			case 2:
				system("clear");
				if (!Pageing_IsLastPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
				}
				break;
		}
	}while(choice!=0);
	List_Destroy(flag, schedule_node_t);
}

void Sale_UI_ShowTicket1(int schedule_id)
{
	schedule_t schedule_buf;
	Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//根据演出计划id，找出演出计划的节点信息  演出计划理由剧目id


	ticket_list_t buf;//buf保存着某演出计划的所有票      票理由演出计划id
	List_Init(buf,ticket_node_t);
	ticket_list_t pos;

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;

	seat_list_t flag;//flag保存演出计划的所有座位      座位里由演出计划id
	List_Init(flag,seat_node_t);
	Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//根据剧目id找到座位链表

	
	paging.totalRecords=Ticket_Srv_FetchBySchID(buf,schedule_id);
	Paging_Locate_FirstPage(buf,paging);

	do {
		
		printf(
				"\n=======================================================\n");
		printf(
				"********************** 票的信息 ***********************\n");
		printf("%5s  %5s  %5s %5s %5s","票id","演出计划id","座位id","价格","状态\n");
		printf(
				"-------------------------------------------------------\n");
		Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
				printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);			
		}
	

		printf(
				"------- 共:%2d条 --------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"*******************************************************\n");
		printf("[1]退票 |[0]返回|[3]上一页|[4]下一页\n");
		printf("=======================================================\n");
		
		

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:
			system("clear");
			
			Sale_UI_SellTicket1(buf,flag);	
			
			break;

			case 3:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
			}
			break;
			case 4:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	List_Destroy(flag, seat_node_t);
	List_Destroy(buf, ticket_node_t);

}

int Sale_UI_SellTicket1(ticket_list_t tickList,seat_list_t seatList)
{
	int x;
	fflush(stdin);
	printf("请输入要退的票id：");
	fflush(stdin);
	scanf("%d", &x);
	fflush(stdin);

	
	ticket_list_t flag;
	flag=Ticket_Srv_FetchByTicketID(x,tickList);//在票链表中 据票id找到对应节点

	if(flag == NULL){
		printf("该票不存在！\n");
		return;
	}
	else
	{
		printf("找到该票！\n");
	}
	
	
	if(flag->data.status==1)
	{
		printf("该票可以退！\n");

		flag->data.status=0;
		Ticket_Srv_Modify(&(flag->data));
		
		sale_t buf;//保存这次售票的销售记录

		long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); //获取主键
		if(key<=0)			
			return 0;
		buf.id = key;	


		printf("输入你的id");
		scanf("%d",&buf.user_id);
		buf.ticket_id==flag->data.id;
		buf.value==flag->data.price;


		struct tm *local;
		time_t t;
		t=time(&t);
		local=localtime(&t);  //当前日期
		printf("%d年%d月%d日\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		buf.date.year=local->tm_year+1900;
		buf.date.month=local->tm_mon+1;
		buf.date.day=local->tm_mday;

		printf("%d时%d分%d秒\n",local->tm_hour,local->tm_min,local->tm_sec);
		buf.time.hour=local->tm_hour;
		buf.time.minute=local->tm_min;
		buf.time.second=local->tm_sec;
		
		// printf("输入销售记录的日期：");
		// scanf("%d/%d/%d",&buf.date.year,&buf.date.month,&buf.date.day);
		// printf("输入销售记录的时间：");
		// scanf("%d/%d/%d",&buf.time.hour,&buf.time.minute,&buf.time.second);
		
		
		buf.type=-1;//买票

		Sale_Srv_Add(&buf);//讲小书记卢写入文件中


		return 1;
	}
	else
	{
		printf("该票未被购买，不可退！");

		return 0;
	}

}

void Sale_UI_ShowTicketBypic(int schedule_id)
{
	schedule_t schedule_buf;
	Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//根据演出计划id，找出演出计划的节点信息  演出计划理由剧目id

	studio_t buf_studio;
	Studio_Srv_FetchByID(schedule_buf.studio_id,&buf_studio);
	ticket_list_t buf;//buf保存着某演出计划的所有票      票理由演出计划id
	List_Init(buf,ticket_node_t);
	ticket_list_t pos;

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;

	seat_list_t flag;//flag保存演出计划的所有座位      座位里由演出计划id
	List_Init(flag,seat_node_t);
	Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//根据剧目id找到座位链表

	
	paging.totalRecords=Ticket_Srv_FetchBySchID(buf,schedule_id);
	Paging_Locate_FirstPage(buf,paging);

	{
	seat_list_t p;
	int flag2 = 0;
	printf("\n===== #待售 +已售 ' '座位不存在/损坏=====\n\n");
	for(int i = 1;i<=buf_studio.rowsCount;i++)
	{
		printf("第%2d行   ",i);
		for(int j = 1;j<=buf_studio.colsCount;j++)
		{
			flag2 = 0;
			List_ForEach(flag,p)//座位链表
			{
				ticket_list_t tic_tmp;
				tic_tmp = Ticket_Srv_FetchBySeatID(buf,p->data.id);
				if(p->data.row == i && p->data.column == j) 
					{
						//printf("1");
						if(tic_tmp != NULL && tic_tmp->data.status == 1) printf("+ ");
						else printf("# ");
						//printf("%c ",Seat_UI_Status2Char(p->data.status));
						flag2 = 1;
						break;
					}
			}
			if(flag2 == 0) printf("  ");
			}
		printf("\n");
		}
        
        printf(
				"*******************************************************\n");
		printf("[1]买票|[0]返回|[3]上一页|[4]下一页\n");
		printf("=======================================================\n");
		
		

		fflush(stdin);
		printf("请输入：");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:
			system("clear");
			
			Sale_UI_SellTicket(buf,flag);	
			
			break;

			case 3:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
			}
			break;
			case 4:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	List_Destroy(flag, seat_node_t);
	List_Destroy(buf, ticket_node_t);



}