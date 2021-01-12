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
    public:
        static void*    allocate(size_t byte);
        static void     deallocate(void* p, size_t byte);
        static void*    reallocate(void* p, size_t old_size, size_t new_size);

	private:
		static size_t   Round_up(size_t bytes);
		static void*    Refill(size_t size);
		static size_t   Find_Index(size_t bytes);
		static char*    Chunk_alloc(size_t size, size_t& nobj);

    private:
        static char*        m_pStart;
        static char*        m_pEnd;
        static size_t       m_sTotal_heap_size;
        static Free_list*   m_free_list[E_LIST_NUM::LIST_NUM];
   

	};
	// initialize static data members
	char* alloc::m_pStart = nullptr;
	char* alloc::m_pEnd = nullptr;
    size_t alloc::m_sTotal_heap_size = 0;
    Free_list* alloc::m_free_list[E_LIST_NUM::LIST_NUM] = {
		nullptr, nullptr, nullptr, nullptr, nullptr, 
		nullptr, nullptr, nullptr, nullptr, nullptr, 
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};


    // round up bytes to a multiple of 8
	inline size_t alloc::Round_up(size_t bytes)
	{
		return (bytes + E_Align::ALIGN - 1) & (~(E_Align::ALIGN - 1));
	};

    // Find index in the free_list given a byte
    inline size_t alloc::Find_Index(size_t bytes)
	{
        return (bytes + E_Align::ALIGN - 1) / (E_Align::ALIGN) - 1;
	};

    // Allocate memory of size bytes
    // If bytes is greater than the maximum size of bytes, use std::allocate
    inline void* alloc::allocate(size_t byte)
	{
        Free_list* my_free_list;
        Free_list* result;
		if (byte > E_MAX_BYTE::MAX_BYTE)
		{
			return std::malloc(byte);
		}
        my_free_list = m_free_list[Find_Index(byte)];

        result = my_free_list;
        if (result == nullptr)
        {
            void* r = Refill(Round_up(byte));
            return r;
        }

        my_free_list = result->next;
        return (void*)result;
	}

    // free the memory pointed at p and have size of n bytes
    inline void alloc::deallocate(void* p, size_t byte)
    {
        if (E_MAX_BYTE::MAX_BYTE < byte)
        {
            std::free(p);
            return;
        }

        // attached the freed memory to the linkedlist under certain index
        Free_list* temp = reinterpret_cast<Free_list*>(p);
        Free_list* cur_node;
        cur_node = m_free_list[Find_Index(byte)];
        temp->next = cur_node;
        cur_node = temp;
    }

    inline void* alloc::reallocate(void* p, size_t old_byte, size_t new_byte)
    {
        alloc::deallocate(p, old_byte);
        p = alloc::allocate(new_byte);
        return p;
    }

    inline void* alloc::Refill(size_t size)
    {
        size_t num_block = E_NUM_BLOCK::NUM_BLOCK;
        char* start_addr = Chunk_alloc(size, num_block);
        

        if (1 == num_block)
        {
            return start_addr;
        }
        Free_list* cur_obj = m_free_list[Find_Index(size)];
        Free_list *next_obj, *result;
        // return the 1st available address.
        result = (Free_list*)start_addr;
        // mark the 2nd available address
        cur_obj = next_obj = (Free_list*)(start_addr + size);
        
        for (size_t i = 1; i++;)
        {
            // next_obj chops memory 
            next_obj = (Free_list*)((char*)next_obj + size);

            if (num_block - 1 == i)
            {
                cur_obj->next = nullptr;
                break;
            }
            else
            {
                // move the current pointer to the next memory
                cur_obj->next = next_obj;
            }
        }
        return result;
    }

    inline char* alloc::Chunk_alloc(size_t byte, size_t& nobj)
    {
        size_t total_byte = byte * nobj;
        size_t byte_left = m_pStart - m_pEnd;
        char* result = m_pStart;
        if (byte_left >= total_byte)
        {   
            m_pStart += total_byte;
            return result;
        }
        else if (byte_left >= byte)
        {
            // how many blocks can be allocated.
            nobj = byte_left / byte;
            total_byte = nobj * byte;
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
                // Search memory on the right nodes. if size is 80, then we search 88, 96...
                for (size_t i = byte; i <= E_MAX_BYTE::MAX_BYTE; i += E_Align::ALIGN)
                {
                    current_node = m_free_list[Find_Index(i)];
                    if (current_node != nullptr)
                    {
                        m_pStart = (char*)current_node;
                        m_pEnd = m_pStart+ i;
                        p = current_node;
                        current_node = current_node->next;
                        return (Chunk_alloc(byte, nobj));
                    }
                }
                printf("out of memory");
                m_pEnd = nullptr;
                throw std::bad_alloc();
            }
            m_sTotal_heap_size += byte_to_get;
            m_pEnd = m_pStart + byte_to_get;
            return (Chunk_alloc(byte, nobj));
        }

    }
}