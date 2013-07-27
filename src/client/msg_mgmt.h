#ifndef _MSG_MGMT_H
#define _MSG_MGMT_H

#include "common/list.h"

enum msg_req_status {
	ST_REQ_START,
	ST_REQ_PENDING
};

struct msg_req {
	unsigned int n;
	unsigned char *data;
	enum msg_req_status sts;
	unsigned int time_out;
	int (*request_complete_cb)(unsigned char ok);
	list_t *next;
};

struct msg_handler {
	int (*write)(int socket, unsigned char *buf, unsigned int n);
	int (*read)(int socket, unsigned char *buf, unsigned int n);
	int socket;
};

struct msg_mgmt {
	list_t *write_req;
	list_t *read_req;
	unsigned int write_tmr;
	unsigned int read_tmr;
	struct msg_handler *handler;
};

extern struct msg_req *msg_req_create_req(void);

extern struct msg_handler *msg_handler_create_handler(int (*write)(int ,unsigned char *, unsigned int),
							int (*read(int ,unsigned char *, unsigned int)));

extern int msg_handler_set_socket(struct msg_handler *handler, int socket);

extern struct msg_mgmt *msg_mgmt_create_mgmt(void);

extern int msg_mgmt_set_handler(struct msg_mgmt *mgmt, struct msg_handler *handler);

extern int msg_mgmt_write_msg(struct msg_mgmt *mgmt, struct msg_req *req);

extern int msg_mgmt_read_msg(struct msg_mgmt *mgmt, struct msg_req *req);

#endif
