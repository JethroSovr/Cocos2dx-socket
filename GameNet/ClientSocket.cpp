//
//  ClientSocket.cpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#include "ClientSocket.hpp"


NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static bool bStartup = false;
#endif

ClientSocket::ClientSocket()
:m_uSocket(INVALID_SOCKET)
{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    if( !bStartup )
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 0), &wsaData);
        bStartup = true;
    }
#endif
}

ClientSocket::~ClientSocket()
{
    ccClose();
}

bool ClientSocket::ccInit()
{
    cocos2d::log("ClientScoket::ccInit");
    
    if (m_uSocket != INVALID_SOCKET) {
        ccClose();
    }
    
    m_uSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_uSocket == INVALID_SOCKET) {
        CCLOGERROR("create socket failed");
        return false;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    int nRet = ioctlsocket(m_uSocket, FIONBIO, (u_long*)&ul);
    if( nRet == SOCKET_ERROR )
    {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    int nFlags = fcntl(m_uSocket, F_GETFL, 0);
    int nRet = fcntl(m_uSocket, F_SETFL, nFlags | O_NONBLOCK);
    if (nRet == SOCKET_ERROR) {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif
    
    int nNoDelay = 1;
    if (setsockopt(m_uSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR ) {
        CCLOGERROR("set nodelay failed");
        ccClose();
        
        return false;
    }
    return true;
}

void ClientSocket::ccClose()
{
    if( m_uSocket != INVALID_SOCKET )
    {
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
        closesocket(m_uSocket);
#endif
        
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        close(m_uSocket);
#endif
        m_uSocket = INVALID_SOCKET;
    }
}

bool ClientSocket::ccConnect()
{
    cocos2d::log("ClientSocket::ccConnect");
    
#if 1 // runtime error on ios
    CCAssert(strlen(m_oInetAddress.getIp()) && m_oInetAddress.getPort() != 0, "_connect");
#endif

    if (m_uSocket == INVALID_SOCKET) {
        if (!ccInit()) {
            return false;
        }
    }
    
    int nRet = ::connect(m_uSocket, m_oInetAddress, m_oInetAddress.getLength());
    if( nRet == 0 )
    {
        return true;
    }
    else
    {
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
        int nError = WSAGetLastError();
        if( nError ==  WSAEWOULDBLOCK )
        {
            return true;
        }
        else
        {
            return false;
        }
#endif
        
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        if( nRet == SOCKET_ERROR && errno == EINPROGRESS )
        {
            return true;
        }
        else
        {
            return false;
        }
#endif
    }
}

void ClientSocket::ccDisconnect()
{
    cocos2d::log("MLClientScoket::ccDisconnect");
    if( m_uSocket != INVALID_SOCKET )
    {
#if 0
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
        shutdown(m_uSocket, SD_BOTH);
#endif
        
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        shutdown(m_uSocket, SHUT_RDWR);
#endif
#endif
        ccClose();
    }
}

void ClientSocket::setInetAddress(const cocos2d::ClientInetAddress &oInetAddress)
{
    m_oInetAddress = oInetAddress;
}

int ClientSocket::ccRead(char* _buff, int _len)
{
    if( m_uSocket == INVALID_SOCKET )
        return eSocketIoError;
    
    return ::recv(m_uSocket, _buff, _len, 0);
}

int ClientSocket::ccWrite(char* _buff, int _len)
{
    if( m_uSocket == INVALID_SOCKET )
        return eSocketIoError;
    
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    return ::send(m_uSocket, _buff, _len, 0);
#endif
    
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return ::send(m_uSocket, _buff, _len, SO_NOSIGPIPE);
#endif
}

bool ClientSocket::ccIsSocketVaild(bool bRecive)
{
    return isSocketVaild(m_uSocket,bRecive);
}

int ClientSocket::ccIsConnected()
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return false;
    }
    fd_set	fd;
    struct timeval tv;
    
    FD_ZERO(&fd);
    FD_SET(m_uSocket, &fd);
    
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    
    if( select((int)(m_uSocket + 1), NULL, &fd, NULL, &tv) > 0 )
    {
        if( FD_ISSET(m_uSocket, &fd) )
        {
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
            
            return eSocketConnected;
            
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
            
            int nError;
            socklen_t len = sizeof(nError);
            if( getsockopt(m_uSocket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0 )
            {
                return eSocketConnectFailed;
            }
            if( nError == ECONNREFUSED || nError == ETIMEDOUT )
            {
                return eSocketConnectFailed;
            }
            return eSocketConnected;
            
#endif
        }
    }
    return eSocketConnecting;
}

NS_CC_END
