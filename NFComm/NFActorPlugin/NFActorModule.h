/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#ifndef NF_ACTOR_MANAGER_H
#define NF_ACTOR_MANAGER_H

#include <map>
#include <string>
#include <queue>
#include "NFActor.h"
#include "NFComm/NFPluginModule/NFIComponent.h"
#include "NFComm/NFPluginModule/NFIActor.h"
#include "NFComm/NFPluginModule/NFIActorModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIThreadPoolModule.h"
#include "NFComm/NFCore/NFQueue.hpp"

class NFActorModule
    : public NFIActorModule
{
public:
	NFActorModule(NFIPluginManager* p);
    virtual ~NFActorModule();

    virtual bool Init();

    virtual bool AfterInit();

    virtual bool BeforeShut();

    virtual bool Shut();

    virtual bool Execute();

	virtual NFGUID RequireActor();
	virtual NF_SHARE_PTR<NFIActor> GetActor(const NFGUID nActorIndex);
	virtual bool ReleaseActor(const NFGUID nActorIndex);

    virtual bool SendMsgToActor(const NFGUID nActorIndex, const int messageID, const std::string& strArg);

	virtual bool AddResult(const NFActorMessage& message);

protected:
	virtual bool AddEndFunc(const int subMessageID, ACTOR_PROCESS_FUNCTOR_PTR functorPtr_end);

    virtual bool AddComponent(const NFGUID nActorIndex, NF_SHARE_PTR<NFIComponent> pComponent);
	virtual bool RemoveComponent(const NFGUID nActorIndex, const std::string& strComponentName);
	virtual NF_SHARE_PTR<NFIComponent> FindComponent(const NFGUID nActorIndex, const std::string& strComponentName);


	virtual bool ExecuteEvent();
	virtual bool ExecuteResultEvent();


private:
    NFIKernelModule* m_pKernelModule;
    NFIThreadPoolModule* m_pThreadPoolModule;

	NFMapEx<NFGUID, NFIActor> mxActorMap;

	NFQueue<NFActorMessage> mxResultQueue;
	NFMapEx<int, ACTOR_PROCESS_FUNCTOR> mxEndFunctor;

    //for schedule
    std::map<NFGUID, int> mActorMessageCount;
};

#endif
