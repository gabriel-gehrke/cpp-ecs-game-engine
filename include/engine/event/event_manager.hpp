#pragma once

#include <functional>
#include <unordered_map>

typedef size_t token;

template<class EVENT>
class EventManager {
    
    private:

        token token_counter;

        /**
         * Map that maps generated tokens to event_listener (aka pointer to function that return void and receive the given EVENT-Type as input)
         */
        std::unordered_map<token, std::function<void(EVENT)>> event_listeners;


    public:

        EventManager() : token_counter(1), event_listeners()
        {

        }

        /**
         * Registers an event-listener function to the event-manager instance.
         * @param new_event_listener
         * @return  Non-zero identifier-token if successfully registered
         */

        token register_listener(std::function<void(EVENT)> new_event_listener)
        {
            this->event_listeners.emplace(this->token_counter, new_event_listener);
            return token_counter++;
        }

        /**
         * Removes an event-listener from the event-manager instance.
         * @param token Token-value to identify the event-listener.
         * @return  true, if the event-listener was successfully removed
         *          false, if no event-listener was identified by the given token
         */
        bool unregister_listener(token token)
        {
            const auto& itr = event_listeners.find(token);
            if (itr == event_listeners.end())
            {
                return false;
            }
            event_listeners.erase(token);
            return true;
        }

        /**
         * Returns the number of registered listeners
         * @return Number of listeners
         */
        int number_of_registered_listener() const
        {
            return event_listeners.size();
        }

        /**
         * Fires the given event and notifies every listener
         * @param event_to_fire The event to pass to the listeners
         */
        void fire(EVENT event_to_fire) const
        {
            for(auto const& [_, listener] : event_listeners)
            {
                listener(event_to_fire);
            }
        }

};