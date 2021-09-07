/*
	Name: BiTree 
	Copyright: ������ 
	Author: ������ 
	Date: 14/05/21 17:14
	Description: ��1�������ַ����У���������������2������ "�ݹ�" ������������ 
	��3������ "�ݹ�" ���������� ����4�� ���� "�ݹ�" ���������� ��
	��5�� ���� "�ǵݹ�" ��������������6���������ĸ߶ȣ���7�����ĸ�����
*/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //ʹ���˱�׼�⺯�� 
#include <stdlib.h>      //ʹ���˶�̬�ڴ���亯�� 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define STACK_INIT_SIZE 50   //˳��ջ�洢�ռ��ʼ������ 
#define STACKINCREMENT 10    //˳��ջ�洢�ռ��������  
#define OVERFLOW -2          //�ڴ����������
#define OK 1                 //��ʾ������ȷ�ĳ��� 
#define ERROR 0              //��ʾ��������ĳ���

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //��typedef��int���������Ҳ���ڳ����ά�� 
typedef char TElemType;   //��typedef��char���������Ҳ���ڳ����ά��

//----------------�������Ķ�������洢��ʾ-------------------- 
typedef struct BiNode {
	TElemType  data;
	struct BiNode  *lchild, *rchild;   //���ӽ��ָ�� 
}BiNode, *BiTree;
 
//-------------------ջ��˳��洢��ʾ------------------------- 

typedef BiTree SElemType;   //ջ��Ԫ��Ϊ������ָ������ 
typedef struct {          //ջ��˳��洢��ʾ                        
	SElemType *base;            //ջ��ָ�룬��ջ����֮ǰ������֮��base��ֵΪNULL 
	SElemType *top;             //ջ��ָ��
	int stacksize;              //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
} Stack; 

//------------------���е���ʽ�洢��ʾ----------------------- 
typedef BiTree QElemType;   //����Ԫ��Ϊ������ָ������
typedef struct  QNode {  //�����е�C���Ա�ʾ                  
	 QElemType data;        //������ 
	 struct QNode *next;   //ָ���� 
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front;  //��ͷָ�� 
	QueuePtr rear;   //��βָ�� 
} Queue; 

//-------------------------------------------����������Ҫ����-----------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.���������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
Status CreateBiTree(BiTree &T){  //���������й�������� 
	//�������������������н���ֵ��һ���ַ������ո��ַ���ʾ������������������ʾ������T
	char ch;
	ch = getchar();
	if (ch == ' ')
	    T = NULL;
	else{
		if (!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW); 
		}//if
		T->data = ch;                //���ɸ���� 
		CreateBiTree(T->lchild);   //���������� 
		CreateBiTree(T->rchild);   //���������� 
	}//else 
	return OK; 
}//CreateBiTree

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.�������ı�����4�ַ�����<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//-------------------------------------Ԫ�ط��ʺ���Visit--------------------------------- 
Status PrintElement(TElemType e) {    //���Ԫ��e��ֵ 
	printf(" %c ", e);
	return OK;
}//PrintElement

//-------------------------------------�ݹ��㷨------------------------------------------ 
Status PreOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //����������������ݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	if (T){
		if (Visit(T->data))
		    if (PreOrderTraverse(T->lchild,Visit))
		        if (PreOrderTraverse(T->rchild,Visit))  return OK;
		    return ERROR;
	} //if
	else return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //����������������ݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	if (T){	
		if (InOrderTraverse(T->lchild,Visit))
		    if (Visit(T->data))
		        if (InOrderTraverse(T->rchild,Visit))  return OK;
		    return ERROR;
	} //if
	else return OK;
}//InOrderTraverse 

Status PostOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //�������ĺ�������ݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	if (T) {	
		if (PostOrderTraverse(T->lchild,Visit))
		    if (PostOrderTraverse(T->rchild,Visit))
		        if (Visit(T->data))    return OK;
		    return ERROR;
	}//if
	else return OK;
}//PostOrderTraverse


//--------------------------ջ����غ���(���ǵݹ�������ʹ��)----------------------------
Status InitStack(Stack &S){//����һ���յ�˳��ջ 
	if (!(S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType)))){
		printf("�ڴ����ʧ�ܣ�\n");
		exit(OVERFLOW);
	}     
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK; 
}//InitStack

Status DestoryStack(Stack &S){//�ͷ�˳��ջS��ռ�ڴ�ռ� 
	free(S.base);
	S.base = NULL;
	S.top = NULL; 
	return OK; 
}//DestoryStack

Status StackEmpty(Stack S){//�ж�˳��ջS�Ƿ�Ϊ��ջ,�Ƿ���1���񷵻�0 
	return S.top == S.base; 
}//StackIsEmpty

Status Push(Stack &S, SElemType e){  //��ջ 
	if (S.top-S.base >= S.stacksize){
		if (!(S.base = (SElemType *)realloc(S.base,(STACK_INIT_SIZE + STACKINCREMENT)*sizeof(SElemType)))){
		    printf("�ڴ����ʧ�ܣ�\n");
		    exit(OVERFLOW);
	    }     
	    S.top = S.base + S.stacksize;
    	S.stacksize += STACKINCREMENT;
	}
	*S.top++=e;  
}//Push

Status Pop(Stack &S, SElemType &e){ //��ջ 
	if (StackEmpty(S)) 
	     return ERROR; 
	e = *--S.top;  
	return OK; 
}//Pop

Status GetTop(Stack S, SElemType &e){
	//��ջ���գ���e����˳��ջSջ��Ԫ�ص�ֵ��������OK�����򷵻�ERRROR 
	if (StackEmpty(S))  
	     return ERROR;
	 e = *(S.top-1);  
	 return OK; 
}//GetTop

//--------------------------���е���غ���(���ǵݹ�������ʹ��)----------------------------
QueuePtr MallocQNode(){//Ϊ�����н�������ڴ�ĺ���
	QueuePtr p;  //����ָ��p 
	if(!(p = (QueuePtr)malloc(sizeof(QNode)))){  //��������ڴ�ռ䣬��ʧ������ʾ���˳�����
		printf("�ڴ����ʧ�ܣ����򼴽��˳���\n");
		exit(OVERFLOW);
	}
	return p;
} //MallocQNode 


Status InitQueue(Queue &Q) //��ʼ�������� 
{   //����һ���ն��� Q
	Q.front = Q.rear = MallocQNode();   //����ͷ�����ڴ�ռ䣬��ʹ��ͷ�Ͷ�βָ��ͬʱָ���� 
	Q.front->next=NULL;   
	Q.front->data=0;    //���ӳ���Ϊ0 
	return OK;
}//InitQueue

Status DestoryQueue(Queue &Q){//���ٶ���Q
	while(Q.front){   //��ͷ��㿪ʼ�������ͷŽ���ڴ�ռ� 
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front=Q.rear; 
	}//while
	printf("�������ѳɹ����٣�\n");
	return OK;
}//DestoryQueue

Status QueueEmpty(Queue Q){   //��QΪ�ն��У��򷵻�OK;���򷵻�ERROR
	if (Q.rear == Q.front) //����Ϊ�յı�־ 
		return OK; 
	return ERROR; 
}//QueueEmpty

Status EnQueue(Queue &Q,QElemType e){
    //����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p = MallocQNode(); 
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.front->data++;  //�ӳ�+1 
	return OK; 
}//EnQueue

Status DeQueue(Queue &Q,QElemType &e)
{   //�����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR
	if (QueueEmpty(Q)) 
	      return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
	    Q.rear = Q.front;
	free(p);
	Q.front->data--;  //�ӳ�-1 
	return OK; 
}//DeQueue



//---------------------------------�ǵݹ�����㷨----------------------------------------

Status PreOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //����������������ǵݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	Stack S;
	InitStack(S);
	BiTree p = T;
	while (p || !(StackEmpty(S))){
		if (p){
			if (!Visit(p->data))   //���ʸ���� 
			    return ERROR;
			Push(S, p);      //��ָ���ջ 
			p = p->lchild;    //����������
		}//if
		else{
			Pop(S, p);             //��ָ����ջ 
			p = p->rchild;          //���������� 
		}//else
	}//while
	return OK;
} //PreOrderTraverse1

Status InOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //����������������ǵݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	Stack S;
	InitStack(S);
	BiTree p = T;
	while (p || !(StackEmpty(S))){
		if (p){
			Push(S, p);      //��ָ���ջ 
			p = p->lchild;    //����������
		}//if
		else{
			Pop(S, p);             //��ָ����ջ 
			if (!Visit(p->data))   //���ʸ���� 
			    return ERROR;
			p = p->rchild;          //���������� 
		}//else
	}//while
	return OK;
} //InOrderTraverse1

Status PostOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //�������ĺ�������ǵݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
	BiTree p = T, q = NULL;  // int n=0;
    Stack s;
    InitStack(s);   
    while ((p) || (!StackEmpty(s))) {
 		while (p){
          	Push(s, p);
         	p = p->lchild;
       	}//while
       	q = NULL;
		while (!StackEmpty(s)){
			GetTop(s, p);
			if ((p->rchild==NULL)||(p->rchild==q)){
		      	if(!Visit(p->data))   //���ʸ���� 
			        return ERROR;    
				if (p == T) return ERROR;
				q = p;
          		Pop(s, p);
			}//if
			else{
         		p=p->rchild;
				break;				
			}//else
		}//while
    }//while
	return OK;
} //PostOrderTraverse1

Status LevelOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //�������Ĳ�������ǵݹ��㷨 
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//�������������T���㷨����ÿ������Ԫ�ص��ú���Visit 
	Queue Q;
	BiTree p = T;
	if (T){           //����������
	    InitQueue(Q);   //��ʼ������  
	    EnQueue(Q, T); 
		while (!QueueEmpty(Q)){   //���в��� 
		   DeQueue(Q, p);
		   if(!Visit(p->data))   //���ʸ���� 
			   return ERROR;
		   if(p->lchild)
		       EnQueue(Q,p->lchild);   //��������� 
		   if(p->rchild)
		       EnQueue(Q,p->rchild);   //�Һ�������� 
	   }//while
	   printf("\n");
    }//if
	return OK;
} //LevelOrderTraverse1

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3.����������Ϣ<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int BiTreeDepth(BiTree T){  //�ݹ���������߶� 
	//��������T���ڣ�����T����ȣ��߶ȣ������򷵻�0
	int Thigh, leftThigh, rightThigh;  //�ֱ��ʾ�������߶ȣ��������߶ȣ��������߶�
	if (!T)  return 0;  //����Ϊ0
	else{
		leftThigh = BiTreeDepth(T->lchild);     //���������߶� 
		rightThigh = BiTreeDepth(T->rchild);    //���������߶� 
		if (leftThigh >= rightThigh)     //��������߶� 
		   Thigh = leftThigh + 1;
		else
		   Thigh = rightThigh + 1; 
	}//else
	return Thigh;
}//BiTreeDepth

int LNM=0;
int LeafNodeNum(BiTree T){  //�ݹ��������Ҷ�ӽ��ĸ��� 
	//��������T���ڣ�����T��Ҷ�ӽ����������򷵻�0
	if (T->lchild==NULL && T->rchild==NULL) LNM++;
	else {
		if (T->lchild!=NULL) LeafNodeNum(T->lchild);	
		if (T->rchild!=NULL) LeafNodeNum(T->rchild);	
	}
	return LNM; 
}//LeafNodeNum


int NodeSubNum(BiTree T){  //ͳ�ƶ������Ľ����� 
	if(!T)  return 0;  //������Ϊ������û�н�� 
	else    return(NodeSubNum(T->lchild) + NodeSubNum(T->rchild) + 1); 
}//NodeSubNum


//-------------------------------------------������--------------------------------------------------- 
int main(int argc, char *argv[]){
	printf("----------------------------------���������ð�----------------------------------\n");
	BiTree T;     //����һ�ö�����
	printf("         -------------------------�������Ľ���--------------------              \n");
	printf("��������Ҫ��������������������(�������ÿո����)��\n");
	CreateBiTree(T); 
	printf("\n         -------------------------�������ı���--------------------              ");
	printf("\n\n��������ݹ�  �㷨�����");
	PreOrderTraverse(T, PrintElement);
	printf("\n\n��������ݹ�  �㷨�����");
	InOrderTraverse(T, PrintElement);
	printf("\n\n��������ݹ�  �㷨�����");
	PostOrderTraverse(T, PrintElement); 
	printf("\n\n��������ǵݹ��㷨�����");
	PreOrderTraverse1(T, PrintElement);
	printf("\n\n��������ǵݹ��㷨�����");
	InOrderTraverse1(T, PrintElement);
	printf("\n\n��������ǵݹ��㷨�����");
  	PostOrderTraverse1(T, PrintElement);
  	printf("\n\n��������ǵݹ��㷨�����");
  	LevelOrderTraverse1(T, PrintElement); 
  	printf("\n         -------------------------����������Ϣ--------------------              ");
  	printf("\n�ö������ĸ߶ȣ�%d", BiTreeDepth(T)); 
  	printf("\nҶ�ӽ��ĸ�����%d", LeafNodeNum(T));
	printf("\n�������ܽ������%d", NodeSubNum(T) );
	getchar();
	getchar();
	return 0;
}//main
