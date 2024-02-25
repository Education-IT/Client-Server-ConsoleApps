![Project Banner](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/banner.png)
## Course Project - *Computer Networks* - **UAM**

> **Completed in the third semester of computer science studies.**

<img align="right" src="https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Bash.png" width="200"/>

The task was to use the **C** and **Python** programming languages to develop two *console-based programs* that communicate with each other using an **object-oriented interface** and **BSD sockets**. The client application sends a selected file (of any size) to be saved on the server. I worked on this project together with [**Szymon Ptaszyński**](https://github.com/PTAKUU). I personally created the client application in C, while my colleague developed the server application in Python. The transmission between the applications occurs using the **TCP** protocol. These programs are intended to run only on **Unix** systems and operate within a *local computer network*. During the development, we used the **Ubuntu** operating system.

![C](https://img.shields.io/badge/C-A8B9CC.svg?style=for-the-badge&logo=C&logoColor=black) ![Python](https://img.shields.io/badge/Python-3776AB.svg?style=for-the-badge&logo=Python&logoColor=white) ![Bash](https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=for-the-badge&logo=GNU-Bash&logoColor=white)  ![Linux](https://img.shields.io/badge/Linux-FCC624.svg?style=for-the-badge&logo=Linux&logoColor=black) <!--[![Website](https://img.shields.io/badge/website-000000?style=for-the-badge&logo=About.me&logoColor=white)](https://education-it.pl/)-->
 ## 
**`klient.c` Program:**
 1) Displays the **login** of the currently logged-in user and a **prompt sign** in the format `[{path}] $`, where `{path}` is the path to the current working directory.
 2) Supports the `cd` command, which works similarly to the `cd` command known from the Bash shell.
 3) Handles the custom command **`transfer <filename>`** to send a file to the server at the specified **IP address** and **port**. The command also supports the **`-two`** flag to send two different files to two different servers simultaneously.
 5) Supports the `exit` command to terminate the client program.
 6) Supports the `help` command to display information about the authors of the programs and their functionalities.
 7) Displays an error message when a command cannot be interpreted correctly.
  
  **`server.py` Program:**
  1. Continuously listens on port `60000`.
  2. Handles only one client at a time.
  3. After receiving a file from the client application, the server checks if a file with the specified name already exists in the current working directory. If it does, the server renames the new file by appending a number to avoid overwriting other important documents.
  4. After completing the connection, the server resumes listening on the specified port.
  
  ## Example Usage:
 > View after using the `help` command (client application)
  
![Client Help](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/klient-help.PNG)
<br>

> Sending a file to the listening server.
  
![File Transfer](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/klient-transfer.PNG)
<br>

> Server view - connection establishment and file reception.
  
![Server](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/server.PNG)

## What I Learned:
- Reinforced my knowledge of utilizing child processes, including functions such as `fork()`, `wait()`, `waitpid()`, and `exec()` (sending two different files to two servers simultaneously).
- This project was an excellent opportunity to summarize the process of establishing connections between applications using the **TCP** protocol.
- It was my first encounter with one of the main practices in software engineering, which involves utilizing existing code instead of starting from scratch. I reused the framework from my custom program [microshell.c](https://github.com/Education-IT/MicroShell) to receive a string from the user and convert it into an array, as well as the entire `cd` command to navigate through the directory tree in the system.
