#ifndef __AOPENCL_CL_H
#define __AOPENCL_CL_H

#ifdef __APPLE__
#include <OpenCL/cl_platform.h>
#else
#include <CL/cl_platform.h>
#endif	

#ifdef __cplusplus
extern "C" {
#endif

#define IAH() 
//#define IAH() printf("File:%s, Line:%d\n",__FILE__, __LINE__);

void initFns();

/* Platform API */
#define clGetPlatformIDs aclGetPlatformIDs
 cl_int 
(*aclGetPlatformIDs)(cl_uint          /* num_entries */,
                 cl_platform_id * /* platforms */,
                 cl_uint *        /* num_platforms */);

#define clGetPlatformInfo aclGetPlatformInfo
 cl_int  
(*aclGetPlatformInfo)(cl_platform_id   /* platform */, 
                  cl_platform_info /* param_name */,
                  size_t           /* param_value_size */, 
                  void *           /* param_value */,
                  size_t *         /* param_value_size_ret */);

/* Device APIs */
#define clGetDeviceIDs aclGetDeviceIDs
 cl_int 
(*aclGetDeviceIDs)(cl_platform_id   /* platform */,
               cl_device_type   /* device_type */, 
               cl_uint          /* num_entries */, 
               cl_device_id *   /* devices */, 
               cl_uint *        /* num_devices */);

#define clGetDeviceInfo aclGetDeviceInfo
 cl_int 
(*aclGetDeviceInfo)(cl_device_id    /* device */,
                cl_device_info  /* param_name */, 
                size_t          /* param_value_size */, 
                void *          /* param_value */,
                size_t *        /* param_value_size_ret */);
    

    
    
/* Context APIs  */
#define clCreateContext aclCreateContext
 cl_context 
(*aclCreateContext)(const cl_context_properties * /* properties */,
                cl_uint                 /* num_devices */,
                const cl_device_id *    /* devices */,
                void (CL_CALLBACK * /* pfn_notify */)(const char *, const void *, size_t, void *),
                void *                  /* user_data */,
                cl_int *                /* errcode_ret */);

#define clCreateContextFromType aclCreateContextFromType
 cl_context 
(*aclCreateContextFromType)(const cl_context_properties * /* properties */,
                        cl_device_type          /* device_type */,
                        void (CL_CALLBACK *     /* pfn_notify*/ )(const char *, const void *, size_t, void *),
                        void *                  /* user_data */,
                        cl_int *                /* errcode_ret */);

#define clRetainContext aclRetainContext
 cl_int 
(*aclRetainContext)(cl_context /* context */);

#define clReleaseContext aclReleaseContext
 cl_int 
(*aclReleaseContext)(cl_context /* context */);

#define clGetContextInfo aclGetContextInfo
 cl_int 
(*aclGetContextInfo)(cl_context         /* context */, 
                 cl_context_info    /* param_name */, 
                 size_t             /* param_value_size */, 
                 void *             /* param_value */, 
                 size_t *           /* param_value_size_ret */);

/* Command Queue APIs */
#define clCreateCommandQueue aclCreateCommandQueue
 cl_command_queue 
(*aclCreateCommandQueue)(cl_context                     /* context */, 
                     cl_device_id                   /* device */, 
                     cl_command_queue_properties    /* properties */,
                     cl_int *                       /* errcode_ret */);

#define clRetainCommandQueue aclRetainCommandQueue
 cl_int 
(*aclRetainCommandQueue)(cl_command_queue /* command_queue */);

#define clReleaseCommandQueue aclReleaseCommandQueue
 cl_int 
(*aclReleaseCommandQueue)(cl_command_queue /* command_queue */);

#define clGetCommandQueueInfo aclGetCommandQueueInfo
 cl_int 
(*aclGetCommandQueueInfo)(cl_command_queue      /* command_queue */,
                      cl_command_queue_info /* param_name */,
                      size_t                /* param_value_size */,
                      void *                /* param_value */,
                      size_t *              /* param_value_size_ret */);

/* Memory Object APIs */
#define clCreateBuffer aclCreateBuffer
 cl_mem 
(*aclCreateBuffer)(cl_context   /* context */,
               cl_mem_flags /* flags */,
               size_t       /* size */,
               void *       /* host_ptr */,
               cl_int *     /* errcode_ret */);

#define clCreateSubBuffer aclCreateSubBuffer
 cl_mem 
(*aclCreateSubBuffer)(cl_mem                   /* buffer */,
                  cl_mem_flags             /* flags */,
                  cl_buffer_create_type    /* buffer_create_type */,
                  const void *             /* buffer_create_info */,
                  cl_int *                 /* errcode_ret */);

                       
#define clRetainMemObject aclRetainMemObject
 cl_int 
(*aclRetainMemObject)(cl_mem /* memobj */);

#define clReleaseMemObject aclReleaseMemObject
 cl_int 
(*aclReleaseMemObject)(cl_mem /* memobj */);

#define clGetSupportedImageFormats aclGetSupportedImageFormats
 cl_int 
(*aclGetSupportedImageFormats)(cl_context           /* context */,
                           cl_mem_flags         /* flags */,
                           cl_mem_object_type   /* image_type */,
                           cl_uint              /* num_entries */,
                           cl_image_format *    /* image_formats */,
                           cl_uint *            /* num_image_formats */);
                                    
#define clGetMemObjectInfo aclGetMemObjectInfo
 cl_int 
(*aclGetMemObjectInfo)(cl_mem           /* memobj */,
                   cl_mem_info      /* param_name */, 
                   size_t           /* param_value_size */,
                   void *           /* param_value */,
                   size_t *         /* param_value_size_ret */);

#define clGetImageInfo aclGetImageInfo
 cl_int 
(*aclGetImageInfo)(cl_mem           /* image */,
               cl_image_info    /* param_name */, 
               size_t           /* param_value_size */,
               void *           /* param_value */,
               size_t *         /* param_value_size_ret */);

#define clSetMemObjectDestructorCallback aclSetMemObjectDestructorCallback
 cl_int 
(*aclSetMemObjectDestructorCallback)(  cl_mem /* memobj */, 
                                    void (CL_CALLBACK * /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/), 
                                    void * /*user_data */ );  

/* Sampler APIs */
#define clCreateSampler aclCreateSampler
 cl_sampler 
(*aclCreateSampler)(cl_context          /* context */,
                cl_bool             /* normalized_coords */, 
                cl_addressing_mode  /* addressing_mode */, 
                cl_filter_mode      /* filter_mode */,
                cl_int *            /* errcode_ret */);

#define clRetainSampler aclRetainSampler
 cl_int 
(*aclRetainSampler)(cl_sampler /* sampler */);

#define clReleaseSampler aclReleaseSampler
 cl_int 
(*aclReleaseSampler)(cl_sampler /* sampler */);

#define clGetSamplerInfo aclGetSamplerInfo
 cl_int 
(*aclGetSamplerInfo)(cl_sampler         /* sampler */,
                 cl_sampler_info    /* param_name */,
                 size_t             /* param_value_size */,
                 void *             /* param_value */,
                 size_t *           /* param_value_size_ret */);
                            
/* Program Object APIs  */
#define clCreateProgramWithSource aclCreateProgramWithSource
 cl_program 
(*aclCreateProgramWithSource)(cl_context        /* context */,
                          cl_uint           /* count */,
                          const char **     /* strings */,
                          const size_t *    /* lengths */,
                          cl_int *          /* errcode_ret */);

#define clCreateProgramWithBinary aclCreateProgramWithBinary
 cl_program 
(*aclCreateProgramWithBinary)(cl_context                     /* context */,
                          cl_uint                        /* num_devices */,
                          const cl_device_id *           /* device_list */,
                          const size_t *                 /* lengths */,
                          const unsigned char **         /* binaries */,
                          cl_int *                       /* binary_status */,
                          cl_int *                       /* errcode_ret */);


#define clRetainProgram aclRetainProgram
 cl_int 
(*aclRetainProgram)(cl_program /* program */);

#define clReleaseProgram aclReleaseProgram
 cl_int 
(*aclReleaseProgram)(cl_program /* program */);

#define clBuildProgram aclBuildProgram
 cl_int 
(*aclBuildProgram)(cl_program           /* program */,
               cl_uint              /* num_devices */,
               const cl_device_id * /* device_list */,
               const char *         /* options */, 
               void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
               void *               /* user_data */);





#define clGetProgramInfo aclGetProgramInfo
 cl_int 
(*aclGetProgramInfo)(cl_program         /* program */,
                 cl_program_info    /* param_name */,
                 size_t             /* param_value_size */,
                 void *             /* param_value */,
                 size_t *           /* param_value_size_ret */);

#define clGetProgramBuildInfo aclGetProgramBuildInfo
 cl_int 
(*aclGetProgramBuildInfo)(cl_program            /* program */,
                      cl_device_id          /* device */,
                      cl_program_build_info /* param_name */,
                      size_t                /* param_value_size */,
                      void *                /* param_value */,
                      size_t *              /* param_value_size_ret */);
                            
/* Kernel Object APIs */
#define clCreateKernel aclCreateKernel
 cl_kernel 
(*aclCreateKernel)(cl_program      /* program */,
               const char *    /* kernel_name */,
               cl_int *        /* errcode_ret */);

#define clCreateKernelsInProgram aclCreateKernelsInProgram
 cl_int 
(*aclCreateKernelsInProgram)(cl_program     /* program */,
                         cl_uint        /* num_kernels */,
                         cl_kernel *    /* kernels */,
                         cl_uint *      /* num_kernels_ret */);

#define clRetainKernel aclRetainKernel
 cl_int 
(*aclRetainKernel)(cl_kernel    /* kernel */);

#define clReleaseKernel aclReleaseKernel
 cl_int 
(*aclReleaseKernel)(cl_kernel   /* kernel */);

#define clSetKernelArg aclSetKernelArg
 cl_int 
(*aclSetKernelArg)(cl_kernel    /* kernel */,
               cl_uint      /* arg_index */,
               size_t       /* arg_size */,
               const void * /* arg_value */);

#define clGetKernelInfo aclGetKernelInfo
 cl_int 
(*aclGetKernelInfo)(cl_kernel       /* kernel */,
                cl_kernel_info  /* param_name */,
                size_t          /* param_value_size */,
                void *          /* param_value */,
                size_t *        /* param_value_size_ret */);


#define clGetKernelWorkGroupInfo aclGetKernelWorkGroupInfo
 cl_int 
(*aclGetKernelWorkGroupInfo)(cl_kernel                  /* kernel */,
                         cl_device_id               /* device */,
                         cl_kernel_work_group_info  /* param_name */,
                         size_t                     /* param_value_size */,
                         void *                     /* param_value */,
                         size_t *                   /* param_value_size_ret */);

/* Event Object APIs */
#define clWaitForEvents aclWaitForEvents
 cl_int 
(*aclWaitForEvents)(cl_uint             /* num_events */,
                const cl_event *    /* event_list */);

#define clGetEventInfo aclGetEventInfo
 cl_int 
(*aclGetEventInfo)(cl_event         /* event */,
               cl_event_info    /* param_name */,
               size_t           /* param_value_size */,
               void *           /* param_value */,
               size_t *         /* param_value_size_ret */);
                            
#define clCreateUserEvent aclCreateUserEvent
 cl_event 
(*aclCreateUserEvent)(cl_context    /* context */,
                  cl_int *      /* errcode_ret */);               
                            
#define clRetainEvent aclRetainEvent
 cl_int 
(*aclRetainEvent)(cl_event /* event */);

#define clReleaseEvent aclReleaseEvent
 cl_int 
(*aclReleaseEvent)(cl_event /* event */);

#define clSetUserEventStatus aclSetUserEventStatus
 cl_int 
(*aclSetUserEventStatus)(cl_event   /* event */,
                     cl_int     /* execution_status */);
                     
#define clSetEventCallback aclSetEventCallback
 cl_int 
(*aclSetEventCallback)( cl_event    /* event */,
                    cl_int      /* command_exec_callback_type */,
                    void (CL_CALLBACK * /* pfn_notify */)(cl_event, cl_int, void *),
                    void *      /* user_data */);

/* Profiling APIs */
#define clGetEventProfilingInfo aclGetEventProfilingInfo
 cl_int 
(*aclGetEventProfilingInfo)(cl_event            /* event */,
                        cl_profiling_info   /* param_name */,
                        size_t              /* param_value_size */,
                        void *              /* param_value */,
                        size_t *            /* param_value_size_ret */);
                                
/* Flush and Finish APIs */
#define clFlush aclFlush
 cl_int 
(*aclFlush)(cl_command_queue /* command_queue */);

#define clFinish aclFinish
 cl_int 
(*aclFinish)(cl_command_queue /* command_queue */);

/* Enqueued Commands APIs */
#define clEnqueueReadBuffer aclEnqueueReadBuffer
 cl_int 
(*aclEnqueueReadBuffer)(cl_command_queue    /* command_queue */,
                    cl_mem              /* buffer */,
                    cl_bool             /* blocking_read */,
                    size_t              /* offset */,
                    size_t              /* size */, 
                    void *              /* ptr */,
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);
                            
#define clEnqueueReadBufferRect aclEnqueueReadBufferRect
 cl_int 
(*aclEnqueueReadBufferRect)(cl_command_queue    /* command_queue */,
                        cl_mem              /* buffer */,
                        cl_bool             /* blocking_read */,
                        const size_t *      /* buffer_offset */,
                        const size_t *      /* host_offset */, 
                        const size_t *      /* region */,
                        size_t              /* buffer_row_pitch */,
                        size_t              /* buffer_slice_pitch */,
                        size_t              /* host_row_pitch */,
                        size_t              /* host_slice_pitch */,                        
                        void *              /* ptr */,
                        cl_uint             /* num_events_in_wait_list */,
                        const cl_event *    /* event_wait_list */,
                        cl_event *          /* event */);
                            
#define clEnqueueWriteBuffer aclEnqueueWriteBuffer
 cl_int 
(*aclEnqueueWriteBuffer)(cl_command_queue   /* command_queue */, 
                     cl_mem             /* buffer */, 
                     cl_bool            /* blocking_write */, 
                     size_t             /* offset */, 
                     size_t             /* size */, 
                     const void *       /* ptr */, 
                     cl_uint            /* num_events_in_wait_list */, 
                     const cl_event *   /* event_wait_list */, 
                     cl_event *         /* event */);
                            
#define clEnqueueWriteBufferRect aclEnqueueWriteBufferRect
 cl_int 
(*aclEnqueueWriteBufferRect)(cl_command_queue    /* command_queue */,
                         cl_mem              /* buffer */,
                         cl_bool             /* blocking_write */,
                         const size_t *      /* buffer_offset */,
                         const size_t *      /* host_offset */, 
                         const size_t *      /* region */,
                         size_t              /* buffer_row_pitch */,
                         size_t              /* buffer_slice_pitch */,
                         size_t              /* host_row_pitch */,
                         size_t              /* host_slice_pitch */,                        
                         const void *        /* ptr */,
                         cl_uint             /* num_events_in_wait_list */,
                         const cl_event *    /* event_wait_list */,
                         cl_event *          /* event */);
                            
                            
#define clEnqueueCopyBuffer aclEnqueueCopyBuffer
 cl_int 
(*aclEnqueueCopyBuffer)(cl_command_queue    /* command_queue */, 
                    cl_mem              /* src_buffer */,
                    cl_mem              /* dst_buffer */, 
                    size_t              /* src_offset */,
                    size_t              /* dst_offset */,
                    size_t              /* size */, 
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);
                            
#define clEnqueueCopyBufferRect aclEnqueueCopyBufferRect
 cl_int 
(*aclEnqueueCopyBufferRect)(cl_command_queue    /* command_queue */, 
                        cl_mem              /* src_buffer */,
                        cl_mem              /* dst_buffer */, 
                        const size_t *      /* src_origin */,
                        const size_t *      /* dst_origin */,
                        const size_t *      /* region */, 
                        size_t              /* src_row_pitch */,
                        size_t              /* src_slice_pitch */,
                        size_t              /* dst_row_pitch */,
                        size_t              /* dst_slice_pitch */,
                        cl_uint             /* num_events_in_wait_list */,
                        const cl_event *    /* event_wait_list */,
                        cl_event *          /* event */);
                            
#define clEnqueueReadImage aclEnqueueReadImage
 cl_int 
(*aclEnqueueReadImage)(cl_command_queue     /* command_queue */,
                   cl_mem               /* image */,
                   cl_bool              /* blocking_read */, 
                   const size_t *       /* origin[3] */,
                   const size_t *       /* region[3] */,
                   size_t               /* row_pitch */,
                   size_t               /* slice_pitch */, 
                   void *               /* ptr */,
                   cl_uint              /* num_events_in_wait_list */,
                   const cl_event *     /* event_wait_list */,
                   cl_event *           /* event */);

#define clEnqueueWriteImage aclEnqueueWriteImage
 cl_int 
(*aclEnqueueWriteImage)(cl_command_queue    /* command_queue */,
                    cl_mem              /* image */,
                    cl_bool             /* blocking_write */, 
                    const size_t *      /* origin[3] */,
                    const size_t *      /* region[3] */,
                    size_t              /* input_row_pitch */,
                    size_t              /* input_slice_pitch */, 
                    const void *        /* ptr */,
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);

                            
#define clEnqueueCopyImage aclEnqueueCopyImage
 cl_int 
(*aclEnqueueCopyImage)(cl_command_queue     /* command_queue */,
                   cl_mem               /* src_image */,
                   cl_mem               /* dst_image */, 
                   const size_t *       /* src_origin[3] */,
                   const size_t *       /* dst_origin[3] */,
                   const size_t *       /* region[3] */, 
                   cl_uint              /* num_events_in_wait_list */,
                   const cl_event *     /* event_wait_list */,
                   cl_event *           /* event */);

#define clEnqueueCopyImageToBuffer aclEnqueueCopyImageToBuffer
 cl_int 
(*aclEnqueueCopyImageToBuffer)(cl_command_queue /* command_queue */,
                           cl_mem           /* src_image */,
                           cl_mem           /* dst_buffer */, 
                           const size_t *   /* src_origin[3] */,
                           const size_t *   /* region[3] */, 
                           size_t           /* dst_offset */,
                           cl_uint          /* num_events_in_wait_list */,
                           const cl_event * /* event_wait_list */,
                           cl_event *       /* event */);

#define clEnqueueCopyBufferToImage aclEnqueueCopyBufferToImage
 cl_int 
(*aclEnqueueCopyBufferToImage)(cl_command_queue /* command_queue */,
                           cl_mem           /* src_buffer */,
                           cl_mem           /* dst_image */, 
                           size_t           /* src_offset */,
                           const size_t *   /* dst_origin[3] */,
                           const size_t *   /* region[3] */, 
                           cl_uint          /* num_events_in_wait_list */,
                           const cl_event * /* event_wait_list */,
                           cl_event *       /* event */);

  void * 
(*aclEnqueueMapBuffer)(cl_command_queue /* command_queue */,
                   cl_mem           /* buffer */,
                   cl_bool          /* blocking_map */, 
                   cl_map_flags     /* map_flags */,
                   size_t           /* offset */,
                   size_t           /* size */,
                   cl_uint          /* num_events_in_wait_list */,
                   const cl_event * /* event_wait_list */,
                   cl_event *       /* event */,
                   cl_int *         /* errcode_ret */);

  void * 
(*aclEnqueueMapImage)(cl_command_queue  /* command_queue */,
                  cl_mem            /* image */, 
                  cl_bool           /* blocking_map */, 
                  cl_map_flags      /* map_flags */, 
                  const size_t *    /* origin[3] */,
                  const size_t *    /* region[3] */,
                  size_t *          /* image_row_pitch */,
                  size_t *          /* image_slice_pitch */,
                  cl_uint           /* num_events_in_wait_list */,
                  const cl_event *  /* event_wait_list */,
                  cl_event *        /* event */,
                  cl_int *          /* errcode_ret */);

#define clEnqueueUnmapMemObject aclEnqueueUnmapMemObject
 cl_int 
(*aclEnqueueUnmapMemObject)(cl_command_queue /* command_queue */,
                        cl_mem           /* memobj */,
                        void *           /* mapped_ptr */,
                        cl_uint          /* num_events_in_wait_list */,
                        const cl_event *  /* event_wait_list */,
                        cl_event *        /* event */);

#define clEnqueueNDRangeKernel aclEnqueueNDRangeKernel
 cl_int 
(*aclEnqueueNDRangeKernel)(cl_command_queue /* command_queue */,
                       cl_kernel        /* kernel */,
                       cl_uint          /* work_dim */,
                       const size_t *   /* global_work_offset */,
                       const size_t *   /* global_work_size */,
                       const size_t *   /* local_work_size */,
                       cl_uint          /* num_events_in_wait_list */,
                       const cl_event * /* event_wait_list */,
                       cl_event *       /* event */);

#define clEnqueueTask aclEnqueueTask
 cl_int 
(*aclEnqueueTask)(cl_command_queue  /* command_queue */,
              cl_kernel         /* kernel */,
              cl_uint           /* num_events_in_wait_list */,
              const cl_event *  /* event_wait_list */,
              cl_event *        /* event */);

#define clEnqueueNativeKernel aclEnqueueNativeKernel
 cl_int 
(*aclEnqueueNativeKernel)(cl_command_queue  /* command_queue */,
					  void (CL_CALLBACK * /*user_func*/)(void *), 
                      void *            /* args */,
                      size_t            /* cb_args */, 
                      cl_uint           /* num_mem_objects */,
                      const cl_mem *    /* mem_list */,
                      const void **     /* args_mem_loc */,
                      cl_uint           /* num_events_in_wait_list */,
                      const cl_event *  /* event_wait_list */,
                      cl_event *        /* event */);




    
#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
//#warning CL_USE_DEPRECATED_OPENCL_1_0_APIS is defined. These APIs are unsupported and untested in OpenCL 1.1!
    /* 
     *  WARNING:
     *     This API introduces mutable state into the OpenCL implementation. It has been REMOVED
     *  to better facilitate thread safety.  The 1.0 API is not thread safe. It is not tested by the
     *  OpenCL 1.1 conformance test, and consequently may not work or may not work dependably.
     *  It is likely to be non-performant. Use of this API is not advised. Use at your own risk.
     *
     *  Software developers previously relying on this API are instructed to set the command queue 
     *  properties when creating the queue, instead. 
     */
#define clSetCommandQueueProperty aclSetCommandQueueProperty
 cl_int 
(*aclSetCommandQueueProperty)(cl_command_queue              /* command_queue */,
                              cl_command_queue_properties   /* properties */, 
                              cl_bool                        /* enable */,
                              cl_command_queue_properties * /* old_properties */);
#endif /* CL_USE_DEPRECATED_OPENCL_1_0_APIS */
    
    
#ifdef CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define clCreateImage2D aclCreateImage2D
 cl_mem 
(*aclCreateImage2D)(cl_context              /* context */,
                    cl_mem_flags            /* flags */,
                    const cl_image_format * /* image_format */,
                    size_t                  /* image_width */,
                    size_t                  /* image_height */,
                    size_t                  /* image_row_pitch */, 
                    void *                  /* host_ptr */,
                    cl_int *                /* errcode_ret */);
    
#define clCreateImage3D aclCreateImage3D
 cl_mem 
(*aclCreateImage3D)(cl_context              /* context */,
                    cl_mem_flags            /* flags */,
                    const cl_image_format * /* image_format */,
                    size_t                  /* image_width */, 
                    size_t                  /* image_height */,
                    size_t                  /* image_depth */, 
                    size_t                  /* image_row_pitch */, 
                    size_t                  /* image_slice_pitch */, 
                    void *                  /* host_ptr */,
                    cl_int *                /* errcode_ret */);
    
#define clEnqueueMarker aclEnqueueMarker
 cl_int 
(*aclEnqueueMarker)(cl_command_queue    /* command_queue */,
                    cl_event *          /* event */);
    
#define clEnqueueWaitForEvents aclEnqueueWaitForEvents
 cl_int 
(*aclEnqueueWaitForEvents)(cl_command_queue /* command_queue */,
                           cl_uint          /* num_events */,
                           const cl_event * /* event_list */);
    
#define clEnqueueBarrier aclEnqueueBarrier
 cl_int 
(*aclEnqueueBarrier)(cl_command_queue /* command_queue */);

#define clUnloadCompiler aclUnloadCompiler
 cl_int 
(*aclUnloadCompiler)(void);
    
void *  
(*aclGetExtensionFunctionAddress)(const char * /* func_name */);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __AOPENCL_CL_H */

