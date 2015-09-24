Bi-Directional Communication with Named Pipes in Unix

An Initial Stride for Peer-to-Peer Protocols with Operating System Intervention

The objective of this programming assignment is to become familiar with, and to become successful in, the usage of Named Pipes for bi-direction communication on a single Unix System. The main idea is to investigate and successfully implement a peer-to-peer client-server modeled application, utilizing the Named Pipe mechanism on the Unix based System, ***.**.*******.***, the Computer Science Department Computer System. Your client should be the only called executable from the shell. The client MUST internally execute the server. Both, THE CLIENT AND SERVER MUST BE PROCESSES. Then the description below should be implemented. You MUST give clear reference/citation(s) of your solution (if you utilized such resources) in your submitted write-up. YOU MAY NOT COPY ANYONE’s SOLUTION/CODE. This will result in a zero for this assignment & invoke an academic dishonesty action on your behalf.

The overall objective is to search a text file for a given word/target {NOT a Sub-string} (or phrase [for an extra 25 points on top of the total score listed above]). The result will be a set of line numbers & frequency that the target appears on such, followed by the total number of times the target appeared within the file. An example of the required output would look like the following:

****************** Sample of Required Output ***********************

cli

Client: PID 8756 - Running on Tuesday December 15, 2015 at 2:45pm
Client: PID 8756 - Enter File Name:
testfile.txt

Server: PID 9146 - Running on Tuesday December 15, 2015 at 2:46pm
Client: PID 8756 - Enter Target:
Logic

Client: PID 8756 - Input File >>>testfile.txt<<<
Client: PID 8756 - Target >>>Logic<<<

Server: PID 9146 - Synchronized to Client.
Client: PID 8756 - Synchronized to Server.

Client: PID 8756 - Target >>Logic<< Appeared on Line 3,    1 Time
Client: PID 8756 - Target >>Logic<< Appeared on Line 7,    4 Times
Client: PID 8756 - Target >>Logic<< Appeared on Line 15,   1 Time
Client: PID 8756 - Target >>Logic<< Appeared on Line 31,   2 Times
Client: PID 8756 - Target >>Logic<< Appeared on Line 32,   3 Times
Client: PID 8756 - Target >>Logic<< in File >>testfile.txt<< Appeared a Total of 11 Times.

Server: PID 9146 - Terminated On Tuesday December 15, 2015 at 2:47pm
Client: PID 8756 - Terminated On Tuesday December 15, 2015 at 2:47pm

***************** End of Sample Required Output **********************

Your client should ‘attach’ to the server by sending an initial message (of your choice) to the server. The server should check & reply to the expected message with a message of your choice. Both sent messages are to be expected by the corresponding receiver. Both client and server must verify the establishes the fact that the two processes are connected & synchronized. The user should enter (via keyboard) a file name, followed by a word ( or text or words appropriately delineated) delimited by the return (‘\n’) to the client. Then, your client should send the information to the server (via the named pipe [only]) and the server will process the file and return to the client a set of results for each line processed from the target file. The client will then display to the screen the messages from the server in the format listed above. The client will terminate the session after receiving the text “Server-EOF” from the server. The client and server should then terminate their execution. Be sure to properly manage your named pipes (see below). All output it to directed to the screen.

Be sure to adhere to the following guidelines:
1. Your named pipes must be created explicitly by each process. They MUST be “Named”.
2. Your named pipes must be properly closed & returned to the operating system after usage (by each process).
3. Both Server and Client MUST be processes.
4. Recall that named pipes are simplex communication mechanisms. No random access files (or the like thereof) allowed.
5. Recall, documents (per syllabus & lecture) you must create & submit. Your writeup should include your program operations, difficulties, successes, etc.
6. You may utilize the languages C, C++, C# or Java. Your solution MUST compile on the Computer Science server.

You should perform the following steps to successfully complete this assignment: Create and compile two separate files, one the client program and the other the server program. Your client must start the execution of your server. O only the client should display the results of the server process. You should turn in files as specified in the Syllabus. Produce & submit a discussion of your work. 
