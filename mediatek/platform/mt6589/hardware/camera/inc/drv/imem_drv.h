#ifndef _IMEM_DRV_H_
#define _IMEM_DRV_H_

/*=================================================================================
                                                            MEMORY TYPE DEFINITION
=================================================================================*/
#if defined(MTK_ION_SUPPORT)
    #define __ISP_USE_ION__
#else
    #define __ISP_USE_STD_M4U__
#endif
/*=================================================================================

=================================================================================*/


#if defined(__ISP_USE_PMEM__)
    #if defined(__ISP_USE_STD_M4U__) || defined(__ISP_USE_ION__)
        #error "MULTIPLE MEMORY TYPE DEFINED"
    #endif
#elif defined(__ISP_USE_STD_M4U__)
    #if defined(__ISP_USE_PMEM__) || defined(__ISP_USE_ION__)
        #error "MULTIPLE MEMORY TYPE DEFINED"
    #endif
#elif defined(__ISP_USE_ION__)
    #if defined(__ISP_USE_PMEM__) || defined(__ISP_USE_STD_M4U__)
        #error "MULTIPLE MEMORY TYPE DEFINED"
    #endif
#else
    #error "NO MEMORY TYPE DEFINED"
#endif
//
#define IMEM_MIN_ION_FD (0)
//
#if 0
typedef enum
{
    BUF_TYPE_PMEM     = 0,// by pmem alloc
    BUF_TYPE_STD_M4U,     // by stblib malloc
    BUF_TYPE_ION,         // by ION alloc
}EBUF_TYPE;
#endif
//
struct IMEM_BUF_INFO
{
    MUINT32     size;
    MINT32      memID;
    MUINT32     virtAddr;
    MUINT32     phyAddr;
    MINT32      bufSecu;
    MINT32      bufCohe;
	MINT32      useNoncache;
    //
    IMEM_BUF_INFO(
        MUINT32     _size = 0,
        MINT32      _memID = -1,
        MUINT32     _virtAddr = 0,
        MUINT32     _phyAddr = 0,
        MINT32      _bufSecu = 0,
        MINT32      _bufCohe = 0,
        MINT32      _useNoncache =0)
    : size(_size)
    , memID(_memID)
    , virtAddr(_virtAddr)
    , phyAddr(_phyAddr)
    , bufSecu(_bufSecu)
    , bufCohe(_bufCohe)
    , useNoncache(_useNoncache)
    {}
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class IMemDrv
{
    protected:
        IMemDrv(){};
        virtual ~IMemDrv() {};
    //
    public:
        static IMemDrv*  createInstance();
        virtual void    destroyInstance(void) = 0;
        virtual MBOOL   init(void) = 0;
        virtual MBOOL   uninit(void) = 0;
        virtual MBOOL   reset(void) = 0;
        virtual MINT32  allocVirtBuf(IMEM_BUF_INFO* pInfo) = 0;
        virtual MINT32  freeVirtBuf(IMEM_BUF_INFO* pInfo) = 0;
        virtual MINT32  mapPhyAddr(IMEM_BUF_INFO* pInfo) = 0;
        virtual MINT32  unmapPhyAddr(IMEM_BUF_INFO* pInfo) = 0;
        virtual MINT32  cacheFlushAll(void) = 0;
};
//----------------------------------------------------------------------------
#endif  // _IMEM_DRV_H_


