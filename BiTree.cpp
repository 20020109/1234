/*
	Name: BiTree 
	Copyright: 任晗舒 
	Author: 任晗舒 
	Date: 14/05/21 17:14
	Description: （1）输入字符序列，建立二叉树；（2）先序 "递归" 遍历二叉树； 
	（3）中序 "递归" 遍历二叉树 ；（4） 后序 "递归" 遍历二叉树 ；
	（5） 中序 "非递归" 遍历二叉树；（6）二叉树的高度；（7）结点的个数。
*/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define STACK_INIT_SIZE 50   //顺序栈存储空间初始分配量 
#define STACKINCREMENT 10    //顺序栈存储空间分配增量  
#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //用typedef给int起个别名，也便于程序的维护 
typedef char TElemType;   //用typedef给char起个别名，也便于程序的维护

//----------------二叉树的二叉链表存储表示-------------------- 
typedef struct BiNode {
	TElemType  data;
	struct BiNode  *lchild, *rchild;   //孩子结点指针 
}BiNode, *BiTree;
 
//-------------------栈的顺序存储表示------------------------- 

typedef BiTree SElemType;   //栈的元素为二叉树指针类型 
typedef struct {          //栈的顺序存储表示                        
	SElemType *base;            //栈底指针，在栈构造之前和销毁之后，base的值为NULL 
	SElemType *top;             //栈顶指针
	int stacksize;              //当前已分配的存储空间，以元素为单位 
} Stack; 

//------------------队列的链式存储表示----------------------- 
typedef BiTree QElemType;   //队列元素为二叉树指针类型
typedef struct  QNode {  //链队列的C语言表示                  
	 QElemType data;        //数据域 
	 struct QNode *next;   //指针域 
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front;  //队头指针 
	QueuePtr rear;   //队尾指针 
} Queue; 

//-------------------------------------------二叉树的主要操作-----------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.构造二叉树<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
Status CreateBiTree(BiTree &T){  //按先序序列构造二叉树 
	//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，构造二叉链表表示二叉树T
	char ch;
	ch = getchar();
	if (ch == ' ')
	    T = NULL;
	else{
		if (!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("内存分配失败！\n");
			exit(OVERFLOW); 
		}//if
		T->data = ch;                //生成根结点 
		CreateBiTree(T->lchild);   //构建左子树 
		CreateBiTree(T->rchild);   //构建右子树 
	}//else 
	return OK; 
}//CreateBiTree

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.二叉树的遍历（4种方法）<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//-------------------------------------元素访问函数Visit--------------------------------- 
Status PrintElement(TElemType e) {    //输出元素e的值 
	printf(" %c ", e);
	return OK;
}//PrintElement

//-------------------------------------递归算法------------------------------------------ 
Status PreOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //二叉树的先序遍历递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
	if (T){
		if (Visit(T->data))
		    if (PreOrderTraverse(T->lchild,Visit))
		        if (PreOrderTraverse(T->rchild,Visit))  return OK;
		    return ERROR;
	} //if
	else return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //二叉树的中序遍历递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
	if (T){	
		if (InOrderTraverse(T->lchild,Visit))
		    if (Visit(T->data))
		        if (InOrderTraverse(T->rchild,Visit))  return OK;
		    return ERROR;
	} //if
	else return OK;
}//InOrderTraverse 

Status PostOrderTraverse(BiTree T, Status(* Visit)(TElemType)){  //二叉树的后序遍历递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
	if (T) {	
		if (PostOrderTraverse(T->lchild,Visit))
		    if (PostOrderTraverse(T->rchild,Visit))
		        if (Visit(T->data))    return OK;
		    return ERROR;
	}//if
	else return OK;
}//PostOrderTraverse


//--------------------------栈的相关函数(供非递归后序遍历使用)----------------------------
Status InitStack(Stack &S){//构造一个空的顺序栈 
	if (!(S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType)))){
		printf("内存分配失败！\n");
		exit(OVERFLOW);
	}     
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK; 
}//InitStack

Status DestoryStack(Stack &S){//释放顺序栈S所占内存空间 
	free(S.base);
	S.base = NULL;
	S.top = NULL; 
	return OK; 
}//DestoryStack

Status StackEmpty(Stack S){//判断顺序栈S是否为空栈,是返回1，否返回0 
	return S.top == S.base; 
}//StackIsEmpty

Status Push(Stack &S, SElemType e){  //入栈 
	if (S.top-S.base >= S.stacksize){
		if (!(S.base = (SElemType *)realloc(S.base,(STACK_INIT_SIZE + STACKINCREMENT)*sizeof(SElemType)))){
		    printf("内存分配失败！\n");
		    exit(OVERFLOW);
	    }     
	    S.top = S.base + S.stacksize;
    	S.stacksize += STACKINCREMENT;
	}
	*S.top++=e;  
}//Push

Status Pop(Stack &S, SElemType &e){ //出栈 
	if (StackEmpty(S)) 
	     return ERROR; 
	e = *--S.top;  
	return OK; 
}//Pop

Status GetTop(Stack S, SElemType &e){
	//若栈不空，用e返回顺序栈S栈顶元素的值，并返回OK，否则返回ERRROR 
	if (StackEmpty(S))  
	     return ERROR;
	 e = *(S.top-1);  
	 return OK; 
}//GetTop

//--------------------------队列的相关函数(供非递归层序遍历使用)----------------------------
QueuePtr MallocQNode(){//为链队列结点申请内存的函数
	QueuePtr p;  //工作指针p 
	if(!(p = (QueuePtr)malloc(sizeof(QNode)))){  //申请结点的内存空间，若失败则提示并退出程序
		printf("内存分配失败，程序即将退出！\n");
		exit(OVERFLOW);
	}
	return p;
} //MallocQNode 


Status InitQueue(Queue &Q) //初始化链队列 
{   //构建一个空队列 Q
	Q.front = Q.rear = MallocQNode();   //申请头结点的内存空间，并使队头和队尾指针同时指向它 
	Q.front->next=NULL;   
	Q.front->data=0;    //将队长设为0 
	return OK;
}//InitQueue

Status DestoryQueue(Queue &Q){//销毁队列Q
	while(Q.front){   //从头结点开始向后逐个释放结点内存空间 
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front=Q.rear; 
	}//while
	printf("链队列已成功销毁！\n");
	return OK;
}//DestoryQueue

Status QueueEmpty(Queue Q){   //若Q为空队列，则返回OK;否则返回ERROR
	if (Q.rear == Q.front) //队列为空的标志 
		return OK; 
	return ERROR; 
}//QueueEmpty

Status EnQueue(Queue &Q,QElemType e){
    //插入元素e为Q的新的队尾元素
	QueuePtr p = MallocQNode(); 
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.front->data++;  //队长+1 
	return OK; 
}//EnQueue

Status DeQueue(Queue &Q,QElemType &e)
{   //若队列不空,则删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
	if (QueueEmpty(Q)) 
	      return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
	    Q.rear = Q.front;
	free(p);
	Q.front->data--;  //队长-1 
	return OK; 
}//DeQueue



//---------------------------------非递归遍历算法----------------------------------------

Status PreOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //二叉树的先序遍历非递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//先序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
	Stack S;
	InitStack(S);
	BiTree p = T;
	while (p || !(StackEmpty(S))){
		if (p){
			if (!Visit(p->data))   //访问根结点 
			    return ERROR;
			Push(S, p);      //根指针进栈 
			p = p->lchild;    //遍历左子树
		}//if
		else{
			Pop(S, p);             //根指针退栈 
			p = p->rchild;          //遍历右子树 
		}//else
	}//while
	return OK;
} //PreOrderTraverse1

Status InOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //二叉树的中序遍历非递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
	Stack S;
	InitStack(S);
	BiTree p = T;
	while (p || !(StackEmpty(S))){
		if (p){
			Push(S, p);      //根指针进栈 
			p = p->lchild;    //遍历左子树
		}//if
		else{
			Pop(S, p);             //根指针退栈 
			if (!Visit(p->data))   //访问根结点 
			    return ERROR;
			p = p->rchild;          //遍历右子树 
		}//else
	}//while
	return OK;
} //InOrderTraverse1

Status PostOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //二叉树的后序遍历非递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//后序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
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
		      	if(!Visit(p->data))   //访问根结点 
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

Status LevelOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){  //二叉树的层序遍历非递归算法 
    //采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//层序遍历二叉树T的算法，对每个数据元素调用函数Visit 
	Queue Q;
	BiTree p = T;
	if (T){           //根结点入队列
	    InitQueue(Q);   //初始化队列  
	    EnQueue(Q, T); 
		while (!QueueEmpty(Q)){   //队列不空 
		   DeQueue(Q, p);
		   if(!Visit(p->data))   //访问根结点 
			   return ERROR;
		   if(p->lchild)
		       EnQueue(Q,p->lchild);   //左孩子入队列 
		   if(p->rchild)
		       EnQueue(Q,p->rchild);   //右孩子入队列 
	   }//while
	   printf("\n");
    }//if
	return OK;
} //LevelOrderTraverse1

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3.二叉树的信息<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int BiTreeDepth(BiTree T){  //递归求二叉树高度 
	//若二叉树T存在，返回T的深度（高度），否则返回0
	int Thigh, leftThigh, rightThigh;  //分别表示二叉树高度，左子树高度，右子树高度
	if (!T)  return 0;  //树高为0
	else{
		leftThigh = BiTreeDepth(T->lchild);     //求左子树高度 
		rightThigh = BiTreeDepth(T->rchild);    //求右子树高度 
		if (leftThigh >= rightThigh)     //求二叉树高度 
		   Thigh = leftThigh + 1;
		else
		   Thigh = rightThigh + 1; 
	}//else
	return Thigh;
}//BiTreeDepth

int LNM=0;
int LeafNodeNum(BiTree T){  //递归求二叉树叶子结点的个数 
	//若二叉树T存在，返回T的叶子结点个数，否则返回0
	if (T->lchild==NULL && T->rchild==NULL) LNM++;
	else {
		if (T->lchild!=NULL) LeafNodeNum(T->lchild);	
		if (T->rchild!=NULL) LeafNodeNum(T->rchild);	
	}
	return LNM; 
}//LeafNodeNum


int NodeSubNum(BiTree T){  //统计二叉树的结点个数 
	if(!T)  return 0;  //二叉树为空树，没有结点 
	else    return(NodeSubNum(T->lchild) + NodeSubNum(T->rchild) + 1); 
}//NodeSubNum


//-------------------------------------------主函数--------------------------------------------------- 
int main(int argc, char *argv[]){
	printf("----------------------------------二叉树引用版----------------------------------\n");
	BiTree T;     //声明一棵二叉树
	printf("         -------------------------二叉树的建立--------------------              \n");
	printf("请输入所要建立二叉树的先序序列(空子树用空格代替)：\n");
	CreateBiTree(T); 
	printf("\n         -------------------------二叉树的遍历--------------------              ");
	printf("\n\n先序遍历递归  算法结果：");
	PreOrderTraverse(T, PrintElement);
	printf("\n\n中序遍历递归  算法结果：");
	InOrderTraverse(T, PrintElement);
	printf("\n\n后序遍历递归  算法结果：");
	PostOrderTraverse(T, PrintElement); 
	printf("\n\n先序遍历非递归算法结果：");
	PreOrderTraverse1(T, PrintElement);
	printf("\n\n中序遍历非递归算法结果：");
	InOrderTraverse1(T, PrintElement);
	printf("\n\n后序遍历非递归算法结果：");
  	PostOrderTraverse1(T, PrintElement);
  	printf("\n\n层序遍历非递归算法结果：");
  	LevelOrderTraverse1(T, PrintElement); 
  	printf("\n         -------------------------二叉树的信息--------------------              ");
  	printf("\n该二叉树的高度：%d", BiTreeDepth(T)); 
  	printf("\n叶子结点的个数：%d", LeafNodeNum(T));
	printf("\n二叉树总结点数：%d", NodeSubNum(T) );
	getchar();
	getchar();
	return 0;
}//main
