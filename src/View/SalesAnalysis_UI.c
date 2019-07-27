#include "SalesAnalysis_UI.h"

#include "../Common/List.h"
#include "../Service/Account.h"
#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include <stdio.h>
#include <stdlib.h>

const int SALESANALYSIS_PAGE_SIZE = 5;
//ͳ��Ʊ������
void SalesAnalysis_UI_MgtEntry ()
{
    int i, id;
	int choice;
	salesanalysis_list_t head;
	salesanalysis_node_t *pos;
	Pagination_t paging;

	List_Init(head, salesanalysis_node_t);
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
 
	
	paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);//+
	// int cnt = 100;
	// List_ForEach(head,pos)
	// {
	// 	printf("name = %s  sales = %d\n",pos->data.name,pos->data.sales);
	// }

    //SalesAnalysis_Srv_SortBySale(head);//+ok
	
	// List_ForEach(head,pos)
	// {
	// 	printf("name = %s sales = %d\n",pos->data.name,pos->data.sales);
	// }
	Paging_Locate_FirstPage(head, paging);

    
    
	do {
      
		printf(
				"\n===================================================================\n");
		printf(
				"************************** 票房信息 *******************************\n");
		printf("%6s %20s  %8s  %5s  %20s  %5s %5s %5s\n", "剧目ID", "剧目名字", "出品地区",
				"时长", "上映时间","上座数量","票房","票价");
		printf(
				"-------------------------------------------------------------------\n");
            Paging_ViewPage_ForEach(head, paging, salesanalysis_node_t, pos, i)
			printf("%6d %20s  %8s  %5d  %d/%d/%d->%d/%d/%d  %5d %5d %5d\n", pos->data.play_id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.totaltickets
			,pos->data.sales,pos->data.price);

		printf(
				"------- 共:%2d页 ---------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        //��ʾ������ӳ���µĿ�ѡ��
        printf(
				"*******************************************************************\n");
		printf(
				"[1]上一页   |   [2]下一页   |   [0]返回上层");
		printf(
				"\n\n\n\n===================================================================\n");
        printf("请输入您要进行的操作:");//ѡ��
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
        printf("choice = %c",choice);
		fflush(stdin);

		switch (choice) {
		case 1:
            system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case 2:
            system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice != 0);
	//�ͷ������ռ�
	List_Destroy(head, salesanalysis_node_t);
}
