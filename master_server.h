
#ifndef MASTER_SERVER_H
#define MASTER_SERVER_H

class master_server {
public:
    virtual ~master_server()
    { delete m_log_server_ptr; }

    void init_log_server();
    void close_log_server();

private:
    class log_server;
private:
    log_server * m_log_server_ptr;
};

#endif
