#pragma once
#include "Entity.h"
#include <unordered_map>
#include <memory>

class Shader;

using entityID = uint32_t;

class EntityManager {
public:
    EntityManager();

    template <typename T, typename... Args>
    entityID create(Args... args) {
        entityID ID = m_nextID++;
        m_entities.insert({ID, std::make_unique<T>(args...)});
        return ID;
    }

    template <typename T>
    T* getEntity(entityID ID) {
        auto search = m_entities.find(ID);
        if(search != m_entities.end()) {
            return dynamic_cast<T*>(search->second.get());
        }
        return nullptr;
    }

    Entity* getEntity(entityID ID);
    bool destroy(entityID ID);

    void updateEntities(float deltaTime);
    void renderEntities(Shader* shader);
    
private:
    std::unordered_map<entityID, std::unique_ptr<Entity>> m_entities;
    entityID m_nextID;
};
