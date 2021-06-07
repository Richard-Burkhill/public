/* CELEBP53 */                                   
#define _GNU_SOURCE
#include <pthread.h>                                                            
#include <stdio.h>                                                              
#include <unistd.h>


// Thread id
pthread_t threadId;
size_t amountRead = 0;
char data[640*480];
FILE* camLive = NULL;

void* threadFunc(void* param){
   while (1){
      amountRead = fread(data, sizeof(data[0]), 640*480, camLive);
      if (amountRead)
         printf("Read %li bytes from /dev/video0", amountRead);
      pthread_yield();
   }
}

int main (int argc, char** argv) {
  FILE* webCamOut = NULL;
  int err = 0;
  
  camLive = fopen("/dev/video0", "rb");
  if (camLive == NULL)
  {
     printf("filp_open error, failed to open webCam resource !!.\n");
  }else{
     printf("Opened webCam resource !!.\n");
     webCamOut=fopen("/home/rich/Videos/webCamOutfile", "wb");
     if (webCamOut == NULL){
        printf("filp_open error, failed to open webCamOutfile !!.\n");
     }else{
        printf("Opened webCamOutfile !!.\n");
        
        // Create a thread that will function threadFunc()
        err = pthread_create(&threadId, NULL, &threadFunc, NULL);
        err = pthread_join(threadId, NULL);
        fclose(webCamOut);
     }
     fclose(camLive);
  }
  
  return 0;
}

