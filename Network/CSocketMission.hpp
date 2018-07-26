//
//  CSocketMission.hpp
//  idlegame
//
//  Created by Sovr on 2017/11/23.
//
//

#ifndef CSocketMission_hpp
#define CSocketMission_hpp

#include <stdio.h>
#include "ISocketEngine.h"

class CSocketMission : public ISocketEngineSink
{
public:
    CSocketMission(const char* url=0, int port=0);
    virtual ~CSocketMission();
    
    void setUrl(const char* url, int port);
    bool isAlive() const;
    bool send(int main, int sub);
    bool send(int main, int sub, void* data, int size);
    bool send(void* data, int size);

    virtual bool start();
    virtual void stop();
    
private:
    ISocketEngine* mSocketEngine;
    char mUrl[260];
    int mPort;
};

#endif /* CSocketMission_hpp */
