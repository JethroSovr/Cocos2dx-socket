//
//  ClientSocket.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/22.
//
//

#ifndef ClientSocket_hpp
#define ClientSocket_hpp

#include "cocos2d.h"
#include "NetDefine.h"
#include "ClientInetAddress.hpp"
#include <string>


NS_CC_BEGIN

class ClientSocket
{
public:
    ClientSocket();
    virtual ~ClientSocket();
    
    bool ccInit();
    int ccRead(char* _buff, int _len);
    int ccWrite(char* _buff, int _len);
    int ccIsConnected();
    bool ccIsSocketVaild(bool bRecive);
    void ccClose();
    bool ccConnect();
    void ccDisconnect();
    void setInetAddress(const ClientInetAddress& oInetAddress);
    
protected:
    SOCKET m_uSocket;
    ClientInetAddress m_oInetAddress;
    
};

NS_CC_END
#endif /* ClientSocket_hpp */
