CXX = gcc

all: ParentProcess LikesServer PrimaryLikesServer

ParentProcess: ParentProcess.c 
	$(CXX) ParentProcess.c -o ParentProcess

LikesServer: LikesServer.c
	$(CXX) LikesServer.c -o LikesServer

PrimaryLikesServer: PrimaryLikesServer.c
	$(CXX) PrimaryLikesServer.c -o PrimaryLikesServer

run:
	./ParentProcess

clean:
	rm /tmp/LikesServer* /tmp/ParentProcessStatus /tmp/PrimaryLikesLog ParentProcess LikesServer PrimaryLikesServer
