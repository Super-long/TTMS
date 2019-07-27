
#ifndef PLAY_UI_H_
#define PLAY_UI_H_
#include "../Common/List.h"
#include "../Service/Play.h"

static const int PLAY_PAGE_SIZE=6;

int Play_UI_Add(void);

int Play_UI_Modify(int id);

int Play_UI_Delete(int id);

int Play_UI_Query(int id);

int Play_UI_Query(int id);

/*���б�ģʽ��ʾ��Ŀ��Ϣ*/
void Play_UI_ShowList(play_list_t list, Pagination_t paging);//

void Play_UI_MgtEntry( );

#endif /* PLAY_UI_H_ */
