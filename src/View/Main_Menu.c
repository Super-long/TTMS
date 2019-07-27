#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Sale_UI.h"
#include "Account_UI.h"
#include "MaiAccount_UI.h"
#include "SalesAnalysis_UI.h"
#include "StaSales_UI.h"
#include <stdio.h>

#include "../View/Studio_UI.h"
extern account_t gl_CurUser;
void Main_Menu(void) {
	system("clear");
	
	//printf("您好，[%s]先生/女士,您的身份是系统管理员。",gl_CurUser.username);sleep(2);
	// printf("哈哈");
	// 	setbuf(stdin,NULL);
	// 	getchar();
	char choice;
	do { 
		system("clear");
		printf("==================================================================\n");
		printf("========您好，[%s]先生/女士,您的身份是系统管理员。==============\n",gl_CurUser.username);
		printf("==================================================================\n");
		printf("**************** 剧院票务管理系统 ****************\n\n");
		printf("                 [S]演出厅管理界面\n\n");
		printf("                 [F]维护个人资料\n\n");
		printf("                 [A]管理系统用户\n\n");
		printf("\n");
		printf("                 [E]退出系统\n\n");
		printf("==================================================================\n");
		printf("\n请输入您要进行的操作");
		
		fflush(stdin);
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
        fflush(stdin);
		switch (choice)
		 {
		case 'S':
		case 's':
            system("clear");
			Studio_UI_MgtEntry();
			break;
		case 'F':
		case 'f':
            system("clear");
			MaiAccount_UI_MgtEntry();
			break;
        //  case 'P': 
		//  case 'p':
		//  		system("clear");
		// 	 Play_UI_MgtEntry(); 
		// 	 break; 
		// case 'c': 
		//  case 'C':
		//  		system("clear");
		// 	 Ticket_UI_Query(); 
		// 	 break; 
		// case 'Q': 
		// case 'q': 
		// 	system("clear");
		// 	 Schedule_UI_ListAll(); 
		// 	 break; 
		// case 'T': 
		// case 't': 
		// 	system("clear");
		// 	Sale_UI_MgtEntry(); 
		// 	break; 
		// case 'R': 
		// case 'r': 
		// 	Sale_UI_RetfundTicket(); 
		// 	break; 
		// case 'N': 
		// case 'n': 
		// 	StaSales_UI_MgtEntry(); 
			break; 
		case 'A': 
		case 'a':
			system("clear");
			Account_UI_MgtEntry();
			break;
		// case 'L': 
		// case 'l':
		// 	system("clear");
		// 	SalesAnalysis_UI_MgtEntry();
		// 	break;
		}
	} while ('E' != choice && 'e' != choice);
	// char choice;
	// do { 
	// 	system("clear");
	// 	printf("\n==================================================================\n");
	// 	printf("      **************** 剧院票务管理系统 ****************\n\n");
	// 	printf("                       [S]演出厅管理界面\n");
	// 	printf("                       [P]剧目管理界面\n");
	// 	printf("                       [T]售票管理界面\n");
	// 	printf("                       [C]查询演出票\n");
	// 	printf("                       [R]退票界面\n");
	// 	printf("                       [Q]查询演出界面\n");
	// 	printf("                       [N]统计销售额界面\n");
	// 	printf("                       [L]统计票房界面\n");
	// 	printf("                       [F]维护个人资料\n");
	// 	printf("                       [A]管理系统用户\n");
	// 	printf("\n");
	// 	printf("                       [E]退出系统\n");
	// 	printf("\n==================================================================\n");
	// 	printf("\n请输入您要进行的操作");
		
	// 	fflush(stdin);
	// 	setbuf(stdin,NULL);
	// 	choice = getchar();
	// 	setbuf(stdin,NULL);
    //     fflush(stdin);
	// 	switch (choice)
	// 	 {
	// 	case 'S':
	// 	case 's':
    //         system("clear");
	// 		Studio_UI_MgtEntry();
	// 		break;
    //      case 'P': 
	// 	 case 'p':
	// 	 		system("clear");
	// 		 Play_UI_MgtEntry(); 
	// 		 break; 
	// 	case 'c': 
	// 	 case 'C':
	// 	 		system("clear");
	// 		 Ticket_UI_Query(); 
	// 		 break; 
	// 	case 'Q': 
	// 	case 'q': 
	// 		system("clear");
	// 		 Schedule_UI_ListAll(); 
	// 		 break; 
	// 	case 'T': 
	// 	case 't': 
	// 		system("clear");
	// 		Sale_UI_MgtEntry(); 
	// 		break; 
	// 	case 'R': 
	// 	case 'r': 
	// 		Sale_UI_RetfundTicket(); 
	// 		break; 
	// 	case 'N': 
	// 	case 'n': 
	// 		StaSales_UI_MgtEntry(); 
	// 		break; 
	// 	case 'A': 
	// 	case 'a':
	// 		system("clear");
	// 		Account_UI_MgtEntry();
	// 		break;
	// 	case 'L': 
	// 	case 'l':
	// 		system("clear");
	// 		SalesAnalysis_UI_MgtEntry();
	// 		break;
	// 	}
	// } while ('E' != choice && 'e' != choice);
}
void Main_Menu1(void) {
	// system("clear");
	// printf("您好，[%s]先生/女士,您的身份是售票员。\n",gl_CurUser.username);
	// sleep(2);
	char choice;
	do { 
		system("clear");
		printf("==================================================================\n");
		printf("========您好，[%s]先生/女士,您的身份是售票员。==============\n",gl_CurUser.username);
		printf("==================================================================\n");
		printf("**************** 剧院票务管理系统 ****************\n\n");
		printf("                       [T]售票管理界面\n");
		printf("                       [C]查询演出票\n");
		printf("                       [R]退票界面\n");
		printf("                       [Q]查询演出界面\n");
		printf("                       [N]统计销售额界面\n");
		printf("                       [F]维护个人资料\n");
		printf("\n");
		printf("                       [E]退出系统\n");
		printf("\n==================================================================\n");
		printf("\n请输入您要进行的操作");
		
		fflush(stdin);
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
        fflush(stdin);
		switch (choice)
		 {
		// case 'S':
		// case 's':
        //     system("clear");
		// 	Studio_UI_MgtEntry();
		// 	break;
        //  case 'P': 
		//  case 'p':
		//  		system("clear");
		// 	 Play_UI_MgtEntry(); 
		//  break; 
		case 'c': 
		 case 'C':
		 		system("clear");
			 Ticket_UI_Query(); 
			 break; 
		case 'Q': 
		case 'q': 
			system("clear");
			 Schedule_UI_ListAll(); 
			 break; 
		case 'T': 
		case 't': 
			system("clear");
			Sale_UI_MgtEntry(); 
			break; 
		case 'R': 
		case 'r': 
			Sale_UI_RetfundTicket(); 
			break; 
		case 'N': 
		case 'n': 
			StaSales_UI_MgtEntry(); 
			break; 
		case 'F':
		case 'f':
            system("clear");
			MaiAccount_UI_MgtEntry();
			break;
		// case 'A': 
		// case 'a':
		// 	system("clear");
		// 	Account_UI_MgtEntry();
		// 	break;
		// case 'L': 
		// case 'l':
		// 	system("clear");
		// 	SalesAnalysis_UI_MgtEntry();
		// 	break;
		}
	} while ('E' != choice && 'e' != choice);
}
void Main_Menu2(void) {
	// system("clear");

	// printf("您好，[%s]先生/女士,您的身份是剧院经理。",gl_CurUser.username);sleep(2);
	char choice;
	do { 
		system("clear");
		printf("==================================================================\n");
		printf("========您好，[%s]先生/女士,您的身份是剧院经理。==============\n",gl_CurUser.username);
		printf("==================================================================\n");
		printf("**************** 剧院票务管理系统 ****************\n\n");
		printf("                       [P]剧目管理界面\n");
		printf("                       [C]查询演出票\n");
		printf("                       [N]统计销售额界面\n");
		printf("                       [L]统计票房界面\n");
		printf("                       [F]维护个人资料\n");
		printf("\n");
		printf("                       [E]退出系统\n");
		printf("\n==================================================================\n");
		printf("\n请输入您要进行的操作");
		
		fflush(stdin);
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
        fflush(stdin);
		switch (choice)
		 {
		// case 'S':
		// case 's':
        //     system("clear");
		// 	Studio_UI_MgtEntry();
		// break;
         case 'P': 
		 case 'p':
		 		system("clear");
			 Play_UI_MgtEntry(); 
			 break; 
		case 'c': 
		 case 'C':
		 		system("clear");
			 Ticket_UI_Query(); 
			 break; 
		case 'F':
		case 'f':
            system("clear");
			MaiAccount_UI_MgtEntry();
			break;
		// case 'Q': 
		// case 'q': 
		// 	system("clear");
		// 	 Schedule_UI_ListAll(); 
		// 	 break; 
		// case 'T': 
		// case 't': 
		// 	system("clear");
		// 	Sale_UI_MgtEntry(); 
		// 	break; 
		// case 'R': 
		// case 'r': 
		// 	Sale_UI_RetfundTicket(); 
		// 	break; 
		case 'N': 
		case 'n': 
			StaSales_UI_MgtEntry(); 
			break; 
		// case 'A': 
		// case 'a':
		// 	system("clear");
		// 	Account_UI_MgtEntry();
		// break;
		case 'L': 
		case 'l':
			system("clear");
			SalesAnalysis_UI_MgtEntry();
			break;

		}
	} while ('E' != choice && 'e' != choice);
}

void Main_Menu9(void) {
	system("clear");
	char choice;
	do { 
		system("clear");
		printf("\n\n==================================================================\n");
		printf("\n========您好，[%s]先生/女士,您的身份是超级管理员。=================\n",gl_CurUser.username);
		printf("\n==================================================================\n");
		printf("     **************** 剧院票务管理系统 ****************\n\n");
		printf("      [S]演出厅管理界面                [P]剧目管理界面\n");
		printf("\n");
		printf("      [T]售票管理界面                  [C]查询演出票\n");
		printf("                      \n");
		printf("      [R]退票界面                      [Q]查询演出界面\n");
		printf("                       \n");
		printf("      [N]统计销售额界面                [L]统计票房界面\n");
		printf("                       \n");
		printf("      [F]维护个人资料                  [A]管理系统用户\n");
		printf("                       \n");
		printf("\n");
		printf("      [E]退出系统\n");
		printf("\n==================================================================\n");
		printf("\n请输入您要进行的操作");
		
		fflush(stdin);
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
        fflush(stdin);
		switch (choice)
		 {
		case 'S':
		case 's':
            system("clear");
			Studio_UI_MgtEntry();
			break;
         case 'P': 
		 case 'p':
		 		system("clear");
			 Play_UI_MgtEntry(); 
			 break; 
		case 'F':
		case 'f':
            system("clear");
			MaiAccount_UI_MgtEntry();
			break;
		case 'c': 
		 case 'C':
		 		system("clear");
			 Ticket_UI_Query(); 
			 break; 
		case 'Q': 
		case 'q': 
			system("clear");
			 Schedule_UI_ListAll(); 
			 break; 
		case 'T': 
		case 't': 
			system("clear");
			Sale_UI_MgtEntry(); 
			break; 
		case 'R': 
		case 'r': 
			Sale_UI_RetfundTicket(); 
			break; 
		case 'N': 
		case 'n': 
			StaSales_UI_MgtEntry(); 
			break; 
		case 'A': 
		case 'a':
			system("clear");
			Account_UI_MgtEntry();
			break;
		case 'L': 
		case 'l':
			system("clear");
			SalesAnalysis_UI_MgtEntry();
			break;
		}
	} while ('E' != choice && 'e' != choice);
}