/*
 * Copyright © 2017 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "anv_private.h"
#include "wsi_common.h"
#include "vk_format_info.h"
#include "vk_util.h"
#include "wsi_common_display.h"

VkResult
anv_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physical_device,
                                          uint32_t *property_count,
                                          VkDisplayPropertiesKHR *properties)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_display_get_physical_device_display_properties(
      physical_device,
      &pdevice->wsi_device,
      property_count,
      properties);
}

VkResult
anv_GetPhysicalDeviceDisplayPlanePropertiesKHR(
   VkPhysicalDevice physical_device,
   uint32_t *property_count,
   VkDisplayPlanePropertiesKHR *properties)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_display_get_physical_device_display_plane_properties(
      physical_device, &pdevice->wsi_device,
      property_count, properties);
}

VkResult
anv_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physical_device,
                                        uint32_t plane_index,
                                        uint32_t *display_count,
                                        VkDisplayKHR *displays)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_display_get_display_plane_supported_displays(physical_device,
                                                           &pdevice->wsi_device,
                                                           plane_index,
                                                           display_count,
                                                           displays);
}


VkResult
anv_GetDisplayModePropertiesKHR(VkPhysicalDevice physical_device,
                                VkDisplayKHR display,
                                uint32_t *property_count,
                                VkDisplayModePropertiesKHR *properties)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_display_get_display_mode_properties(physical_device,
                                                  &pdevice->wsi_device,
                                                  display,
                                                  property_count,
                                                  properties);
}

VkResult
anv_CreateDisplayModeKHR(VkPhysicalDevice physical_device,
                         VkDisplayKHR display,
                         const VkDisplayModeCreateInfoKHR *create_info,
                         const VkAllocationCallbacks *allocator,
                         VkDisplayModeKHR *mode)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_display_create_display_mode(physical_device,
                                          &pdevice->wsi_device,
                                          display,
                                          create_info,
                                          allocator,
                                          mode);
}

VkResult
anv_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physical_device,
                                   VkDisplayModeKHR mode_khr,
                                   uint32_t plane_index,
                                   VkDisplayPlaneCapabilitiesKHR *capabilities)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_get_display_plane_capabilities(physical_device,
                                             &pdevice->wsi_device,
                                             mode_khr,
                                             plane_index,
                                             capabilities);
}

VkResult
anv_CreateDisplayPlaneSurfaceKHR(
   VkInstance _instance,
   const VkDisplaySurfaceCreateInfoKHR *create_info,
   const VkAllocationCallbacks *allocator,
   VkSurfaceKHR *surface)
{
   ANV_FROM_HANDLE(anv_instance, instance, _instance);
   const VkAllocationCallbacks *alloc;

   if (allocator)
     alloc = allocator;
   else
     alloc = &instance->alloc;

   return wsi_create_display_surface(_instance, alloc, create_info, surface);
}

VkResult
anv_ReleaseDisplayEXT(VkPhysicalDevice physical_device,
                       VkDisplayKHR     display)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_release_display(physical_device,
                              &pdevice->wsi_device,
                              display);
}

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
VkResult
anv_AcquireXlibDisplayEXT(VkPhysicalDevice     physical_device,
                           Display              *dpy,
                           VkDisplayKHR         display)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_acquire_xlib_display(physical_device,
                                   &pdevice->wsi_device,
                                   dpy,
                                   display);
}

VkResult
anv_GetRandROutputDisplayEXT(VkPhysicalDevice  physical_device,
                              Display           *dpy,
                              RROutput          output,
                              VkDisplayKHR      *display)
{
   ANV_FROM_HANDLE(anv_physical_device, pdevice, physical_device);

   return wsi_get_randr_output_display(physical_device,
                                       &pdevice->wsi_device,
                                       dpy,
                                       output,
                                       display);
}
#endif /* VK_USE_PLATFORM_XLIB_XRANDR_EXT */