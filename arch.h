#ifndef __ARCH_H__
#define __ARCH_H__

int msg_init(msg_t *pMsg);
void msgq_init(msgq_t *q);
int	msgq_in(msgq_t *q, msg_t *val);
int	msgq_in_irq(msgq_t *q, msg_t *val);
int	msgq_out(msgq_t *q, msg_t *val);
int	msgq_out_irq(msgq_t *q, msg_t *val);


void fstack_init(fstack_t *s);
//int	fstack_pop(fstack_t *s);
int	fstack_push(fstack_t *s, func_t *f);
//int fstack_update(fstack_t *s, func_t *f);
int	fstack_top(const fstack_t *s, func_t *f);


void SetTimer(Timer_t * timer, int tick, msgType_t msgType); 
void SetTimer_irq(Timer_t * timer, int tick, msgType_t msgType);

void ClrTimer(Timer_t * timer);
void ClrTimer_irq(Timer_t * timer);


void actionQueueInit(actionQueue_t *q, Timer_t *timer, msgType_t stepMsgType, msgType_t overMsgType);
int actionQueueIn(actionQueue_t *q, action_t *action);
int actionQueueOut(actionQueue_t *q, action_t *action);
void actionDoing(actionQueue_t * q);
void actProcess(actionQueue_t * q);

void charQueueInit(charQueue_t *q);
int charQueueIn(charQueue_t *q, char ch);
int charQueueMoveTo_irq(charQueue_t *q, char* array);

int charQueueIn(charQueue_t *q, char ch);
int charQueueIn_irq(charQueue_t *q, char ch);
int charQueueOut(charQueue_t *q, char *ch);
int charQueueOut_irq(charQueue_t *q, char* ch);
int charQueueMove(charQueue_t *from, charQueue_t *to);
int charQueueMove_irq(charQueue_t *from, charQueue_t *to);

#endif
