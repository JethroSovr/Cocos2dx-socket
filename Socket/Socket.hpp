//
//  Socket.hpp
//  
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef Socket_hpp
#define Socket_hpp

#include <stdio.h>
#include <list>
#include "ClientNetDelegate.hpp"

struct ISocketSink
{
    virtual ~ISocketSink(){};
    virtual void onSocketLink() = 0;
    virtual void onSocketShut() = 0;
    virtual void onSocketTimeOut() = 0;
    virtual void onSocketError(int errorCode) = 0;
    virtual void onSocketData(void* data, int dataSize) = 0;
};

class CSocket :public cocos2d::ClientNetDelegate
{
public:
    CSocket();
    ~CSocket();
    void setSocketSink(ISocketSink* pISocketSink);
    bool isAlive();
    int connect(const char* url, int port);
    void disconnect();
    int send(const char* data, int size);
    
private:
    virtual void onConnected();
    virtual void onConnectTimeout();
    virtual void onDisconnected();
    virtual void onExceptionCaught(CCSocketStatus eStatus);
    virtual void onMessageReceived(char* pData, unsigned int iLenght);
    
    ISocketSink* mSocketSink;
    
};

#endif /* Socket_hpp */
