#include "common.h"
#include "d3d.h"
#include "addresses.h"
#include "cheat-manager.h"

#include "MinHook.h"


namespace ResidentEvil4
{
    unsigned long** D3D::m_d3d9VTable;

    using EndScene = HRESULT (WINAPI*) (IDirect3DDevice9*);
    EndScene D3D::m_originalEndSceneFn;

    
    void D3D::drawLine (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &from,
            const D3DXVECTOR2 &to,
            const DWORD color
        )
    {
        IDirect3DVertexBuffer9* vertexBuffer;
        device->CreateVertexBuffer (
            2 * sizeof (Vertex),
            0,
            DEFAULT_FVF,
            D3DPOOL_MANAGED,
            &vertexBuffer,
            nullptr
        );

        const Vertex vertices[] = {
            { from.x, from.y, 0.0f, 1.0f, color },
            { to.x, to.y, 0.0f, 1.0f, color }
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
        device->DrawPrimitive (D3DPT_LINESTRIP, 0, 1);

        vertexBuffer->Release ();
    }
    
    void D3D::drawRectangle (
            IDirect3DDevice9* const device,
            const D3DXVECTOR2 &pos,
            const float w,
            const float h,
            const DWORD color
        )
    {
        const float x = pos.x, y = pos.y;
        const D3DXVECTOR2 corners[] = {
            /* Top left. */
            { x, y },
            /* Top right. */
            { x + w, y },
            /* Bottom right. */
            { x + w, y - h },
            /* Bottom left. */
            { x, y - h }
        };
        
        drawLine (device, corners[0], corners[1], color);
        drawLine (device, corners[1], corners[2], color);
        drawLine (device, corners[2], corners[3], color);
        drawLine (device, corners[3], corners[0], color);
    }
    
    
    HRESULT WINAPI D3D::EndSceneHook (IDirect3DDevice9* device)
    {
        if ( CheatManager::getInstance().isCheatToggled (Player::TogglingCheats::ESP) )
        {
            drawRectangle ( device, { 250.0f, 250.0f }, 100.0f, 100.0f, D3DCOLOR_XRGB (0xFF, 0x0, 0x0) );
        }
        
        return m_originalEndSceneFn (device);
    }
    

    bool D3D::hook ()
    {
        IDirect3DDevice9* d3d9Device;
        do
        {
            d3d9Device = *(IDirect3DDevice9**)g_d3d9DeviceAddress;
            Sleep (100);
        } while (d3d9Device == nullptr);

        m_d3d9VTable = *(unsigned long***)d3d9Device;

        if (MH_Initialize () != MH_OK)
        {
            return false;
        }        


        bool hooksResult = false;

        /* Hook EndScene. */
        hooksResult = []() -> bool
                      {
                          m_originalEndSceneFn = (EndScene)m_d3d9VTable[42];
                          if (MH_CreateHook (m_d3d9VTable[42], &EndSceneHook,
                              (void**)&m_originalEndSceneFn) != MH_OK)
                          {
                              return false;
                          }
                          if (MH_EnableHook ( m_d3d9VTable[42] ) != MH_OK)
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
        if (MH_RemoveHook ( m_d3d9VTable[42] ) != MH_OK)
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
