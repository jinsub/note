#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node * left, * right;
};

struct qnode{
  struct node * data_ptr;
  struct qnode * next;
};

struct queue{
  struct qnode * write, * read;
  int size;
};

void push(struct qnode * qn, struct queue *q){
  if(q->write == NULL){
    q->write = q->read = qn;
  } else {
    q->write->next = qn;
    q->write = qn;
  }
  q->size++;
}
struct qnode * pop(struct queue *q){
  struct qnode * ret;
  if(q->read == NULL) return NULL;
  ret = q->read;
  q->read = q->read->next;
  if(q->read == NULL) q->write = NULL;
  q->size--;
  return ret;
}

struct node * genNode(int data){
  struct node * ytp = (struct node *)calloc(1, sizeof(struct node));
  ytp->data = data;
  return ytp;
}

int main(){
  // node declare
  struct node * YTA[8];
  // node data init;
  for(int i=1;i<=8;i++){
    YTA[i-1] = genNode(i);
  }
  // build tree
  YTA[0]->left = YTA[1];
  YTA[0]->right = YTA[2];
  YTA[1]->left = YTA[3];
  YTA[2]->left = YTA[4];
  YTA[2]->right = YTA[5];
  YTA[4]->left = YTA[6];
  YTA[4]->right = YTA[7];
  /*
        1
      /  \
     2    3
    /   /  \
   4   5   6
      / \
     7  8
  */
  //
  int tot_size = 0;
  int bst2arr[20];    // 적당히 20
  int idx = 1;
  struct queue * q = (struct queue *)calloc(1, sizeof(struct queue));
  struct qnode * qn = (struct qnode *)calloc(1, sizeof(struct qnode));
  struct qnode * cur;
  qn->data_ptr = YTA[0];
  push(qn, q);
  while(q->size != 0){
    cur = pop(q);
    if(cur->data_ptr == NULL) bst2arr[idx++] = 0;
    else {
      tot_size++;
      bst2arr[idx++] = cur->data_ptr->data;
      qn = (struct qnode *)calloc(1, sizeof(struct qnode));
      qn->data_ptr = cur->data_ptr->left;
      push(qn, q);
      qn = (struct qnode *)calloc(1, sizeof(struct qnode));
      qn->data_ptr = cur->data_ptr->right;
      push(qn, q);
    }
    free(cur);
  }
  bst2arr[0] = tot_size;
  for(int i=0;i<idx;i++){
    printf("[%d]", bst2arr[i]);
  }
  printf("\n");
  return 0;
}
