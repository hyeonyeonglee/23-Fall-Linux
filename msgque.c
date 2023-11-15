#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
ssize_t mq_receive(mqd_t mqdes, const char *msg_ptr,size_t msg_len, unsigned int *msg_prio);
int mq_close(mqd_t mqdes);

