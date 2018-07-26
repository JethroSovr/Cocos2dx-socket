//
//  Socket.cpp
//  
//
//  Created by Sovr on 2017/11/22.
//
//

#include "Socket.hpp"
#include <map>
#include "cocos2d.h"
#include <iostream>

CSocket::CSocket()
:mSocketSink(0)
{
    
}

CSocket::~CSocket()
{
    
}

void CSocket::setSocketSink(ISocketSink *pISocketSink)
{
    mSocketSink = pISocketSink;
}

bool CSocket::isAlive()
{
    return cocos2d::ClientNetDelegate::isConnected();
}

int CSocket::send(const char *data, int size)
{
    if (!isAlive()) {
        return -1;
    }
    
    cocos2d::ClientNetDelegate::send(data, size);
    return 1;
}

int CSocket::connect(const char *url, int port)
{
    disconnect();
    m_oInetAddress.setIp(url);
    m_oInetAddress.setPort(port);
    
    cocos2d::ClientNetDelegate::connect();
    
    return 0;
}

void CSocket::disconnect()
{
    if (!isAlive()) {
        return;
    }
    
    cocos2d::ClientNetDelegate::disconnect();
}

void CSocket::onConnected()
{
    if (mSocketSink) {
        mSocketSink->onSocketLink();
    }
}

void CSocket::onConnectTimeout()
{
    cocos2d::log("CSocket::onConnectTimeout %s.\n", mSocketSink == 0 ? "null" : "no null");
    if (mSocketSink) {
        mSocketSink->onSocketTimeOut();
    }
}

void CSocket::onDisconnected()
{
    cocos2d::log("CSocket::onDisconnected %s.\n", mSocketSink == 0 ? "null" : "no null");
    if (mSocketSink)
        mSocketSink->onSocketShut();
}

void CSocket::onExceptionCaught(CCSocketStatus eStatus)
{
    cocos2d::log("CSocket::onSocketError %s.\n", mSocketSink == 0 ? "null" : "no null");
    if (mSocketSink)
        mSocketSink->onSocketError(eStatus);
}

void CSocket::onMessageReceived(char* pData,unsigned int iLenght)
{
    if (mSocketSink)
        mSocketSink->onSocketData(pData, iLenght);
}
