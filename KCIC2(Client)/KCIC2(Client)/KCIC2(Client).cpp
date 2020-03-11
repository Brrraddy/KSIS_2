#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	//WSAStartup
	setlocale(LC_ALL, "Russian");
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";
	char msg[256];
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout <<"SERVER: "<< msg << std::endl;
	std::cin >> msg;
	send(Connection, msg, sizeof(msg), NULL);


	char* nm, namme[100];
	int n = recv(Connection, (char*)& namme, sizeof(namme), 0);
	nm = new char[n + 1];
	strncpy(nm, namme, n); nm[n] = '\0';
	//открываем файл с принятым именем и принимаем его
	std::ofstream f(nm, std::ios::binary);
	char buffer[1024];
	int i = 0;
	std::cout << "Прием";
	while (1) {
		n = recv(Connection, buffer, sizeof(buffer), 0);
		std::cout << "."; //1 килобайт-1 точка получается
		if (n <= 0) break;
		f.write(buffer, n);//пишем в файл, сколько прочитали
		break;
	};
	f.close();
	std::cout << "\nПринял файл " << nm << "!" << std::endl;
	std::cout << "\nТеперь UDP" << std::endl;
	std::cin >> msg;
	send(Connection, msg, sizeof(msg), NULL);
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout << "SERVER: " << msg << std::endl;

	char* nm1, namme1[100];
	int n1 = recv(Connection, (char*)& namme1, sizeof(namme1), 0);
	nm1 = new char[n1 + 1]; 
	strncpy(nm1, namme1, n1); nm1[n1] = '\0';
	std::ofstream f1(nm1, std::ios::binary);
	//открываем файл с принятым именем и принимаем его
	
	i = 0;
	std::cout << "Прием";
	while (1) {
		n1 = recv(Connection, buffer, sizeof(buffer), 0);
		std::cout << "."; //1 килобайт-1 точка получается
		if (n1 <= 0) break;
		f1.write(buffer, n1);//пишем в файл, сколько прочитали
		break;
	};
	f1.close();
	std::cout << "\nПринял файл " << nm1 << "!" << std::endl;
	
	return 0;
}
