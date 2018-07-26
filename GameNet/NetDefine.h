//
//  NetDefine.h
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef NetDefine_h
#define NetDefine_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
typedef unsigned int          SOCKET;
#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (SOCKET)(~0)
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR            (-1)
#endif
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <WS2tcpip.h>
typedef int socklen_t;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#endif

#ifndef DEBUG_SOCKET_DATA_INFO
#define DEBUG_SOCKET_DATA_INFO 0
#endif // DEBUG_SOCKET_DATA_INFO

#ifndef SOCKET_SOTIMEOUT
#define SOCKET_SOTIMEOUT 5.0f
#endif
#ifndef SOCKET_READ_BUFFER_SIZE
#define SOCKET_READ_BUFFER_SIZE 20480
#endif
#ifndef MEMORYTYPE_REVERSE
#define MEMORYTYPE_REVERSE 0
#endif
#ifndef HANDLE_ON_SINGLE_FRAME
#define HANDLE_ON_SINGLE_FRAME 1
#endif
#ifndef CCBUFFER_ORGINAL_SIZE
#define CCBUFFER_ORGINAL_SIZE 512
#endif

#ifndef SOCKET_HOSTPORT
#define SOCKET_HOSTPORT 3193
#endif

#ifndef SOCKET_GAMEPORT
#define SOCKET_GAMEPORT 3194
#endif

/**
 * enum   : CCSocketStatus
 * author : Jason lee
 * email  : jason.lee.c@foxmail.com
 * descpt : socket status define
 */
enum CCSocketStatus
{
    eSocketConnected			=  1,
    eSocketConnecting			=  2,
    eSocketDisconnected			=  3,
    eSocketConnectFailed		=  4,
    eSocketConnectTimeout		=  5,
    eSocketIoClosed				=  0,
    eSocketIoError				= -1,
    eSocketCreateFailed			= -2,
};

static bool isSocketVaild(const SOCKET& iSocket,bool bRecive)
{
    
    if (iSocket == INVALID_SOCKET)
    {
        return false;
    }
    fd_set	fd;
    struct timeval tv;
    
    FD_ZERO(&fd);
    FD_SET(iSocket, &fd);
    
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    
    
    if(!bRecive && select((int)(iSocket + 1), NULL, &fd, NULL, &tv) > 0 )
    {
        if( FD_ISSET(iSocket, &fd) )
        {
            return true;
        }
    }
    if(bRecive &&  select((int)(iSocket + 1), &fd, NULL, NULL, &tv) > 0 )
    {
        if( FD_ISSET(iSocket, &fd) )
        {
            return true;
        }
    }
    
    return false;
}


#endif /* NetDefine_h */
