#ifndef PIPE_MGR_DRV_H
#define PIPE_MGR_DRV_H
//-----------------------------------------------------------------------------
#define PIPE_MGR_DRV_PIPE_MASK_CAM_IO       ((MUINT32)1 << 0)
#define PIPE_MGR_DRV_PIPE_MASK_POST_PROC    ((MUINT32)1 << 1)
#define PIPE_MGR_DRV_PIPE_MASK_CDP_CAM      ((MUINT32)1 << 2)
#define PIPE_MGR_DRV_PIPE_MASK_CDP_CONCUR   ((MUINT32)1 << 3)
#define PIPE_MGR_DRV_PIPE_MASK_CDP_LINK     ((MUINT32)1 << 4)
//-----------------------------------------------------------------------------
typedef struct
{
    MUINT32 PipeMask;
    MUINT32 Timeout; //ms
}PIPE_MGR_DRV_LOCK_STRUCT;

typedef struct
{
    MUINT32 PipeMask;
}PIPE_MGR_DRV_UNLOCK_STRUCT;
//-----------------------------------------------------------------------------
class PipeMgrDrv
{
    protected:
        virtual ~PipeMgrDrv() {};
    //
    public:
        static PipeMgrDrv* CreateInstance(void);
        virtual MVOID   DestroyInstance(void) = 0;
        virtual MBOOL   Init(void) = 0;
        virtual MBOOL   Uninit(void) = 0;
        virtual MBOOL   Lock(PIPE_MGR_DRV_LOCK_STRUCT* pLock) = 0;
        virtual MBOOL   Unlock(PIPE_MGR_DRV_UNLOCK_STRUCT* pUnlock) = 0;
        virtual MBOOL   Dump(void) = 0;
};
//-----------------------------------------------------------------------------
#endif

