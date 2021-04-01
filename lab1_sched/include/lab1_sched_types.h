
/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32162956
*	    Student name : Yun Jun Sung
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

/*
 * You need to Declare functions in  here
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TIME_LINE_SIZE 1024
#define MAX_QUEUE 1024
#define MAX_TICKET 256

typedef struct tagProcess {
	char	proc_name[256];
	int		arrival_time;
	int		service_time;
	int		q_value;
	int		ticket;
} tagProcess;

typedef struct tagTimeline {
	char proc_name[256];
	int time_line[TIME_LINE_SIZE];
	int last_index;
} tagTimeline;

typedef struct tagNode {
	void* data;
	struct tagNode* next;
} tagNode;

typedef struct tagLinkedList {
	tagNode* head;
	int data_size;
} tagLinkedList;

typedef struct tagQueue {
	tagLinkedList queue;
	int q_value;
} tagQueue;

tagNode* create_node(void* data, int data_size); // create_node
void insert_node(tagLinkedList* list, tagNode* node); // insert_node
void delete_node(tagLinkedList* list, tagNode** node); // delete_node
tagLinkedList clone_list(tagLinkedList list); // clone list from argument 1
tagLinkedList clone_time_line_list(tagLinkedList list); // for each process, time line from process list
int do_service(tagLinkedList* list, tagNode** proc, tagTimeline** timeline, int service_time, int curr_time); // service
tagTimeline* get_time_line_node(tagLinkedList list, char* proc_name); // find time line by process name

tagLinkedList FCFS(tagLinkedList proc_list); // FCFS
tagLinkedList RR(tagLinkedList proc_list, int q); // Round Robin
tagLinkedList SPN(tagLinkedList proc_list); // SPN
tagLinkedList SRT(tagLinkedList proc_list); // SRT
tagLinkedList HRRN(tagLinkedList proc_list); // HRRN
tagLinkedList MLFQ(tagLinkedList proc_list, int q_value); // MLFQ
tagLinkedList LOTTERY(tagLinkedList proc_list); // Lottery


#endif /* LAB1_HEADER_H*///#pragma once

