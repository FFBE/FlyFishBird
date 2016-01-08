//
//  Handle.cpp
//  test1
//
//  Created by weitoo on 15/12/30.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#include "Handle.hpp"
#include <cassert>

namespace ffb {
    
    
    template <typename TAG>
    void Handle<TAG>:: Init(unsigned int index)
    {
        
        assert(IsNull());                   //不允许重新赋值
        assert(index <= MAX_INDEX);         //有效范围验证
        
        static unsigned int s_AutoMagic = 0;
        if (++s_AutoMagic > MAX_MAGIC)
        {
            s_AutoMagic = 1;                //0用于“空句柄”
        }
        
        m_index = index;
        m_Magic = s_AutoMagic;
    }
    
    
    
    
    
    template <typename DATA, typename HANDLE>
    DATA* HandleMgr <DATA, HANDLE>::Acquire( HANDLE & handle)
    {
        //如果空闲列表为空，则新增一个，否则使用第一个可用表项
        
        unsigned int index;
        if (m_FreeSolts.empty())
        {
            index = m_MagicNumbers.size();
            handle.Init(index);
            m_UserData.push_back( DATA() );
            m_MagicNumbers.push_back( handle.GetMagic() );
        }
        else
        {
            index = m_FreeSolts.back();
            handle.Init(index);
            m_FreeSolts.pop_back();
            m_MagicNumbers[ index ] = handle.GetMagic();
        }
        
        return &*(m_UserData.begin() + index);
    }
    
    
    template <typename DATA, typename HANDLE>
    void HandleMgr <DATA, HANDLE>::Release( HANDLE handle) {
        
        //哪一个
        unsigned int index = handle.GetIndex();
        
        //确认其有效性
        assert( index < m_UserData.size() );
        assert( m_MagicNumbers[ index ] == handle.GetMagic() );
        
        //可以删除了 —— 标记其没有使用并加入到空闲列表
        m_MagicNumbers[ index ] = 0;
        m_FreeSolts.push_back( index );
    }
    
    template <typename DATA, typename HANDLE>
    inline DATA* HandleMgr<DATA, HANDLE> :: Dereference( HANDLE handle)
    {
        if ( handle.IsNull() )  return 0;
        
        //检查句柄有效性——为提供性能可用去掉这个检查
        //如果你假设索引句柄解引用总是有效
        unsigned int index = handle.GetIndex();
        if ( (index >= m_UserData.size()) || m_MagicNumbers[ index ] != handle.GetMagic() )
        {
            //无效句柄 = 客户程序错误
            assert(0);
            return 0;
        }
        
        return &*(m_UserData.begin() + index);
    }
    
    
    
    template <typename DATA, typename HANDLE>
    inline const DATA* HandleMgr<DATA, HANDLE> :: Dereference( HANDLE handle) const
    {
        typedef HandleMgr <DATA, HANDLE> ThisType;
        return const_cast<ThisType *>(this) -> Dereference( handle );
    }
    
}
