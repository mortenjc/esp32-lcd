# Echo server program

try:
    import usocket as socket
except:
    import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
print('start')
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
print('listen')
s.listen(1)
conn, addr = s.accept()
print('Connected by', addr)
while True:
    data = conn.recv(1024)
    print('after recv')
    if not data: break
    print('sending data', data)
    conn.sendall(data)
conn.close()
print('done')