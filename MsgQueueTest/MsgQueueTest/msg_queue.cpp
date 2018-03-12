#include "stdafx.h"

void init_list(p_queue h)
{
	h->node = new lnode();
	h->cntNode = 0;
	h->cp = h->node;
	p_lnode n0 = h->node;
	n0->cntRef = 0;
	n0->msgType = NULL;
	n0->next = NULL;
}

void close_list(p_queue h)
{
	if (!h) return;
	h->cp = NULL;
	p_lnode	p = h->node;
	while (p != NULL)
	{
		h->node = p->next;
		delete p;
		p = h->node;
	}
	h->cntNode = 0;
}

void add_node(p_queue h, p_msg m, int c, int t)
{
	if (!h || !(h->node) || !m) return;
	if (!h->cp) return;
	p_lnode cp = h->cp;
	cp->msgType = &(m->type);
	p_lnode n = new lnode();
	n->cntRef = 0;
	n->msgType = NULL;
	n->next = NULL;
	cp->next = n;
	h->cntNode++;
	h->cp = cp->next;
}

void remove_node(p_queue h)
{
	if (!h || !h->node) return;
	
	p_lnode	p = h->node;
	if (h->node->cntRef != 0) return;

	h->node = p->next;
	delete p;
	h->cntNode--;
}

QueueNode::QueueNode()
{
	this->CntRef = 0;
	this->MsgType = NULL;
	this->next = NULL;
}
void QueueNode::SetNext(QueueNode *p)
{
	if(p) this->next = p;
}
QueueNode * QueueNode::GetNext()
{
	return this->next;
}

MsgQueue::MsgQueue()
{
	this->cntNode = 0;
	this->node = new QueueNode();
	this->cp = this->node;
}
MsgQueue::~MsgQueue()
{
	while (this->cntNode > 0)
	{
		QueueNode *p = this->node;
		if (p)
		{
			this->node = p->GetNext();
			delete p;
			this->cntNode--;
		}
	}
	this->cp = NULL;
	delete this->node;
}
int MsgQueue::GetCntNode()
{
	return this->cntNode;
}
QueueNode * MsgQueue::GetNode()
{
	return this->node;
}
template<> MsgQueue & MsgQueue::operator+<struct _MSG_> (const struct _MSG_ &msg)
{
	QueueNode *p = this->cp;
	if (!p)
		return *this;
	p->SetNext(new QueueNode());
	p->CntRef = 1;
	p->MsgType = (int *)&(msg.type);
	this->cntNode++;
	this->cp = p->GetNext();
	return *this;
}
template<> MsgQueue & MsgQueue::operator+<MsgBase> (const MsgBase &msg)
{
	QueueNode *p = this->cp;
	if (!p)
		return *this;
	p->SetNext(new QueueNode());
	p->CntRef = 1;
	p->MsgType = (int *)&(msg.type);
	this->cntNode++;
	this->cp = p->GetNext();
	return *this;
}
template<typename T> MsgQueue & MsgQueue::operator+ (const T &msg)
{
	QueueNode *p = this->cp;
	if (!p)
		return *this;
	p->next = new QueueNode();
	p->CntRef = 1;
	p->MsgType = &msg;
	this->cntNode++;
	this->cp = p->next;
	return *this;
}
MsgQueue & MsgQueue::operator--()
{
	if (this->cntNode > 0)
	{
		QueueNode *p = this->node;
		if (p&&p->CntRef<=0)
		{
			this->node = p->GetNext();
			delete p;
			this->cntNode--;
		}
	}
	return *this;
}
MsgQueue & MsgQueue::operator=(const MsgQueue &n)
{
	return (MsgQueue &)n;
}

MsgBase::MsgBase()
{
	this->type = 0;
	this->len = 0;
	this->val = NULL;
}