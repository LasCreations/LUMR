#ifndef ROUTE_H
#define ROUTE_H

#include "pages.h"


void handleRouting(CLIENT *client);

void pageRequest(CLIENT *client);
void handleAbout(CLIENT *client);
void handleUserProfile(CLIENT *client);



struct Route {
    const char *method;
    const char *path;
    void (*handler)(CLIENT *client);
};

//store routes
extern struct Route routes[];


#endif