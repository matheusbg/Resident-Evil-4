#ifndef D3D_H
#define D3D_H

#include "d3dx9.h"


namespace ResidentEvil4
{
    constexpr DWORD DEFAULT_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
    

    class D3D
    {
    public:
        static bool hook ();
        static bool unhook ();

    protected:
    private:
        typedef struct
        {
            float x, y, z, rhw;
            DWORD color;
        } Vertex;

        
        static unsigned long** m_d3d9VTable;

        /* Prototype & Original address of hooked function(s). */
        using EndScene = HRESULT (WINAPI*) (IDirect3DDevice9*);
        static EndScene m_originalEndSceneFn;

        
        static void drawLine (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &from,
            const D3DXVECTOR2 &to,
            const DWORD color
        );
        
        static void drawRectangle (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &pos,
            const float w,
            const float h,
            const DWORD color
        );


        /* Hooks. */
        static HRESULT WINAPI EndSceneHook (IDirect3DDevice9* device);

    };

}

#endif