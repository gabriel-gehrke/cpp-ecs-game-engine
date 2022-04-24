#pragma once

#include "event_handler.hpp"

#include <map>


template<typename EVENT>
class EventManager {
private:

    int token_counter;

    /**
     * Map that maps generated tokens to event_listener (aka pointer to function that return void and receive the given EVENT-Type as input)
     */
    const std::map<int, EventHandler<EVENT>*> event_listener;


public:

    EventManager();


    /**
     * Registers an event-listener function to the event-manager instance.
     * @param new_event_listener
     * @return  Non-zero identifier-token if successfully registered
     *          -1, if the function_pointer is already registered
     */

    int register_listener(EventHandler<EVENT>*);

    /**
     * Removes an event-listener from the event-manager instance.
     * @param token Token-value to identify the event-listener.
     * @return  true, if the event-listener was successfully removed
     *          false, if no event-listener was identified by the given token
     */
    bool unregister_listener(int token);

    /**
     * Returns the number of registered listeners
     * @return Number of listeners
     */
    int number_of_registered_listener();

    /**
     * Fires the given event and notifies every listener
     * @param event_to_fire The event to pass to the listeners
     */
    void fire_event(EVENT event_to_fire);

};


template<typename EVENT>
int EventManager<EVENT>::register_listener(EventHandler<EVENT> *new_event_listener) {

    for(auto const& [_, listener] : event_listener)
        if(listener == new_event_listener)
            return -1;

    event_listener.emplace(std::make_pair<int, EventHandler<EVENT>>(token_counter, new_event_listener));
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
int EventManager<EVENT>::number_of_registered_listener() {
    return event_listener.size();
}

template<typename EVENT>
EventManager<EVENT>::EventManager() : token_counter(0), event_listener(std::map<int, EventHandler<EVENT>*>()) {}