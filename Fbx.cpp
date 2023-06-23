#include "Fbx.h"

Fbx::Fbx():pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr),vertexCount_(0),polygonCount_(0)
{
}

HRESULT Fbx::Load(std::string fileName)
{
    return E_NOTIMPL;
}

void Fbx::Draw(Transform& transform)
{
}

void Fbx::Release()
{
}
