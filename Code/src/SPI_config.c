#include "stm32f10x.h"
#include "SPI_define.h"
/*
   SPI ���� ����.
   SPI�� Master�� Slave�� ������ ��� ���.
   SPI�� 2���� ���� ���� FullDuplex���� ���. ��, �ִ� 2Line FullDuplex ��� ����.
*/
SPI_InitTypeDef SPI_InitStructure;

void SPIy_Master_Configuration()
{
    /* SPIy Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	//�����͸�����
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIy, &SPI_InitStructure);			//SPIy�� �����ͷ�

    /* SPIz Config -------------------------------------------------------------*/
    //SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    //SPI_Init(SPIz, &SPI_InitStructure);			//SPIz�� �����ͷ�

    /* Enable SPIy */
    SPI_Cmd(SPIy, ENABLE);
    /* Enable SPIz */
    //SPI_Cmd(SPIz, ENABLE);

}

void SPIz_Slave_Configuration()
{
    /* SPIz Config -------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;	//�����͸�����
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIz, &SPI_InitStructure);			//SPIy�� �����ͷ�

    /* SPIz Config -------------------------------------------------------------*/
    //SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    //SPI_Init(SPIz, &SPI_InitStructure);			//SPIz�� �����ͷ�

    /* Enable SPIy */
    //SPI_Cmd(SPIy, ENABLE);
    /* Enable SPIz */
    SPI_Cmd(SPIz, ENABLE);

}



//SPIy�� Buffer��(Tx,Rx) ���Ҷ� ���
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
        return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}