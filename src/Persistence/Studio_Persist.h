/*
 * StudioPersist.h
 *
 *  Created on: 2015��4��24��
 *      Author: Administrator
 */

#ifndef STUDIO_PERSIST_H_
#define STUDIO_PERSIST_H_

#include "../Service/Studio.h"

int Studio_Perst_Insert(studio_t *data);	////�·�����dataǰ���constȥ��

int Studio_Perst_Update(const studio_t *data);

int Studio_Perst_DeleteByID(int ID);

int Studio_Perst_SelectByID(int ID, studio_t *buf);

int Studio_Perst_SelectAll(studio_list_t list);


#endif /* STUDIO_PERSIST_H_ */
