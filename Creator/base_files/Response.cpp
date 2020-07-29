#include "Response.h"

int Response::notify(int value){
	if (value == 0) cout << "Notificación de amenaza: No se presenta amenaza";
	else if (value == 1) cout << "Notificación de amenaza: baja probabilidad de amenaza";
	else if (value == 2) cout << "Notificación de amenaza: media probabilidad  de amenaza";
	else cout << "Notificación de amenaza: alta probabilidad de amenaza. Es necesario tomar acciones";	

	return 0;
}

int Response::blockAntigen(int option, Antigen antigen){

	if (option == 0){

		vector <string> data = antigen.getValueString();

		if (data.size() > 1){
			blockIp(true, data[0]);
			blockIp(false, data[1]);	
		}

		else cout << "No se presenta los valores necesarios" << endl;
	}

	else if (option == 1){
		vector <int> data = antigen.getValueInt();
		vector <bool> data2 = antigen.getValueBool();

		if (data.size() > 0 && data2.size() > 0){
			string str1 = to_string(data[0]);
			blockPort(data2[0], str1);
		}
		else cout << "No se presenta los valores necesarios" << endl;	
	}

	else{
		blockAntigen(0, antigen);
		blockAntigen(1, antigen);
	}	
}

int Response::blockPort(bool option, string arg){
	if (option){
		string str1 = "iptables -A INPUT -p tcp --dport " + arg + " -j DROP";
		string str2 = "iptables -A OUTPUT -p tcp --dport " + arg + " -j DROP";
		string str3 = "iptables -A FORWARD -p tcp --dport " + arg + " -j DROP";

		const char *command1 = str1.c_str();
		const char *command2 = str2.c_str();
		const char *command3 = str3.c_str();

		system(command1);
		system(command2);
		system(command3);
	}
	else{
		string str1 = "iptables -A INPUT -p udp --dport " + arg + " -j DROP";
		string str2 = "iptables -A OUTPUT -p udp --dport " + arg + " -j DROP";
		string str3 = "iptables -A FORWARD -p udp --dport " + arg + " -j DROP";	

		const char *command1 = str1.c_str();
		const char *command2 = str2.c_str();
		const char *command3 = str3.c_str();

		system(command1);
		system(command2);
		system(command3);
	}
}

int Response::blockIp(bool option, string arg){
	if (option){
		string str1 = "iptables -A INPUT -s " + arg + " -j DROP";
		string str2 = "iptables -A OUTPUT -s " + arg + " -j DROP";
		string str3 = "iptables -A FORWARD -s " + arg + " -j DROP";	

		const char *command1 = str1.c_str();
		const char *command2 = str2.c_str();
		const char *command3 = str3.c_str();

		system(command1);
		system(command2);
		system(command3);
	}
	else{
		string str1 = "iptables -A INPUT -d " + arg + " -j DROP";
		string str2 = "iptables -A OUTPUT -d " + arg + " -j DROP";
		string str3 = "iptables -A FORWARD -d " + arg + " -j DROP";	

		const char *command1 = str1.c_str();
		const char *command2 = str2.c_str();
		const char *command3 = str3.c_str();

		system(command1);
		system(command2);
		system(command3);
	}
}

int Response::dropAll(){
	string str1 = "iptables -P INPUT DROP";
	string str2 = "iptables -P OUTPUT DROP";
	string str3 = "iptables -P FORWARD DROP";	

	const char *command1 = str1.c_str();
	const char *command2 = str2.c_str();
	const char *command3 = str3.c_str();

	system(command1);
	system(command2);
	system(command3);
}

Response::Response(){

}

Response::~Response(){

}