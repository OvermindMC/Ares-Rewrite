#include "Manager.h"
#include "Modules/Module/Module.h"

Manager::Manager(Client* client_raw_ptr) : client(client_raw_ptr) {};

Manager::~Manager(void) {

    if(!this->hooks.empty()) {
        
        //

    };

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    for(auto& item : this->categories) {
        delete item.second;
    };

    this->categories.clear();

};

auto Manager::getClient(void) -> Client* {

    return this->client;

};

auto Manager::init(void) -> void {

    Debugger::log("Initialized Manager");

    if(this->initHooks()) {
        this->initCategories();
        this->initSubModules();

        while(this->client->isRunning()) {

            for(auto [ type, category ] : this->categories) {
                for(auto module : category->getModules()) {
                    module->baseTick();
                };
            };

            Sleep(1);

        };
    };

};

auto Manager::initHooks(void) -> bool {

    if(MH_Initialize() != MH_OK)
        return false;
    
    // WIP

    return true;

};

auto Manager::initCategories(void) -> void {

    for(auto i = static_cast<int>(CategoryType::COMBAT); i <= static_cast<int>(CategoryType::MISC); i++) {
        
        auto type = static_cast<CategoryType>(i);
        
        if(!this->categories.contains(type)) {
            this->categories[type] = new Category(this, type);
            Debugger::log(
                std::string("Initializing Category <" + this->categories[type]->getName() + ">")
            );
        };

    };

};

#include "Modules/Module/Misc/TestModule.h"

auto Manager::initSubModules(void) -> void {

    new TestMod(this);

};

auto Manager::getCategory(CategoryType category_type) -> Category* {

    return (this->categories.contains(category_type) ? this->categories.at(category_type) : nullptr);

};

auto Manager::getSortedEvents(void) -> std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> {

    auto dispatchers = std::vector<EventDispatcher*>([&]() { std::vector<EventDispatcher*> result; for(auto [ type, category ] : this->categories) for(auto module : category->getModules()) result.push_back(module->getEventDispatcher()); return result; }());
    return ([&, this]() { std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> result; for(auto& dispatcher : dispatchers) for(const auto& [eventType, eventList] : dispatcher->events_map) if(!eventList.empty()) result[eventType].insert(result[eventType].end(), eventList.begin(), eventList.end()); for (auto& [eventType, eventList] : result) std::sort(eventList.begin(), eventList.end(), [](const auto& a, const auto& b) { return a.first > b.first; }); return result; }());

};