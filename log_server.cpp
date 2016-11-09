
#include "master_server.h"

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <boost/filesystem.hpp>

class master_server::log_server {
public:
    log_server(master_server * master_server_ptr);
    ~log_server();

    int init();

private:
    master_server * m_master_server_ptr;
    log4cpp::FileAppender * m_appender_ptr;
    log4cpp::PatternLayout * m_layout_ptr;
};

master_server::log_server::log_server(master_server *master_server_ptr)
        : m_master_server_ptr(master_server_ptr)
        , m_appender_ptr(nullptr)
        , m_layout_ptr(nullptr)
{ }

master_server::log_server::~log_server() {
    log4cpp::Category::shutdown();
    delete m_appender_ptr;  m_appender_ptr = nullptr;
    delete m_layout_ptr;    m_layout_ptr = nullptr;
}

int master_server::log_server::init() {
    std::string logname = master_server_LOG_DIR;
    boost::filesystem::path path(logname);
    if (!boost::filesystem::exists(path))
        boost::filesystem::create_directory(path);

    char psztemp[64] = {0};
    time_t ct = time( NULL );
    struct tm* ctm = localtime( &ct );
    snprintf( psztemp, 64, "websocket_server_%d%02d%02d.log", ctm->tm_year+1900, ctm->tm_mon+1, ctm->tm_mday );
    logname += psztemp;

    log4cpp::Category::shutdown();

    m_appender_ptr = new log4cpp::FileAppender("Appender", logname);
    m_layout_ptr = new log4cpp::PatternLayout();
    m_layout_ptr->setConversionPattern("%d{%Y-%m-%d %H:%M:%S}: [%p][%c] : %m%n");
    m_appender_ptr->setLayout(m_layout_ptr);

    log4cpp::Category & root = log4cpp::Category::getRoot();
    root.addAppender(m_appender_ptr);
    root.setPriority(log4cpp::Priority::DEBUG);

    /// should be define in head file
    log4cpp::Category::getInstance(LOG_MASTER_SERVER_NAME);
#if 0
    log4cpp::Category::getInstance(LOG_REDIS_SERVER_NAME);
    log4cpp::Category::getInstance(LOG_CONNECTION_NAME);
#endif
    return 0;
}

void master_server::init_log_server() {
    m_log_server_ptr = new log_server(this);
    m_log_server_ptr->init();
}

void master_server::close_log_server() {
    delete m_log_server_ptr;
}



