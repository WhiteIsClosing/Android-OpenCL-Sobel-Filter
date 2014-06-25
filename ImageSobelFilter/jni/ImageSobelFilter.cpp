#include "com_white_imagesobelfilter_nativeSobelFilter.h"
#include <opencv2/opencv.hpp>//这个头文件一定要包含进来的
#include<CL/cl.h>
#include"aopencl.h"
#include<math.h>
#include<stdio.h>
#include<time.h>

using namespace std;
using namespace cv;

#define N 20	//这里的N是sobel滤波的阈值
#define  KERNEL_SRC "\n" \
	"			__kernel void Sobel(__global char *array1, __global char *array2, __global int *array3)		\n "\
	"			{																							\n "\
	"				size_t gidx = get_global_id(0);															\n "\
	"				size_t gidy = get_global_id(1);															\n "\
	"				unsigned char a00, a01, a02;															\n "\
	"				unsigned char a10, a11, a12;															\n "\
	"				unsigned char a20, a21, a22;															\n "\
	"				int width=array3[0];																	\n "\
	"				int heigh=array3[1];																	\n "\
	"				int widthStep=array3[2];																\n "\
	"				if(gidy>0&&gidy<heigh-1&&gidx>0&&gidx<width-1)											\n "\
	"				{																						\n "\
	"					a00 = array1[gidx-1+widthStep*(gidy-1)];											\n "\
	"					a01 = array1[gidx+widthStep*(gidy-1)];												\n "\
	"					a02 = array1[gidx+1+widthStep*(gidy-1)];											\n "\
	"					a10 = array1[gidx-1+widthStep*gidy];												\n "\
	"					a11 = array1[gidx+widthStep*gidy];													\n "\
	"					a12 = array1[gidx+1+widthStep*gidy];												\n "\
	"					a20 = array1[gidx-1+widthStep*(gidy+1)];											\n "\
	"					a21 = array1[gidx+widthStep*(gidy+1)];												\n "\
	"					a22 = array1[gidx+1+widthStep*(gidy+1)];											\n "\
	"					float ux=a20+2*a21+a22-a00-2*a01-a02;												\n "\
	"					float uy=a02+2*a12+a22-a00-2*a10-a20;												\n "\
	"					//array2[gidx+width*gidy]=sqrt(ux*ux + uy*uy);										\n "\
	"					float u=sqrt(ux*ux + uy*uy);														\n "\
	"					if(u>255) {																			\n "\
	"						u=-1;																			\n "\
	"					} else if(u<20) {																	\n "\
	"						u=0;																			\n "\
	"					}																					\n "\
	"					array2[gidx+widthStep*gidy]=u;														\n "\
	"				}																						\n "\
"}"

//下面是三个函数的声明
void CPU_Sobel(IplImage* inputImg_gray, IplImage* outputImg);
int GPU_Sobel(IplImage* inputImg_gray, IplImage* outputImg);
double difference(IplImage* input1, IplImage* input2, IplImage* output);

extern "C" {

JNIEXPORT jstring JNICALL Java_com_white_imagesobelfilter_nativeSobelFilter_sobelFilter(
		JNIEnv* env, jobject thiz, jstring imagePath) {
	/*从方法的参数中得到相应的布尔值和字符串
	 *(*env)->NewStringUTF(env, "Hello from JNI !");
	 *这一行，这是c的写法，而我的是cpp程序，需要改写成下面的形式
	 */
	char *clImagePath = (char *) (env)->GetStringUTFChars(imagePath, 0);

	//读取图像clImagePath
	const char* imagename = clImagePath;
	IplImage* inputImg = cvLoadImage(imagename);

	CvSize size;
	size.width = inputImg->width;
	size.height = inputImg->height;

	//初始化输入，得到灰度图
	IplImage* inputImg_gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
	cvCvtColor(inputImg, inputImg_gray, CV_BGR2GRAY); //RGB2GRAY
	//初始化输出
	IplImage* cpu_outputImg = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* gpu_outputImg = cvCreateImage(size, IPL_DEPTH_8U, 1);

	clock_t start, finish;
	double CPU_time, GPU_time;

	//GPU
	start = clock();	//gpu计时开始
//	for (int i = 0; i < 10; i++)
		GPU_Sobel(inputImg_gray, gpu_outputImg);
	finish = clock();	//gpu计时结束
	GPU_time = (double) (finish - start) / CLOCKS_PER_SEC;

	//CPU
	start = clock();	//cpu计时开始
//	for (int i = 0; i < 10; i++)
		CPU_Sobel(inputImg_gray, cpu_outputImg);
	finish = clock();	//cpu计时结束
	CPU_time = (double) (finish - start) / CLOCKS_PER_SEC;

	double s = CPU_time / GPU_time;	//加速比

	//差异图，差异百分比
	IplImage* differenceImg = cvCreateImage(size, IPL_DEPTH_8U, 1);
	double f = 0.0;
	f = difference(cpu_outputImg, gpu_outputImg, differenceImg);

	//保存图像
	cvSaveImage("/storage/sdcard0/Sobel_input_gray.jpg", inputImg_gray);
	cvSaveImage("/storage/sdcard0/cpu_sobel.jpg", cpu_outputImg);
	cvSaveImage("/storage/sdcard0/gpu_sobel.jpg", gpu_outputImg);
	cvSaveImage("/storage/sdcard0/differenceImg.jpg", differenceImg);

	cvReleaseImage(&inputImg);
	cvReleaseImage(&inputImg_gray);
	cvReleaseImage(&cpu_outputImg);
	cvReleaseImage(&gpu_outputImg);

	char rr[100] = "Compute result:\nGPU:";
	char b[10];
	sprintf(b, "%.8f", GPU_time);
	strcat(rr, b);
	strcat(rr, " CPU:");
	sprintf(b, "%.8f", CPU_time);
	strcat(rr, b);

	strcat(rr, "\nSpeed-up ratio:");
	sprintf(b, "%.8f", s);
	strcat(rr, b);
	strcat(rr, "\ndifference:");
	sprintf(b, "%.8f", f);
	strcat(rr, b);

//	char zz[4];
//	sprintf(zz, "%d", z);

	/*下面的返回字符串写法有点不同*/
	const char* result = rr;
	return env->NewStringUTF(rr);
}
}

void CPU_Sobel(IplImage* inputImg_gray, IplImage* outputImg) {
	unsigned char a00, a01, a02;
	unsigned char a10, a11, a12;
	unsigned char a20, a21, a22;
	for (int i = 1; i < inputImg_gray->height - 1; i++) {
		for (int j = 1; j < inputImg_gray->width - 1; j++) {
			a00 = inputImg_gray->imageData[j - 1
					+ inputImg_gray->widthStep * (i - 1)];
			a01 = inputImg_gray->imageData[j
					+ inputImg_gray->widthStep * (i - 1)];
			a02 = inputImg_gray->imageData[j + 1
					+ inputImg_gray->widthStep * (i - 1)];
			a10 =
					inputImg_gray->imageData[j - 1
							+ inputImg_gray->widthStep * i];
			a11 = inputImg_gray->imageData[j + inputImg_gray->widthStep * i];
			a12 =
					inputImg_gray->imageData[j + 1
							+ inputImg_gray->widthStep * i];
			a20 = inputImg_gray->imageData[j - 1
					+ inputImg_gray->widthStep * (i + 1)];
			a21 = inputImg_gray->imageData[j
					+ inputImg_gray->widthStep * (i + 1)];
			a22 = inputImg_gray->imageData[j + 1
					+ inputImg_gray->widthStep * (i + 1)];

			// x方向上的近似导数
			float ux = a20 * (1) + a21 * (2) + a22 * (1) + a00 * (-1)
					+ a01 * (-2) + a02 * (-1);
			// y方向上的近似导数
			float uy = a02 * (1) + a12 * (2) + a22 * (1) + a00 * (-1)
					+ a10 * (-2) + a20 * (-1);
			//梯度
			float u = sqrt(ux * ux + uy * uy);

			//阈值法确定边缘
			if (u > 255) {
				u = 255;
			} else if (u < N) {
				u = 0;
			}
			outputImg->imageData[j + outputImg->widthStep * i] = u;
		}
	}
}
int GPU_Sobel(IplImage* inputImg_gray, IplImage* outputImg) {
	/*這裡一定要初始化各个函数*/

	initFns();
	/*宿主机变量*/
	cl_uint numPlatforms; //the NO. of platforms
	cl_platform_id platform = NULL; //the chosen platform
	cl_int status;
	cl_platform_id* platforms;
	cl_uint numDevices = 0;
	cl_device_id *devices;
	cl_context context;
	cl_command_queue commandQueue;
	cl_program program;
	cl_kernel kernel;
	//size_t global;
	cl_mem a1, a2, a3;

	int IMG_WIDTH = inputImg_gray->width;
	int IMG_HEIGHT = inputImg_gray->height;

	long IN_DATA_SIZE = inputImg_gray->widthStep * IMG_HEIGHT;
	long OUT_DATA_SIZE = outputImg->widthStep * IMG_HEIGHT;
	//unsigned char *inputData1;
	//inputData1=(unsigned char *)malloc(DATA_SIZE*sizeof(unsigned char));
	char *inputData1;
	inputData1 = inputImg_gray->imageData;

	//float *outputData;
	//outputData=(float *)malloc(DATA_SIZE*sizeof(float));
	char *outputData;
	outputData = outputImg->imageData;

	int inputData2[3] = { IMG_WIDTH, IMG_HEIGHT, inputImg_gray->widthStep };

	/*Step1: Getting platforms and choose an available one.*/
	status = clGetPlatformIDs(0, NULL, &numPlatforms);

	/*For clarity, choose the first available platform. */
	if (numPlatforms > 0) {
		platforms = (cl_platform_id*) malloc(
				numPlatforms * sizeof(cl_platform_id));
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		platform = platforms[0];
		free(platforms);
	}

	/*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
//	if (numDevices == 0) //no GPU available.
//			{
//		printf("No GPU device available.\n");
//		printf("Choose CPU as default device.\n");
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL,
//				&numDevices);
//		devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices,
//				devices, NULL);
//	} else {
//		devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices,
//				devices, NULL);
//	}
	devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices,
			NULL);

	/*Step 3: Create context.*/
	context = clCreateContext(NULL, 1, devices, NULL, NULL, &status);

	/*Step 4: Creating command queue associate with the context.*/
	commandQueue = clCreateCommandQueue(context, devices[0], 0, &status);

	/*Step 5: Create program object */
	const char *source = KERNEL_SRC;
	size_t sourceSize[] = { strlen(source) };
	program = clCreateProgramWithSource(context, 1, &source, sourceSize,
			&status);

	/*Step 6: Build program. */
	status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);

	a1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(unsigned char) * IN_DATA_SIZE, inputData1, &status);

	a2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(unsigned char) * OUT_DATA_SIZE, outputData, &status);

	a3 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(int) * 3, inputData2, &status);

	/*Step 8: Create kernel object */
	kernel = clCreateKernel(program, "Sobel", &status);

	// set the argument list for the kernel command
	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &a1);
	status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &a2);
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &a3);

	size_t local[] = { 11, 11 };
	size_t global[2];
	global[0] = (
			IMG_WIDTH % local[0] == 0 ?
					IMG_WIDTH : (IMG_WIDTH + local[0] - IMG_WIDTH % local[0]));
	global[1] =
			(IMG_HEIGHT % local[1] == 0 ?
					IMG_HEIGHT : (IMG_HEIGHT + local[1] - IMG_HEIGHT % local[1]));
//	size_t local[] = { 2, 2 };
//		size_t global[]={10,10};

	// enqueue the kernel command for execution
	status = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global,
			local, 0, NULL, NULL);
	if (status != 0)
		return status;
	clFinish(commandQueue);

	clEnqueueReadBuffer(commandQueue, a2, CL_TRUE, 0,
			sizeof(unsigned char) * OUT_DATA_SIZE, outputData, 0, NULL, NULL);

	clReleaseMemObject(a1);
	clReleaseMemObject(a2);
	clReleaseMemObject(a3);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);

	return 0;
}
double difference(IplImage* input1, IplImage* input2, IplImage* output) {
	unsigned char a;
	double re;
	int k = 0;
	for (int i = 0; i < input1->height; i++) {
		for (int j = 0; j < input1->width; j++) {
			a = input1->imageData[j + input1->widthStep * i]
					- input2->imageData[j + input2->widthStep * i];
			output->imageData[j + output->widthStep * i] = a;
			if (a != 0) {
				k++;
			}
		}
	}
	printf("差异点：%d\n", k);
	re = (double) k / (double) (input1->height * input1->width);
	return re;
}
