#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

static constexpr unsigned int g_WindowWidth = 800u;
static constexpr unsigned int g_WindowHeight = 600u;

int main(const int argc, char* argv)
{
	// Initialise SDL2.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "SDL failed to initialise.\n";

		return EXIT_FAILURE;
	}

	// Create a window.
	SDL_Window* window = SDL_CreateWindow(
		"Vulkan Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(g_WindowWidth),
		static_cast<int>(g_WindowHeight),
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_VULKAN
	);

	if (window == nullptr)
	{
		std::cerr << "Could not create a window.\n";
	}

	// Create a Vulkan instance.
	VkInstance vulkanInstance = VK_NULL_HANDLE;

	const VkApplicationInfo applicationInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "Vulkan Application",
		.applicationVersion = VK_MAKE_VERSION(0, 0, 1),
		.pEngineName = "No Engine",
		.pEngineVersion = VK_MAKE_VERSION(0, 0, 1),
		.apiVersion = VK_API_VERSION_1_0,
	};

	const VkInstanceCreateInfo instanceCreateInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = 0u,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0u,
		.ppEnabledExtensionNames = nullptr,
	};

	if (vkCreateInstance(&instanceCreateInfo, nullptr, &vulkanInstance) != VK_SUCCESS)
	{
		std::cerr << "Couold not create a Vulkan instance.\n";
	}

	// Cleanup.
	vkDestroyInstance(vulkanInstance, nullptr);

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();

	return EXIT_SUCCESS;
}