#include "Client.h"
#include "Manager/Manager.h"
#include "Manager/Notification/Manager.h"

Client::Client(const char* client_name, Version client_version) : name(client_name ? client_name : "Client"), version(client_version) {};

Client::~Client() {

    delete this->mgr_raw_ptr;
    delete this->nfMgr_raw_ptr;
    delete this->socketLayer;

};

auto Client::getName(void) -> std::string {

    return this->name;

};

auto Client::getVersion(void) -> Version {

    return this->version;

};

auto Client::init(void) -> void {

    if(this->_isRunning)
        return;
    
    this->_isRunning = true;
    
    Debugger::init(this->name);
    Debugger::log("Initialized Client <" + this->name + ">");
    
    this->nfMgr_raw_ptr = new NotificationManager(this); /* Create new Notification Manager Instance */

    this->nfMgr_raw_ptr->addNotif(std::string(this->name + ", " + this->version.get()), "Running v" + this->version.get());
    
    this->mgr_raw_ptr = new Manager(this); /* Create new Manager instance */

    this->socketLayer = new SocketLayer(this); /* Create Socket Connection to back-end Server */
    
    this->mgr_raw_ptr->init();
    this->socketLayer->start();
    this->mgr_raw_ptr->tickModules();

};

auto Client::isRunning(void) -> bool {

    return this->_isRunning;

};

auto Client::stop(void) -> void {

    this->_isRunning = false;

};

auto Client::addNotif(std::string title, std::string contents, int msDelay, bool isError) -> void {

    this->nfMgr_raw_ptr->addNotif(title, contents, msDelay, isError ? Notification::Type::Error : Notification::Type::Default);

};

auto Client::getNotifMgr(void) -> NotificationManager* {

    return this->nfMgr_raw_ptr;

};