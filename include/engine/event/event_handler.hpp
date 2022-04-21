#pragma once

template<class EVENT>
class IEventHandler {
public:
    virtual void handle(EVENT) = 0;
};