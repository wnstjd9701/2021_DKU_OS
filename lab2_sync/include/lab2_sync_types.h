/*
*   DKU Operating System Lab
*           Lab2 (Vehicle Production Problem)
*           Student id : 
*           Student name : 
*
*   lab1_sync_types.h :
*       - lab2 header file.
*       - must contains Vehicle Production Problem's declations.
*
*/

#ifndef _LAB2_HEADER_H
#define _LAB2_HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#define MAX_SIZE 100

/*
 * You need to Declare functions in  here
 */

typedef struct Node {
	int car_num;
	struct Node *next;
}Node;

typedef struct car_queue {
	int balance;
	Node *front, *rear;
}CQ;



#endif /* LAB2_HEADER_H*/


