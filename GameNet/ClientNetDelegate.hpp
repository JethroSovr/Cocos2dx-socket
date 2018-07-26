//
//  ClientNetDelegate.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef ClientNetDelegate_hpp
#define ClientNetDelegate_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "NetDefine.h"
#include "ClientSocket.hpp"

NS_CC_BEGIN

class ClientNetDelegate : public Ref
{
public:
    ClientNetDelegate();
    virtual ~ClientNetDelegate();
    
public:
    // will calling when a package is coming
    virtual void onMessageReceived(char* pData, unsigned int iLenght) = 0;
    
    // when connected will calling
    virtual void onConnected(){}
    
    // when connect time out will calling
    virtual void onConnectTimeout(){}
    
    // on disconnected will call
    virtual void onDisconnected(){}
    
    // on exception
    virtual void onExceptionCaught(CCSocketStatus eStatus){}
    
protected:
    // set target address
    void setInetAddress(const ClientInetAddress& oInetAddress);
    
    // get target address
    const ClientInetAddress& getInetAddress() const;
    // the time out of connecting
    void setSoTimeout(float fSoTimeout);
    
    // get the time out value
    float getSoTimeout() const;
    
    // send package to target address
    void send(const char* pData,int iSize);
    
    // check the net status
    bool isConnected();
    
    // close the socket
    void close();
    
    // connect to target address
    bool connect();
    
    // disconnect as close for now
    void disconnect();
    
    // frame call
    void runSchedule(float dt);
private:
    // read data on every frame, if needed
    bool runRead();
    
    // send data on every frame, if needed
    bool runWrite();
    
protected:
    float                  m_fConnectingDuration;
    float                  m_fSoTimeout;
    char*				   m_pSendBuffer;
    int					   m_iSendCout;
    ClientInetAddress      m_oInetAddress;
    ClientSocket           m_oSocket;
    char*                  m_pReadBuffer;
    
protected:
    CCSocketStatus         m_eStatus;

    
};

NS_CC_END

#endif /* ClientNetDelegate_hpp */
