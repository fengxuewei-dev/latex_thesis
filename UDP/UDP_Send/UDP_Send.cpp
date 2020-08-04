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

void RunSend (int sock_fd, Senddata send_buf, sockaddr_in addr_serv, int len){
  int send_num = 0;
  
  //printf("client send: %s\n", send_buf);
  //std::cout<<"client send:"<<send_buf.localposition_x<<std::endl;
  send_num = sendto(sock_fd, &send_buf, sizeof(send_buf), 0, (struct sockaddr *)&addr_serv, len);
  if(send_num < 0)
  {
     perror("sendto error:");
     exit(1);
  }
}

int main(int argc, char **argv)
{
  
  int sock_fd;
  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)
  {
    perror("socket");
    exit(1);
  }
  
  const int opt = 1;
  //设置该套接字为广播类型，
  int nb = 0;
  setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
  
  sockaddr_in addr_serv_temp;

  memset(&addr_serv_temp, 0, sizeof(addr_serv_temp));
  addr_serv_temp.sin_family = AF_INET;
  addr_serv_temp.sin_addr.s_addr = htonl(INADDR_BROADCAST); // 广播
  addr_serv_temp.sin_port = htons(8002);
  
  Senddata send_buf;



  /*******************************************************************UDP*************************************************/
  while(true){
  
    send_buf.heading = 16;
    send_buf.airspeed = 17;
    send_buf.position_x = 18;
    send_buf.position_y = 19;
    send_buf.position_z = 20;
    send_buf.yaw = 21;

    send_buf.id++;
    send_buf.Parity = (int)(send_buf.heading + send_buf.airspeed + send_buf.position_x + send_buf.position_y + send_buf.position_z + send_buf.yaw );
    
    std::cout<<"send heading    is:"<<send_buf.heading<<std::endl;
    std::cout<<"send airspeed   is:"<<send_buf.airspeed<<std::endl;
    std::cout<<"send position_x is:"<<send_buf.position_x<<std::endl;
    std::cout<<"send position_y is:"<<send_buf.position_y<<std::endl;
    std::cout<<"send position_z is:"<<send_buf.position_z<<std::endl;
    std::cout<<"send yaw        is:"<<send_buf.yaw<<std::endl;
    std::cout<<"message:"<<send_buf.id<<" Parity is:"<<send_buf.Parity<<std::endl;
    
    RunSend(sock_fd, send_buf, addr_serv_temp, sizeof(addr_serv_temp));
    sleep(1);
        
  }

  close(sock_fd);
  return 0;
}