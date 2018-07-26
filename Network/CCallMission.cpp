//
//  CCallMission.cpp
//  idlegame
//
//  Created by Sovr on 2017/11/23.
//
//

#include "CCallMission.hpp"

CCallMission::CCallMission(std::string kName, const char* url, int port)
:CSocketMission(url, port), m_kClassName(kName)
{
    
}

CCallMission::~CCallMission()
{
    clearCall();
}

void CCallMission::clearCall()
{
    for (int i=0; i<(int)m_kLinkCallFun.size(); i++) {
        delete m_kLinkCallFun[i];
    }
    m_kLinkCallFun.clear();
}

bool CCallMission::start()
{
    if (isAlive()) {
        return true;
    }
    return CSocketMission::start();
}

void CCallMission::stop()
{
    if (m_kLinkCallFun.size()) {
        onEventTCPSocketLink();
    }
    else
    {
        CSocketMission::stop();
    }
}

void CCallMission::onEventTCPSocketLink()
{
    if (m_kLinkCallFun.size() == 0) {
        return;
    }
    CallBase* pCall = (*m_kLinkCallFun.begin());
    pCall->CallFun();
    m_kLinkCallFun.erase(m_kLinkCallFun.begin());
    delete pCall;
}

void CCallMission::onEventTCPSocketShut()
{
    if (m_kLinkCallFun.size()) {
        start();
    }
}

void CCallMission::onEventTCPSocketError(int errorCode)
{
    if (m_kLinkCallFun.size()) {
        start();
    }
}

bool CCallMission::onEventTCPSocketRead(int main, int sub, void *data, int dataSize)
{
    for (int i = 0;i<(int)m_kNetCallFun.size();i++)
    {
        NetCall& kNetInfo = m_kNetCallFun[i];
        if (kNetInfo.iSub == sub)
        {
            kNetInfo.pFun(data,dataSize);
            return true;
        }
    }
    CCASSERT(false,"");
    return false;
}
