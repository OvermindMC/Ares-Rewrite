#include "Manager.h"
#include "Hook/Hook.h"
#include "Modules/Module/Module.h"

Manager::Manager(Client* client_raw_ptr) : client_instance_raw_ptr(client_raw_ptr) {};

Manager::~Manager(void) {

    this->categories.clear();

    if(!this->hooks.empty()) {
        
        //

    };

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

};

auto Manager::init(void) -> void {

    Debugger::log("Initialized Manager");

    this->signature_map = {
        {"Actor_VTable", []() {
            auto ptr = std::make_unique<Signature>("48 8D 05 ? ? ? ? 48 89 03 48 C7 83 ? ? ? ? ? ? ? ? 48 8B 8B ? ? ? ?");
            return ptr->get(Signature::SearchType::VTable);
        }()},
        {"Player_VTable", []() {
            auto ptr = std::make_unique<Signature>("48 8D 05 ? ? ? ? 48 89 01 B8 ? ? ? ? 8D 50 FA 44 8D 48 FE 44 8D 40 FC 66 89 44 24 ? E8 ? ? ? ? 48 8B 8B ? ? ? ?");
            return ptr->get(Signature::SearchType::VTable);
        }()},
        {"Level_VTable", []() {
            auto ptr = std::make_unique<Signature>("48 8D 05 ? ? ? ? 48 89 ? 48 8D 05 ? ? ? ? 48 89 ? 18 48 8D 05 ? ? ? ? 48 89 ? 20 ? ? ? ? ? ? ? 48 ? ? ? ? E8 ? ? ? ? 48 8B");
            return ptr->get(Signature::SearchType::VTable);
        }()},
        {"GameMode_VTable", []() {
            auto ptr = std::make_unique<Signature>("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17");
            return ptr->get(Signature::SearchType::VTable);
        }()},
        {"AVMouseInput", []() {
            auto ptr = std::make_unique<Signature>("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 EC 60");
            return ptr->get(Signature::SearchType::Default);
        }()},
        {"AVMouseInput", []() {
            auto ptr = std::make_unique<Signature>("48 83 EC 48 0F B6 C1 4C 8D 05");
            return ptr->get(Signature::SearchType::Default);
        }()}
    };

    if(this->initHooks()) {
        this->initCategories();
        this->initSubModules();

        while(this->client_instance_raw_ptr->isRunning()) {

            for(auto& pair : this->categories) {
                for(auto module : pair.second->getModules()) {
                    module->baseTick();
                };
            };

            Sleep(1);

        };
    };

};

#include "Hook/Hooks/Actor/Tick.h"

auto Manager::initHooks(void) -> bool {

    if(MH_Initialize() != MH_OK)
        return false;
    
    new Actor_TickHook(this);

    return true;

};

auto Manager::initCategories(void) -> void {

    for(auto i = static_cast<int>(CategoryType::COMBAT); i <= static_cast<int>(CategoryType::MISC); i++) {
        
        auto type = static_cast<CategoryType>(i);
        
        if(!this->categories.contains(type)) {
            this->categories[type] = std::make_unique<Category>(this, type);
            Debugger::log(
                std::string("Initializing Category <" + this->categories[type]->getName() + ">")
            );
        };

    };

};

#include "Modules/Module/Misc/TestMod.h"
#include "Modules/Module/Misc/Uninject.h"

auto Manager::initSubModules(void) -> void {

    new TestMod(this);
    new Uninject(this);

};

auto Manager::registerHook(void* hook_raw_ptr) -> void {

    auto hook = (Hook<void>*)hook_raw_ptr;
    auto canPush = true;

    for(auto curr_hook_raw_ptr : this->hooks) {

        auto currHook = (Hook<void>*)curr_hook_raw_ptr;

        if(currHook->name == hook->name) {
            canPush = false;
            break;
        };

    };

    if(canPush) {
        this->hooks.push_back(hook_raw_ptr);
    } else {
        Debugger::log("This hook was already initialized!");
    };

};

auto Manager::getCategory(CategoryType category_type) -> Category* {

    return (this->categories.contains(category_type) ? this->categories.at(category_type).get() : nullptr);

};

auto Manager::getSortedEvents(void) -> std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> {

    auto dispatchers = std::vector<EventDispatcher*>();
    for (auto& [type, category] : this->categories) {
        for (auto module : category->getModules()) {
            dispatchers.push_back(module->getEventDispatcher());
        };
    };

    std::map<EventType, std::vector<std::pair<EventDispatcher::EventPriority, void*>>> result;
    for (auto& dispatcher : dispatchers) {
        for (const auto& [eventType, eventList] : dispatcher->events_map) {
            if (!eventList.empty()) {
                auto& destination = result[eventType];
                destination.insert(destination.end(), eventList.begin(), eventList.end());
            };
        };
    };

    for (auto& [eventType, eventList] : result) {
        std::sort(eventList.begin(), eventList.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
    };

    return result;

};