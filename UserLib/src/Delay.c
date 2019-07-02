/**
 * @File: Delay.c
 * @Brief: Provide funtions used for delay
 * @Author: J.T. Yu
 * @Date: 2019/7/1
 */

/**
  * @brief  delay n nanoseconds
  * @param  n
  * @retval None
  */
void delay_nus(unsigned long n)
{
    unsigned long j;
    while (n--)
    {
        j=8;
        while (j--);
    }
}

/**
  * @brief  delay n microseconds
  * @param  n
  * @retval None
  */
void delay_nms(unsigned long n)
{
while (n--)
delay_nus(1100);
}

