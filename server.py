import socket
import os
import os.path
from _thread import *

s = socket.socket()
hostname = socket.gethostname()
host = socket.gethostbyname(hostname)
port = 60000
BUFFER = 1024

try:
    s.bind((host, port))
except socket.error as e:
    print(str(e))

s.listen(5)
print(f'Server listening at {host}:60000')

def threaded_client(conn):
    with open('file' + str(i) + '.txt', 'wt') as f:
        print ('file opened')
        while True:
            print(f'receiving data from {addr}')
            
            data = conn.recv(BUFFER).decode('UTF-8', 'ignore')
            f.write(data)
            if not data:
                break
        f.close()
        print('Successfully get the file')
    conn.close()
    print('connection closed')
    return 1

while True:
    conn, addr = s.accept()
    print(f'Got connection from  {addr}')

    i = 1
    while True:
        file_exists = os.path.exists('file' + str(i) + '.txt')
        if file_exists:
            i = i+1
        else:
            f = open('file' + str(i) + '.txt', 'wt')
            f.close()
            break
    start_new_thread(threaded_client, (conn, ))
