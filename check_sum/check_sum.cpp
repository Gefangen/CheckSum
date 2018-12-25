#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char* argv[])
{
	char fbuf[128];
	int fbuflen = 0;
	int checksum = 0;
	fstream infile("infile", ios::out);
	infile << "Hello world.";
	infile.close();
	if (argc == 2)
	{
		infile.open(argv[1], ios::in);
		if (!infile)
		{
			cout << "读取文件失败！" << endl;
			return 0;
		}
		infile.get(fbuf, 256);        //将文件流的数据保存到数组中     
		for (int i = 0; fbuf[i] != '\0'; i++)
		{
			fbuflen++;
		}
		cout << "读取的文件内容：" << fbuf << endl;
		if (fbuflen % 2 != 0)        //数据为奇数个时，在最末尾补一个字节的0      
			fbuf[fbuflen++] = '0';
		else
		{
			short *bit_16= new short[fbuflen / 2];
			cout << "文件内容对应的整数序列：";
			for (int i = 0; i<(fbuflen / 2); i++)
			{
				bit_16[i] = (fbuf[i * 2] << 8) | fbuf[i * 2 + 1];
				cout << hex << bit_16[i] << ' ';
				checksum += bit_16[i];        //计算检验和
				if (checksum >> 16)
					checksum = (checksum & 0xffff) + (checksum >> 16);
			}
		}
		cout << endl << hex << "校验和:" << checksum << endl;
	}
	else
	{
		cout << "请以命令行形式运行：check_sum  infile" << endl;
	}
	system("pause");
	return 0;
}