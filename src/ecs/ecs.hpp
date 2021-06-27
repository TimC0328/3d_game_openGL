#pragma once

#include "ecs/ecsComponent.hpp"
#include "ecs/ecsSystem.hpp"
#include "dataStructures/map.hpp"

class ECS
{
    public:
        ECS() {}
        ~ECS();

        //Entity methods
        EntityHandle makeEntity(BaseECSComponent* components, const uint32* componentIDs, size_t numComponents);
        void removeEntity(EntityHandle handle);

        //Component methods
        template<class Component>
        inline void addComponent(EntityHandle entity,Component* component)
        {
            addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
        }

        template<class Component>
        bool removeComponent(EntityHandle entity)
        {
            return removeComponentInternal(entity, Component::ID);
        }

        template<class Component>
        Component* getComponent(EntityHandle entity)
        {
            getComponentInternal(handleToEntity(entity), Component::ID);
        }

        //System methods
        inline void addSystem(BaseECSSystem& system)
        {
            systems.push_back(&system);
        }
        void updateSystem(float delta);
        void removeSystem(BaseECSSystem& system);
    private:
        Array<BaseECSSystem*> systems;
        Map<uint32, Array<uint8>> components;
        Array<std::pair<uint32, Array<std::pair<uint32, uint32> > >* > entities;

        inline std::pair<uint32, Array<std::pair<uint32, uint32> > >* handleToRawType(EntityHandle handle)
        {
            (std::pair<uint32, Array<std::pair<uint32, uint32> > >*)handle;
        }

        inline uint32 handleToEntityIndex(EntityHandle handle)
        {
            return handleToRawType(handle)->first;
        }

        inline Array<std::pair<uint32, uint32> >& handleToEntity(EntityHandle handle)
        {
            return handleToRawType(handle)->second;
        }

        void deleteComponent(uint32 componentID, uint32 index);
        bool removeComponentInternal(EntityHandle handle, uint32 componentID);
        void addComponentInternal(EntityHandle handle, Array<std::pair<uint32, uint32> >& entity, uint32 componentID, BaseECSComponent* component);
        BaseECSComponent* getComponentInternal(Array<std::pair<uint32, uint32> >& entityComponents, uint32 componentID);

        NULL_COPY_AND_ASSIGN(ECS);
};
