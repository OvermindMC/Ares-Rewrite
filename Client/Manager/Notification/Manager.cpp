#include "Manager.h"

NotificationManager::NotificationManager(Client* client_ptr) : client(client_ptr) {

    //

};

NotificationManager::~NotificationManager(void) {

    this->notifications.clear();

};

auto NotificationManager::render(void) -> void {

    if(this->notifications.empty())
        return;
    
    auto display = ImGui::GetIO().DisplaySize;
    auto& notif = this->notifications.front();
    auto bounds = notif->getBounds(this->fontSize);

    auto reachOff = [&](float* x, float xOff, float modifier) -> void {
        if (*x < xOff) {

            if (*x < (xOff - modifier))
                *x += modifier;
            else
                *x = xOff;

        } else if (*x > xOff) {

            if (*x > (xOff + modifier))
                *x -= modifier;
            else
                *x = xOff;

        };
    };

    if(notif->animXOff <= 0.f)
        notif->animXOff = display.x;
    
    auto targetX = ((display.x - this->space) - bounds.x) - 10.f;
    reachOff(&notif->animXOff, targetX, 2.f);

    if(notif->animXOff <= targetX && !notif->doneAnim)
        notif->doneAnim = true;
    
    auto rect = ImVec4(
        notif->animXOff,
        (display.y - this->space) - bounds.y,
        notif->animXOff + (bounds.x + this->space), display.y - bounds.y
    );

    Renderer::fillRect(rect, ImColor(21.f, 21.f, 21.f, std::max(notif->alpha - .4f, 0.f)), 5.f);

    Renderer::drawText(
        ImVec2(
            rect.x + 5.f,
            rect.y + 5.f
        ), notif->title, this->fontSize, ImColor(255.f, 255.f, 255.f, notif->alpha)
    );

    auto titleSize = Renderer::getTextSize(notif->title, this->fontSize);
    if(!notif->title.empty()) {
        Renderer::fillRect(
            ImVec4(
                rect.x + 4.f, (rect.y + 5.f) + titleSize.y, (rect.x + 6.f) + titleSize.x, (rect.y + 6.f) + titleSize.y
            ), ImColor(255.f, 255.f, 255.f, notif->alpha), 1.f
        );
    };

    if(!notif->contents.empty()) {
        Renderer::drawText(
            ImVec2(
                rect.x + 5.f,
                ((rect.y + 5.f) + (titleSize.y * 2.f))
            ), notif->contents, this->fontSize, ImColor(255.f, 255.f, 255.f, notif->alpha)
        );
    };

    auto now = std::chrono::high_resolution_clock::now();
    if(now < notif->timepoint)
        return;

    if(notif->doneAnim && notif->alpha) {
        reachOff(&notif->alpha, 0.f, .02f);
    } else if(notif->doneAnim) {
        this->notifications.erase(this->notifications.begin());
    };

};