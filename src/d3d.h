#ifndef D3D_H
#define D3D_H

#include "utils/singleton.h"
#include "d3dx9.h"


namespace ResidentEvil4
{
    /* Hooks. */
    ////////////////////////////////////////////////////////////////////////

    HRESULT WINAPI endSceneHook (IDirect3DDevice9* device);

    
    class D3D : public Singleton<D3D>
    {
        friend class Singleton<D3D>;
    
    public:
        bool hook ();
        bool unhook ();

    protected:
    private:
        const DWORD DEFAULT_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
        
        typedef struct
        {
            float x, y, z, rhw;
            DWORD color;
        } Vertex;

        
        unsigned long** m_d3d9VTable;

        /* Prototype & Original address of hooked function(s). */
        ////////////////////////////////////////////////////////////////////////

        using EndScene = HRESULT (WINAPI*) (IDirect3DDevice9*);
        EndScene m_fnOriginalEndScene;

        
        D3D ();
        ~D3D ();
        
        void drawLine (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &from,
            const D3DXVECTOR2 &to,
            const DWORD color
        );
        
        void drawRectangle (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &origin,
            const FLOAT w,
            const FLOAT h,
            const DWORD color
        );


        /* Hooks. */
        ////////////////////////////////////////////////////////////////////////

        friend HRESULT WINAPI endSceneHook (IDirect3DDevice9* device);

    };

}

#endif