#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node * left, * right;
};

struct lnode{
  int node_num;
  struct node * data_ptr;
  struct lnode * next;
};

struct queue{
  struct lnode * write, * read;
  int size;
};
struct stack{
  struct lnode * top;
  int size;
};

void q_push(struct lnode * ln, struct queue *q){
  if(q->write == NULL){
    q->write = q->read = ln;
  } else {
    q->write->next = ln;
    q->write = ln;
  }
  q->size++;
}
struct lnode * q_pop(struct queue *q){
  struct lnode * ret;
  if(q->read == NULL) return NULL;
  ret = q->read;
  q->read = q->read->next;
  if(q->read == NULL) q->write = NULL;
  q->size--;
  return ret;
}
void s_push(struct lnode *ln, struct stack * st){
  if(st->top == NULL){
    st->top = ln;
    ln->next = NULL;
  } else {
    ln->next = st->top;
    st->top = ln;
  }
  st->size++;
}
struct lnode * s_pop(struct stack * st){
  struct lnode * ln;
  if(st->top == NULL) return NULL;
  ln = st->top;
  st->top = st->top->next;
  st->size--;
  return ln;
}

struct node * genNode(int data){
  struct node * node_ptr = (struct node *)calloc(1, sizeof(struct node));
  node_ptr->data = data;
  return node_ptr;
}

int * bstToArray(struct node * root){
  if(root == NULL) return NULL;
  int arr_size;
  int * bst2arr;

  struct queue q;
  struct stack st;
  q.write = q.read = NULL;
  st.top = NULL;
  q.size = st.size = 0;

  struct lnode * qn = (struct lnode *)calloc(1, sizeof(struct lnode));
  struct lnode * cur;
  qn->data_ptr = root;
  qn->node_num = 1;
  q_push(qn, &q);

  while(q.size != 0){
    cur = q_pop(&q);
    s_push(cur, &st);
    if(cur->data_ptr->left != NULL){
      qn = (struct lnode *)calloc(1, sizeof(struct lnode));
      qn->data_ptr = cur->data_ptr->left;
      qn->node_num = cur->node_num*2;
      q_push(qn, &q);
    }
    if(cur->data_ptr->right != NULL){
      qn = (struct lnode *)calloc(1, sizeof(struct lnode));
      qn->data_ptr = cur->data_ptr->right;
      qn->node_num = cur->node_num*2 + 1;
      q_push(qn, &q);
    }
  }

  arr_size = st.top->node_num+1;
  bst2arr = (int *)calloc(arr_size, sizeof(int));
  bst2arr[0] = st.size;
  while(st.size != 0){
    cur = s_pop(&st);
    bst2arr[cur->node_num] = cur->data_ptr->data;
    free(cur);
  }
  for(int i=0;i<arr_size; i++){
    printf("[%d]:%d, ",i,bst2arr[i]);
  }
  printf("\n");
  return bst2arr;
}

int main(){
  // node declare
  struct node * nodeArr[8];
  // node data init;
  for(int i=1;i<=8;i++){
    nodeArr[i-1] = genNode(i);
  }
  // build tree
  nodeArr[0]->left = nodeArr[1];
  nodeArr[0]->right = nodeArr[2];
  nodeArr[1]->left = nodeArr[3];
  nodeArr[2]->left = nodeArr[4];
  nodeArr[2]->right = nodeArr[5];
  nodeArr[4]->left = nodeArr[6];
  nodeArr[4]->right = nodeArr[7];
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
  bstToArray(nodeArr[0]);
  return 0;
}
