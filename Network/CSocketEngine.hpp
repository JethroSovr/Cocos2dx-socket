//
//  CSocketEngine.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef CSocketEngine_hpp
#define CSocketEngine_hpp

#include "ISocketEngine.h"
#include "Socket.hpp"

typedef unsigned char byte;

class CSocketEngine : public ISocketEngine, public ISocketSink
{
  
public:
    CSocketEngine();
    virtual ~CSocketEngine();
    
    // 接口ISocketEngine
public:
    /*设置socket接收器*/
    virtual void setSocketEngineSink(ISocketEngineSink* pISocketEngineSink);
    /*链接网络*/
    virtual bool connect(const char* url, int port);
    /** 关闭网络 **/
    virtual bool disconnect();
    /** 发送数据 **/
    virtual bool send(int main, int sub, void* data, int dataSize);
    virtual bool send(void* data, int dataSize);

    /** 状态判断 **/
    virtual bool isAlive();
    /** 发送校验 **/
    virtual void setTCPValidate(bool send);
    // 接口ISocketSink
public:
    virtual void onSocketLink();
    virtual void onSocketShut();
    virtual void onSocketTimeOut();
    virtual void onSocketError(int errorCode);
    virtual void onSocketData(void* data, int dataSize);
    
    //////////////////////////////////////////////////////////////////////////
    // 辅助函数
private:
    void initValue();
    void sendTCPValidate();
//    const byte* pack(int main, int sub, byte* data, int size);
//    bool unpack(byte* data, int start, int length);
private:
    // 接收处理模块
    ISocketEngineSink* mISocketEngineSink;
    // 连接SOCKET
    CSocket mSocket;
    // 发送校验
    bool mIsSendTCPValidate;
    
    //////////////////////////////////////////////////////////////////////////
    // 数据缓冲
private:
    // 临时缓冲
    byte* mBufPack;
    byte* mBufUnPack;
    // 接收缓冲
    byte* mBufRecieve;
    // 接收长度
    int mBufRevLength;
    
    //  add by  lesten
private:
    byte* mTempBuf;
    unsigned int temp_size_;
    
protected:
    //计数变量
    unsigned int							m_dwSendPacketCount;				//发送计数
    unsigned int							m_dwRecvPacketCount;				//接受计数

    
};

#endif /* CSocketEngine_hpp */
