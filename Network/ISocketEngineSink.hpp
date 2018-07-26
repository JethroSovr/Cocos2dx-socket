//
//  ISocketEngineSink.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef ISocketEngineSink_hpp
#define ISocketEngineSink_hpp

struct ISocketEngineSink
{
    virtual ~ISocketEngineSink(){}
    virtual void onEventTCPSocketLink() = 0;
    virtual void onEventTCPSocketShut() = 0;
    virtual void onEventTCPSocketError(int errorCode) = 0;
    virtual bool onEventTCPSocketRead(int main, int sub, void* data, int dataSize) = 0;
    virtual bool onEventTCPHeartTick(){return true;};
}; // ISocketEngineSink


#endif /* ISocketEngineSink_hpp */
