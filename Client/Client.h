#pragma once

#include "Socket/Socket.h"
#include "Version/Version.h"

/* Forward Declarations */
class Manager;
class NotificationManager;

/* Client Class */

class Client {
/* Constructor, Deconstructor */

public:
    Client(const char* client_name);
    ~Client(void);
    
/* Client Name, Client Version */

    auto getName(void) -> std::string;
    auto getVersion(void) -> Version;
    
private:
    std::string name;
    Version version = Version(3, 0, 0);

/* Runtime Attributes */

    bool _isRunning = false;
    Manager* mgr_raw_ptr = nullptr;
    SocketLayer* socketLayer = nullptr;
    NotificationManager* nfMgr_raw_ptr = nullptr;

public:
    PTR_ACCESS(Manager*, mgr, mgr_raw_ptr);

/* Runtime Methods */

    auto init(void) -> void;

    auto isRunning(void) -> bool;
    auto stop(void) -> void;

    auto addNotif(std::string title, std::string contents, int msDelay = 3000, bool isError = false) -> void;
    auto getNotifMgr(void) -> NotificationManager*;
};