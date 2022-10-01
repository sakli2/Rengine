#pragma once 



#define BASE_RESOURCE_HELPER_2(ResourceName, counter) class ResourceName

#define BASE_RESOURCE_HELPER_1(ResourceName, counter) BASE_RESOURCE_HELPER_2(ResourceName, counter)
#define BASE_RESOURCE(ResourceName) BASE_RESOURCE_HELPER_1(ResourceName, __COUNTER__) 


