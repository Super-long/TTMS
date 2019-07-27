#ifndef STASALES_H_
#define STASALES_H_

#include "../Common/List.h"
#include "../Common/common.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Account_Persist.h"

// static const int STASALES_PAGE_SIZE=6;

//����ID��ȡ���۶�ͳ��
int StaSales_Srv_CompSaleVal(int usrID, ttms_date_t stDate, ttms_date_t endDate);

#endif 
