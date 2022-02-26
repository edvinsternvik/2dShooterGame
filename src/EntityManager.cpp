#include "EntityManager.h"
#include "Rendering/Shader.h"

EntityManager::EntityManager()
    : m_nextID(1) {
    
}

bool EntityManager::destroy(entityID ID) {
    auto search = m_entities.find(ID);
    if(search != m_entities.end()) {
        search->second->m_destroyed = true;
        return true;
    }
    return false;
}

Entity* EntityManager::getEntity(entityID ID) {
    auto search = m_entities.find(ID);
    if(search != m_entities.end()) return search->second.get();
    return nullptr;
}

void EntityManager::updateEntities(float deltaTime) {
    auto it = m_entities.begin();
    while(it != m_entities.end()) {
        if(!it->second->m_destroyed) {
            it->second->update(deltaTime);
            it++;
        }
        else {
            it = m_entities.erase(it);
        }
    }
}

void EntityManager::renderEntities(Shader* shader) {
    for(auto it = m_entities.begin(); it != m_entities.end(); it++) {
        it->second->render(shader);
    }
}
