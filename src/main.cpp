//
// Created by Stuart on 3/5/2016.
//
#include <logger.h>
#include <consoleappender.h>
#include <loglevel.h>
#include <layout.h>
#include <ndc.h>
#include <loggingmacros.h>
#include "integrator.h"

using namespace log4cplus;

int main(int argc, char* argv[]) {
    SharedAppenderPtr myAppender(new ConsoleAppender());
    myAppender->setName("myAppenderName");
    std::auto_ptr<Layout> myLayout = std::auto_ptr<Layout>(new log4cplus::TTCCLayout());
    myAppender->setLayout( myLayout );
    initialize(); // start logging system
    Logger applogger = Logger::getInstance("myapp");
    applogger.addAppender(myAppender);
    LOG4CPLUS_INFO(applogger,"Starting logging"); // say hello

    // Let's use the integrator library
    const int stepSize = .1;
    double xdata[] = {1.0, 2.0, 3.0, 4.0};
    double ydata[] = {1.0, 2.0, 3.0, 4.0};
    integrator::Trapezoidal trapezoidal;
    double integrationResult = trapezoidal.integrate(stepSize,xdata,ydata);
    LOG4CPLUS_INFO(applogger, "Integration result: " << integrationResult);

}