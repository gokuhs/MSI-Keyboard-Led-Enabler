
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/auxv.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "msg.h"

void sendMesage(char * mensaje)
{
  int id, msgSize;
  MSG m1;

  id = msgget(1258, IPC_CREAT | 0666);
  m1.type = 2;;

  if (id < 0) {
    perror("The message queue cannot be accessed");
    exit(2);
  }
  msgSize = sizeof(MSG);
  
  strcpy(m1.val,mensaje);
  msgsnd(id, &m1, msgSize, IPC_NOWAIT);
  //printf("Msg. sent: type=%d, val=%s\nValores 0->%#x 1->%#x 2->%#x 3->%#x 4->%#x 5->%#x\n",  m1.type, m1.val, mensaje[0], mensaje[1], mensaje[2], mensaje[3], mensaje[4], mensaje[5]);

  //msgctl(id, IPC_RMID, 0);
}

void ReadMesage(char * mensaje)
{
  int id, msgSize,rcvType;
  MSG m2;

  id = msgget(1258, 0666);
  rcvType = 2;

  if (id < 0) {
    perror("The message queue cannot be accessed");
    //exit(2);
  }
  msgSize = sizeof(MSG);

  msgrcv(id, &m2, msgSize, rcvType, IPC_NOWAIT);
  //printf("Msg. received: type=%d, val=%s\n",m2.type, m2.val);
  //printf("Msg. received: type=%d, val=%s\nValores 0->%#x 1->%#x 2->%#x 3->%#x 4->%#x 5->%#x\n",  m2.type, m2.val, mensaje[0], mensaje[1], mensaje[2], mensaje[3], mensaje[4], mensaje[5]);
  
  strcpy(mensaje,m2.val);
}