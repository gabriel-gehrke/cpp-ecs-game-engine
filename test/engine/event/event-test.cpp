#include "engine/event/event_manager.hpp"

#include <iostream>



struct StringEvent{
    std::string event_message;
    static int event_received_counter;
};

class EventPublisher{
    EventManager<StringEvent> event_manager;

    EventPublisher() : event_manager(EventManager<StringEvent>()){}
};

class EventReceiver1 : IEventHandler<StringEvent>{

    void handle(StringEvent event) override {

    }
};


int main(){


}