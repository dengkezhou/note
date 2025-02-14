#include "memalloc.h"
#include <assert.h>
#include <stdint.h>

typedef uint16_t offset_t;
#define PTR_OFFSET_SZ sizeof(offset_t)

#ifndef align_up
#define align_up(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))
#endif

void *aligned_malloc(size_t align, size_t size)
{
    void * ptr = NULL;
    
    // We want it to be a power of two since
    // align_up operates on powers of two
    assert((align & (align - 1)) == 0);

    if(align && size)
    {
        /*
         * We know we have to fit an offset value
         * We also allocate extra bytes to ensure we 
         * can meet the alignment
         */
        uint32_t hdr_size = PTR_OFFSET_SZ + (align - 1);
        void * p = malloc(size + hdr_size);

        if (p)
        {
            /*
             * Add the offset size to malloc's pointer 
             * (we will always store that)
             * Then align the resulting value to the 
             * target alignment
             */
            ptr = (void *)align_up(((uintptr_t)p + PTR_OFFSET_SZ), align);

            // Calculate the offset and store it 
            // behind our aligned pointer
            *((offset_t *)ptr - 1) = 
                (offset_t)((uintptr_t)ptr - (uintptr_t)p);

        } // else NULL, could not malloc
    } //else NULL, invalid arguments

    return ptr;
}

void aligned_free(void *ptr)
{
    assert(ptr);

    /*
    * Walk backwards from the passed-in pointer 
    * to get the pointer offset. We convert to an offset_t 
    * pointer and rely on pointer math to get the data
    */
    offset_t offset = *((offset_t *)ptr - 1);

    /*
    * Once we have the offset, we can get our 
    * original pointer and call free
    */
    void * p = (void *)((uint8_t *)ptr - offset);
    free(p);
}

// void *memalign (size_t __alignment, size_t __size)
// {
//     return malloc(__size);
// }
