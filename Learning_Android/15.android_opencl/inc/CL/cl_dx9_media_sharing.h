/*******************************************************************************
 * Copyright (c) 2008-2023 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef OPENCL_CL_DX9_MEDIA_SHARING_H_
#define OPENCL_CL_DX9_MEDIA_SHARING_H_

/*
** This header is generated from the Khronos OpenCL XML API Registry.
*/

#if defined(_WIN32)
#if defined(_MSC_VER)
#if _MSC_VER >= 1500
#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 5105)
#endif
#endif
#include <d3d9.h>
#if defined(_MSC_VER)
#if _MSC_VER >= 1500
#pragma warning(pop)
#endif
#endif
#endif

#include <CL/cl.h>

/* CL_NO_PROTOTYPES implies CL_NO_EXTENSION_PROTOTYPES: */
#if defined(CL_NO_PROTOTYPES) && !defined(CL_NO_EXTENSION_PROTOTYPES)
#define CL_NO_EXTENSION_PROTOTYPES
#endif

/* CL_NO_EXTENSION_PROTOTYPES implies
   CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES and
   CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES: */
#if defined(CL_NO_EXTENSION_PROTOTYPES) && !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)
#define CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES
#endif
#if defined(CL_NO_EXTENSION_PROTOTYPES) && !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES)
#define CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************
 * cl_khr_dx9_media_sharing
 ***************************************************************/
#define cl_khr_dx9_media_sharing 1
#define CL_KHR_DX9_MEDIA_SHARING_EXTENSION_NAME \
    "cl_khr_dx9_media_sharing"

#define CL_KHR_DX9_MEDIA_SHARING_EXTENSION_VERSION CL_MAKE_VERSION(1, 0, 0)

typedef cl_uint cl_dx9_media_adapter_type_khr;
typedef cl_uint cl_dx9_media_adapter_set_khr;

#if defined(_WIN32)
typedef struct _cl_dx9_surface_info_khr {
    IDirect3DSurface9* resource;
    HANDLE shared_handle;
} cl_dx9_surface_info_khr;

#endif /* defined(_WIN32) */

/* Error codes */
#define CL_INVALID_DX9_MEDIA_ADAPTER_KHR -1010
#define CL_INVALID_DX9_MEDIA_SURFACE_KHR -1011
#define CL_DX9_MEDIA_SURFACE_ALREADY_ACQUIRED_KHR -1012
#define CL_DX9_MEDIA_SURFACE_NOT_ACQUIRED_KHR -1013

/* cl_media_adapter_type_khr */
#define CL_ADAPTER_D3D9_KHR 0x2020
#define CL_ADAPTER_D3D9EX_KHR 0x2021
#define CL_ADAPTER_DXVA_KHR 0x2022

/* cl_media_adapter_set_khr */
#define CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR 0x2023
#define CL_ALL_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR 0x2024

/* cl_context_info */
#define CL_CONTEXT_ADAPTER_D3D9_KHR 0x2025
#define CL_CONTEXT_ADAPTER_D3D9EX_KHR 0x2026
#define CL_CONTEXT_ADAPTER_DXVA_KHR 0x2027

/* cl_mem_info */
#define CL_MEM_DX9_MEDIA_ADAPTER_TYPE_KHR 0x2028
#define CL_MEM_DX9_MEDIA_SURFACE_INFO_KHR 0x2029

/* cl_image_info */
#define CL_IMAGE_DX9_MEDIA_PLANE_KHR 0x202A

/* cl_command_type */
#define CL_COMMAND_ACQUIRE_DX9_MEDIA_SURFACES_KHR 0x202B
#define CL_COMMAND_RELEASE_DX9_MEDIA_SURFACES_KHR 0x202C

typedef cl_int CL_API_CALL
clGetDeviceIDsFromDX9MediaAdapterKHR_t(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapter_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices);

typedef clGetDeviceIDsFromDX9MediaAdapterKHR_t*
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn CL_API_SUFFIX__VERSION_1_2;

typedef cl_mem CL_API_CALL
clCreateFromDX9MediaSurfaceKHR_t(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret);

typedef clCreateFromDX9MediaSurfaceKHR_t*
    clCreateFromDX9MediaSurfaceKHR_fn CL_API_SUFFIX__VERSION_1_2;

typedef cl_int CL_API_CALL
clEnqueueAcquireDX9MediaSurfacesKHR_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueAcquireDX9MediaSurfacesKHR_t*
    clEnqueueAcquireDX9MediaSurfacesKHR_fn CL_API_SUFFIX__VERSION_1_2;

typedef cl_int CL_API_CALL
clEnqueueReleaseDX9MediaSurfacesKHR_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueReleaseDX9MediaSurfacesKHR_t*
    clEnqueueReleaseDX9MediaSurfacesKHR_fn CL_API_SUFFIX__VERSION_1_2;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDsFromDX9MediaAdapterKHR(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapter_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromDX9MediaSurfaceKHR(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueAcquireDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReleaseDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

/***************************************************************
 * cl_intel_dx9_media_sharing
 ***************************************************************/
#define cl_intel_dx9_media_sharing 1
#define CL_INTEL_DX9_MEDIA_SHARING_EXTENSION_NAME \
    "cl_intel_dx9_media_sharing"

#define CL_INTEL_DX9_MEDIA_SHARING_EXTENSION_VERSION CL_MAKE_VERSION(0, 0, 0)

typedef cl_uint cl_dx9_device_source_intel;
typedef cl_uint cl_dx9_device_set_intel;

/* Error codes */
#define CL_INVALID_DX9_DEVICE_INTEL -1010
#define CL_INVALID_DX9_RESOURCE_INTEL -1011
#define CL_DX9_RESOURCE_ALREADY_ACQUIRED_INTEL -1012
#define CL_DX9_RESOURCE_NOT_ACQUIRED_INTEL -1013

/* cl_dx9_device_source_intel */
#define CL_D3D9_DEVICE_INTEL 0x4022
#define CL_D3D9EX_DEVICE_INTEL 0x4070
#define CL_DXVA_DEVICE_INTEL 0x4071

/* cl_dx9_device_set_intel */
#define CL_PREFERRED_DEVICES_FOR_DX9_INTEL 0x4024
#define CL_ALL_DEVICES_FOR_DX9_INTEL 0x4025

/* cl_context_info */
#define CL_CONTEXT_D3D9_DEVICE_INTEL 0x4026
#define CL_CONTEXT_D3D9EX_DEVICE_INTEL 0x4072
#define CL_CONTEXT_DXVA_DEVICE_INTEL 0x4073

/* cl_mem_info */
#define CL_MEM_DX9_RESOURCE_INTEL 0x4027
#define CL_MEM_DX9_SHARED_HANDLE_INTEL 0x4074

/* cl_image_info */
#define CL_IMAGE_DX9_PLANE_INTEL 0x4075

/* cl_command_type */
#define CL_COMMAND_ACQUIRE_DX9_OBJECTS_INTEL 0x402A
#define CL_COMMAND_RELEASE_DX9_OBJECTS_INTEL 0x402B

typedef cl_int CL_API_CALL
clGetDeviceIDsFromDX9INTEL_t(
    cl_platform_id platform,
    cl_dx9_device_source_intel dx9_device_source,
    void* dx9_object,
    cl_dx9_device_set_intel dx9_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices);

typedef clGetDeviceIDsFromDX9INTEL_t*
    clGetDeviceIDsFromDX9INTEL_fn CL_API_SUFFIX__VERSION_1_1;

typedef cl_mem CL_API_CALL
clCreateFromDX9MediaSurfaceINTEL_t(
    cl_context context,
    cl_mem_flags flags,
    IDirect3DSurface9* resource,
    HANDLE sharedHandle,
    UINT plane,
    cl_int* errcode_ret);

typedef clCreateFromDX9MediaSurfaceINTEL_t*
    clCreateFromDX9MediaSurfaceINTEL_fn CL_API_SUFFIX__VERSION_1_1;

typedef cl_int CL_API_CALL
clEnqueueAcquireDX9ObjectsINTEL_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueAcquireDX9ObjectsINTEL_t*
    clEnqueueAcquireDX9ObjectsINTEL_fn CL_API_SUFFIX__VERSION_1_1;

typedef cl_int CL_API_CALL
clEnqueueReleaseDX9ObjectsINTEL_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueReleaseDX9ObjectsINTEL_t*
    clEnqueueReleaseDX9ObjectsINTEL_fn CL_API_SUFFIX__VERSION_1_1;

#if !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDsFromDX9INTEL(
    cl_platform_id platform,
    cl_dx9_device_source_intel dx9_device_source,
    void* dx9_object,
    cl_dx9_device_set_intel dx9_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_1;

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromDX9MediaSurfaceINTEL(
    cl_context context,
    cl_mem_flags flags,
    IDirect3DSurface9* resource,
    HANDLE sharedHandle,
    UINT plane,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueAcquireDX9ObjectsINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_1;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReleaseDX9ObjectsINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_1;

#endif /* !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

/***************************************************************
 * cl_intel_sharing_format_query_dx9
 ***************************************************************/
#define cl_intel_sharing_format_query_dx9 1
#define CL_INTEL_SHARING_FORMAT_QUERY_DX9_EXTENSION_NAME \
    "cl_intel_sharing_format_query_dx9"

#define CL_INTEL_SHARING_FORMAT_QUERY_DX9_EXTENSION_VERSION CL_MAKE_VERSION(0, 0, 0)

/* when cl_khr_dx9_media_sharing or cl_intel_dx9_media_sharing is supported */

typedef cl_int CL_API_CALL
clGetSupportedDX9MediaSurfaceFormatsINTEL_t(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint plane,
    cl_uint num_entries,
    D3DFORMAT* dx9_formats,
    cl_uint* num_surface_formats);

typedef clGetSupportedDX9MediaSurfaceFormatsINTEL_t*
    clGetSupportedDX9MediaSurfaceFormatsINTEL_fn;

#if !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_int CL_API_CALL
clGetSupportedDX9MediaSurfaceFormatsINTEL(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint plane,
    cl_uint num_entries,
    D3DFORMAT* dx9_formats,
    cl_uint* num_surface_formats);

#endif /* !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

#ifdef __cplusplus
}
#endif

#endif /* OPENCL_CL_DX9_MEDIA_SHARING_H_ */
