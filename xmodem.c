/*
 * xmodem.c
 *
 *  Created on: Aug 30, 2023
 *      Author: alper
 */
#include "xmodem.h"
#include "stm32f4xx_ll_usart.h"
int xmodemReceive(int *huart,char *buf)
{
	unsigned char packet_data[PACKET_SIZE + PACKET_HEADER + PACKET_CRC];
    unsigned char fileSize[FILESIZE_LEN], *pFile;
	char *pcBuf;
	int i, file_done, packets_received, errors, imageSize = 0, key;
	unsigned int oReturnCheck;
	unsigned char ucBank=0;
	unsigned short packet_size, loop=1;
    //unsigned int FlashDestination = APP_START_ADDRESS ;

    enum rcvstates              // states when receiving
    	{
    	     AskHeader,             // ask for a header
    	     WaitHeader,            // await header 1st char
    	     EOTHeader,             // EOT process
    	     EndSession,
    	     CANHeader,
    		 AbortHeader,
    		 PacketErrors,
    		 GetPacketData,
    		 Packet0,
    		 DataPacket
    	} state;

    	while(loop)
    	{
    		file_done = 0;
    		packets_received = 0;
    		pcBuf = buf;
    		errors = 0;
    		state = AskHeader;
    		while(file_done==0)
    		{
    			switch (state)
    			{
    				case AskHeader:
    					HAL_UART_Transmit(huart, "C", 1, 0);
    					HAL_Delay(100);
    					state = WaitHeader;
    				case WaitHeader:
    					HAL_UART_Receive(huart,&key, 1, 0);
    					switch (key)
    					{
    					case 0x01:
    						packet_size = PACKET_SIZE;
    						HAL_UART_Transmit(huart, 0x06, 1, 0);
    						state = GetPacketData;
    						break;
    					case 0x04:
    						state = EOTHeader;
    						break;
    					}
    					break;
    				case GetPacketData:
    					 memcpy(pcBuf, packet_data + PACKET_HEADER, packet_size);
    					 HAL_UART_Transmit(huart, ACK, 1, 0);
    					 break;
    				case EOTHeader:
    					HAL_UART_Transmit(huart, ACK, 1, 0);
    					file_done = 1;
    					break;
    				case EndSession:
    					HAL_UART_Transmit(huart, ACK, 1, 0);
    					file_done = 1;
    					break;


    			}
    		}

    	}
}
