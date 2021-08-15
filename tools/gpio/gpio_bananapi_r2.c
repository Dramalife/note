/* https://www.cnblogs.com/topbin/p/10577137.html */



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MMAP_PATH    "/dev/mem"

static uint8_t* gpio_mmap_reg = NULL;
static int gpio_mmap_fd = 0;

int pins[] = {75, 76, 206, 80, 79, 205, 56, 55, 54, 57, 126, 74, 73, 49, 202,
	82, 81, 24, 25, 21, 18, 53, 20, 58, 72, 19, 22, 200};

#define GPIO_DOUT_BASE_OFFSET  0x500
#define GPIO_MODE_BASE_OFFSET  0x760
#define GPIO_REG_BASE          0x10005000


static int gpio_mmap(void)
{
	if ((gpio_mmap_fd = open(MMAP_PATH, O_RDWR|O_SYNC)) < 0) {
		fprintf(stderr, "unable to open mmap file");
		return -1;
	}

	gpio_mmap_reg = (uint8_t*) mmap(NULL, 1024, PROT_READ | PROT_WRITE,
			MAP_FILE | MAP_SHARED , gpio_mmap_fd, GPIO_REG_BASE);
	if (gpio_mmap_reg == MAP_FAILED) {
		perror("foo");
		fprintf(stderr, "failed to mmap");
		gpio_mmap_reg = NULL;
		close(gpio_mmap_fd);
		return -1;
	}

	return 0;
}

int main()
{
	int ret = -1;
	int pin = 75;

	if (gpio_mmap())
		return -1;
	printf("set dir\n");
	uint32_t tmp;
	int position = 0;

	printf("BASEADDR=%X\nSET MODE AS GPIO\n", gpio_mmap_reg);
	for(int i = 0; i < sizeof(pins)/sizeof(int); i++){
		pin = pins[i];
		position = gpio_mmap_reg + GPIO_MODE_BASE_OFFSET + (pin / 5) * 16;
		printf("pin=%d, positon = %X\n", pin, position);
		tmp = *(volatile uint32_t*)(position);        
		tmp &= ~(1u << ((pin % 5) * 3));
		*(volatile uint32_t*)(position) = tmp;

	}

	printf("\nSET DIR AS OUT\n");
	for(int i = 0; i < sizeof(pins)/sizeof(int); i++){
		pin = pins[i];
		if(pin < 199){    
			position = gpio_mmap_reg + (pin / 16) * 16;
		}else{
			position = gpio_mmap_reg + (pin / 16) * 16 + 0x10;
		}
		  printf("pin=%d, positon = %X\n", pin, position);
		tmp = *(volatile uint32_t*)(position);
		      tmp |= (1u << (pin % 16));
		  *(volatile uint32_t*)(position) = tmp;
		usleep(100000);
	}



	printf("\nSET VALUE AS HIGH LEVEL\n");
	for(int i = 0; i < sizeof(pins)/sizeof(int); i++){
		pin = pins[i];
		   position = gpio_mmap_reg + GPIO_DOUT_BASE_OFFSET + (pin / 16) * 16;
		   printf("pin=%d, positon = %X\n", pin, position);
		   tmp = *(volatile uint32_t*)(position);
		   tmp |= (1u << (pin % 16));
		   *(volatile uint32_t*)(position) = tmp;
		   usleep(100000);
	}

	  printf("\nSET VALUE AS LOW LEVEL\n");
	for(int i = 0; i < sizeof(pins)/sizeof(int); i++){
		pin = pins[i];
		position = gpio_mmap_reg + GPIO_DOUT_BASE_OFFSET + (pin / 16) * 16;
		      printf("pin=%d, positon = %X\n", pin, position);
		tmp = *(volatile uint32_t*)(position);
		printf("tmp = %X\n", tmp);
		   tmp &= ~(1u << (pin % 16));
		   printf("tmp = %X\n", tmp);
		   *(volatile uint32_t*)(position) = tmp;
		usleep(100000);
	}
	close(gpio_mmap_fd);
}
