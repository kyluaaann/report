#include<reg52.h> //包含頭文件，一般情況不需要改動，頭文件包含特殊功能寄存器的定義 
#include <string.h>                    
#define MAX 5
#define DataPort P0 //定義數據端口 程序中遇到DataPort 則用P0 替換
sbit LATCH1=P1^0;//定義鎖存使能端口 段鎖存
sbit LATCH2=P1^1;//定義鎖存使能端口 位鎖存
unsigned char TempData[8]; //存儲顯示值的全局變量
unsigned char code dofly_DuanMa[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x39,0x76,0x38,0x37,0x73,0x78,0x66};//0,1,2,3,4,5,6,7,8,9,C,H,L,N,P,T,Y分別對應相應的字點亮,即段碼
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//分別對應相應的數碼管點亮,即位碼
unsigned char buf[MAX];
unsigned char head = 0;
sbit KEY0 = P2^0;
sbit KEY1 = P2^1;
sbit KEY2 = P2^2;
sbit KEY3 = P2^3;
sbit KEY4 = P2^4;
sbit KEY5 = P2^5;
sbit KEY6 = P2^6;
sbit KEY7 = P2^7;
/*------------------------------------------------
                   函數聲明
------------------------------------------------*/
void Delay(unsigned int t);//Display使用的延遲
void delay();//KEY使用的延遲 
void SendStr(unsigned char *s);//傳送字串到ESP32
void Display(unsigned char FirstBit,unsigned char Num);//顯示溫度資料在七段顯示器
/*------------------------------------------------
                    串口初始化
------------------------------------------------*/
void InitUART  (void)
{
    SCON  = 0x50;		        // SCON: 模式 1, 8-bit UART, 使能接收  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重裝
    TH1   = 0xFD;               // TH1:  重裝值 9600 波特率 晶振 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 打開                         
    EA    = 1;                  //打開總中斷斷
}  
/*------------------------------------------------
                    主函數
------------------------------------------------*/
void main (void)
{
InitUART();
ES    = 1;                  //打開串口中斷
while (1)                       
    {
		//taipei
		if(!KEY0)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY0)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY0)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Taipei");
					head=0;
					TempData[0]=dofly_DuanMa[15];//T
					TempData[1]=dofly_DuanMa[14];//P
				}	
			}
		}
		//new taipei
		if(!KEY1)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY1)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY1)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("New+Taipei");
					head=0;
					TempData[0]=dofly_DuanMa[13];//N
					TempData[1]=dofly_DuanMa[15];//T
				}
			}
		}
		//taoyuan
		if(!KEY2)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY2)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY2)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Taoyuan");
					head=0;
					TempData[0]=dofly_DuanMa[15];//T
					TempData[1]=dofly_DuanMa[16];//Y
				}
			}
		}
		//taichung
		if(!KEY3)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY3)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY3)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Taichung");
					head=0;
					TempData[0]=dofly_DuanMa[15];//T
					TempData[1]=dofly_DuanMa[10];//C
				}
			}
		}
		//tainan
		if(!KEY4)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY4)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY4)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Tainan");
					head=0;
					TempData[0]=dofly_DuanMa[15];//T
					TempData[1]=dofly_DuanMa[13];//N
				}
			}
		}
		//yilan
		if(!KEY5)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY5)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY5)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Yilan");
					head=0;
					TempData[0]=dofly_DuanMa[16];//Y
					TempData[1]=dofly_DuanMa[12];//L
				}
			}
		}
		//hsinchu
		if(!KEY6)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY6)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY6)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Hsinchu");
					head=0;
					TempData[0]=dofly_DuanMa[11];//H
					TempData[1]=dofly_DuanMa[10];//C
				}
			}
		}
		//changhua
		if(!KEY7)//如果檢測到低電平，說明按鍵按下
		{
			delay();
			if(!KEY7)//再次確認按鍵是否按下，沒有按下則退出
			{
				while(!KEY7)delay();//如果確認按下按鍵等待按鍵釋放，沒有釋放則一直等待
				{
					SendStr("Changhua");
					head=0;
					TempData[0]=dofly_DuanMa[10];//C
					TempData[1]=dofly_DuanMa[11];//H
				}
			}
		}
 		if (head == 5)
		{
			if(buf[4]==' ')//遇到空格轉為0
				buf[4]=0x30;
			if(buf[3]==' ')//遇到空格轉為0
				buf[3]=0x30;
			TempData[3]=dofly_DuanMa[buf[0]- '0'];
			TempData[4]=0x80+dofly_DuanMa[buf[1]- '0'];//0x80是小數點的位址
			TempData[5]=dofly_DuanMa[buf[3]- '0'];
			TempData[6]=dofly_DuanMa[buf[4]- '0'];
			TempData[2]=0x00;
			TempData[7]=0x00;
			Display(0,8);
		}

    }
}

/*------------------------------------------------
                    發送一個字節
------------------------------------------------*/
void SendByte(unsigned char dat)
{
 SBUF = dat;
 while(!TI);
      TI = 0;
}
/*------------------------------------------------
                    發送一個字符串
------------------------------------------------*/
void SendStr(unsigned char *s)
{
 while(*s!='\0')// \0 表示字符串結束標誌，通過檢測是否字符串末尾
  {
  SendByte(*s);
  s++;
  }
}
/*------------------------------------------------
                     串口中斷程序
------------------------------------------------*/
void UART_SER (void) interrupt 4 //串行中斷服務程序
{
    unsigned char Temp;          //定義臨時變量 
   
   if(RI)                        //判斷是接收中斷產生
     {
		if(head<6)
		{
		  	RI=0;                      //標誌位清零
		  	Temp=SBUF;                 //讀入緩衝區的值
		  	buf[head] = Temp;
			head++;
		}
	 }
} 
void Delay(unsigned int t)
{
 while(--t);
}
void Display(unsigned char FirstBit,unsigned char Num)
{
      unsigned char i;	  
	  for(i=0;i<Num;i++)
	   { 
	   DataPort=0;   //清空數據，防止有交替重影
       LATCH1=1;     //段鎖存
       LATCH1=0;
       DataPort=dofly_WeiMa[i+FirstBit]; //取位碼 
       LATCH2=1;     //位鎖存
       LATCH2=0;
       DataPort=TempData[i]; //取顯示數據，段碼
       LATCH1=1;     //段鎖存
       LATCH1=0;       
	   Delay(200); // 掃瞄間隙延時，時間太長會閃爍，太短會造成重影
       }
}
void delay()
{
unsigned int i;
	for(i=0;i<6000;i++);
}
