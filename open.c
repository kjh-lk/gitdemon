#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>

#define BASE_addr 0x1E780000
#define BASE_addr1 0x1E6E2000
#define SIZE 0xff

void poweron_l(void)
{
	int fd;
	fd=open("/dev/mem",O_RDWR|O_NDELAY);
	unsigned int* map_base=(unsigned int*)mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,BASE_addr);
	*(volatile unsigned int*)(map_base+0x24/4)|=(1<<8);//输出状态寄存器
	*(volatile unsigned int*)(map_base+0x20/4)&=~(1<<8);//数据寄存器
	usleep(1000000);
	if(fd)
		close(fd);
	munmap(map_base,SIZE);
}

void ask_l(void)
{
	int fd;
	fd=open("/dev/mem",O_RDWR|O_NDELAY);
	unsigned int* map_base=(unsigned int*)mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,BASE_addr);
	*(volatile unsigned int*)(map_base+0x24/4)|=(1<<11);//输出状态寄存器
	*(volatile unsigned int*)(map_base+0x20/4)&=~(1<<11);//数据寄存器
	usleep(1000000);
	if(fd)
		close(fd);
	munmap(map_base,SIZE);
}
void scu70(void)
{
	int fd;
	fd=open("/dev/mem",O_RDWR|O_NDELAY);
	unsigned int* map_base=(unsigned int*)mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,BASE_addr1);
	*(volatile unsigned int*)(map_base+0x70/4)|=(1<<19);
	usleep(1000000);
	if(fd)
		close(fd);
	munmap(map_base,SIZE);
}

int main(void)
{
	scu70();
	poweron_l();
	ask_l();
	return 0;
}

