#include <log4cxx/logger.h>
#include <string>
#include <memory>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

std::string FLAGS_log_conf_file = "./log4j.properties";
int main() {
    log4cxx::LoggerPtr logger(log4cxx::Logger::getRootLogger());
    log4cxx::PropertyConfigurator::configure(FLAGS_log_conf_file);
    LOG4CXX_TRACE(logger, "trace");
    LOG4CXX_DEBUG(logger, "debug");
    LOG4CXX_INFO(logger, "info");
    LOG4CXX_WARN(logger, "warn");
    LOG4CXX_ERROR(logger, "error");
}