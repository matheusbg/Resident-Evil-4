#include "common.h"
#include "d3d.h"
#include "addresses.h"
#include "cheat-manager.h"

#include "d3dx9.h"
#include "MinHook.h"


namespace ResidentEvil4
{
#define DEFAULT_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
    
    unsigned long** g_d3d9VTable;
    

    using EndScene = HRESULT (WINAPI*) (IDirect3DDevice9*);
    HRESULT WINAPI EndSceneHook (IDirect3DDevice9*);
    EndScene g_originalEndSceneFn;

    
    typedef struct
    {
        float x, y, z, rhw;
        DWORD color;
    } Vertex;

    
    static void drawRectangle (
            IDirect3DDevice9* const device,
            const float x,
            const float y,
            const float w,
            const float h,
            const unsigned char r,
            const unsigned char g,
            const unsigned char b
        )
    {
        IDirect3DVertexBuffer9* vertexBuffer;
        device->CreateVertexBuffer (
            5 * sizeof (Vertex),
            0,
            DEFAULT_FVF,
            D3DPOOL_MANAGED,
            &vertexBuffer,
            nullptr
        );

        const Vertex vertices[] = {
            { x, y, 0.0f, 1.0f, D3DCOLOR_XRGB (r, g, b) },
            { x + w, y, 0.0f, 1.0f, D3DCOLOR_XRGB (r, g, b) },
            { x + w, y - h, 0.0f, 1.0f, D3DCOLOR_XRGB (r, g, b) },
            { x, y - h, 0.0f, 1.0f, D3DCOLOR_XRGB (r, g, b) },
            { x, y, 0.0f, 1.0f, D3DCOLOR_XRGB (r, g, b) }
        };

        void* data;
        vertexBuffer->Lock (0, 0, &data, 0);
        {
            memcpy ( data, vertices, sizeof (vertices) );
        }
        vertexBuffer->Unlock ();

        device->SetTexture (0, nullptr);
        device->SetPixelShader (nullptr);

        device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);

        device->SetFVF (DEFAULT_FVF);
        device->SetStreamSource ( 0, vertexBuffer, 0, sizeof (Vertex) );
        device->DrawPrimitive (D3DPT_LINESTRIP, 0, 4);
    }
    
    
    static HRESULT WINAPI EndSceneHook (IDirect3DDevice9* device)
    {
        if ( CheatManager::getInstance().isCheatToggled (Player::TogglingCheats::ESP) )
        {
            drawRectangle (device, 250, 250, 100, 100, 0xFF, 0x0, 0x0);
        }
        
        return g_originalEndSceneFn (device);
    }
    

    bool D3D::hook ()
    {
        IDirect3DDevice9* d3d9Device;
        do
        {
            d3d9Device = *(IDirect3DDevice9**)g_d3d9DeviceAddress;
            Sleep (100);
        } while (d3d9Device == nullptr);

        g_d3d9VTable = *(unsigned long***)d3d9Device;

        if (MH_Initialize () != MH_OK)
        {
            return false;
        }        


        bool hooksResult = false;

        /* Hook EndScene. */
        hooksResult = []() -> bool
                      {
                          g_originalEndSceneFn = (EndScene)g_d3d9VTable[42];
                          if (MH_CreateHook (g_d3d9VTable[42], &EndSceneHook,
                              (void**)&g_originalEndSceneFn) != MH_OK)
                          {
                              return false;
                          }
                          if (MH_EnableHook ( g_d3d9VTable[42] ) != MH_OK)
                          {
                              return false;
                          }

                          return true;
                      }();

        return hooksResult;
    }

    bool D3D::unhook ()
    {
        /* Unhook EndScene. */
        if (MH_RemoveHook ( g_d3d9VTable[42] ) != MH_OK)
        {
            return false;
        }

        if (MH_Uninitialize () != MH_OK)
        {
            return false;
        }

        return true;
    }

}
