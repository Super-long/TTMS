/*
 * studio.c
 *
 *  Created on: 2015��6��12��
 *      Author: Administrator
 */
#include "Studio.h"
#include "../Persistence/Studio_Persist.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

inline int Studio_Srv_Add(studio_t *data) {
	return Studio_Perst_Insert(data);
}

inline int Studio_Srv_Modify(const studio_t *data) {
	return Studio_Perst_Update(data);
}

inline int Studio_Srv_DeleteByID(int ID) {
	return Studio_Perst_DeleteByID(ID);
}

inline int Studio_Srv_FetchByID(int ID, studio_t *buf) {
	return Studio_Perst_SelectByID(ID, buf);

}

inline int Studio_Srv_FetchAll(studio_list_t list) {
	return Studio_Perst_SelectAll(list);
}

//ͨ��ID��list�в��Ҷ�Ӧ��ӳ�����
inline studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID){
	assert(NULL!=list);
	studio_node_t *ptr=list->next;
	while(ptr!=list){
		if(ptr->data.id==ID)
			return ptr;
		else
			ptr=ptr->next;
	}

	return NULL;
}
