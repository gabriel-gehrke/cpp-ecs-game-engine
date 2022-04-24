#include "engine/event/event_manager.hpp"

#include <iostream>
#include <stdexcept>
#include <cassert>

#define EVENTMESSAGE1 "This is for EventListener1"
#define EVENTMESSAGE2 "This is for EventListener2"



int event_received_counter;
std::string expected_event_message;
bool should_listener_1_invoke;
bool should_listener_2_invoke;


struct StringEvent{
    std::string event_message;
};


template class EventManager<StringEvent>;
template class EventHandler<StringEvent>;

struct EventPublisher{
    EventManager<StringEvent> event_manager;
    EventPublisher() : event_manager(EventManager<StringEvent>()){}
};


struct EventListener1 : EventHandler<StringEvent>{

    static bool should_invoke;

    void handle(StringEvent event) override {
        if(should_invoke) {
            if (event.event_message != expected_event_message)
                throw std::invalid_argument("EventListener1 did not receive correct message: " + event.event_message);
        }else{
            throw std::runtime_error("EventListener1 was invoked, event though it wasn't supposed to");
        }
        event_received_counter++;
    }
};


struct EventListener2 : EventHandler<StringEvent>{

    static bool should_invoke;

    void handle(StringEvent event) override {
        if(should_invoke) {
            if (event.event_message != expected_event_message)
                throw std::invalid_argument("EventListener2 did not receive correct message: " + event.event_message);
        }else{
            throw std::runtime_error("EventListener2 was invoked, event though it wasn't supposed to");
        }
        event_received_counter++;
    }
};


void set_listener_invokability(bool val){
    should_listener_1_invoke = val;
    should_listener_2_invoke = val;
}

int main(){

    EventPublisher publisher;
    EventManager<StringEvent> event_manager = publisher.event_manager;
    EventListener1 listener1;
    EventListener2 listener2;
    event_received_counter = 0;

    StringEvent event1 = { .event_message=EVENTMESSAGE1 };
    StringEvent event2 = { .event_message=EVENTMESSAGE2 };

    // Test adding and running single listener
    int token1 = event_manager.register_listener(&listener1);
    assert(event_manager.number_of_registered_listener() == 1);
    should_listener_1_invoke = true;

    expected_event_message = EVENTMESSAGE1;
    event_manager.fire_event(event1);
    assert(event_received_counter == 1);


    // Test second listener next to first one
    int token2 = event_manager.register_listener(&listener2);
    assert(event_manager.number_of_registered_listener() == 2);
    should_listener_2_invoke = true;

    expected_event_message = EVENTMESSAGE2;
    event_manager.fire_event(event2);
    assert(event_received_counter == 3);

    set_listener_invokability(false);


    // Test add first listener again
    assert(event_manager.register_listener(&listener1) == -1);

    // Test remove 1 listener and send event

    assert(event_manager.unregister_listener(token1) == true);
    assert(event_manager.number_of_registered_listener() == 1);

    should_listener_2_invoke = true;
    event_manager.fire_event(event2);
    assert(event_received_counter == 4);

    // Test remove all listener
    assert(event_manager.unregister_listener(token2) == true);
    set_listener_invokability(false);
    event_manager.fire_event(event2);
    assert(event_received_counter == 4);

    // Test remove already removed listener
    assert(event_manager.unregister_listener(token1) == false);
}