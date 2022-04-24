#pragma once


template<class EVENT>
class EventHandler {
public:
    virtual void handle(EVENT) = 0;
};