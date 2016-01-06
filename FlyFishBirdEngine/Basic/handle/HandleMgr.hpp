//
//  HandleMgr.hpp
//  test1
//
//  Created by weitoo on 15/12/30.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#ifndef HandleMgr_hpp
#define HandleMgr_hpp

#include <stdio.h>

#include <vector>
#include <cassert>
#include "Handle.hpp"


namespace ffb {
    
    template <typename DATA, typename HANDLE>
    class HandleMgr {
        
    private:
        //私有类型
        typedef std::vector<DATA>           UserVec;
        typedef std::vector<unsigned int>   MagicVec;
        typedef std::vector<unsigned int>   FreeVec;
        
        //私有数据
        UserVec m_UserData;             //我们需要获取的数据
        MagicVec m_MagicNumbers;        //相应的魔术数
        FreeVec m_FreeSolts;            //数据库中需要跟踪的空闲列表
        
    public:
        
        
        //生命周期
        HandleMgr(){}
        ~HandleMgr(){}
        
        //句柄方法
        //分配
        DATA* Acquire(HANDLE& handle);
        //释放
        void  Release(HANDLE handle);
        
        //解引用
        DATA* Dereference(HANDLE handle);
        const DATA* Dereference(HANDLE handle) const;
        
        //其他查询
        unsigned int GetUsedHandleCount(void) const
        { return m_MagicNumbers.size() - m_FreeSolts.size(); }
        
        bool HasUsedHandles(void) const
        { return !!GetUsedHandleCount(); }
    };
}







#endif /* HandleMgr_hpp */
