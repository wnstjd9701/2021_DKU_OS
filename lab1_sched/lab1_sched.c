/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32162956
*	    Student name : Yun Jun Sung
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include "lab1_sched_types.h"

/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler.
 */

tagNode* create_node(void* data, int data_size)
{
	tagNode* ret = (tagNode*)malloc(sizeof(tagNode));

	ret->data = (void*)malloc(data_size);
	memcpy(ret->data, data, data_size);
	ret->next = NULL;

	return ret;
}

void insert_node(tagLinkedList* list, tagNode* node)
{
	tagNode* temp;
	if (list->head == NULL)
		list->head = node;
	else if (list->head->next == NULL)
		list->head->next = node;
	else
	{
		temp = list->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

void delete_node(tagLinkedList* list, tagNode** node)
{
	tagNode* temp;
	if (list->head->data == (*node)->data)
		list->head = list->head->next;
	else if (list->head->next->data == (*node)->data)
		list->head->next = (*node)->next;
	else
	{
		temp = list->head;
		while (temp->next != NULL && temp->next->data != (*node)->data)
			temp = temp->next;
		temp->next = (*node)->next;
	}

	(*node)->next = NULL;
	free(*node);
	*node = NULL;
}

tagLinkedList clone_list(tagLinkedList list)
{
	tagLinkedList ret;
	tagNode *temp = list.head;
	ret.head = NULL;
	ret.data_size = list.data_size;

	while (temp != NULL)
	{
		insert_node(&ret, create_node(temp->data, list.data_size));
		temp = temp->next;
	}

	return ret;
}

tagLinkedList clone_time_line_list(tagLinkedList list)
{
	tagLinkedList ret;	
	tagTimeline timeline;
	tagNode* temp = list.head;

	ret.head = NULL;
	ret.data_size = sizeof(tagTimeline);

	while (temp != NULL)
	{
		strcpy(timeline.proc_name, ((tagProcess*)temp->data)->proc_name);
		memset(timeline.time_line, 0, sizeof(int) * TIME_LINE_SIZE);
		insert_node(&ret, create_node(&timeline, ret.data_size));
		temp = temp->next;
	}

	return ret;
}

/* get next arrival node in current time to compare */
tagProcess* get_next_arrival_node(tagNode* head, int curr_time)
{
	int gap = -1;
	tagProcess *ret = NULL, *temp;
	while (head != NULL)
	{
		temp = (tagProcess*)(head->data);
		if (curr_time - temp->arrival_time > gap)
		{
			gap = curr_time - temp->arrival_time;
			ret = (tagProcess*)(head->data);
		}

		head = head->next;
	}

	return ret;
}

/* get mininum service node in current time to neighbor */
tagProcess* get_min_service_node(tagNode* head, int curr_time)
{
	int gap = 12345678;
	tagProcess *ret = NULL, *temp;
	while (head != NULL)
	{
		temp = (tagProcess*)(head->data);
		if (temp->arrival_time <= curr_time &&
				temp->service_time < gap)
		{
			gap = temp->service_time;
			ret = (tagProcess*)(head->data);
		}

		head = head->next;
	}

	return ret;
}

/* get next srt service node */
tagProcess* get_srt_service_node(tagNode* head, int curr_time)
{
	int gap = 12345678;
	tagProcess* ret = NULL, * temp;
	while (head != NULL)
	{
		temp = (tagProcess*)(head->data);
		if (curr_time >= temp->arrival_time && temp->service_time < gap)
		{
			gap = temp->service_time;
			ret = (tagProcess*)(head->data);
		}

		head = head->next;
	}

	return ret;
}

/* get next hrrn service node */
tagProcess* get_hrrn_service_node(tagNode* head, int curr_time)
{
	int gap = -1;
	tagProcess* ret = NULL, * temp;
	while (head != NULL)
	{
		temp = (tagProcess*)(head->data);
		if ((curr_time + temp->service_time) / temp->service_time > gap)
		{
			gap = (curr_time + temp->service_time) / temp->service_time;
			ret = (tagProcess*)(head->data);
		}

		head = head->next;
	}

	return ret;
}

/* get total time (Lottery scheduling) */
int get_total_time(tagNode* head, int curr_time)
{
	int ret = 0;
	while (head != NULL)
	{
		if (((tagProcess*)head->data)->arrival_time <= curr_time)
		{
			((tagProcess*)head->data)->ticket = rand() % MAX_TICKET;
			ret += ((tagProcess*)head->data)->ticket;
		}

		head = head->next;
	}

	return ret;
}

/* find own ticketer process from process list */
tagProcess* get_ticketer_process(tagNode* head, int winner)
{
	int sum = 0;
	while (head != NULL)
	{
		sum += ((tagProcess*)head->data)->ticket;
		if (sum > winner)
			return (tagProcess*)head->data;

		head = head->next;
	}

	return NULL;
}

int do_service(tagLinkedList* list, tagNode** proc, tagTimeline** timeline, int service_time, int curr_time)
{
	int i;
	for (i = 0; i < service_time; i++)
	{
		if (*timeline != NULL)
			(*timeline)->time_line[curr_time] = 1;

		((tagProcess*)((*proc)->data))->service_time--;
		curr_time++;
		if (((tagProcess*)((*proc)->data))->service_time <= 0)
		{
			(*timeline)->last_index = curr_time - 1;
			delete_node(list, proc);
			break;
		}
	}

	return curr_time;
}

tagTimeline* get_time_line_node(tagLinkedList list, char* proc_name)
{
	tagNode* temp = list.head;
	while (temp != NULL)
	{
		if (strcmp(((tagTimeline*)(temp->data))->proc_name, proc_name) == 0)
			return (tagTimeline*)(temp->data);

		temp = temp->next;
	}

	return NULL;
}

tagLinkedList FCFS(tagLinkedList proc_list)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp;
	tagProcess* proc;
	tagTimeline* timeline;

	while (cloned.head != NULL)
	{
		temp = cloned.head;
		proc = get_next_arrival_node(temp, time);
		if (proc != NULL)
		{
			timeline = get_time_line_node(ret, proc->proc_name);
			time = do_service(&cloned, &temp, &timeline, proc->service_time, time);
		}
		else
			time++;
	}

	return ret;
}

tagLinkedList RR(tagLinkedList proc_list, int q)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;

	while (cloned.head != NULL)
	{
		if (temp == NULL)
			temp = cloned.head;

		if (time >= ((tagProcess*)temp->data)->arrival_time &&
			((tagProcess*)temp->data)->service_time > 0)
		{
			timeline = get_time_line_node(ret, ((tagProcess*)(temp->data))->proc_name);
			time = do_service(&cloned, &temp, &timeline, q, time);
		}

		if (temp != NULL)
			temp = temp->next;
	}

	return ret;
}

tagLinkedList SPN(tagLinkedList proc_list)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;
	tagProcess* proc;

	while (cloned.head != NULL)
	{
		temp = cloned.head;
		proc = get_min_service_node(temp, time);
		if (proc != NULL)
		{
			timeline = get_time_line_node(ret, proc->proc_name);
			time = do_service(&cloned, &temp, &timeline, proc->service_time, time);
		}
		else
			time++;
	}

	return ret;
}

tagLinkedList SRT(tagLinkedList proc_list)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;
	tagProcess* proc;

	while (cloned.head != NULL)
	{
		if (temp == NULL)
			temp = cloned.head;

		proc = get_srt_service_node(temp, time);
		if (proc != NULL)
		{
			timeline = get_time_line_node(ret, proc->proc_name);
			time = do_service(&cloned, &temp, &timeline, 1, time);
		}

		if (temp != NULL)
			temp = temp->next;
	}

	return ret;
}

tagLinkedList HRRN(tagLinkedList proc_list)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;
	tagProcess* proc;

	while (cloned.head != NULL)
	{
		temp = cloned.head;
		proc = get_hrrn_service_node(temp, time);
		if (proc != NULL)
		{
			timeline = get_time_line_node(ret, proc->proc_name);
			time = do_service(&cloned, &temp, &timeline, proc->service_time, time);
		}
		else
			time++;
	}

	return ret;
}

tagLinkedList MLFQ(tagLinkedList proc_list, int q_value)
{
	int time = 0;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;

	while (cloned.head != NULL)
	{
		if (temp == NULL)
			temp = cloned.head;

		if (time >= ((tagProcess*)temp->data)->arrival_time)
		{
			if (((tagProcess*)temp->data)->q_value == 0)
				((tagProcess*)temp->data)->q_value = 1;
			else
			{	
				if (q_value != 1)
					((tagProcess*)temp->data)->q_value *= 2;
				else
					((tagProcess*)temp->data)->q_value = 1;
			}

			timeline = get_time_line_node(ret, ((tagProcess*)(temp->data))->proc_name);
			time = do_service(&cloned, &temp, &timeline, ((tagProcess*)(temp->data))->q_value, time);
		}

		if (temp != NULL)
			temp = temp->next;
	}

	return ret;
}

tagLinkedList LOTTERY(tagLinkedList proc_list)
{
	int time = 0, total_time, winner;
	tagLinkedList cloned = clone_list(proc_list);
	tagLinkedList ret = clone_time_line_list(proc_list);
	tagNode* temp = NULL;
	tagTimeline* timeline;
	tagProcess* proc;

	while (cloned.head != NULL)
	{
		temp = cloned.head;
		total_time = get_total_time(cloned.head, time);
		if (total_time == 0)
		{
			time++;
			continue;
		}

		winner = rand() % total_time;
		proc = get_ticketer_process(temp, winner);
		if (proc != NULL)
		{
			timeline = get_time_line_node(ret, proc->proc_name);
			time = do_service(&cloned, &temp, &timeline, proc->service_time, time);
		}
		else
			time++;
	}

	return ret;
}
