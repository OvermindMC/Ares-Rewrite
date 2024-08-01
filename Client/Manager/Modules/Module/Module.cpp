#include "Module.h"

Module::Module(Category* category, const std::string& display_name) : cPtr(category), evDis(new EventDispatcher()), name(display_name) {
    category->registerModule(this);

    this->evDispatcher->registerEvent<EventType::BaseTick>(
        EventDispatcher::EventPriority::High,
        [&]() {
            if(this->state.first != this->state.second) {
                this->state.second = this->state.first;

                if(this->state.first) {
                    this->evDispatcher->dispatchEvent<EventType::OnEnable>();
                } else {
                    this->evDispatcher->dispatchEvent<EventType::OnDisable>();
                };
            };

            if(this->state.first) {
                this->evDispatcher->dispatchEvent<EventType::OnTick>();
            };
        }
    );
};

Module::~Module() {
    delete this->evDispatcher;
};

Manager* Module::getMgr() const {
    return this->category ? this->category->mgr : nullptr;
};

bool Module::isEnabled() const {
    return this->state.second;
};

void Module::setIsEnabled(bool state) {
    this->state.first = state;
};

std::string Module::getName() const {
    return this->name;
};