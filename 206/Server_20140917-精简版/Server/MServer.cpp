//���ر�Ҫ��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include <sstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "MServer.hpp"


map<int, client> clients; //�洢�ͻ��˵�ӳ���
deque< pair<int, string> > cmds;  //ָ�����
map<string, string> statue; //������״̬��Ϣ��
HANDLE cmd_mutex; //ָ��������
int cmd_id = 0; //ָ��ID
string current_cmd; //��ǰָ��
int current_id = -1; //��ǰָ���ID
int server_port = 1400; //�������˿ں�

//�����ַ���
void handler(client &c){
	string val = "nil\n";
	if (WaitForSingleObject(cmd_mutex, 100) != 0){ //����ȴ��ͷŻ�����ʧ��
		val = "busy waiting for lock\n";
		goto die; //��ת���������
	}
	if (c.data[0] == '?'){	//�����ѯ״̬
		if (strcmp(c.data, "?") == 0){ //����ǲ�ѯ����״̬
			ostringstream oss;
			oss << "{";
			//������״̬������װ��Json��ʽ
			for (map<string,string>::iterator mi = statue.begin(); mi != statue.end(); mi++){
				oss << "\"" << mi->first << "\"" << ":" << "\"" << mi->second + "\"" << ",";
			}
			oss << "}\n";
			val = oss.str(); //�������תΪ�ַ���
		}else{
			string key = c.data+1; //�õ�Ҫ��ѯ��״̬��������
			if(statue.count(key) > 0) //���������״̬���д��ڸ�״̬����
				val = statue[key]+"\n"; //�õ���״̬��ֵ
			cerr<<key<<":"<<val<<endl;
		}
		goto end;
	}
	if (c.data[0] == '#'){	//�����ѯ��ǰָ��
		if (strcmp(c.data, "#") == 0){ //�����ѯ��ǰָ���ID
			ostringstream oss;
			oss<<current_id<<endl; //�����ǰָ���ID
			val = oss.str(); //ת�����ַ���
		}else{ //�������ָ��ID����ָ������
			int cid = atoi(c.data+1); //�õ�ָ���ID
			if (cid == current_id){ //�����ѯ���ǵ�ǰָ��
				val = current_cmd + "\n"; //�õ���ǰָ������
				goto end; //��ת���������
			}
			//�����ѯ�Ĳ��ǵ�ǰָ��
			for (deque<pair<int, string>>::iterator i = cmds.begin(); i != cmds.end(); i++){
				if(cid == i->first){
					val = i->second + "\n"; //����ָ����еõ�ָ������
					break;
				}
			}
		}
		goto end;
	}
	if (c.data[0] == '-'){ //���ɾ��ָ��
		int cid = atoi(c.data+1); //�õ�ָ���ID
		for (deque<pair<int, string>>::iterator i = cmds.begin(); i != cmds.end(); i++){
			if(cid == i->first){ //����ָ������ҵ�Ҫɾ����ָ��
				cmds.erase(i);  //��ָ�������ɾ��ָ��
				break;
			}
		}
		goto end; //��ת���������
	}
	if (c.data[0] == '@'){ //����ǲ�ѯָ�����ָ��
		ostringstream oss;
		oss << "{";
		//������ָ����װ��Json��ʽ
		for (deque<pair<int, string>>::iterator qi = cmds.begin(); qi != cmds.end(); qi++){
			oss << "\"" << qi->first << "\"" << ":" << "\"" << qi->second << "\"" << ",";
		}
		oss << "}\n";
		val = oss.str(); //ת�����ַ���
		goto end; //��ת���������
	}
	if (c.data_len > 2){ //�����ִ��ָ��
		cmds.push_back(make_pair(cmd_id, string(c.data))); //����ָ�����
		ostringstream oss;
		oss << cmd_id << "\n"; //���ָ���ID
		val = oss.str(); //ת�����ַ���
		cmd_id++; //ָ��ID����
	}
	
end:
	ReleaseMutex(cmd_mutex); //�ͷŻ�����
die:
	send(c.fd, val.c_str(), val.length(), 0); //��ͻ��˷�������
	c.data_len = 0; //�ͻ������ݳ�������
	memset(c.data, 0, 1024*1024); //�ͻ������ݴ洢�����
}

//��������ʼ������
int WINAPI MServer(void)
{
	int port = 1400; //�˿ں�
	int server_fd, client_fd; //�������Ϳͻ����׽���
	struct sockaddr_in server_addr, client_addr; //��ַ�ṹ��
	int server_addr_len, client_addr_len; //��ַ�ṹ��Ĵ�С
	memset(&server_addr, 0, sizeof(struct sockaddr_in)); //��ַ�ṹ�帴λ

	//��ʼ���������˵�ַ�ṹ��
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	server_fd = socket(AF_INET, SOCK_STREAM, 0); //��ʼ���������׽���
	if (server_fd == -1) //����������׽��ֳ�ʼ��ʧ��
		exit(-1); //�˳�����
	//�󶨷�������ַ�ṹ�嵽�������׽���
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		exit(-1); //�˳�����

	listen(server_fd, 5);  //�����׽���

	fd_set rfds, wfds, efds; //�������д�ʹ����¼�������
	struct timeval tv; //��ʱʱ��ṹ��
	int retval; //��·���÷���ֵ
	while (1){ //����ѭ��, һֱ����
		FD_ZERO(&rfds); //���ö��¼�������
		FD_ZERO(&wfds); //����д�¼�������
		FD_ZERO(&efds); //���ô����¼�������

		int max_fd = server_fd;
		FD_SET(server_fd, &rfds); //�������������׽�������Ϊ���¼�������
		//�����пͻ����׽�������Ϊ���¼��ʹ����¼�������
		for (map<int, client>::iterator i = clients.begin(); i != clients.end(); i++){
			FD_SET(i->second.fd, &rfds); //���ͻ����׽�������Ϊ���¼�������
			FD_SET(i->second.fd, &efds); //���ͻ����׽�������Ϊ�����¼�������
			max_fd = i->second.fd > max_fd ? i->second.fd : max_fd;
		}
		tv.tv_sec = 5; //���ó�ʱʱ��

		retval = select(max_fd + 1, &rfds, &wfds, &efds, &tv); //��·���õȴ��¼�����
		if (retval == SOCKET_ERROR){//�����·���÷�������
			int err = WSAGetLastError(); //�õ�������Ϣ
			printf("select error %d\n", err); //���������Ϣ
		}else if (retval){//�����·����δ��������
			//printf("Data is ready\n");
			if (FD_ISSET(server_fd, &rfds)){ //����пͻ�����������
				client_addr_len = sizeof(client_addr); //�õ��ͻ��˵�ַ�ṹ��Ĵ�С
				//���տͻ�������
				client_fd = accept(server_fd, \
					(struct sockaddr *)&client_addr, \
					&client_addr_len);
				if(client_fd == -1){ //�������ʧ��
					int err = WSAGetLastError(); //�õ�������Ϣ
					printf("accept error %d\n", err); //���������Ϣ
					continue; //������һ��ѭ��
				}
				//����ͻ������ӳɹ�
				struct client c; //�ͻ��������׽��ֽṹ�����
				c.fd = client_fd; //Ϊ�׽��ָ�ֵ
				c.data = (char *)malloc(1024*1024); //Ϊ�������ݿ�����ڴ�
				c.data_len = 0; //�������ݳ���Ϊ0
				memset(c.data, 0, 1024*1024); //�������ݿ�����
				clients[client_fd] = c; //���ÿͻ��˴���ͻ���ӳ���
				printf("new connection %d\n", c.fd); //�����Ϣ
			}

			for (map<int, client>::iterator i = clients.begin(); i != clients.end();++i){
				if (FD_ISSET(i->first, &rfds)){ //����ͻ����׽����ж��¼�
					int recv_len = recv(i->first, i->second.data+i->second.data_len, \
						1, 0); //�ӿͻ��˽�������
					// client socket close
					if (recv_len == 0){ //����ͻ����׽��ֹر�
						closesocket(i->first); //�ر��׽���
						free(i->second.data); //�ͷ����ݿ�
						clients.erase(i); //���ÿͻ���ӳ�����ɾ��
						break;
					}

					// data recv
					if (recv_len > 0){ //������յ�������
						if (i->second.data[i->second.data_len] == '\n'){ //������ݽ������
							i->second.data[i->second.data_len] == '\0'; //�����ַ����Ľ�����
							char *p = strchr(i->second.data, '\n'); //�õ��ַ�����'\n'�״γ��ֵ�λ��
							if (p) *p = '\0'; //�ַ�����β
							handler(i->second); //�����ַ���
						}else{ //������ݻ�δ�������
							i->second.data_len += recv_len; //�����ѽ������ݳ���
						}
					} // end data recv
				}
			}// end for i = clients.begin
		}else{
			;//printf("No data\n");
		}
	}
}

//��ָ����ж�ȡָ��
char *read_cmd()
{
	char *retval = NULL;
	//�ȴ�����������
	WaitForSingleObject(cmd_mutex, INFINITE);

	//remove old cmd
	if (!cmds.empty()){ //���ָ����зǿ�
		pair<int, string> cmd = cmds.front(); //�õ�ָ����еĵ�һ��ָ��
		if (current_id == cmd.first)
			cmds.pop_front(); //ɾ����һ��ָ��
	}

	//read new cmd
	if (!cmds.empty()){ //���ָ����зǿ�
		pair<int, string> cmd = cmds.front(); //�õ�ָ����еĵ�һ��ָ��
		retval = strdup(cmd.second.c_str()); //��ָ���
		current_id = cmd.first; //��ǰָ���ID
		current_cmd = cmd.second; //��ǰָ�������
	}else{ //���ָ�����Ϊ��
		current_id = -1;
	} 
	ReleaseMutex(cmd_mutex);  //�ͷŻ�����
	return retval; //���ص�ǰָ��
}

//��ָ�����׷��ָ��
void append_cmd(const char *cmd)
{
	//�ȴ�����������
	WaitForSingleObject(cmd_mutex, INFINITE);
	//��ָ��������ָ��
	cmds.push_back(make_pair(cmd_id++, string(cmd)));
	 //�ͷŻ�����
	ReleaseMutex(cmd_mutex);
}

//дϵͳ״̬��Ϣ
void write_statue(const char *key, const char *val)
{
	//�ȴ�����������
	WaitForSingleObject(cmd_mutex, INFINITE);
	//����ϵͳ״̬��Ϣ
	statue[key] = val;
	//�ͷŻ�����
	ReleaseMutex(cmd_mutex);
}

//���ϵͳ״̬��Ϣ
void clear_statue()
{
	//�ȴ�����������
	WaitForSingleObject(cmd_mutex, INFINITE);
	//���ϵͳ״̬
	statue.clear();
	//�ͷŻ�����
	ReleaseMutex(cmd_mutex);
}