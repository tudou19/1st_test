#include <atomic>
using namespace std;

#pragma once

typedef struct __list_node__
{
	atomic<int> cntRef;
	int *msgType;
	struct __list_node__ *next;
}lnode,*p_lnode;

class QueueNode
{
public:
	atomic<int> CntRef;
	int *MsgType;

	QueueNode();
	virtual ~QueueNode() {};

	void SetNext(QueueNode *p);
	QueueNode * GetNext();
private:
	QueueNode *next;
};

class MsgQueue
{
public:
	atomic<QueueNode *> cp;
	MsgQueue();
	virtual ~MsgQueue();

	int GetCntNode();
	QueueNode * GetNode();
	template<typename T> MsgQueue & operator+ (const T &msg);
	MsgQueue & operator--();
	MsgQueue & operator=(const MsgQueue &n);
private:
	QueueNode *node;
	int cntNode;
};

typedef struct __queue__
{
	p_lnode node;
	int cntNode;
	atomic<p_lnode> cp;
}queue,*p_queue;

typedef struct _MSG_
{
	int type;
	int len;
	char *data;
}msg,*p_msg;

class MsgBase
{
public:
	MsgBase();
	virtual	~MsgBase() {};

	int type;
	int len;
	char *val;
};

class MsgExt : public MsgBase
{
public :
	int version;
};

void init_list(p_queue h);
void close_list(p_queue h);
void add_node(p_queue h,p_msg m,int c,int t);
void remove_node(p_queue h);