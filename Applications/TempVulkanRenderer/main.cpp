#include "Proto.h"

#include "Platform/Debug/AssertMessage.h"
#include "VulkanIncludes.h"

#include <iostream>
#include <string>
#include <vector>

USING_NAMESPACE(Platform)

namespace
{
	VkInstance g_Instance = VK_NULL_HANDLE;
	VkPhysicalDevice g_PhysicalDevice = VK_NULL_HANDLE;
}

void GetInstanceExtensionProperties(const char *a_LayerName, std::vector<VkExtensionProperties> &a_ExtensionProperties)
{
	uint32_t propertyCount = 0;
	VkResult result = vkEnumerateInstanceExtensionProperties(a_LayerName, &propertyCount, nullptr);
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate instance extension property count!");

	a_ExtensionProperties.resize(propertyCount);
	result = vkEnumerateInstanceExtensionProperties(a_LayerName, &propertyCount, a_ExtensionProperties.data());
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate instance extension properties!");
}

void GetInstanceLayerProperties()
{
	uint32_t propertyCount = 0;
	VkResult result = vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate instance layer property count!");

	std::vector<VkLayerProperties> layerProperties;
	layerProperties.resize(propertyCount);
	vkEnumerateInstanceLayerProperties(&propertyCount, layerProperties.data());
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate instance layer properties!");

	std::cout << std::endl << "Instanced layers" << std::endl;
	std::cout << "================" << std::endl;
	for (auto globalLayerProperty : layerProperties)
	{
		std::cout << std::endl << globalLayerProperty.description <<
			"\n\t|\n\t|---[Layer name]--> " <<
			globalLayerProperty.layerName << std::endl;
		
		std::vector<VkExtensionProperties> extensionProperties;
		GetInstanceExtensionProperties(globalLayerProperty.layerName, extensionProperties);

		for (auto extensionProperty : extensionProperties)
		{
			std::cout << "\t\t|\n\t\t|---[Layer extension]--> " << extensionProperty.extensionName << std::endl;
		}
	}
}

void CreateInstance(std::vector<const char*> &a_Layers, std::vector<const char*> &a_Extensions)
{
	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "TempVulkanRenderer";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "Proto";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_Extensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = a_Extensions.data();
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_Layers.size());
	instanceCreateInfo.ppEnabledLayerNames = a_Layers.data();

	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &g_Instance);
	AssertMessage(VK_SUCCESS == result, "Failed to create Vulkan instance!");
}

void DestroyInstance()
{
	vkDestroyInstance(g_Instance, nullptr);
	g_Instance = VK_NULL_HANDLE;
}

void EnumeratePhysicalDevices(VkInstance &a_Instance, std::vector<VkPhysicalDevice> &a_PhysicalDevices)
{
	uint32_t physicalDevicesCount = 0;
	VkResult result = vkEnumeratePhysicalDevices(a_Instance, &physicalDevicesCount, nullptr);
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate physical devices count!");

	a_PhysicalDevices.resize(physicalDevicesCount);
	result = vkEnumeratePhysicalDevices(a_Instance, &physicalDevicesCount, a_PhysicalDevices.data());
	AssertMessage(VK_SUCCESS == result, "Failed to enumerate physical devices!");
}

void InspectPhysicalDevice(VkPhysicalDevice a_PhysicalDevice)
{
	VkPhysicalDeviceProperties physicalDeviceProperties;
	vkGetPhysicalDeviceProperties(a_PhysicalDevice, &physicalDeviceProperties);

	VkPhysicalDeviceFeatures physicalDeviceFeatures;
	vkGetPhysicalDeviceFeatures(a_PhysicalDevice, &physicalDeviceFeatures);

	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(a_PhysicalDevice, &memoryProperties);
}

int GetQueueIndex(VkPhysicalDevice a_PhysicalDevice, uint32_t a_QueueFlag)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(a_PhysicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(a_PhysicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	int index = 0;
	for (const auto& queueFamilyProperty : queueFamilyProperties)
	{
		if (queueFamilyProperty.queueCount > 0 && queueFamilyProperty.queueFlags & a_QueueFlag)
		{
			return index;
		}
		index++;
	}
	return -1;
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	//GetInstanceLayerProperties();

	std::vector<const char*> instanceExtensionNames = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
	std::vector<const char*> layerNames = { "VK_LAYER_LUNARG_api_dump" };
	CreateInstance(layerNames, instanceExtensionNames);
	
	std::vector<VkPhysicalDevice> physicalDevices;	
	EnumeratePhysicalDevices(g_Instance, physicalDevices);
	AssertMessage(1 == physicalDevices.size(), "Found more than 1 physical Vulkan device!");
	InspectPhysicalDevice(physicalDevices[0]);

	const int graphicsQueueIndex = GetQueueIndex(physicalDevices[0], VK_QUEUE_GRAPHICS_BIT);
// 	const int computeQueueIndex = GetQueueIndex(physicalDevices[0], VK_QUEUE_COMPUTE_BIT);
// 	const int transferQueueIndex = GetQueueIndex(physicalDevices[0], VK_QUEUE_TRANSFER_BIT);
// 	const int sparseBindingQueueIndex = GetQueueIndex(physicalDevices[0], VK_QUEUE_SPARSE_BINDING_BIT);
// 	const int protectedQueueIndex = GetQueueIndex(physicalDevices[0], VK_QUEUE_PROTECTED_BIT);

	DestroyInstance();
	return 0;
}
