#ifndef VSS_IMG_TRANS_H
#define VSS_IMG_TRANS_H
//-----------------------------------------------------------------------------
class VssImgTrans
{
    protected:
        virtual ~VssImgTrans() {};
    //
    public:
        typedef struct
        {
            MUINT32             Width;
            MUINT32             Height;
            MUINT32             Stride;
        }IMG_SIZE_STRUCT;
        //
        typedef struct
        {
            MINT32              id; //ION FD
            MUINT32             Vir;
            MUINT32             Phy;
        }IMG_MEM_STRUCT;
        //
        typedef struct
        {
            MUINT32             X;
            MUINT32             Y;
            MUINT32             W;
            MUINT32             H;
        }IMG_CROP_STRUCT;
        //
        typedef struct
        {
            IMG_SIZE_STRUCT     Size;
            IMG_MEM_STRUCT      Mem;
            EImageFormat        Format;
            IMG_CROP_STRUCT     Crop;
        }IMAGE_IN_STRUCT;
        //
        typedef struct
        {
            MBOOL               Enable;
            IMG_SIZE_STRUCT     Size;
            IMG_MEM_STRUCT      Mem;
            EImageFormat        Format;
        }DISPO_OUT_STRUCT;
        //
        typedef struct
        {
            MBOOL               Enable;
            IMG_SIZE_STRUCT     Size;
            IMG_MEM_STRUCT      Mem;
            EImageFormat        Format;
            EImageRotation      Rotate;
            EImageFlip          Flip;
        }VIDO_OUT_STRUCT;
        //
        typedef struct
        {
            IMAGE_IN_STRUCT     ImageIn;
            DISPO_OUT_STRUCT    DispoOut;
            VIDO_OUT_STRUCT     VidoOut;
        }CONFIG_STRUCT;
        //
        static VssImgTrans* CreateInstance(void);
        virtual MVOID   DestroyInstance(void) = 0;
        virtual MBOOL   Init(CONFIG_STRUCT& Config, MUINT32& TpipeNum) = 0;
        virtual MBOOL   Uninit(void) = 0;
        virtual MBOOL   Start(MUINT32 TpipeIndex) = 0;
        virtual MBOOL   WaitDone(void) = 0;
};
//-----------------------------------------------------------------------------
#endif

