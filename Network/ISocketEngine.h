//
//  ISocketEngine.h
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef ISocketEngine_h
#define ISocketEngine_h

#include "ISocketEngineSink.hpp"

static const bool	SOCKET_CHECK		= true;
/** 数据包最大大小 **/
static const int	SIZE_TCP_BUFFER		= 20480;
/** 头包大小 **/
static const int	SIZE_PACK_HEAD		= 8;
/** 包头信息大小 **/
static const int	SIZE_PACK_INFO		= 4;
/** 命令信息大小 **/
static const int	SIZE_PACK_COMMAND	= 4;
/** 附加数据最大大小 **/
static const int	SIZE_PACK_DATA		= SIZE_TCP_BUFFER - SIZE_PACK_INFO - SIZE_PACK_COMMAND;

/**
 * 网络操作接口
 * @note
 * @remark
 */
struct ISocketEngine
{
    virtual ~ISocketEngine(){}
    /*设置Socket接收器*/
    virtual void setSocketEngineSink(ISocketEngineSink* pISocketEngineSink) = 0;
    /*链接网络*/
    virtual bool connect(const char* url, int port) = 0;
    /*关闭网络*/
    virtual bool disconnect() = 0;
    /*状态判断*/
    virtual bool isAlive() = 0;
    /*发送数据*/
    virtual bool send(void* data, int dataSize);
    /** 发送校验 **/
    virtual void setTCPValidate(bool send) = 0;
    /** 创建 */
    static ISocketEngine* create();
    /** 销毁 */
    static void destory(ISocketEngine* pISocketEngine);
    
};


#endif /* ISocketEngine_h */
