/*
 * OS.c
 *
 *  Created on: 26 avr. 2019
 *      Author: alois
 */
#include "OS.h"
#include "stm32f4xx_hal.h"


void processus_0(void){
	static uint8_t nb_appels = 0;
	nb_appels++;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	HAL_Delay(10*nb_appels);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	HAL_Delay(5*nb_appels);
}

void processus_1(void){
	static uint8_t nb_appels = 0;
	nb_appels++;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
	HAL_Delay(10*nb_appels);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
	HAL_Delay(5*nb_appels);
}

void processus_2(void){
	static uint8_t nb_appels = 0;
	nb_appels++;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
	HAL_Delay(10*nb_appels);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
	HAL_Delay(5*nb_appels);
}

void processus_3(void){
	static uint8_t nb_appels = 0;
	nb_appels++;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
	HAL_Delay(10*nb_appels);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
	HAL_Delay(5*nb_appels);
}

void MySleep(uint32_t Wait){
	uint32_t time;
	for(time=0;time<Wait; time++);
}

void OS_Init(T_OS *OS){
	OS->Processes.Next=NULL;
	OS->Processes.Prev=NULL;
	OS->Processes.proc=NULL;
	OS->running_proc=NULL;
}

void createProcess(T_OS *OS, T_Processus *p, void (*fct)(void), uint8_t Prio){
	T_element *e = &OS->Processes;
	T_element *New;
	p->priorite=Prio;
	p->fct=fct;
	while(e->Next){
		e=e->Next;
	}
	New=createListElem();	/*création et insertion d'un processus à la fin la liste chainee*/
	New->Next=NULL;
	New->Prev=e;
	New->proc=p;
	e->Next=New;
}

void electProcess(T_OS *OS){
	T_element *e;
	if(OS->running_proc != NULL){
		e=OS->Processes.Next;
		while(e->Next){
			e=e->Next;
		}
		e->Next=OS->running_proc;
		OS->running_proc->Prev=e;
		OS->running_proc->Next=NULL;
	}
	OS->running_proc=OS->Processes.Next;
	OS->Processes.Next=OS->Processes.Next->Next;
	OS->Processes.Next->Prev=&(OS->Processes);
}

T_element * createListElem(void){
	static T_element elemTab[30];
	static uint8_t nb_appels = 0;
	return &elemTab[nb_appels++];
}

void startOS(T_OS *OS){
	while(1){
		electProcess(OS);
		OS->running_proc->proc->fct();
	}
}

