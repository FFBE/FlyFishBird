//
//  Handle.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/8.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef Handle_hpp
#define Handle_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <cassert>

namespace ffb {
    
    template <typename TAG>
    class Handle
    {
    private:
        enum
        {
            //使用位域（bit fields）的大小
            MAX_BITS_INDEX = 16,
            MAX_BITS_MAGIC = 16,
            
            //解引用断言中需要比较的大小
            MAX_INDEX = ( 1 << MAX_BITS_INDEX) -1,
            MAX_MAGIC = ( 1 << MAX_BITS_MAGIC) -1,
        };
        
        union
        {
            struct
            {
                unsigned m_index : MAX_BITS_INDEX; //资源数组的索引
                unsigned m_Magic : MAX_BITS_MAGIC; //需要检查的魔术数
            };
            unsigned int m_Handle;
        };
        
    public:
        
        //生命期
        
        Handle():m_Handle(0) { }
        
        void  Init(unsigned int index);
        
        //查询
        unsigned int GetIndex (void) const {return m_index;}
        unsigned int GetMagic (void) const {return m_Magic;}
        unsigned int GetHandle(void) const {return m_Handle;}
        bool IsNull()   const {return !m_Handle;}
        
        operator unsigned int ()const {return m_Handle;}
    };
    
    
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
    
    template <typename TAG>
    inline bool operator != (Handle<TAG> l, Handle<TAG> r)
    {  return l.GetHandle() != r.GetHandle(); }
    
    
    template <typename TAG>
    inline bool operator == (Handle<TAG> l, Handle<TAG> r)
    { return l.GetHandle() == r.GetHandle(); }
    
    
    
    
    
    
    
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
        HandleMgr() {}
        ~HandleMgr() {}
        
        
        //句柄方法
        //分配
        DATA* Acquire( HANDLE& handle);
        //释放
        void Release( HANDLE handle);
        
        
        
        //解引用
        inline DATA*  Dereference( HANDLE handle);
        
        
        inline const DATA* Dereference( HANDLE handle) const ;
        
        //其他查询
        unsigned int GetUsedHandleCount(void) const
        { return m_MagicNumbers.size() - m_FreeSolts.size(); }
        
        bool HasUsedHandles(void) const
        { return !!GetUsedHandleCount(); }
    };
    
    template <typename DATA, typename HANDLE>
    DATA* HandleMgr <DATA, HANDLE>::Acquire( HANDLE& handle)
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


#endif /* Handle_hpp */
