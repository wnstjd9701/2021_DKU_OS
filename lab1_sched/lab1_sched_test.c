/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32162956
*	    Student name : Yun Jun Sung
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/

/*#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>*/

#include "lab1_sched_types.h"

/*
 * you need to implement scheduler simlator test code.
 *
 */

tagLinkedList read_input_file(char* filename)
{
	FILE* fp = fopen(filename, "rt");
	tagLinkedList ret;
	tagProcess info;

	ret.head = NULL;
	ret.data_size = sizeof(tagProcess);
	while (fscanf(fp,
		"%s\t%d\t%d\n", info.proc_name, &info.arrival_time, &info.service_time) != EOF)
	{
		info.q_value = 0;
		insert_node(&ret, create_node(&info, sizeof(tagProcess)));
	}

	return ret;
}

void display_time_line(char* title, tagLinkedList list)
{
	tagNode* temp = list.head;
	tagTimeline* timeline;
	int i, max_index = -1;

	while (temp != NULL)
	{
		timeline = (tagTimeline*)temp->data;
		if (max_index < timeline->last_index)
			max_index = timeline->last_index;

		temp = temp->next;
	}

	printf("%s\n", title);

	temp = list.head;
	while (temp != NULL)
	{
		timeline = (tagTimeline*)temp->data;
		printf("%s", timeline->proc_name);
		for (i = 0; i <= max_index; i++)
		{
			if (timeline->time_line[i] == 1)
				printf(" ■ ");
			else
				printf(" □ ");
		}
		printf("\n");

		temp = temp->next;
	}

	printf("\n");
}

int main(int argc, char* argv[])
{
	tagLinkedList proc_list;

	if (argc != 2)
	{
		printf("usage : <lab1_shed_test> <process_info.txt>\n");
		return 0;
	}

	proc_list = read_input_file(argv[1]);
	tagLinkedList fcfs = FCFS(proc_list);
	tagLinkedList rr_q1 = RR(proc_list, 1);
	tagLinkedList rr_q4 = RR(proc_list, 4);
	tagLinkedList spn = SPN(proc_list);
	tagLinkedList srt = SRT(proc_list);
	tagLinkedList hrrn = HRRN(proc_list);
	tagLinkedList mlfq = MLFQ(proc_list, 1);
	tagLinkedList mlfq2i = MLFQ(proc_list, 2);
	tagLinkedList lottery = LOTTERY(proc_list);

	display_time_line("---FCFS---", fcfs);
	display_time_line("---RR(q:1)---", rr_q1);
	display_time_line("---RR(q:4)---", rr_q4);
	display_time_line("---SPN---", spn);
	display_time_line("---SRT---", srt);
	display_time_line("---HRRN---", hrrn);
	display_time_line("---MLFQ(q=1)---", mlfq);
	display_time_line("---MLFQ(q=2^i)---", mlfq2i);
	display_time_line("---LOTTERY---", lottery);

	return 0;
}
