#pragma once
#include <new>
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
		static size_t Refill(size_t bytes);
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

	static size_t Round_up(size_t bytes)
	{
		return (bytes + E_Align::ALIGN - 1) & (~E_Align::ALIGN - 1);
	};
	static size_t Find_Index(size_t byte)
	{
		return Round_up(byte) / 8 - 1;
	};
	static void* allocate(size_t bytes)
	{
		if (bytes > E_MAX_BYTE::MAX_BYTE)
		{
			return std::malloc(bytes);
		}
		Free_list* current_node;

	}
}