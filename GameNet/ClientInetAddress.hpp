//
//  ClientInetAddress.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef ClientInetAddress_hpp
#define ClientInetAddress_hpp

#include "cocos2d.h"
#include "NetDefine.h"
#include <string>

NS_CC_BEGIN

class ClientInetAddress : public sockaddr_in
{
public:
    ClientInetAddress();
    ClientInetAddress(const char* ip, unsigned short port);
    ClientInetAddress(const struct sockaddr* addr);
    
    virtual ~ClientInetAddress(void);
    
public:
    operator struct sockaddr*();
    operator const struct sockaddr*() const;
    const char* getHostAddress() const;
    const char* getIp() const;
    unsigned short getPort() const;
    void setIp(const char* ip);
    void setIp(unsigned int ip);
    void setPort(unsigned short port);
    void setHost(const char* name);
    
public:
    int getLength();
    
};

NS_CC_END

#endif /* ClientInetAddress_hpp */
