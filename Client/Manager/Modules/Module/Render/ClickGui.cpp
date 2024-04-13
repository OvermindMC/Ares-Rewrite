#include "ClickGui.h"

ClickGui::ClickGui(Manager* mgr) : Module(mgr, CategoryType::RENDER, "ClickGui", "Interact with Modules", VK_INSERT) {

    this->setState(true);

    this->getEventDispatcher()->registerEvent(
        EventType::Present_Tick, EventDispatcher::EventPriority::Highest, std::function<void(void)>(
            [&](void) -> void {
                auto instance = MC::getClientInstance();
            }
        )
    );

};