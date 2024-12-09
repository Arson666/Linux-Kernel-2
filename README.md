To compile:

make

make run

You will see "All LikesServers exited" when the program finishes

Each server will run for about 5 mins so after the last server is created it will contiue for 5 mins (so it should be about 6-8 mins total for all the servers to finish cause it's kinda slow).

p.s if you want to run this code a second time you need to change the port, usually I just went down by two (EX: 1st iteration 9999 2nd iteration 9997).

The code consists of three processes: ParentProcess, LikesServer, and PrimaryLikesServer. The ParentProcess creates 10 child LikesServers, each emulating a YouTube server generating random likes within a five-minute period. LikesServers communicate with the PrimaryLikesServer using sockets to update the total like count. The PrimaryLikesServer maintains a log of likes received from each LikesServer and updates the total count.
