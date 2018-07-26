//
//  CSocketEngine.cpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#include "CSocketEngine.hpp"
#include <sstream>
#include <platform/CCCommon.h>

using namespace std;
#define SOCKET_TCP_BUFFER			16384								//网络缓冲
#define SOCKET_TCP_PACKET			(SOCKET_TCP_BUFFER-sizeof(TCP_Head))//网络缓冲

//长度定义
#define SOCKET_UDP_BUFFER			16384								//网络缓冲
#define SOCKET_UDP_PACKET			(SOCKET_UDP_BUFFER-sizeof(UDP_Head))//网络缓冲


ISocketEngine* ISocketEngine::create()
{
    return new CSocketEngine();
}

void ISocketEngine::destory(ISocketEngine *pISocketEngine)
{
    if (pISocketEngine)
    {
        delete pISocketEngine;
    }
}

CSocketEngine::CSocketEngine()
{
    mISocketEngineSink = 0;
    mIsSendTCPValidate = false;
    mSocket.setSocketSink(this);
    
    mBufPack = new byte[SIZE_TCP_BUFFER];
    mBufUnPack = new byte[SIZE_TCP_BUFFER];
    // 接收缓冲
    mBufRecieve = new byte[SIZE_TCP_BUFFER];
    mTempBuf = new byte[SIZE_TCP_BUFFER];
    
    m_dwSendPacketCount = 0;
    m_dwRecvPacketCount = 0;
    
    // add by lesten
    temp_size_ = 0;
}

CSocketEngine::~CSocketEngine()
{
    delete [] mBufPack;
    delete [] mBufUnPack;
    delete [] mBufRecieve;
    delete [] mTempBuf;
    
    mISocketEngineSink=0;
    mSocket.setSocketSink(0);
    disconnect();
}

// ISocketEngine 接口实现

/** 设置Socket接收器 */
void CSocketEngine::setSocketEngineSink(ISocketEngineSink* pISocketEngineSink)
{
    mISocketEngineSink = pISocketEngineSink;
}

void CSocketEngine::initValue()
{
    m_dwSendPacketCount = 0;
    m_dwRecvPacketCount = 0;
    mBufRevLength = 0;
    temp_size_ = 0;
    memset(mTempBuf, SIZE_TCP_BUFFER, 0);
}
/** 链接网络 **/
bool CSocketEngine::connect(const char* url, int port)
{
    initValue();
    
    cocos2d::log("Connect %s",url);
    
    return mSocket.connect(url, port) == 0;
}

/** 关闭网络 **/
bool CSocketEngine::disconnect()
{
    //恢复数据
    initValue();
    
    mSocket.disconnect();
    return true;
}

/** 发送数据 **/
bool CSocketEngine::send(void* data, int dataSize)
{
    if (!isAlive())
        return false;

    mSocket.send((const char*)data, dataSize);
    return true;
}

bool CSocketEngine::send(int main, int sub, void* data, int dataSize)
{
    if (!isAlive())
        return false;

    
    mSocket.send((const char*)data, dataSize);
    return true;
}

/** 状态判断 **/
bool CSocketEngine::isAlive()
{
    return mSocket.isAlive();
}

/** 发送校验 **/
void CSocketEngine::setTCPValidate(bool send)
{
    mIsSendTCPValidate = send;
}

//////////////////////////////////////////////////////////////////////////
// 接口ISocketSink
void CSocketEngine::onSocketLink()
{
    sendTCPValidate();
    if (mISocketEngineSink != 0)
        mISocketEngineSink->onEventTCPSocketLink();
}

void CSocketEngine::onSocketShut()
{
    if (mISocketEngineSink != nullptr)
        mISocketEngineSink->onEventTCPSocketShut();
}
void CSocketEngine::onSocketTimeOut()
{
    if (mISocketEngineSink != nullptr)
        mISocketEngineSink->onEventTCPSocketError(0);
}

void CSocketEngine::onSocketError(int errorCode)
{
    if (mISocketEngineSink != 0)
        mISocketEngineSink->onEventTCPSocketError(errorCode);
}

// 接收数据
void CSocketEngine::onSocketData(void* data, int dataSize)
{
    // 接收数据
    // 使用onEventTCPSocketRead推送出去
}

void CSocketEngine::sendTCPValidate()
{
    if (mIsSendTCPValidate == false)
        return;

//    mSocket.send(ss.str().c_str(), (int)ss.str().size());
}
