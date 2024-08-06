#include "Aimbot.h"

Vec2 calcAnglesDeg(const Vec3& currPos, const Vec3& target) {
    Vec2 angles;

    float dX = target.x - currPos.x;
    float dY = target.y - currPos.y;
    float dZ = target.z - currPos.z;

    double horizontalDistance = sqrt(dX * dX + dZ * dZ);

    angles.x = atan2(dY, horizontalDistance) * RAD_TO_DEG;
    angles.y = atan2(dZ, dX) * RAD_TO_DEG;

    return angles;
};

Vec2 calcAnglesRad(const Vec3& currPos, const Vec3& target) {
    Vec2 vec2;

    float dX = currPos.x - target.x;
    float dY = currPos.y - target.y;
    float dZ = currPos.z - target.z;
    double distance = sqrt(dX * dX + dY * dY + dZ * dZ);

    vec2.x = ((float)atan2(dY, (float) distance) * (float) 3.138102054 / PI);
    vec2.y = ((float)atan2(dZ, dX) * (float) 3.138102054 / PI) - (float) 1.569051027;

    return vec2;
};

Aimbot::Aimbot(Category* c) : Module(c, "Aimbot") {
    this->registerEvent<EventType::OnFirstPersonLook, Vec2*>(
        EventDispatcher::EventPriority::High,
        [&](Vec2* mAngles) {
            if(!this->isEnabled())
                return;
            
            Player* player = MC::getLocalPlayer();

            if(!player)
                return;
            
            uint64_t lRuntimeId = player->getRuntimeId();
            Vec3 myPos = player->getPosition();

            auto entities = MC::getEntities();
            if(entities.size() <= 1)
                return;
            
            std::sort(entities.begin(), entities.end(), [&](Actor* a, Actor* b) {
                return a->getPosition().distance(myPos) < b->getPosition().distance(myPos);
            });

            for(auto ent : entities) {
                if(ent->getRuntimeId() == lRuntimeId)
                    continue;
                
                Vec3 tPos = ent->getPosition();

                if(tPos.distance(myPos) > this->distance)
                    break;

                Vec2 calcsDeg = calcAnglesDeg(myPos, tPos);
                Vec2 calcsRad = calcAnglesRad(myPos, tPos);

                *mAngles = Vec2(
                    -calcsRad.y,
                    calcsDeg.x * DEG_TO_RAD
                );

                break;
            }
        }
    );
};