#include <iostream>

#define LOG_MASTER_SERVER_NAME "master_server"

#ifndef MASTER_SERVER_RELEASE
#define MASTER_SERVER_DIR       "./"
#define MASTER_SERVER_LOG_DIR   "./log/"
#else
#define MASTER_SERVER_DIR
#define MASTER_SERVER_LOG_DIR   "/var/log/websocket_server/"
#endif

int main () {
    log4cpp::Category * pctg = log4cpp::Category::exists(LOG_MASTER_SERVER_NAME);

    pctg->info("trace program");
    pctg->error("errors occured");

    return 0;
}
