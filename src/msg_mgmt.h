#ifndef _MSG_MGMT_H
#define _MSG_MGMT_H

enum request_status {
	ST_REQ_START,
	ST_REQ_PENDING,
	ST_REQ_END
};

struct request {
	unsigned int n;
	unsigned char *data;
	enum request_status sts;
	unsigned int time_out;
	int (*request_complete_cb)(struct request *, unsigned char ok);
};

struct msg_mgmt {
	list_t *write_req;
	list_t *read_req;
	unsigned int write_count;
	unsigned int read_count;
};

extern int msg_mgmt_write_msg(struct msg_mgmt *mgmt, struct request *req);

extern int msg_mgmt_read_msg(struct msg_mgmt *mgmt, struct request *req);

#endif
