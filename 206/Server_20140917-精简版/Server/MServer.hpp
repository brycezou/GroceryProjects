//������Ҫ��ͷ�ļ�
#pragma once
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <string>
#include <map>
using namespace std;
#include <windows.h>


//�ͻ��˽ṹ��
struct client
{
	int fd; //�ͻ����׽���
	char *data; //�ͻ�������
	int data_len; //�ͻ������ݳ���
};

//�����ⲿ����
extern map<int, client> clients;	//�洢�ͻ��˵�ӳ���
extern deque< pair<int,string> > cmds; //ָ�����
extern map<string, string> statue; //������״̬��Ϣ��
extern HANDLE cmd_mutex; //ָ��������
extern int cmd_id; //ָ��ID
extern string current_cmd; //��ǰָ��
extern int current_id; //��ǰָ���ID

extern int server_port; //�������˿ں�

int WINAPI MServer(); //��������ʼ������
char *read_cmd(); //��ȡָ���
void append_cmd(const char *cmd); //׷��ָ���
void write_statue(const char *key, const char *val); //д�������״̬��Ϣ
void clear_statue(); //���������״̬��Ϣ