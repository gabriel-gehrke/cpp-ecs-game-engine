#include "engine/event/event_manager.hpp"


template<typename EVENT>
int EventManager<EVENT>::register_listener(IEventHandler<EVENT> *new_event_listener) {

    for(auto const& [_, listener] : event_listener)
        if(listener == new_event_listener)
            return -1;

    event_listener.insert(std::pair<int, IEventHandler<EVENT>*>(token_counter, new_event_listener));
    return token_counter++;
}

template<typename EVENT>
bool EventManager<EVENT>::unregister_listener(const int token) {
    return event_listener.erase(token);
}

template<typename EVENT>
void EventManager<EVENT>::fire_event(const EVENT event_to_fire) {
    for(auto const& [_, listener] : event_listener){
        listener->handle(event_to_fire);
    }

}

template<typename EVENT>
EventManager<EVENT>::EventManager() : token_counter(0), event_listener(std::unordered_map<int, IEventHandler<EVENT>*>()) {}
