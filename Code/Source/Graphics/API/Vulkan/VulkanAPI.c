#include "Graphics/API/GFX.h"

#include "Graphics/API/Vulkan/VulkanAPI.h"
#include "Graphics/API/Vulkan/VulkanStructs.h"

#include <assert.h>

#if defined(GFX_API_VULKAN)

void GFXSetParameters(GFXParameterHandle a_Parameters)
{	
	GFX_UNUSED(a_Parameters);
	VulkanParameters *parameters = a_Parameters;
	GFX_UNUSED(parameters);
}

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor, GFXParameterHandle a_Parameters)
{
	GFX_UNUSED(a_Allocator);
	GFX_UNUSED(a_Descriptor);

	VulkanAPI *api = ALLOCATE(VulkanAPI);
	assert(0 != api);
	VulkanParameters *vulkanParameters = a_Parameters;

	VkApplicationInfo applicationInfo = { 0 };
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = vulkanParameters->m_ApplicationName;
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = vulkanParameters->m_EngineName;
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceCreateInfo = { 0 };
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledExtensionCount = vulkanParameters->m_NumEnabledExtensions;
	instanceCreateInfo.ppEnabledExtensionNames = vulkanParameters->m_EnabledExtensions;
	instanceCreateInfo.enabledLayerCount = vulkanParameters->m_NumEnabledLayers;
	instanceCreateInfo.ppEnabledLayerNames = vulkanParameters->m_EnabledLayers;

	VkResult result = vkCreateInstance(&instanceCreateInfo, 0, &api->m_Instance);
	assert(VK_SUCCESS == result);

	uint32_t physicalDevicesCount = 0;
	result = vkEnumeratePhysicalDevices(api->m_Instance, &physicalDevicesCount, 0);
	assert(VK_SUCCESS == result);

	VkPhysicalDevice *physicalDevices = malloc(sizeof(VkPhysicalDevice) * physicalDevicesCount);
	result = vkEnumeratePhysicalDevices(api->m_Instance, &physicalDevicesCount, physicalDevices);
	assert(VK_SUCCESS == result);

	*a_API = api;
}

void GFXTerminate(GFXAPI a_API)
{
	assert(0 != a_API);
	VulkanAPI *api = a_API;

	vkDestroyInstance(api->m_Instance, 0);
	api->m_Instance = VK_NULL_HANDLE;
}

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXClearRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget, GFXColor a_ClearColor)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_RenderTarget);
	GFX_UNUSED(a_ClearColor);
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}


void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
	GFX_UNUSED(a_VariableName);
	GFX_UNUSED(a_Data);
}

void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
	GFX_UNUSED(a_NumVertices);
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXUpdateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

#endif
