#include "Module.h"

Module::Module(Category* category, const std::string& display_name) : cPtr(category), evDis(std::make_unique<EventDispatcher>()), name(display_name) {
    category->registerModule(this);

    this->evDis->registerEvent<EventType::BaseTick>(
        EventDispatcher::EventPriority::High,
        [&]() {
            if(this->state.first != this->state.second) {
                this->state.second = this->state.first;

                if(this->state.first) {
                    this->evDis->dispatchEvent<EventType::OnEnable>();
                } else {
                    this->evDis->dispatchEvent<EventType::OnDisable>();
                };
            };

            if(this->state.first) {
                this->evDis->dispatchEvent<EventType::OnTick>();
            };
        }
    );
};

Manager* Module::getMgr() const {
    return this->category ? this->category->mgr : nullptr;
};

EventDispatcher* Module::getEventDispatcher() const {
    return this->evDis.get();
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

uint64_t Module::getBind() const {
    return this->bindKey;
};

void Module::setBind(uint64_t bind) {
    if(bind)
        this->bindKey = bind;
};