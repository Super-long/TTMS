/*
 *  Seat_Persist.h
 *
 *  Created on: 2015��5��23��
 *  Author: lc
 */

#ifndef SEATPERSIST_H_
#define SEATPERSIST_H_

#include "../Service/Seat.h"

int Seat_Perst_Insert(seat_t *data);	

int Seat_Perst_InsertBatch(seat_list_t list);

int Seat_Perst_Update(seat_t *data);

int Seat_Perst_DeleteByID(int ID);

int Seat_Perst_DeleteAllByRoomID(int roomID);

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID);

int Seat_Perst_SelectByID(int ID, seat_t *buf);

int Seat_Perst_SelectAll(seat_list_t list);

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID);

int  Seat_Perst_Showticket(list,schedule_id);

#endif /* SEATPERSIST_H_ */
