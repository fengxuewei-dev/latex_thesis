#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <cstdlib>
#include <cmath>
#include <inttypes.h>
#include <fstream>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define DEFAULT_PORT 8002
#define DEFAULT_IP_ADDRESS  "127.0.0.1"

#define LOCALUAVID 0

struct Senddata {
  int id = 0;
  double yaw = 0.0;
  double position_x = 0.0;
  double position_y = 0.0;
  double position_z = 0.0;
  double heading = 0.0;
  double airspeed = 0.0;
  int Parity = 0;
};

void CreatSocket(int* length, int* sockfd, int port){
  ///////////////////////////////////////////////////////
  cout<<port<<endl;
  /* sock_fd --- socket文件描述符 创建udp套接字*/
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)
  {
    perror("socket");
    exit(1);
  }

  /* 将套接字和IP、端口绑定 */
  struct sockaddr_in addr_serv;
  int len;
  memset(&addr_serv, 0, sizeof(struct sockaddr_in));  //每个字节都用0填充
  addr_serv.sin_family = AF_INET;                     //使用IPV4地址
  addr_serv.sin_port = htons(port);              //端口
  /* INADDR_ANY表示不管是哪个网卡接收到数据，只要目的端口是SERV_PORT，就会被该应用程序接收到 */
  addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);  //自动获取IP地址
  len = sizeof(addr_serv);

  /* 绑定socket */
  if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
  {
    perror("bind error:");
    exit(1);
  }
  *length = len;
  *sockfd = sock_fd;
}

int main(int argc, char **argv)
 {

  int sock_fd, len;
  int port = 8002; // 默认端口为8002  
 	
  CreatSocket(&len, &sock_fd, port);

  int recv_num;
  unsigned short int temtreat;
  void *tempsave_v = new char[100];

  struct sockaddr_in addr_client;
  struct Senddata rece_data;
  while(true)
  {
    printf("server wait:\n");
    
    recv_num = recvfrom(sock_fd, tempsave_v, sizeof(rece_data), MSG_DONTWAIT, (struct sockaddr *)&addr_client, (socklen_t *)&len);
    
    memcpy(&rece_data,tempsave_v,sizeof(rece_data));
      
    std::cout<<"send heading    is:"<<rece_data.heading<<std::endl;
    std::cout<<"send airspeed   is:"<<rece_data.airspeed<<std::endl;
    std::cout<<"send position_x is:"<<rece_data.position_x<<std::endl;
    std::cout<<"send position_y is:"<<rece_data.position_y<<std::endl;
    std::cout<<"send position_z is:"<<rece_data.position_z<<std::endl;
    std::cout<<"send yaw        is:"<<rece_data.yaw<<std::endl;
    std::cout<<"message:"<<rece_data.id<<" Parity is:"<<rece_data.Parity<<std::endl;
    std::cout << std::endl;
    sleep(1);
  }
  close(sock_fd);
  return 0;
}
