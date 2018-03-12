// MsgQueueTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <atomic>

using namespace std;

template<typename T>
class E
{
public:
	E() {};
	virtual ~E() {};
	int type;
	T *a;
};

class B : public E<B>
{
public:
	int b;
};

int main()
{
	B bb = B();
	bb.b = 9;
	bb.type = 2;

	int *pp = &(bb.type);

	B* pb = NULL;
	container_of(pb, pp, B, type);
	E<B>* pe = NULL;
	container_of(pe, pp, E<B>, type);
	((B*)pe)->b;

	queue q_h;
	init_list(&q_h);
	MsgQueue &mq = MsgQueue();
	msg m1;
	m1.type = 1;
	m1.len = 0;
	m1.data = NULL;
	add_node(&q_h, &m1, 2, 1);
	mq = mq + m1;

	msg m2;
	m2.type = 2;
	m2.len = 0;
	m2.data = NULL;
	add_node(&q_h, &m2, 3, 2);
	mq = mq + m2;

	MsgExt m3 = MsgExt();
	m3.type = 3;
	m3.version = 2;
	mq = mq + (MsgBase &)m3;

	p_lnode m = q_h.node;
	//p_msg p=NULL;
	//container_of(p, m->msgType, msg, type);

	QueueNode *qn = mq.GetNode()->GetNext()->GetNext();
	MsgExt *pm = NULL;
	container_of(pm, qn->MsgType, MsgExt, type);

	m->cntRef = 0;
	remove_node(&q_h);
	mq.GetNode()->CntRef = 0;
	--(mq);

	close_list(&q_h);

    return 0;
}
