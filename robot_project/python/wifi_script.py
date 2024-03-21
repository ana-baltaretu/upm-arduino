import socket

host = '192.168.204.78'  # '192.168.1.100' # Replace with Arduino's IP address
port = 80

data_to_send = 'B'
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((host, port))
    print("Connected!")
    s.sendall(data_to_send.encode())
    print("Data sent!")
    # data = s.recv(1024)
    # print('Received:', data.decode())