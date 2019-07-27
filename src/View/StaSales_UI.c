#include "StaSales_UI.h"

#include "../Common/List.h"
#include "../Service/Sale.h"
#include "../Service/Account.h"
#include "../Service/StaSales.h"
#include <stdio.h>
#include <time.h>

extern account_t gl_CurUser;

void StaSales_UI_MgtEntry ()
{

    if(gl_CurUser.type==USR_CLERK)//售票员
    {
        StaSales_UI_Self();//统计个人销售额
    }
    else if(gl_CurUser.type==USR_MANG ||gl_CurUser.type== 0  )//经理
    {
        StaSales_UI_Clerk();//统计售票员销售额
    }
    else
    {
        printf("账号没有权限！");
        printf("按{ENTER}返回上层!\n");
        getchar();
        
    }
    system("clear");
    return ;
}


void StaSales_UI_Self(){
    int id;
    id=gl_CurUser.id;//销售员id

    ttms_date_t curdate;//当前日期
    ttms_date_t startdate;//当月第一天
    ttms_date_t enddate;//当月最后一天

    struct tm *local;
    time_t t;
    t=time(&t);
    local=localtime(&t); //当前日期
    
    curdate.year=local->tm_year+1900;
    curdate.month=local->tm_mon+1;
    curdate.day=local->tm_mday;

    startdate.year=local->tm_year+1900;
    startdate.month=local->tm_mon+1;
    startdate.day=1;

    startdate.year=local->tm_year+1900;
    startdate.month=local->tm_mon+1;
    startdate.day=31;

    int choice;
    do
    {
        system("clear");
    printf("=======================================\n");
    printf("[1]当日销售额 | [2]当月销售额 | [0]返回\n");
    printf("---------------------------------------\n");

    printf("请选择你想查询的选项：");
    setbuf(stdin,NULL);
    scanf("%d",&choice);
    setbuf(stdin,NULL);
    system("clear");

    int count;
    switch(choice)
    {
        case 1: 
            system("clear");
            count=StaSales_Srv_CompSaleVal(id,curdate,curdate);
            printf("===========================================\n");
            printf("%5s  %5s  %5s","ID","类型","姓名\n");
            printf("%5d  %5d  %5s\n",gl_CurUser.id,gl_CurUser.type,gl_CurUser.username);
            printf("销售总额为：%5d\n",count);
            printf("******************************************\n");
            break;
        case 2:
            system("clear");
            count=StaSales_Srv_CompSaleVal(id,startdate,enddate);
            printf("===========================================\n");
            printf("%5s  %5s  %5s","ID","类型","姓名\n");
            printf("%5d  %5d  %5s\n",gl_CurUser.id,gl_CurUser.type,gl_CurUser.username);
            printf("销售总额为：%5d\n",count);
            printf("******************************************\n");
            break;
    }
    }while(choice != 0);
}


void StaSales_UI_Clerk()
{
    int id;
    char username[100];
    ttms_date_t startdate;
    ttms_date_t enddate;
    system("clear");
    printf("请输入售票员姓名：");
    setbuf(stdin,NULL);
    scanf("%s",username);
    setbuf(stdin,NULL);
    system("clear");

    account_t user;//存储用户信息
    int i;
    i=Account_Srv_FetchByName(username,&user);
    id=user.id;
    if(i==0)
    {
        printf("该用户不存在！");
        return;
    }
    printf("请输入要查询的开始日期(x/y/z):");
    setbuf(stdin,NULL);
    scanf("%d/%d/%d",&startdate.year,&startdate.month,&startdate.day);
    setbuf(stdin,NULL);
    printf("输入要查询的结束日期(x/y/z)：");
    setbuf(stdin,NULL);
    scanf("%d/%d/%d",&enddate.year,&enddate.month,&enddate.day);

    // printf("青山！");
    // setbuf(stdin,NULL);
    // getchar();
    int count;
    count=StaSales_Srv_CompSaleVal(id,startdate,enddate);
    //  printf("青山！");
    // setbuf(stdin,NULL);
    // getchar();
    printf("\n\n\n\n");
    printf("===========================================\n");
    printf("%5s  %5s  %5s","ID","类型","姓名\n");
    printf("%5d  %5d  %5s\n",user.id,user.type,user.username);
    printf("销售总额为：%5d\n",count);
    printf("*******************************************\n");
    setbuf(stdin,NULL);
    getchar();

}
