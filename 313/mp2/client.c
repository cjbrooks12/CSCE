int main() {
	int pid = fork();
	
	if(pid == -1) {
		printf("error in forking child process");
	}
	if(pid == 0) {
		//got into child process
		//copy from simple client
	}
	else {
		execv("./dataserver", NULL);
	}
}