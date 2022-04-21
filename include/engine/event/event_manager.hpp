#pragma once

#include "event_handler.hpp"

#include <unordered_map>


template<typename EVENT>
class EventManager {
private:

    int token_counter;

    /**
     * Map that maps generated tokens to event_listener (aka pointer to function that return void and receive the given EVENT-Type as input)
     */
    const std::unordered_map<int, IEventHandler<EVENT>*> event_listener;


public:

    EventManager();


    /**
     * Registers an event-listener function to the event-manager instance.
     * @param new_event_listener
     * @return  Non-zero identifier-token if successfully registered
     *          -1, if the function_pointer is already registered
     */
    int register_listener(IEventHandler<EVENT>*);

    /**
     * Removes an event-listener from the event-manager instance.
     * @param token Token-value to identify the event-listener.
     * @return  true, if the event-listener was successfully removed
     *          false, if no event-listener was identified by the given token
     */
    bool unregister_listener(int token);

    /**
     * Fires the given event and notifies every listener
     * @param event_to_fire The event to pass to the listeners
     */
    void fire_event(EVENT event_to_fire);

};
