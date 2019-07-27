/*
 *  Seat_UI.h
 *
 *  Created on: 2015��5��23��
 *  Author: lc
 */

#ifndef SEAT_UI_H_
#define SEAT_UI_H_
#include "../Common/List.h"
#include "../Service/Seat.h"
#include "../Service/Ticket.h"//?
void Seat_UI_MgtEntry(int roomID);



char Seat_UI_Status2Char(seat_status_t status);


seat_status_t Seat_UI_Char2Status(char statusChar);


int Seat_UI_Add(seat_list_t list, int roomID, int rowsCount,int colsCount);

int Seat_UI_Modify(seat_list_t list, int rowsCount, int colsCount);

int Seat_UI_Delete(seat_list_t list, int rowsCount, int colsCount);

int Seat_UI_ShowTicket(ticket_list_t list,int schedule_id);

#endif /* SEAT_UI_H_ */
