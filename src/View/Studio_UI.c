/*
 * Studio_UI.c
 *
 *  Created on: 2015��4��24��
 *      Author: Administrator
 */
#include "../View/Studio_UI.h"

#include "../Common/List.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"


static const int STUDIO_PAGE_SIZE = 5;

#include <stdio.h>

void Studio_UI_MgtEntry(void) {
	int i, id;
	int choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//��������
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
    
    /* int cnt = 0; */
	do {
        //��ӡ��ӳ���Ļ�����Ϣ
		printf(
				"\n\n==================================================================\n\n");
		printf(
				"********************** 演出厅信息 ********************************\n\n");
		printf("%5s %20s %2s %2s %5s\n", "ID", "名字", "行",
				"列", "座位数量\n");
		printf(
				"------------------------------------------------------------------\n\n");
		    //��ʾ����
		Paging_ViewPage_ForEach(head, paging, studio_node_t, pos, i){
			printf("%5d %20s %2d %2d %5d\n\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
		}

		printf(
				"------- 共:%2d条 ----------------------- 页数 :%2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		 
        
        //��ʾ������ӳ���µĿ�ѡ��
        printf("******************************************************************\n\n");
		printf(
				"[1]上一页　　            [2]下一页　　            [3]添加演出厅\n\n[4]删除演出厅            [5]修改演出厅             [6]座位管理 \n\n[0]返回上层");
		printf(
				"\n\nt==================================================================\n");
        printf("\n请输入您要进行的操作:");//ѡ��
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
		fflush(stdin);


        //����ѡ�������Ӧ�ĺ���
		switch (choice) {
		case 3:
            system("clear");
			if (Studio_UI_Add()) //�����ӳɹ����������һҳ��ʾ
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
			}
			break;
		case 4:
            system("clear");
			printf("请输入要删除的演出厅ID:");
			scanf("%d", &id);
			if (Studio_UI_Delete(id)) {	//������������
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 5:
            system("clear");
			printf("请输入要修改的演出厅ID");
			scanf("%d", &id);
			if (Studio_UI_Modify(id)) {	//������������
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 6:
            system("clear");
			printf("请输入要管理座位的演出厅:");
			scanf("%d", &id);
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t)
			;
			break;
		case 1:
            system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 2:
            system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 0);
	//�ͷ������ռ�
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;

	do {
		printf("\n=======================================================\n");
		printf("****************  添加新的演出厅  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("演出厅名字:");
		fflush(stdin);
		gets(rec.name);
		printf("演出厅座位行数:");
		scanf("%d", &(rec.rowsCount));
		printf("演出厅座位列数:");
		scanf("%d", &(rec.colsCount));
		rec.seatsCount = 0;
		printf("=======================================================\n");

		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("成功添加新演出厅!\n");
		} else
			printf("新演出厅添加失败!\n");
		printf("-------------------------------------------------------\n");
		printf("[A]继续添加, [R]返回上层:");
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	system("clear");
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("该演出厅不存在!\n按下 [Enter] 返回上层!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}

	printf("\n=======================================================\n");
	printf("****************  修改演出厅信息  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("演出厅ID:%d\n", rec.id);
	printf("演出厅名字[%s]:", rec.name);
	fflush(stdin);
	setbuf(stdin,NULL);
	gets(rec.name);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		do {			//�����λ�ļ���������λ��Ϣ������µ����б������ǰ�󣬷�����������
			printf("演出厅行数>= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("演出厅列数 >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		} while (newrow < rec.rowsCount || newcolumn < rec.colsCount);
		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	} else {
		printf("座位行数:");
		scanf("%d", &rec.rowsCount);
		printf("座位列数:");
		scanf("%d", &rec.colsCount);
		rec.seatsCount = 0;
	}

	printf("-------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"成功修改演出厅信息!\n按下[Enter]返回上层!\n");
	} else
		printf("修改演出厅信息失败!\n按下[Enter]返回上层!\n");

	setbuf(stdin,NULL);
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		
		if (Seat_Srv_DeleteAllByRoomID(id))
			printf("成功删除演出厅座位!\n");
		printf(
				"成功删除演出厅!\n按下 [Enter]返回上层!\n");
		rtn = 1;
	} else {
		printf("演出厅不存在!\n按下[Enter]返回上层!\n");
	}

	setbuf(stdin,NULL);
	getchar();
	return rtn;
}

