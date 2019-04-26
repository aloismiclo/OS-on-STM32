/*
 * OS.h
 *
 *  Created on: 26 avr. 2019
 *      Author: alois
 */

#ifndef OS_H_
#define OS_H_

#include "stdint.h"

typedef struct {
	uint8_t priorite;
	uint8_t timer;
	void (*fct)(void);
}T_Processus;

typedef struct _element{
	struct _element *Next;
	struct _element *Prev;
	T_Processus *proc;
}T_element;

typedef struct {
	T_element Processes;
	T_element *running_proc;
}T_OS;

void processus_0(void);
void processus_1(void);
void processus_2(void);
void processus_3(void);
void MySleep(uint32_t);
void OS_Init(T_OS *);
void createProcess(T_OS *OS, T_Processus *p, void (*fct)(void), uint8_t Prio);
void electProcess(T_OS *OS);
T_element * createListElem(void);
void startOS(T_OS *OS);


#endif /* OS_H_ */
