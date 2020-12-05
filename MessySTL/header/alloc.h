#pragma once
#include <new>
#include <cstdlib>
#include <cstdio>
namespace MessySTL
{
	enum E_Align
	{
		ALIGN = 8
	};

	enum E_MAX_BYTE
	{
		MAX_BYTE = 128
	};

	enum E_LIST_NUM
	{
		LIST_NUM = E_MAX_BYTE::MAX_BYTE / E_Align::ALIGN
	};

    enum E_NUM_BLOCK
    {
        NUM_BLOCK = 20
    };

	union Free_list
	{
		Free_list* next;
		char data[1]; // first address of the current list node
	};

	class alloc
	{
	private:

		static char* m_pStart;
		static char* m_pEnd;
		static size_t m_sTotal_heap_size;
		static Free_list* m_free_list[E_LIST_NUM::LIST_NUM];

		static size_t Round_up(size_t bytes);
		static void* Refill(size_t bytes);
		static size_t Find_Index(size_t byte);
		static void*  allocate(size_t bytes);
		static char*  Chunk_alloc(size_t bytes, size_t& nobj);

	};
	// initialize static data members
	char* alloc::m_pStart = nullptr;
	char* alloc::m_pEnd = nullptr;
	size_t alloc::m_sTotal_heap_size = 0;
	Free_list* alloc::m_free_list[E_LIST_NUM::LIST_NUM] = {
		nullptr, nullptr, nullptr, nullptr, nullptr, 
		nullptr, nullptr, nullptr, nullptr, nullptr, 
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	inline size_t alloc::Round_up(size_t bytes)
	{
		return (bytes + E_Align::ALIGN - 1) & (~E_Align::ALIGN - 1);
	};
    inline size_t alloc::Find_Index(size_t byte)
	{
		return Round_up(byte) / 8 - 1;
	};
    inline void* alloc::allocate(size_t bytes)
	{
        
		if (bytes > E_MAX_BYTE::MAX_BYTE)
		{
			return std::malloc(bytes);
		}
        Free_list* current_node = m_free_list[Find_Index(bytes)];

        Free_list* result = current_node;
        if (current_node == nullptr)
        {
            void* r = Refill(Round_up(bytes));
            return r;
        }

        current_node = result->next;
        return (void*)result;
	}

    inline void* alloc::Refill(size_t bytes)
    {
        size_t num_block = E_NUM_BLOCK::NUM_BLOCK;
        char* result = Chunk_alloc(bytes, num_block);
    }

    inline char*  alloc::Chunk_alloc(size_t bytes, size_t& nobj)
    {
        size_t total_byte = bytes * nobj;
        size_t byte_left = m_pStart - m_pEnd;
        char* result = m_pStart;
        if (byte_left >= total_byte)
        {   
            m_pStart += total_byte;
            return result;
        }
        else if (byte_left >= bytes)
        {
            // how many blocks can be allocated.
            nobj = byte_left / bytes;
            total_byte = nobj * bytes;
            m_pStart += total_byte;
            return result;
        }
        else
        {
            size_t byte_to_get = 2 * total_byte + Round_up(m_sTotal_heap_size >> 4);
            
            if (byte_left > 0)
            {
                Free_list* target_node = m_free_list[Find_Index(byte_left)];
                ((Free_list*)m_pStart)->next = target_node;
                target_node = (Free_list*)m_pStart;
            }

            m_pStart = (char*)std::malloc(byte_to_get);
            if (m_pStart == nullptr)
            {
                // not enough space in the heap
                
                Free_list* current_node, *p;
                // Search memory on the right nodes. if bytes is 80, then we search 88, 96...
                for (size_t i = bytes; i <= E_MAX_BYTE::MAX_BYTE; i + E_Align::ALIGN)
                {
                    current_node = m_free_list[Find_Index(i)];
                    if (current_node != nullptr)
                    {
                        m_pStart = (char*)current_node;
                        m_pEnd = m_pStart+ i;
                        p = current_node;
                        current_node = current_node->next;
                        return (Chunk_alloc(bytes, nobj));
                    }
                }
                printf("out of memory");
                m_pEnd = nullptr;
                throw std::bad_alloc();
            }
            m_sTotal_heap_size += byte_to_get;
            m_pEnd = m_pStart + byte_to_get;
            return (Chunk_alloc(bytes, nobj));
        }

    }
}